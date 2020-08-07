#include"shader.h"
#include"bx.h"
#include"stb_image.h"

extern float factor;
float rotate_factor = 0.0f;


int lesson_06()
{
	GLFWwindow* window = initializeWindow();

	if (window == NULL)
	{
		std::cout << "Faild to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Faild to initialize GLAD" << std::endl;
		return -1;
	}

	float rectVertices[] =
	{
		//位置					// 颜色					//纹理坐标
		0.5f,	0.5f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f,	1.0f,	//右上角
		0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,	0.0f,	//右下角
		-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	//左下角
		-0.5f,	0.5f,	0.0f,	1.0f,	1.0f,	0.0f,	0.0f,	1.0f	//左上角
	};

	unsigned int indices[] =
	{
	0, 1, 3,
	1, 2, 3,
	};

	Shader shader_01 = Shader("Shader_03.vs", "Shader_03.fs");

	unsigned int VAO_01, VBO_01, EBO_01;
	glGenVertexArrays(1, &VAO_01);
	glBindVertexArray(VAO_01);

	glGenBuffers(1, &VBO_01);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_01);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &EBO_01);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_01);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	unsigned int texture_01, texture_02;
	glGenTextures(1, &texture_01);
	glBindTexture(GL_TEXTURE_2D, texture_01);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width_01, height_01, nrChannel_01;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data_01 = stbi_load("test_01.jpg", &width_01, &height_01, &nrChannel_01, 0);

	if (data_01)
	{
		GLint format = nrChannel_01 == 3 ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width_01, height_01, 0, format, GL_UNSIGNED_BYTE, data_01);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "无法加载问题，请检查代码或资源是否有误。" << std::endl;
	}
	stbi_image_free(data_01);

	glGenTextures(1, &texture_02);
	glActiveTexture(GL_TEXTURE1);	//注意 texuture1是不用激活的，默认激活。//并且每个glTexParameteri的开头就是glActiveTexture：激活->绑定->设置
	glBindTexture(GL_TEXTURE_2D, texture_02);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width_02, height_02, nrChannel_02;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data_02 = stbi_load("test_02.jpg", &width_02, &height_02, &nrChannel_02, 0);

	if (data_02)
	{
		GLint format = nrChannel_02 == 3 ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width_02, height_02, 0, format, GL_UNSIGNED_BYTE, data_02);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "无法加载问题，请检查代码或资源是否有误。" << std::endl;
	}
	stbi_image_free(data_02);

	//仿射矩阵
	glm::mat4 trans;	//单位矩阵
	trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
	

	shader_01.use();
	shader_01.setInt("texture1", 0);
	shader_01.setInt("texture2", 1);
	

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_01);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_02);



		shader_01.use();
		shader_01.setFloat("factor", factor);
		//if (rotate_flag)
		//{
		//	//用glm::radians将角度转化为弧度，glm::vec3(0.0, 0.0, 1.0)表示沿Z轴旋转
		//	trans = glm::rotate(trans, rotate_degree(), glm::vec3(0.0f, 0.0f, 1.0f));
		//	shader_01.setMat4("trans", glm::value_ptr(trans));
		//	rotate_flag = 0;
		//}

		glBindVertexArray(VAO_01);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO_01);
	glDeleteBuffers(1, &VBO_01);
	glDeleteBuffers(1, &EBO_01);
	glDeleteBuffers(1, &texture_01);
	glfwTerminate();
	return 0;

}