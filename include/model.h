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
	std::vector<Mesh> meshes;	//模型就是一些网格
	std::string directory;	//不知道用来干嘛

	void loadModel(std::string path);	//加载模型(网格)
	void processNode(aiNode* node, const aiScene* scene);	//处理节点
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);	//处理网格
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);	//处理材质
};

#endif // !MODEL_H
