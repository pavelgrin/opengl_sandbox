#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SDL.h>
#include <string>
#include <iostream>

class Window {
public:
    virtual ~Window() {}
    virtual void create(const int, const int, const char*) const = 0;
};

class WindowSDL2 final : public Window {
public:
    void create(const int, const int, const char*) const override;
};

class WindowGLFW final : public Window {
public:
    void create(const int, const int, const char*) const override;
private:
    void processInput(GLFWwindow *window) const;
};
