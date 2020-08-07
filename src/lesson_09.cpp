#include"shader.h"
#include"bx.h"
#include"camera.h"
#include"stb_image.h"

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;
extern Camera myCamera;

int lesson_09_01()
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

	//Shader 第一个是反射物体的 第二个是光源的
	Shader myShader_01 = Shader("Shader_Light_01.vs", "Shader_Light_01.fs");
	Shader myShader_02 = Shader("Shader_Light_02.vs", "Shader_Light_02.fs");

	//DATA
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

	glm::mat4 model_Source;
	model_Source = glm::translate(model_Source, glm::vec3(10.0f, 10.0f, 0.0f));

	glm::vec3 reflectObject(1.0f, 0.5f, 0.25f);
	glm::vec3 sourceObject(15.0f, 1.0f, 1.0f);

	myShader_01.use();
	myShader_01.setVec3("reflectObject", reflectObject);
	myShader_01.setVec3("sourceObject", sourceObject);
	myShader_01.setVec3("sourcePos", glm::vec3(10.0f, 10.0f, 0.0f));

	myShader_02.use();
	myShader_02.setVec3("sourceObject", sourceObject);

	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 model_Feflect;	//局部 > 世界 (本来点是基于原点定义的，即理解成物体中心。 在本例子中没有变成世界空间)
		glm::mat4 view;	// > 观察 （通过移动原点来改变空间）
		glm::mat4 projection;	// > 裁剪

		processInput(window);

		glClearColor(0.2f, 0.7f, 0.3f, 0.3f);
		//清除颜色缓存和深度缓存
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		model_Feflect = glm::rotate(model_Feflect, (float)glfwGetTime() * glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		view = myCamera.getView();
		projection = myCamera.getProjection();

		//更新VAO
		glBindVertexArray(VAO_01);

		//更新着色器
		myShader_01.use();
		myShader_01.setVec3("cameraPos", myCamera.getCameraPos());
		myShader_01.setMat4("model", glm::value_ptr(model_Feflect));
		myShader_01.setMat4("view", glm::value_ptr(view));
		myShader_01.setMat4("projection", glm::value_ptr(projection));
		
		glDrawArrays(GL_TRIANGLES, 0, 36); //这一步前 都是准备工作 配置上下文

		glBindVertexArray(VAO_02);

		myShader_02.use();
		myShader_02.setMat4("model", glm::value_ptr(model_Source));
		myShader_02.setMat4("view", glm::value_ptr(view));
		myShader_02.setMat4("projection", glm::value_ptr(projection));

		glDrawArrays(GL_TRIANGLES, 0, 36); //这一步前 都是准备工作 配置上下文

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO_01);
	glDeleteBuffers(1, &VBO_01);
	glfwTerminate();
	return 0;

}