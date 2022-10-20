#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include <cstring>

#include <uv/uv.h>
namespace
{
    // 小端
    unsigned long long parse_id(char *buf)
    {
        unsigned long long res{0};
        for (int index{7}; index >= 0; --index)
        {
            res *= 256;
            res += buf[index];
        }
        return res;
    }
    // 小端
    void put_id(char *buf, unsigned long long id)
    {
        for (int index{0}; index < 8; ++index)
        {
            buf[index] = static_cast<char>(id % 256);
            id /= 256;
        }
    }
}
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
    int start_server()
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

    ssize_t g_read{0};
    char g_buf[65535];
    char g_msg[1000];
    int mode{0};
    unsigned long long g_id;
    unsigned long long g_len;

    void on_read(uv_stream_t *tcp, ssize_t nread, const uv_buf_t *buf)
    {
        printf("on_read. %p\n", tcp);
        if (nread >= 0)
        {
            // printf("read: %s\n", tcp->data);
            printf("readptr: %p bufLen:%zu nread:%zd\n", buf->base, buf->len, nread);
            if (nread > 0)
            {
                std::memcpy(g_buf + g_read, buf->base, nread);
                g_read += nread;
                while (true)
                {
                    if (mode == 0) // read id and len
                    {
                        if (g_read < 16)
                        {
                            break;
                        }
                        else
                        {
                            g_id = parse_id(g_buf);
                            g_len = parse_id(g_buf + 8);
                            std::memcpy(g_buf, g_buf + 16, g_read - 16);
                            g_read -= 16;
                            mode = 1;
                            printf("g_id:%llu, g_len:%llu mode:%d g_read:%zu\n", g_id, g_len, mode, g_read);
                        }
                    }
                    else if (mode == 1) // read msg by g_len
                    {
                        if (g_read < g_len)
                        {
                            break;
                        }
                        else
                        {
                            std::memcpy(g_msg, g_buf, g_len);
                            g_msg[g_len] = 0;
                            //
                            std::memcpy(g_buf, g_buf + g_len, g_read - g_len);
                            g_read -= g_len;
                            mode = 0;
                            printf("g_id:%llu, g_len:%llu mode:%d g_read:%zu msg:%s\n", g_id, g_len, mode, g_read, g_msg);
                            if (g_id == 0)
                            {
                                printf("[Login] msg:%s\n", g_msg);
                            }
                            else if (g_id == 1)
                            {
                                printf("[Chat] msg:%s\n", g_msg);
                            }
                        }
                    }
                }
            }
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
            {.base = data, .len = static_cast<size_t>(len2)}};
        uv_write_t *req = static_cast<uv_write_t *>(malloc(sizeof(uv_write_t)));
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
        // send login
        char *idbuf = new char[8 + 8 + 1];
        printf("on_connect_buf_ptr:%p\n", idbuf);
        std::fill(idbuf, idbuf + 8 + 8 + 1, 0);
        idbuf[8] = 1;
        idbuf[16] = 'A';
        write2(stream, idbuf, 8 + 8 + 1);
        uv_read_start(stream, alloc_cb, on_read);
    }

    void startConn(const char *host, int port)
    {
        uv_tcp_t *pSock = static_cast<uv_tcp_t *>(malloc(sizeof(uv_tcp_t)));
        uv_tcp_init(loop, pSock);
        uv_tcp_keepalive(pSock, 1, 60);

        struct sockaddr_in dest;
        uv_ip4_addr(host, port, &dest);

        uv_connect_t *pConn = static_cast<uv_connect_t *>(malloc(sizeof(uv_connect_t)));
        printf("allocated %p\n", pConn);
        uv_tcp_connect(pConn, pSock, (const struct sockaddr *)&dest, on_connect);
    }
    int start_client()
    {
        loop = uv_default_loop();
        startConn("127.0.0.1", 8888);
        return uv_run(loop, UV_RUN_DEFAULT);
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
        return uv::client::start_client();
    }
}
