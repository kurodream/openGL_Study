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

	//ע��ص�����
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	//������겻�ɼ�
	glfwSetCursorPosCallback(window, mouse_callback);	//���������첽��Ӧ�ã� �ص������glfwSetCursorPosCallback������ע��ص��������¼�Ϊ����ƶ���
	glfwSetScrollCallback(window, scroll_callback);

	//Shader ��һ���Ƿ�������� �ڶ����ǹ�Դ��
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

	//����VAO
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

	//��ԴVAO
	unsigned int VAO_02, VBO_02;
	glGenVertexArrays(1, &VAO_02);
	glBindVertexArray(VAO_02);

	glGenBuffers(1, &VBO_02);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_02);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//������ȼ��
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
		glm::mat4 model_Feflect;	//�ֲ� > ���� (�������ǻ���ԭ�㶨��ģ��������������ġ� �ڱ�������û�б������ռ�)
		glm::mat4 view;	// > �۲� ��ͨ���ƶ�ԭ�����ı�ռ䣩
		glm::mat4 projection;	// > �ü�

		processInput(window);

		glClearColor(0.2f, 0.7f, 0.3f, 0.3f);
		//�����ɫ�������Ȼ���
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		model_Feflect = glm::rotate(model_Feflect, (float)glfwGetTime() * glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		view = myCamera.getView();
		projection = myCamera.getProjection();

		//����VAO
		glBindVertexArray(VAO_01);

		//������ɫ��
		myShader_01.use();
		myShader_01.setVec3("cameraPos", myCamera.getCameraPos());
		myShader_01.setMat4("model", glm::value_ptr(model_Feflect));
		myShader_01.setMat4("view", glm::value_ptr(view));
		myShader_01.setMat4("projection", glm::value_ptr(projection));
		
		glDrawArrays(GL_TRIANGLES, 0, 36); //��һ��ǰ ����׼������ ����������

		glBindVertexArray(VAO_02);

		myShader_02.use();
		myShader_02.setMat4("model", glm::value_ptr(model_Source));
		myShader_02.setMat4("view", glm::value_ptr(view));
		myShader_02.setMat4("projection", glm::value_ptr(projection));

		glDrawArrays(GL_TRIANGLES, 0, 36); //��һ��ǰ ����׼������ ����������

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO_01);
	glDeleteBuffers(1, &VBO_01);
	glfwTerminate();
	return 0;

}