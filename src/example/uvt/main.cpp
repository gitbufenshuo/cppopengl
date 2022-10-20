#include <iostream>
#include <string>
#include <fstream>

#include <uv/uv.h>

namespace uv::server
{
    uv_loop_t *loop;

    void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
    {
        printf("alloc_buffer, buf->%p\n", buf);
        uv_buf_t temp = uv_buf_init((char *)malloc(suggested_size), suggested_size);
        buf->base = temp.base;
        buf->len = temp.len;
        return;
    }

    void echo_write(uv_write_t *req, int status)
    {
        if (status == -1)
        {
            fprintf(stderr, "Write error!\n");
        }
        char *base = (char *)req->data;
        free(base);
        free(req);
    }

    void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
    {
        if (nread == -1)
        {
            fprintf(stderr, "Read error!\n");
            uv_close((uv_handle_t *)client, NULL);
            return;
        }
        printf("buf->len:%zu, nread->%ld\n", buf->len, nread);
        uv_write_t *write_req = (uv_write_t *)malloc(sizeof(uv_write_t));
        write_req->data = (void *)buf->base;
        uv_write(write_req, client, buf, 1, echo_write);
    }

    void on_new_connection(uv_stream_t *server, int status)
    {
        if (status == -1)
        {
            return;
        }

        uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
        uv_tcp_init(loop, client);
        if (uv_accept(server, (uv_stream_t *)client) == 0)
        {
            uv_read_start((uv_stream_t *)client, alloc_buffer, echo_read);
        }
        else
        {
            uv_close((uv_handle_t *)client, NULL);
        }
    }

}

namespace uv::client
{
    void on_close(uv_handle_t *handle);
    void on_connect(uv_connect_t *req, int status);
    void on_write(uv_write_t *req, int status);

    uv_loop_t *loop;

    void alloc_cb(uv_handle_t *handle, size_t size, uv_buf_t *buf)
    {
        *buf = uv_buf_init(static_cast<char *>(malloc(size)), size);
    }

    void on_close(uv_handle_t *handle)
    {
        printf("closed.");
    }

    void on_write(uv_write_t *req, int status)
    {
        if (status)
        {
            perror("uv_write error ");
            return;
        }
        printf("wrote.\n");
        free(req);
        // uv_close((uv_handle_t*)req->handle, on_close);
    }

    void on_read(uv_stream_t *tcp, ssize_t nread, const uv_buf_t *buf)
    {
        printf("on_read. %p\n", tcp);
        if (nread >= 0)
        {
            // printf("read: %s\n", tcp->data);
            printf("read: %s\n", buf->base);
        }
        else
        {
            // we got an EOF
            uv_close((uv_handle_t *)tcp, on_close);
        }

        // cargo-culted
        free(buf->base);
    }

    void write2(uv_stream_t *stream, char *data, int len2)
    {
        uv_buf_t buffer[] = {
            {.base = data, .len = len2}};
        uv_write_t *req = malloc(sizeof(uv_write_t));
        uv_write(req, stream, buffer, 1, on_write);
    }

    void on_connect(uv_connect_t *connection, int status)
    {
        if (status < 0)
        {
            printf("failed to connect\n");
            return;
        }
        printf("connected. %p %d\n", connection, status);

        uv_stream_t *stream = connection->handle;
        free(connection);
        write2(stream, "echo  world!", 12);
        uv_read_start(stream, alloc_cb, on_read);
    }

    void startConn(char *host, int port)
    {
        uv_tcp_t *pSock = malloc(sizeof(uv_tcp_t));
        uv_tcp_init(loop, pSock);
        uv_tcp_keepalive(pSock, 1, 60);

        struct sockaddr_in dest;
        uv_ip4_addr(host, port, &dest);

        uv_connect_t *pConn = malloc(sizeof(uv_connect_t));
        printf("allocated %p\n", pConn);
        uv_tcp_connect(pConn, pSock, (const struct sockaddr *)&dest, on_connect);
    }
}

/**
 * @brief 测试 libuv 相关功能
 *
 */
namespace game::example_list::uvt
{

    int Main()
    {
        uv::server::loop = uv_default_loop();

        uv_tcp_t server;
        uv_tcp_init(uv::server::loop, &server);

        int err{};

        struct sockaddr_in bind_addr;
        err = uv_ip4_addr("0.0.0.0", 7000, &bind_addr);

        printf("uv_ip4_addr:%d\n", err);

        err = uv_tcp_bind(&server, reinterpret_cast<sockaddr *>(&bind_addr), 0);
        printf("uv_tcp_bind:%d\n", err);

        int r = uv_listen((uv_stream_t *)&server, 128, uv::server::on_new_connection);
        if (r)
        {
            fprintf(stderr, "Listen error!\n");
            return 1;
        }
        else
        {
            printf("ListenGood!!\n");
        }
        return uv_run(uv::server::loop, UV_RUN_DEFAULT);
    }
}
