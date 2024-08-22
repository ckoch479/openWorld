#pragma once

#include "glad/glad.h"
#include "Includes/glm/glm.hpp"
#include "Includes/glm/gtc/matrix_transform.hpp"
#include <glm/gtx/string_cast.hpp>

#include <vector>
#include <iostream>
#include <algorithm>

#ifndef CAMERA_H
#define CAMERA_H

enum Mode
{
    firstPerson,
    thirdPerson,
    freeCam,
};

// Default camera values
const float YAW =   0.0f;
const float PITCH = 90.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 25.0f;

class Camera
{
public:

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    Camera();

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();
    
    void update(float dt);

    void switchMode(Mode newMode);

    void setTarget(glm::vec3 newTarget);

    void setPosition(glm::vec3 newPos);

    glm::vec3 getPosition();

    glm::vec3 getTarget();

    float getZoom();

    void setZoomLevel(float newZoom);

    void setOrientation(float newYaw, float newPitch);

    glm::vec3* getFront();

    glm::vec3* getRight();

    glm::vec3* getUp();

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    Mode cameraMode = thirdPerson;
    glm::vec3 position = target - offset;
    glm::vec3 target = glm::vec3(0,0,0);
    glm::vec3 offset = glm::vec3(0,1.5,2);

    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    // euler Angles
    float Yaw;
    float Pitch;

    float Zoom = 25.0f;
    float minZoom = 10;
    float maxZoom = 90;

    glm::mat4 viewMatrix;

    void updatePosition();

    void lookAt(glm::vec3 point);
   
};

#endif