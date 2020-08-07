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
	aiProcess_Triangulate������ʾ����ϣ����ģ���еĻ���ͼ�α��������
	aiProcess_FlipUVs������ʾ����ϣ����ת����y���꣨����б�Ҫ�Ļ���
	*/
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	//����Ƿ�ɹ�
	//scene�����Ƿ���Ч||�ļ��Ƿ�����||���ڵ��Ƿ���Ч
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Assimp����ģ��ʧ�ܣ�������Ϣ: " << importer.GetErrorString() << std::endl;
		return;
	}

	//��ָ��λ�ÿ�ʼ��ָ��λ�ý��� ����
	directory = path.substr(0, path.find_last_of('/'));

	//����processNode������ڵ�����
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	//����node �� mesh
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		/*
		�ⲽ����˼���� �ҵ���ǰnode�е�mesh������i��ֵ��node->mMeshes[i]����
		�����ֵ��scene����mesh������ļ�
		���ü���Ӧ��ֵ��һ��aiMesh��ĵ�ַ������ָ��
		*/
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		//���ҳ�����mesh��ָ�룩�ŵ�ģ����,vectorĩβ
		meshes.push_back(processMesh(mesh, scene));
	}

	//�ݹ�
	for (int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{


}