#include "shader.h"
#include"bx.h"
#include"stb_image.h"

int lesson_03()
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

	//data
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,		//左
	0.5f, -0.5f, 0.0f,		//右
	0.0f, 0.5f, 0.0f,		//上
	1.0f, 0.0f, 0.0f,
	0.75f, 0.5f, 0.0f,
	0.5f, 0.0f, 0.0f
	};

	float rectVertices[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-1.0f, -0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3,
		3, 2, 4
	};

	// VAO
	unsigned int VAO, VAO_01, VAO_02;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//VBO
	unsigned int VBO, VBO_01, VBO_02;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);

	//VEO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//应该每个VAO的下界就是 glEnableVertexAttribArray
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glGenVertexArrays(1, &VAO_01);
	glBindVertexArray(VAO_01);

	glGenBuffers(1, &VBO_01);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_01);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glGenVertexArrays(1, &VAO_02);
	glBindVertexArray(VAO_02);

	glGenBuffers(1, &VBO_02);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_02);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices + 9, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//Vertices Shader
	const char* verticeShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	unsigned int verticeShader;
	verticeShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(verticeShader, 1, &verticeShaderSource, NULL);
	glCompileShader(verticeShader);

	//Fragment Shader
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//FS_01
	const char* fragmentShaderSource_01 = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(0.3f, 1.0f, 0.1f, 1.0f);\n"
		"}\0";
	unsigned int fragmentShader_01;
	fragmentShader_01 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_01, 1, &fragmentShaderSource_01, NULL);
	glCompileShader(fragmentShader_01);

	//连接器
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, verticeShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	

	//连接器_01
	unsigned int shaderProgram_01;
	shaderProgram_01 = glCreateProgram();
	glAttachShader(shaderProgram_01, verticeShader);
	glAttachShader(shaderProgram_01, fragmentShader_01);
	glLinkProgram(shaderProgram_01);


	glDeleteShader(verticeShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShader_01);


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//use program
		glUseProgram(shaderProgram);

		//draw
		//VAO_EBO
		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		//VAO_VBO_01
		glBindVertexArray(VAO_01);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		////VAO_VBO_01
		//glBindVertexArray(VAO_02);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//program_01
		glUseProgram(shaderProgram_01);
		glBindVertexArray(VAO_02);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}
