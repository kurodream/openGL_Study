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
	glfwMakeContextCurrent(window);	//将窗口的上下文环境设置为当前主线程的上下文环境

	//初始化glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Faild to initialize GLAD" << std::endl;
		return -1;
	}

	//注册窗口回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//渲染循环
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		//渲染
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);	//设置清屏颜色（黄色）
		glClear(GL_COLOR_BUFFER_BIT);	//清屏

		glfwSwapBuffers(window);	//将显示缓存和高频缓存交换（显示高频缓存中的内容）
		glfwPollEvents();	//检测是否有事件触发（鼠标键盘）

	}

	glfwTerminate();
	return -1;

}

