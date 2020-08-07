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
//ÿһ���������������ݣ������������꣬���編�ߣ���������
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TextureCoord;
};

//ÿ���������������ݣ�ID�����͡���ַ
struct Texture
{
	unsigned int ID;
	std::string Type;
	std::string Path;
};

/*
������ǰ�����������������Ӧ�ķ��ߣ���������Ķ���
��Ȼ�������ݾͿ��Ժ���Ȼ�İѶ����ݵĲ���һ���װ��
*/
class Mesh
{
public:
	//���캯����ɶ��������װ����,�Լ���ʼ��(setUpMesh)
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
	//����Shader����Ϊ�˴�������
	void Draw(Shader shader) const;

private:
	//��vector
	//vector���Զ�̬���ݺ�ʹ��������
	std::vector<Vertex> vertices;
	//���������û���̫���
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	//�������ݺ󣬴�����Ⱦ����
	void setUpMesh();

	unsigned int VAO, VBO, EBO;
};
#endif 