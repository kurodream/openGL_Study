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

#define STB_IMAGE_IMPLEMENTATION

#endif 



#ifndef COMMFUN_H
#define COMMFUN_H

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
float rotate_degree();
void mouse_callback(GLFWwindow* window, double xpos, double ypos);	//该回调函数功能：
void scroll_callback(GLFWwindow* window, double xpos, double ypos);
unsigned int loadTexture(const char* path);
/*
window表示捕获的窗口，xpos表示x坐标，ypos表示y坐标。

为了计算一个方向向量，我们需要做这么几件事：

计算鼠标相对于上一次的位置偏移。
将偏移值累加到摄像机的yaw和pitch值中去。
添加一些旋转的限制
计算方向向量


*/
GLFWwindow* initializeWindow();

#endif // !COMMFUN_H





