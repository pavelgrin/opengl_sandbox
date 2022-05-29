#pragma once

#include <glm/glm.hpp>

struct CameraMovement
{
    float forward;
    float backward;
    float left;
    float right;
    float yaw;
    float pitch;
    float zoom;
};

class Camera
{
    glm::vec3 m_world_up;

    glm::vec3 m_position;
    glm::vec3 m_direction;
    glm::vec3 m_up;
    glm::vec3 m_right;

    float m_yaw{-90.0f};
    float m_pitch{0.0f};
    float m_zoom{45.0f};

public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 lookAt() const;
    void move(CameraMovement movement);

    float zoom() const { return m_zoom; }
    glm::vec3 getCameraPos();
    glm::vec3 getCameraFront();

private:
    void updateYawAngle(float angle);
    void updatePitchAngle(float angle);
    void updateZoom(float offset);
    void updateDirection();
    void updateCameraVectors();
};
