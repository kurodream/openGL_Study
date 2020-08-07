#include"bx.h"
#include"shader.h"

int lesson_01()
{
	GLFWwindow* window = initializeWindow();

	if (window == NULL)
	{
		std::cout << "Faild to create window" << std::endl;
		glfwTerminate();	// quit process
		return -1;
	}
	glfwMakeContextCurrent(window);	//�����ڵ������Ļ�������Ϊ��ǰ���̵߳������Ļ���

	//��ʼ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Faild to initialize GLAD" << std::endl;
		return -1;
	}

	//ע�ᴰ�ڻص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		//��Ⱦ
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);	//����������ɫ����ɫ��
		glClear(GL_COLOR_BUFFER_BIT);	//����

		glfwSwapBuffers(window);	//����ʾ����͸�Ƶ���潻������ʾ��Ƶ�����е����ݣ�
		glfwPollEvents();	//����Ƿ����¼������������̣�

	}

	glfwTerminate();
	return -1;

}

