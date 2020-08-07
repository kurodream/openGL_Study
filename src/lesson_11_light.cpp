#include"shader.h"
#include"bx.h"
#include"camera.h"
#include"stb_image.h"

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;
extern Camera myCamera;

int lesson_11_01()
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

	Shader lighting_Shader = Shader("Shader_Light_05.vert", "Shader_Light_05.frag");
	Shader lamp_Shader = Shader("Shader_Light_06.vert", "Shader_Light_06.frag");

    float vertices[] = {
        // 位置                  // 法线                 // 纹理坐标
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    //物体VAO
    unsigned int VAO_01, VBO_01;
    glGenVertexArrays(1, &VAO_01);
    glBindVertexArray(VAO_01);

    glGenBuffers(1, &VBO_01);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_01);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //光源VAO
    unsigned int VAO_02, VBO_02;
    glGenVertexArrays(1, &VAO_02);
    glBindVertexArray(VAO_02);

    glGenBuffers(1, &VBO_02);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_02);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture
    unsigned int texture_01,texture_02;
    texture_01 = loadTexture("wood_wall.png");
    //激活某个 纹理单元（指针一样的东西）
    glActiveTexture(GL_TEXTURE0);
    //在glActiveTexture 之下绑定
    glBindTexture(GL_TEXTURE_2D, texture_01);

    texture_02 = loadTexture("wall_edge.png");
    //激活某个 纹理单元（指针一样的东西）
    glActiveTexture(GL_TEXTURE1);
    //在glActiveTexture 之下绑定
    glBindTexture(GL_TEXTURE_2D, texture_02);


    glm::vec3 lampPos = glm::vec3(4.0f, 0.0f, 4.0f);
    glm::mat4 model_Lamp;
    model_Lamp = glm::translate(model_Lamp, lampPos);
    glm::vec3 lampObjectColor = glm::vec3(1.0f, 1.0f, 1.0f);


    lighting_Shader.use();
    lighting_Shader.setVec3("lampPos", lampPos);
    lighting_Shader.setVec3("lampObjectColor", lampObjectColor);
    lighting_Shader.setInt("material.diffuse", 0);
    lighting_Shader.setInt("material.specular", 1);
    lighting_Shader.setFloat("material.shininess", 128 * 0.6f);
    lighting_Shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    lighting_Shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    lighting_Shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    lamp_Shader.use();
    lamp_Shader.setMat4("model_Lamp", glm::value_ptr(model_Lamp));
    lamp_Shader.setVec3("lampObjectColor", lampObjectColor);



    //启动深度检测
    glEnable(GL_DEPTH_TEST);

    glActiveTexture(GL_TEXTURE0);
    //在glActiveTexture 之下绑定
    glBindTexture(GL_TEXTURE_2D, texture_01);
    glActiveTexture(GL_TEXTURE1);
    //在glActiveTexture 之下绑定
    glBindTexture(GL_TEXTURE_2D, texture_02);

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

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(VAO_02);
        lamp_Shader.use();
        lamp_Shader.setMat4("view", glm::value_ptr(view));
        lamp_Shader.setMat4("projection", glm::value_ptr(projection));

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();

        int er = glGetError();
        if (er > 0)
            std::cout << er << std::endl;
    }

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO_01);
    glDeleteBuffers(1, &VBO_01);
    glfwTerminate();
    return 0;
}