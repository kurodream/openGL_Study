#ifndef HEAD_GL
#define HEAD_GL

#include <stdio.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include<vector>


#endif 

#ifndef CAMERA_H
#define CAMERA_H

enum Camera_Move_Mode
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
public:
	Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);
	void setFov(float fov);
	float getFov() const;
	glm::vec3 getCameraPos() const;
	glm::vec3 getCameraFront() const;
	void moveCamera(float cameraSpeed, Camera_Move_Mode direction);	//操作 cameraPos
	void rotateCamera(glm::vec3 front);	//操作 cameraFront
	glm::mat4 getView() const;
	glm::mat4 getProjection() const;
private:
	float fov = 45.0f;
	//世界坐标
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
};

#endif // !CAMERA_H



