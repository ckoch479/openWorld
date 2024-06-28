#include "Camera.h"


void Camera::updateThirdPersonCamera(glm::vec3 playerPos, float playerRot)
{
	//playerPos.y += 1.5f; //for a more over the shoulder look
	
	float horizontalFromPlayer = this->radiusFromPlayer * cos(this->Pitch);
	float verticalDistance = this->radiusFromPlayer * sin(this->Pitch);
	this->Yaw = 180 - playerRot + this->cameraFreeRotationAngle;
	//this->Yaw = playerRot + this->cameraFreeRotationAngle;
	float Xoffset = horizontalFromPlayer * sin(playerRot + cameraFreeRotationAngle);
	float Zoffset = horizontalFromPlayer * cos(playerRot + cameraFreeRotationAngle);
	this->Position.x = playerPos.x - Xoffset;
	this->Position.y = playerPos.y + verticalDistance;
	this->Position.z = playerPos.z - Zoffset;

	glm::vec3 front;
	front.x = playerPos.x - this->Position.x;
	front.y = playerPos.y - this->Position.y;
	front.z = playerPos.z - this->Position.z;

	this->Position += Right * 0.5f;

	Front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));
}

bool Camera::isThirdPerson()
{
	bool mode = false;
	if(this->cameraMode == thirdPerson)
	{
		mode = true;
	}

	return mode;
}

void Camera::setCameraThirdPerson(float radiusFromPlayer)
{
	this->cameraMode = thirdPerson;
	this->radiusFromPlayer = radiusFromPlayer;
}

void Camera::setCameraFreeCam()
{
	this->cameraMode = freeCam;
}
//glm::mat4 Camera::GetViewMatrix() 
//{
//	return glm::lookAt(CameraPosition, Front, Up);
//}
//
//void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
//{
//	//float velocity = this->MovementSpeed * deltaTime;
//
//	//switch(direction)
//	//{
//	//case (FORWARD):
//
//	//	CameraPosition += Front * velocity;
//	//	break;
//
//	//case(BACKWARD):
//	//	CameraPosition -= Front * velocity;
//	//	break;
//
//	//case(LEFT):
//	//	CameraPosition -= Right * velocity;
//	//	break;
//
//	//case(RIGHT):
//	//	CameraPosition += Right * velocity;
//	//	break;
//	//}
//}
//
//void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
//{
//	//xoffset *= MouseSensitivity;
//	//yoffset *= MouseSensitivity;
//
//	//Yaw += xoffset;
//	//Pitch += yoffset;
//
//	//// make sure that when pitch is out of bounds, screen doesn't get flipped
//	//if (constrainPitch)
//	//{
//	//	if (Pitch > 89.0f)
//	//		Pitch = 89.0f;
//	//	if (Pitch < -89.0f)
//	//		Pitch = -89.0f;
//	//}
//
//	//// update Front, Right and Up Vectors using the updated Euler angles
//	//updateCameraVectors();
//}
//
//void Camera::ProcessMouseScroll(float yoffset)
//{
//	Zoom -= (float)yoffset;
//	if (Zoom < 1.0f)
//		Zoom = 1.0f;
//	if (Zoom > 45.0f)
//		Zoom = 45.0f;
//}
//
//void Camera::updateCameraVectors() 
//{
//	//// calculate the new Front vector
//	glm::vec3 front;
//	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
//	front.y = sin(glm::radians(Pitch));
//	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
//	Front = glm::normalize(front);
//
//	// also re-calculate the Right and Up vector
//	Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
//	Up = glm::normalize(glm::cross(Right, Front));
//}
//
//
//void Camera::updateCamera(glm::vec3 target, glm::vec3 position, float pitch, float yaw)
//{
//	//target = front
//    glm::vec3 front = target;
//	this->Front = front;//glm::normalize(front);
//
//	this->Pitch = pitch;
//	this->Yaw = yaw;
//
//
//	this->CameraPosition = position;
//
//	//updateCameraVectors();
//
//	
//}