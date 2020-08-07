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
#include"shader.h"


#ifndef MESH_H
#define MESH_H
//每一个顶点有三个数据：顶点世界坐标，世界法线，纹理坐标
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TextureCoord;
};

//每个纹理有三个数据：ID、类型、地址
struct Texture
{
	unsigned int ID;
	std::string Type;
	std::string Path;
};

/*
纹理就是包含：多个顶点与其对应的法线，纹理坐标的对象。
自然有了数据就可以很自然的把对数据的操作一起封装。
*/
class Mesh
{
public:
	//构造函数完成对网格的填装工作,以及初始化(setUpMesh)
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
	//传入Shader类是为了处理纹理
	void Draw(Shader shader) const;

private:
	//用vector
	//vector可以动态扩容和使用摸板类
	std::vector<Vertex> vertices;
	//索引，作用还不太理解
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	//有了数据后，创建渲染环境
	void setUpMesh();

	unsigned int VAO, VBO, EBO;
};
#endif 