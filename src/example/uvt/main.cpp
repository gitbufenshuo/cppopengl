#include <iostream>
#include <string>
#include <fstream>

#include <uv/uv.h>

namespace
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

/**
 * @brief 测试 libuv 相关功能
 *
 */
namespace game::example_list::uvt
{

    int Main()
    {
        loop = uv_default_loop();

        uv_tcp_t server;
        uv_tcp_init(loop, &server);

        int err{};

        struct sockaddr_in bind_addr;
        err = uv_ip4_addr("0.0.0.0", 7000, &bind_addr);

        printf("uv_ip4_addr:%d\n", err);

        err = uv_tcp_bind(&server, reinterpret_cast<sockaddr *>(&bind_addr), 0);
        printf("uv_tcp_bind:%d\n", err);

        int r = uv_listen((uv_stream_t *)&server, 128, on_new_connection);
        if (r)
        {
            fprintf(stderr, "Listen error!\n");
            return 1;
        }
        else
        {
            printf("ListenGood!!\n");
        }
        return uv_run(loop, UV_RUN_DEFAULT);
    }
}
