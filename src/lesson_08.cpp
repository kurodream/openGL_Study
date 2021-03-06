#include"shader.h"
#include"bx.h"
#include"camera.h"
#include"stb_image.h"

extern float factor;
extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;
extern Camera myCamera;

float vertices[] = {
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
glm::vec3(0.0f,  0.0f,  1.0f),
glm::vec3(2.0f,  5.0f, -15.0f),
glm::vec3(-1.5f, -2.2f, -2.5f),
glm::vec3(-3.8f, -2.0f, -12.3f),
glm::vec3(2.4f, -0.4f, -3.5f),
glm::vec3(-1.7f,  3.0f, -7.5f),
glm::vec3(1.3f, -2.0f, -2.5f),
glm::vec3(1.5f,  2.0f, -2.5f),
glm::vec3(1.5f,  0.2f, -1.5f),
glm::vec3(-1.3f,  1.0f, -1.5f)
};

int lesson_08_01()
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

	Shader shader_01 = Shader("Shader_04.vs", "Shader_04.fs");

	unsigned int VAO_01, VBO_01;
	glGenVertexArrays(1, &VAO_01);
	glBindVertexArray(VAO_01);

	glGenBuffers(1, &VBO_01);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_01);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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
									//激活一个纹理单元
	glBindTexture(GL_TEXTURE_2D, texture_02);	//绑定到当前渲染环境
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


	float radius = 5.0f;


	glm::mat4 projection;	// > 裁剪
	projection = myCamera.getProjection();


	shader_01.use();
	shader_01.setInt("texture1", 0);
	shader_01.setInt("texture2", 1);

	//启动深度检测
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//清除颜色缓存和深度缓存
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view;	// > 观察 （通过移动原点来改变空间）
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));	//在世界空间中要确定观察矩阵的三个基， 需要相机的位置（世界），观察目标位置（世界），以及世界的单位y

		//更新纹理单元
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_01);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_02);

		//更新着色器
		shader_01.use();
		shader_01.setFloat("factor", factor);
		shader_01.setMat4("view", glm::value_ptr(view));
		shader_01.setMat4("projection", glm::value_ptr(projection));

		//更新VAO
		glBindVertexArray(VAO_01);

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model;	//局部 > 世界 (本来点是基于原点定义的，即理解成物体中心。 在本例子中没有变成世界空间)
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * (i + 1);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
			shader_01.setMat4("model", glm::value_ptr(model));
			//画
			glDrawArrays(GL_TRIANGLES, 0, 36); //这一步前 都是准备工作 配置上下文

		}



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO_01);
	glDeleteBuffers(1, &VBO_01);
	glfwTerminate();
	return 0;
}

int lesson_08_02()
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

	//注册回调函数
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	//设置鼠标不可见
	glfwSetCursorPosCallback(window, mouse_callback);	//非阻塞，异步（应该） 回调。这个glfwSetCursorPosCallback（）是注册回调函数。事件为鼠标移动。
	glfwSetScrollCallback(window, scroll_callback);

	Shader shader_01 = Shader("Shader_04.vs", "Shader_04.fs");

	unsigned int VAO_01, VBO_01;
	glGenVertexArrays(1, &VAO_01);
	glBindVertexArray(VAO_01);

	glGenBuffers(1, &VBO_01);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_01);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int texture_01, texture_02;
	texture_01 = loadTexture("test_01.jpg");
	//激活某个 纹理单元（指针一样的东西）
	glActiveTexture(GL_TEXTURE0);
	//在glActiveTexture 之下绑定
	glBindTexture(GL_TEXTURE_2D, texture_01);
	/*glGenTextures(1, &texture_01);
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
	stbi_image_free(data_01);*/

	//glGenTextures(1, &texture_02);
	//glActiveTexture(GL_TEXTURE1);	//注意 texuture1是不用激活的，默认激活。//并且每个glTexParameteri的开头就是glActiveTexture：激活->绑定->设置
	//glBindTexture(GL_TEXTURE_2D, texture_02);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	texture_02 = loadTexture("test_02.jpg");
	//激活某个 纹理单元（指针一样的东西）
	glActiveTexture(GL_TEXTURE1);
	//在glActiveTexture 之下绑定
	glBindTexture(GL_TEXTURE_2D, texture_02);

	/*int width_02, height_02, nrChannel_02;
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
	stbi_image_free(data_02);*/

	shader_01.use();
	shader_01.setInt("texture1", 0);
	shader_01.setInt("texture2", 1);

	//启动深度检测
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 view;	// > 观察 （通过移动原点来改变空间）
		glm::mat4 projection;	// > 裁剪

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//清除颜色缓存和深度缓存
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		view = myCamera.getView();/*glm::lookAt(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/
		projection = myCamera.getProjection();/* glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f)*/;

		//更新纹理单元
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_01);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_02);

		//更新着色器
		shader_01.use();
		shader_01.setFloat("factor", factor);
		shader_01.setMat4("view", glm::value_ptr(view));
		shader_01.setMat4("projection", glm::value_ptr(projection));

		//更新VAO
		glBindVertexArray(VAO_01);

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model;	//局部 > 世界 (本来点是基于原点定义的，即理解成物体中心。 在本例子中没有变成世界空间)
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * (i + 1);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
			shader_01.setMat4("model", glm::value_ptr(model));
			//画
			glDrawArrays(GL_TRIANGLES, 0, 36); //这一步前 都是准备工作 配置上下文

		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO_01);
	glDeleteBuffers(1, &VBO_01);
	glfwTerminate();
	return 0;
}