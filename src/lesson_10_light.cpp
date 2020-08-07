#include"shader.h"
#include"bx.h"
#include"camera.h"
#include"stb_image.h"

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;
extern Camera myCamera;

int lesson_10_01()
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

	Shader lighting_Shader = Shader("Shader_Light_03.vert", "Shader_Light_03.frag");
	Shader lamp_Shader = Shader("Shader_Light_04.vert", "Shader_Light_04.frag");

	float vertices[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
	};

	//VAO VBO

//物体VAO
	unsigned int VAO_01, VBO_01;
	glGenVertexArrays(1, &VAO_01);
	glBindVertexArray(VAO_01);

	glGenBuffers(1, &VBO_01);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_01);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//光源VAO
	unsigned int VAO_02, VBO_02;
	glGenVertexArrays(1, &VAO_02);
	glBindVertexArray(VAO_02);

	glGenBuffers(1, &VBO_02);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_02);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//启动深度检测
	glEnable(GL_DEPTH_TEST);

	glm::mat4 model_Lamp;
	model_Lamp= glm::translate(model_Lamp, glm::vec3(10.0f, 10.0f, 0.0f));

	glm::vec3 lightingObjectColor = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::vec3 lampObjectColor = glm::vec3(1.0f, 1.0f, 1.0f);

	lighting_Shader.use();
	lighting_Shader.setVec3("lightingObjectColor", lightingObjectColor);
	lighting_Shader.setVec3("lampObjectColor", lampObjectColor);
	lighting_Shader.setVec3("lampObjectPos", glm::vec3(10.0f, 10.0f, 0.0f));
	lighting_Shader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
	lighting_Shader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	lighting_Shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	lighting_Shader.setFloat("material.shininess", 32.0f);
	lighting_Shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	lighting_Shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	lighting_Shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	lamp_Shader.use();
	lamp_Shader.setMat4("model_Lamp", glm::value_ptr(model_Lamp));
	lamp_Shader.setVec3("lampObjectColor", lampObjectColor);
	

	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 model_Lighting;	//局部 > 世界 (本来点是基于原点定义的，即理解成物体中心。 在本例子中没有变成世界空间)
		glm::mat4 view;	// > 观察 （通过移动原点来改变空间）
		glm::mat4 projection;	// > 裁剪

		processInput(window);

		glClearColor(0.2f, 0.7f, 0.3f, 0.3f);
		//清除颜色缓存和深度缓存
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model_Lighting = glm::rotate(model_Lighting, (float)glfwGetTime() * glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		view = myCamera.getView();
		projection = myCamera.getProjection();

		//更新VAO
		glBindVertexArray(VAO_01);

		lighting_Shader.use();
		lighting_Shader.setMat4("model_Lighting", glm::value_ptr(model_Lighting));
		lighting_Shader.setMat4("view", glm::value_ptr(view));
		lighting_Shader.setMat4("projection", glm::value_ptr(projection));
		//lighting_Shader.setVec3("cameraPos", myCamera.getCameraPos());

		glDrawArrays(GL_TRIANGLES, 0, 36); //这一步前 都是准备工作 配置上下文

		glBindVertexArray(VAO_02);

		lamp_Shader.use();
		lamp_Shader.setMat4("view", glm::value_ptr(view));
		lamp_Shader.setMat4("projection", glm::value_ptr(projection));


		glDrawArrays(GL_TRIANGLES, 0, 36); //这一步前 都是准备工作 配置上下文

		glfwSwapBuffers(window);
		glfwPollEvents();

		int er = glGetError();
		if(er > 0)
			std::cout << er << std::endl;

	}
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO_01);
	glDeleteBuffers(1, &VBO_01);
	glfwTerminate();
	return 0;
}