#include "Camera.h"

Camera::Camera(glm::vec3 position, float yaw, float pitch)
{
    position = position;

    Yaw = yaw;
    Pitch = pitch;

    this->viewMatrix = glm::mat4(1.0f);
}

Camera::Camera()
{
    this->position = glm::vec3(0, 2, 0);
    this->Yaw = 0.0f;
    this->Pitch = 0.0f;
    this->viewMatrix = glm::mat4(1.0f);
}

glm::mat4 Camera::GetViewMatrix()
{
    return this->viewMatrix;
}

void Camera::update(float dt)
{
    updatePosition();
    this->lookAt(this->target);
}

void Camera::switchMode(Mode newMode)
{
    this->cameraMode = newMode;
}

void Camera::setTarget(glm::vec3 newTarget)
{
    this->target = newTarget;
}

void Camera::setPosition(glm::vec3 newPos)
{
    this->position = newPos;
}

glm::vec3 Camera::getPosition()
{
    return position;
}

glm::vec3 Camera::getTarget()
{
    return target;
}

float Camera::getZoom()
{
    return this->Zoom;
}

void Camera::setZoomLevel(float newZoom)
{
    this->Zoom = std::clamp(newZoom, minZoom, maxZoom);
}

void Camera::setOrientation(float newYaw, float newPitch)
{
    this->Yaw = newYaw;
    this->Pitch = std::clamp(newPitch, -89.0f,89.0f);
}

void Camera::updatePosition()
{
    if (cameraMode == Mode::firstPerson) {
        position = target;
    }
    else if (cameraMode == Mode::thirdPerson) 
    {
       /* glm::vec3 direction;
        direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        direction.y = sin(glm::radians(Pitch));
        direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        direction = glm::normalize(direction);

        position = target - direction * Zoom + offset;*/
    }

    lookAt(target);
}

void Camera::lookAt(glm::vec3 point)
{
    this->viewMatrix = glm::lookAt(this->position, point, glm::vec3(0, 1, 0));
}