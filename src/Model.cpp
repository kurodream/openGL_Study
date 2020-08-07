#include"bx.h"
#include"model.h"

void Model::Draw(Shader shader) const
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	/*
	aiProcess_Triangulate参数表示我们希望把模型中的基本图形变成三角形
	aiProcess_FlipUVs参数表示我们希望翻转纹理y坐标（如果有必要的话）
	*/
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	//检测是否成功
	//scene对象是否有效||文件是否完整||根节点是否有效
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Assimp加载模型失败，错误信息: " << importer.GetErrorString() << std::endl;
		return;
	}

	//从指定位置开始到指定位置结束 复制
	directory = path.substr(0, path.find_last_of('/'));

	//调用processNode来处理节点数据
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	//访问node 的 mesh
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		/*
		这步的意思就是 找到当前node中的mesh的索引i的值（node->mMeshes[i]），
		而这个值是scene索引mesh索引表的键
		而该键对应的值是一个aiMesh类的地址，赋给指针
		*/
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		//把找出来的mesh（指针）放到模型里,vector末尾
		meshes.push_back(processMesh(mesh, scene));
	}

	//递归
	for (int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{


}