#include"shader.h"
#include"bx.h"
#include"stb_image.h"

int lesson_04()
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

	//获取最大属性数量
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "最大支持的属性数量为：" << nrAttributes << std::endl;

	float rectVertices[] = 
	{
		//位置					// 颜色					//纹理坐标
		0.5f,	0.5f,	0.0f,	1.0f,	0.0f,	0.0f,	1.5f,	0.0f,	//右上角
		0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	0.0f,	1.5f,	1.0f,	//右下角
		-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,	//左下角
		-0.5f,	0.5f,	0.0f,	1.0f,	1.0f,	0.0f,	0.0f,	0.0f	//左上角
	};

	unsigned int indices[] = 
	{
	0, 1, 3,
	1, 2, 3,
	};

	Shader shader_01 = Shader("Shader_01.vs", "Shader_01.fs");

	unsigned int VAO_01, VBO_01, EBO_01;
	glGenVertexArrays(1, &VAO_01);
	glBindVertexArray(VAO_01);

	glGenBuffers(1, &VBO_01);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_01);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO_01);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_01);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int texture_01;
	glGenBuffers(1, &texture_01);
	glBindBuffer(GL_TEXTURE_2D, texture_01);

	//纹理过滤函数glTexParameteri() 
	//第一参数：layer 第二参数：u，v方向的环绕方式。放大缩小的算法 第三参数：环绕方式和过滤方式，是哪一个取决于第二参数 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//
	int width, height, nrChannels;
	unsigned char* data = stbi_load("test.jpg", &width, &height, &nrChannels, 0);

	//
	if (data)
	{
		GLint format = nrChannels == 3 ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "无法加载问题，请检查代码或资源是否有误。" << std::endl;
	stbi_image_free(data);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader_01.use();
		// BIND shader_01.fs @ uniform sampler2D texture1;
		glBindTexture(GL_TEXTURE_2D, texture_01);
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