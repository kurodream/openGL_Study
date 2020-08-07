#include"mesh.h"
#include"stb_image.h"
#include<stddef.h>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
{
	(this->vertices).insert((this->vertices).end(), vertices.begin(), vertices.end());
	(this->indices).insert((this->indices).end(), indices.begin(), indices.end());
	(this->textures).insert((this->textures).end(), textures.begin(), textures.end());

	setUpMesh();
}

void Mesh::setUpMesh()
{
	unsigned int VAO, VBO, EBO;
	//name -> bind -> data
	//bind 是把object绑定到当前环境
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bing 当前VAO
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.max_size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureCoord));
	glEnableVertexAttribArray(2);

	//恢复默认的VAO环境
	glBindVertexArray(0);

}

void Mesh::Draw(Shader shader) const
{
	//用于生成
	unsigned int diffuse_Nr = 1;
	unsigned int specular_Nr = 1;
	for (int i = 0; i < textures.size(); i++)
	{
		//顺序加载 textures中的元素，并分类
		glActiveTexture(GL_TEXTURE0 + i);	//激活一个 texture unit
		std::string number;
		std::string name = textures[i].Type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuse_Nr++);
		else if (name == "texture_specular")
			number = std::to_string(specular_Nr++);
		shader.setFloat(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].ID);	//将该 texture object 绑定到 当前unit的target上
		//然后用 glTexImage2D, glTexParameteri等函数改变texture object的状态
	}

	//渲染
	glBindVertexArray(VAO);	//操作上下文（状态）
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);	//操作上下文（状态）

	glActiveTexture(GL_TEXTURE0);	//这步的目的 不清楚
}