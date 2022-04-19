#pragma once

#include "../render/render.hpp"
#include <SDL.h>
#include <iostream>
#include <string>

using loadproc = void* (*)(const char*);

class Window final
{
  public:
    void create(const int, const int, const char*, Render*) const;
};
