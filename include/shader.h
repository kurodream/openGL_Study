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


#ifndef SHADER_H
#define SHADER_H

class Shader
{
public:
	unsigned int ID;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void use();
	//…Ë÷√uniform÷µ
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value)const;
	void setVec4(const std::string& name, float value[]) const;
	void setVec4(const std::string& name, glm::vec4 value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
	void setVec3(const std::string& name, float value0, float value1, float value2) const;
	void setMat4(const std::string& name, float value[]) const;
};
#endif

#ifndef VEC4
#define VEC4

class Vec4
{
	
public:
	Vec4(float x, float y, float z, float w);
	void setVec4(float x, float y, float z, float w);
	float* getVec4() const;
private:
	float x, y, z, w;
};

#endif
