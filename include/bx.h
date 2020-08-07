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
void mouse_callback(GLFWwindow* window, double xpos, double ypos);	//�ûص��������ܣ�
void scroll_callback(GLFWwindow* window, double xpos, double ypos);
unsigned int loadTexture(const char* path);
/*
window��ʾ����Ĵ��ڣ�xpos��ʾx���꣬ypos��ʾy���ꡣ

Ϊ�˼���һ������������������Ҫ����ô�����£�

��������������һ�ε�λ��ƫ�ơ�
��ƫ��ֵ�ۼӵ��������yaw��pitchֵ��ȥ��
���һЩ��ת������
���㷽������


*/
GLFWwindow* initializeWindow();

#endif // !COMMFUN_H





