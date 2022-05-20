#pragma once

#include "../window/states.hpp"
#include <string>

using GLADloadproc = void* (*)(const char*);

class Render
{
private:
    static float m_aspect_ratio;

public:
    static int init(const GLADloadproc get_proc_address,
                    const std::string res_dir,
                    const int viewport_width, const int viewport_height);

    static void fini();

    static void update(EventStates* states,
                       EventActions* actions,
                       const float dt);

private:
    static void updateViewport(const int width, const int height);
    static void processEvents(EventStates* states,
                              EventActions* actions,
                              const float dt);
};
