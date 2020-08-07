#include"camera.h"
#include"bx.h"
#include"stb_image.h"

unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;

Camera myCamera = Camera(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp)
{
	this->cameraPos = cameraPos;
	this->cameraFront = cameraFront;
	this->cameraUp = cameraUp;


}

void Camera::setFov(float fov)
{
	this->fov = fov;
}

float Camera::getFov() const
{
	return fov;
}

glm::vec3 Camera::getCameraPos() const
{
	return cameraPos;
}

glm::vec3 Camera::getCameraFront() const
{
	return cameraFront;
}

void Camera::moveCamera(float cameraSpeed, Camera_Move_Mode direction)
{
	//if (isAD)
	//{
	//	cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
	//}
	//else
	//{
	//	cameraPos += cameraSpeed * cameraFront;
	//}
	if(direction == FORWARD)
		cameraPos += cameraSpeed * cameraFront;
	if(direction == BACKWARD)
		cameraPos -= cameraSpeed * cameraFront;
	if(direction == LEFT)
		cameraPos -= cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
	if (direction == RIGHT)
		cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
	if (direction == UP)
		cameraPos += cameraSpeed * cameraUp;
	if (direction == DOWN)
		cameraPos -= cameraSpeed * cameraUp;
}

void Camera::rotateCamera(glm::vec3 front)
{
	cameraFront = front;
}

glm::mat4 Camera::getView() const
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::mat4 Camera::getProjection() const
{
	return glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
}