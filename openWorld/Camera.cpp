#include "Camera.h"

Camera::Camera(glm::vec3 position, float yaw, float pitch)
{
    //position = position;
    this->offset = position;
    this->position = target - offset * Zoom;

    Yaw = yaw;
    Pitch = pitch;

    this->front = glm::vec3(0, 0, 1);
    this->up = glm::vec3(0, 1, 0);
    this->right = glm::vec3(1, 0, 0);


    lookAt(target);
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

   // std::cout << " camera debug\n camera position: " << glm::to_string(this->position) << std::endl;
   // std::cout << " camera target: " << glm::to_string(this->target) << std::endl;
   // std::cout << " pitch: " << this->Pitch << " yaw: " << this->Yaw << std::endl;
   // std::cout << " camera offset: " << glm::to_string(this->offset) << std::endl;
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

glm::vec3* Camera::getFront()
{
    return &this->front;
}

glm::vec3* Camera::getRight()
{
    return &this->right;
}

glm::vec3* Camera::getUp()
{
    return &this->up;
}

void Camera::updatePosition()
{
    if (cameraMode == Mode::firstPerson) {
        position = target;
    }
    else if (cameraMode == Mode::thirdPerson) 
    {
        glm::vec3 direction; //direction is front
        direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        direction.y = sin(glm::radians(Pitch));
        direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        direction = glm::normalize(direction);

       /* position = target - direction * Zoom + offset;*/
        this->front = direction;
        this->right = glm::normalize(glm::cross(direction,glm::vec3(0, 1, 0)));
        this->up = glm::normalize(glm::cross(direction, this->right));
    }
   // std::cout <<" Zoom: " << this->Zoom << std::endl;
    lookAt(target);
}

void Camera::lookAt(glm::vec3 point)
{
    this->viewMatrix = glm::lookAt(this->position, this->target, glm::vec3(0,1,0));
}