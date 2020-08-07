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

#endif #pragma once

#include"mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#ifndef MODEL_H
#define MODEL_H

class Model
{
public:
	Model(char* path)
	{
		loadModel(path);
	}
	void Draw(Shader shader) const;
private:
	std::vector<Mesh> meshes;	//ģ�;���һЩ����
	std::string directory;	//��֪����������

	void loadModel(std::string path);	//����ģ��(����)
	void processNode(aiNode* node, const aiScene* scene);	//����ڵ�
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);	//��������
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);	//�������
};

#endif // !MODEL_H
