#include "./window.hpp"

void WindowGLFW::create(
    const int scr_width,
    const int scr_height,
    const char *scr_header,
    Render *render
) const {
    if (!glfwInit()) {
        std::cerr << "GLFW couldn't be initialized!\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(scr_width, scr_height, scr_header, NULL, NULL);

    if (window == NULL) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    render->loadGLLoader((loadproc)glfwGetProcAddress);
    render->updateViewport(scr_width, scr_height);

    // This is the trick to call updateViewport from callback
    static Render *renderStatic = render;
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        renderStatic->updateViewport(width, height);
    });

    while (!glfwWindowShouldClose(window)) {
        render->frame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
