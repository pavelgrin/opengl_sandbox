#include "./window.hpp"

void WindowGLFW::create(const int scr_width, const int scr_height, const char *scr_header) const
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(scr_width, scr_height, scr_header, NULL, NULL);

    if (window == NULL) {
        glfwTerminate();
        throw "Failed to create GLFW window\n";
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(
        window,
        [](GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        }
    );

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw "Failed to initialize GLAD\n";
    }

    while (!glfwWindowShouldClose(window)) {
        this->processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void WindowGLFW::processInput(GLFWwindow *window) const {}
