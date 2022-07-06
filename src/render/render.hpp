#pragma once

#include <string>

struct EventStates;
struct EventActions;

class Camera;
class Shader;
class Model;

using GLADloadproc = void* (*)(const char*);

class Render
{
private:
    static float m_aspect_ratio;

    static Camera m_camera;

    static Shader* m_main_shader;
    static Shader* m_light_shader;

    static Model* m_object;

public:
    static int init(const GLADloadproc get_proc_address,
                    const std::string res_dir,
                    const int viewport_width, const int viewport_height);

    static void fini();

    static void update(EventStates* states, EventActions* actions, const float dt);

private:
    static void updateViewport(const int width, const int height);
    static void processEvents(EventStates* states, EventActions* actions, const float dt);
};
