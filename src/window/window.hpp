#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include "../render/render.hpp"

typedef void *(*loadproc)(const char*);

class Window {
public:
    virtual ~Window() {}
    virtual void create(const int, const int, const char*, Render*) const = 0;
};

class WindowSDL2 final : public Window {
public:
    void create(const int, const int, const char*, Render*) const override;
};
