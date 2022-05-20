#include "./render/render.hpp"
#include "./window/events.hpp"
#include "./window/window.hpp"
#include <string>

const int WIDTH   = 1280;
const int HEIGHT  = 720;
const char* TITLE = "OpenGL Sandbox";

int main(int argc, char* argv[])
{
    int init_result = 0;

    std::string app_path      = argv[0];
    std::string app_dir       = app_path.substr(0, app_path.find("/app"));
    std::string resources_dir = app_dir + "/../../resources/";

    init_result = Window::create(WIDTH, HEIGHT, TITLE);

    if (init_result)
        return init_result;

    loadproc get_proc_address = Window::getProcAddressFunction();
    init_result               = Render::init(get_proc_address, resources_dir, WIDTH, HEIGHT);

    if (init_result)
    {
        Window::terminate();
        return init_result;
    }

    Events::init(Window::getWindow(), WIDTH, HEIGHT);

    float lifetime     = Window::getElapsedTime();
    float current_time = 0.0f;
    float frame_time   = 0.0f;

    while (Events::states.keep_window_open)
    {
        current_time = Window::getElapsedTime();
        frame_time   = current_time - lifetime;
        lifetime     = current_time;

        Events::poll();
        Render::update(&Events::states, &Events::actions, frame_time);
        Window::swapBuffers();
    }

    Events::fini();
    Render::fini();
    Window::terminate();

    return 0;
}
