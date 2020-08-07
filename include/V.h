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
#include<assimp/config.h>
#include<vector>



#endif 

#ifndef MY_V_H
#define MY_V_H

class myVAO
{
public:

	myVAO();
	int getID() const;
private:
	unsigned int ID;
};

class myVBO
{
public:
	unsigned int ID;
	myVBO(void* vertext);
private:
	int getID() const;
};

class myEBO
{
public:
	unsigned int ID;
	myEBO(float* value);
private:
	int getID() const;
};

#endif // !MY_V_H


