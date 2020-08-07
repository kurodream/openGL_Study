#include "shader.h"
#include"bx.h"
#include"V.h"
#include"stb_image.h"

extern float factor;

int lesson_02()
{
	GLFWwindow* window = initializeWindow();

	if (window == NULL)
	{
		std::cout << "Faild to create window" << std::endl;
		glfwTerminate();	// quit process
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Faild to initialize GLAD" << std::endl;
		return -1;
	}

	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};


	//创建VAO vertex array object
	//unsigned int VAO;
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);

	myVAO myVAO_01 = myVAO();
	unsigned int VAO = myVAO_01.getID();

	//创建VBO vertex buffer object
	//申请ID
	unsigned int VBO;
	glGenBuffers(1, &VBO);	//生成缓冲区名称

	//绑定缓冲区
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	//开辟显存

	//将点传到缓冲区
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//myVBO myVBO_01 = myVBO(vertices);
	//unsigned int VBO = myVAO_01.getID();

	//指明顶点属性格式
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Shader shader("Shader.vs", "Shader.fs");

	Vec4 myvec4(1.5f, 0.0f, 0.5f, 1.0f);
	float* myvec = myvec4.getVec4();

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//每次使用program都要有一下三步：
		// use
		myvec4.setVec4(1.5f, 0.0f, factor, 1.0f);
		myvec = myvec4.getVec4();

		shader.setVec4("ourColor", myvec);
		shader.use();
		
		//刷新VAO?
		glBindVertexArray(VAO);
		//画图
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//每一个buffer都要手动释放
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}