#include "Camera.h"

glm::mat4 Camera::GetViewMatrix() 
{
	return glm::lookAt(CameraPosition, CameraPosition + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	//float velocity = this->MovementSpeed * deltaTime;

	//switch(direction)
	//{
	//case (FORWARD):

	//	CameraPosition += Front * velocity;
	//	break;

	//case(BACKWARD):
	//	CameraPosition -= Front * velocity;
	//	break;

	//case(LEFT):
	//	CameraPosition -= Right * velocity;
	//	break;

	//case(RIGHT):
	//	CameraPosition += Right * velocity;
	//	break;
	//}
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	//xoffset *= MouseSensitivity;
	//yoffset *= MouseSensitivity;

	//Yaw += xoffset;
	//Pitch += yoffset;

	//// make sure that when pitch is out of bounds, screen doesn't get flipped
	//if (constrainPitch)
	//{
	//	if (Pitch > 89.0f)
	//		Pitch = 89.0f;
	//	if (Pitch < -89.0f)
	//		Pitch = -89.0f;
	//}

	//// update Front, Right and Up Vectors using the updated Euler angles
	//updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}

void Camera::updateCameraVectors() 
{
	//// calculate the new Front vector
	//glm::vec3 front;
	//front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	//front.y = sin(glm::radians(Pitch));
	//front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	//Front = glm::normalize(front);
	//// also re-calculate the Right and Up vector
	//Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	//Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::setPosition(glm::vec3 position)
{
	this->CameraPosition = position;
}

void Camera::setTarget(glm::vec3 focusTarget)
{
	this->Front = focusTarget;
}

void Camera::setUp(glm::vec3 cameraUp)
{
	this->Up = cameraUp;
}

void Camera::updateCamera(glm::vec3 target, float pitch, float yaw, float Radius)
{
	//target = front
	this->Front = target;
	Front = glm::normalize(Front);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));

	CameraPosition.x = sin(yaw) * Radius;
	CameraPosition.y = 0.0;
	CameraPosition.z = cos(yaw) * Radius;


}