#include <iostream>
#include <string>
#include <fstream>

#include <uv/uv.h>

namespace
{

}

/**
 * @brief 测试 libuv 相关功能
 *
 */
namespace game::example_list::uvt
{
    int64_t counter = 0;

    void wait_for_a_while(uv_idle_t *handle)
    {
        counter++;
        if (counter % 100000 == 0)
        {
            std::cout << "loop idler " << counter << std::endl;
        }
        if (counter >= 10e6)
            uv_idle_stop(handle);
    }

    int Main()
    {
        uv_idle_t idler;

        uv_idle_init(uv_default_loop(), &idler);
        uv_idle_start(&idler, wait_for_a_while);

        printf("Idling...\n");
        uv_run(uv_default_loop(), UV_RUN_DEFAULT);

        uv_loop_close(uv_default_loop());
        return 0;
    }
}
