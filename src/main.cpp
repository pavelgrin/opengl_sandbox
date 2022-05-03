#include "./render/render.hpp"
#include "./window/window.hpp"
#include <string>

int main(int argc, char* argv[])
{

    std::string app_path      = argv[0];
    std::string app_dir       = app_path.substr(0, app_path.find("/app"));
    std::string resources_dir = app_dir + "/../../resources/";

    Render render(resources_dir);
    Window window;

    window.create(800, 600, "OpenGL Sandbox", &render);

    return 0;
}
