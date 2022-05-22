#include "./camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 world_up)
    : m_position(position), m_world_up(world_up)
{
    updateDirection();
}

glm::vec3 Camera::getCameraPos()
{
    return m_position;
}

glm::mat4 Camera::lookAt() const
{
    return glm::lookAt(m_position, m_position + m_direction, m_up);
}

void Camera::move(CameraMovement movement)
{
    const float lateral_offset      = movement.right - movement.left;
    const float longitudinal_offset = movement.forward - movement.backward;

    m_position += m_right * lateral_offset;
    m_position += m_direction * longitudinal_offset;

    updateYawAngle(movement.yaw);
    updatePitchAngle(movement.pitch);
    updateZoom(movement.zoom);
    updateDirection();
}

void Camera::updateYawAngle(float angle)
{
    m_yaw += angle;
}

void Camera::updatePitchAngle(float angle)
{
    m_pitch += angle;

    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    else if (m_pitch < -89.0f)
        m_pitch = -89.0f;
}

void Camera::updateZoom(float offset)
{
    m_zoom -= offset;

    if (m_zoom < 1.0f)
        m_zoom = 1.0f;
    else if (m_zoom > 45.0f)
        m_zoom = 45.0f;
}

void Camera::updateDirection()
{
    glm::vec3 direction;
    direction.x = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
    direction.y = std::sin(glm::radians(m_pitch));
    direction.z = std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));

    m_direction = glm::normalize(direction);

    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    m_right = glm::normalize(glm::cross(m_direction, m_world_up));
    m_up    = glm::normalize(glm::cross(m_right, m_direction));
}
