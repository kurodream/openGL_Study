#include"shader.h"
#include"bx.h"
#include"camera.h"
#include"stb_image.h"

extern float factor_unlimited;
extern bool rotate;
extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;
extern Camera myCamera;

int lesson_12_01_DirectLight()
{
    //������ʼ��
    float vertices[] = {
        // λ��                  // ����                 // ��������
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
    glm::vec3 cubePositions[] = {
      glm::vec3(0.0f,  0.0f,  0.0f),
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
    
    glm::vec3 lampObjectColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 SpotLightPos = glm::vec3(0.0f, 3.0f, 0.0f);
    glm::vec3 SpotLightDir = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 dotLightPos = glm::vec3(0.0f, 0.0f, 15.0f);
    glm::vec3 lampPos = dotLightPos;
    float angle[10] = {0.0f};
    float lastTime = 0.0f;
    float deltaTime = 0.0f;

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

	Shader lighting_Shader = Shader("Shader_Light_07.vert", "Shader_Light_07_DirLight_BKUP.frag");
	Shader lamp_Shader = Shader("Shader_Light_08.vert", "Shader_Light_08.frag");
    

    //����VAO
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

    //��ԴVAO
    unsigned int VAO_02, VBO_02;
    glGenVertexArrays(1, &VAO_02);
    glBindVertexArray(VAO_02);

    glGenBuffers(1, &VBO_02);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_02);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture
    unsigned int texture_01, texture_02;
    texture_01 = loadTexture("wood_wall.png");
    //����ĳ�� ����Ԫ��ָ��һ���Ķ�����
    glActiveTexture(GL_TEXTURE0);
    //��glActiveTexture ֮�°�
    glBindTexture(GL_TEXTURE_2D, texture_01);

    texture_02 = loadTexture("wall_edge.png");
    //����ĳ�� ����Ԫ��ָ��һ���Ķ�����
    glActiveTexture(GL_TEXTURE1);
    //��glActiveTexture ֮�°�
    glBindTexture(GL_TEXTURE_2D, texture_02);

    glm::mat4 model_Lamp;
    model_Lamp = glm::translate(model_Lamp, lampPos);
    

    lighting_Shader.use();
    lighting_Shader.setVec3("lampPos", lampPos);
    lighting_Shader.setVec3("lampObjectColor", lampObjectColor);
    lighting_Shader.setInt("material.diffuse", 0);
    lighting_Shader.setInt("material.specular", 1);
    lighting_Shader.setFloat("material.shininess", 128 * 0.6f);
    
    lighting_Shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    lighting_Shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    lighting_Shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    lighting_Shader.setVec3("dotLightPos", dotLightPos);
    lighting_Shader.setFloat("light.constant", 1.0f);
    lighting_Shader.setFloat("light.linear", 0.09f);
    lighting_Shader.setFloat("light.quadratic", 0.032f);
    lighting_Shader.setFloat("light.cutOff", glm::cos(glm::radians(1.047f)));
    lighting_Shader.setVec3("spotLightPos", SpotLightPos);
    lighting_Shader.setVec3("spotLightDir", SpotLightPos);

    lamp_Shader.use();
    lamp_Shader.setMat4("model_Lamp", glm::value_ptr(model_Lamp));
    lamp_Shader.setVec3("lampObjectColor", lampObjectColor);

    //������ȼ��
    glEnable(GL_DEPTH_TEST);

    glActiveTexture(GL_TEXTURE0);
    //��glActiveTexture ֮�°�
    glBindTexture(GL_TEXTURE_2D, texture_01);
    glActiveTexture(GL_TEXTURE1);
    //��glActiveTexture ֮�°�
    glBindTexture(GL_TEXTURE_2D, texture_02);

    while (!glfwWindowShouldClose(window))
    {
        glm::vec3 directLight = glm::vec3(glm::cos(glm::radians(factor_unlimited)), glm::sin(glm::radians(factor_unlimited)), 0.0f);

        //ÿһ֡��ʱ���߼�
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
       
        glm::mat4 view;	// > �۲� ��ͨ���ƶ�ԭ�����ı�ռ䣩
        glm::mat4 projection;	// > �ü�

        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 0.3f);
        //�����ɫ�������Ȼ���
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        view = myCamera.getView();
        projection = myCamera.getProjection();

        //����VAO
        glBindVertexArray(VAO_01);

        lighting_Shader.use();
        lighting_Shader.setVec3("direction", directLight);
        lighting_Shader.setMat4("view", glm::value_ptr(view));
        lighting_Shader.setMat4("projection", glm::value_ptr(projection));

        for (int i = 0; i < 10; i++)
        {
            glm::mat4 model_Lighting;	//�ֲ� > ���� (�������ǻ���ԭ�㶨��ģ��������������ġ� �ڱ�������û�б������ռ�)
            model_Lighting = glm::translate(model_Lighting, cubePositions[i]);
            /*float angel = deltaTime * 30.f;*/
            
            if (rotate)
            {
                angle[i] += 1.0f * i * deltaTime;
            }
            else
                angle[i] += 0.0f;
            
            model_Lighting = glm::rotate(model_Lighting,  glm::radians(angle[i]), glm::vec3(1.0f, 0.3f, 0.5f));
            lighting_Shader.setMat4("model_Lighting", glm::value_ptr(model_Lighting));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

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

int lesson_12_02_DotLight()
{
    //������ʼ��
    float vertices[] = {
        // λ��                  // ����                 // ��������
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
    glm::vec3 cubePositions[] = {
      glm::vec3(0.0f,  0.0f,  0.0f),
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
    glm::vec3 directLight = glm::vec3(-8.0f, 0.0f, 0.0f);
    glm::vec3 lampObjectColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 SpotLightPos = glm::vec3(0.0f, 3.0f, 0.0f);
    glm::vec3 SpotLightDir = glm::vec3(0.0f, 1.0f, 0.0f);
    float angle[10] = { 0.0f };
    float lastTime = 0.0f;
    float deltaTime = 0.0f;

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

    Shader lighting_Shader = Shader("Shader_Light_07.vert", "Shader_Light_07_DotLight.frag");
    Shader lamp_Shader = Shader("Shader_Light_08.vert", "Shader_Light_08.frag");


    //����VAO
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

    //��ԴVAO
    unsigned int VAO_02, VBO_02;
    glGenVertexArrays(1, &VAO_02);
    glBindVertexArray(VAO_02);

    glGenBuffers(1, &VBO_02);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_02);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture
    unsigned int texture_01, texture_02;
    texture_01 = loadTexture("wood_wall.png");
    //����ĳ�� ����Ԫ��ָ��һ���Ķ�����
    glActiveTexture(GL_TEXTURE0);
    //��glActiveTexture ֮�°�
    glBindTexture(GL_TEXTURE_2D, texture_01);

    texture_02 = loadTexture("wall_edge.png");
    //����ĳ�� ����Ԫ��ָ��һ���Ķ�����
    glActiveTexture(GL_TEXTURE1);
    //��glActiveTexture ֮�°�
    glBindTexture(GL_TEXTURE_2D, texture_02);


    lighting_Shader.use();

    lighting_Shader.setVec3("lampObjectColor", lampObjectColor);
    lighting_Shader.setInt("material.diffuse", 0);
    lighting_Shader.setInt("material.specular", 1);
    lighting_Shader.setFloat("material.shininess", 128 * 0.6f);
    lighting_Shader.setVec3("direction", directLight);
    lighting_Shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    lighting_Shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    lighting_Shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    lighting_Shader.setFloat("light.constant", 1.0f);
    lighting_Shader.setFloat("light.linear", 0.09f);
    lighting_Shader.setFloat("light.quadratic", 0.032f);
    lighting_Shader.setFloat("light.cutOff", glm::cos(glm::radians(1.047f)));
    lighting_Shader.setVec3("spotLightPos", SpotLightPos);
    lighting_Shader.setVec3("spotLightDir", SpotLightPos);

    lamp_Shader.use();

    lamp_Shader.setVec3("lampObjectColor", lampObjectColor);

    //������ȼ��
    glEnable(GL_DEPTH_TEST);

    glActiveTexture(GL_TEXTURE0);
    //��glActiveTexture ֮�°�
    glBindTexture(GL_TEXTURE_2D, texture_01);
    glActiveTexture(GL_TEXTURE1);
    //��glActiveTexture ֮�°�
    glBindTexture(GL_TEXTURE_2D, texture_02);

    while (!glfwWindowShouldClose(window))
    {
        glm::vec3 dotLightPos = glm::vec3(0.0f, 0.0f, factor_unlimited);
        glm::vec3 lampPos = dotLightPos;

        glm::mat4 model_Lamp;
        model_Lamp = glm::translate(model_Lamp, lampPos);

        //ÿһ֡��ʱ���߼�
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glm::mat4 view;	// > �۲� ��ͨ���ƶ�ԭ�����ı�ռ䣩
        glm::mat4 projection;	// > �ü�

        processInput(window);

        glClearColor(0.2f, 0.7f, 0.3f, 0.3f);
        //�����ɫ�������Ȼ���
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        view = myCamera.getView();
        projection = myCamera.getProjection();

        //����VAO
        glBindVertexArray(VAO_01);

        lighting_Shader.use();
        lighting_Shader.setVec3("lampPos", lampPos);
        lighting_Shader.setVec3("dotLightPos", dotLightPos);
        lighting_Shader.setMat4("view", glm::value_ptr(view));
        lighting_Shader.setMat4("projection", glm::value_ptr(projection));

        for (int i = 0; i < 10; i++)
        {
            glm::mat4 model_Lighting;	//�ֲ� > ���� (�������ǻ���ԭ�㶨��ģ��������������ġ� �ڱ�������û�б������ռ�)
            model_Lighting = glm::translate(model_Lighting, cubePositions[i]);
            if (rotate)
            {
                angle[i] += 1.0f * i * deltaTime;
            }
            else
                angle[i] += 0.0f;

            model_Lighting = glm::rotate(model_Lighting, glm::radians(angle[i]), glm::vec3(1.0f, 0.3f, 0.5f));
            lighting_Shader.setMat4("model_Lighting", glm::value_ptr(model_Lighting));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(VAO_02);
        lamp_Shader.use();
        lamp_Shader.setMat4("model_Lamp", glm::value_ptr(model_Lamp));
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

int lesson_12_03_SpotLight()
{
    //������ʼ��
    float vertices[] = {
        // λ��                  // ����                 // ��������
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
    glm::vec3 cubePositions[] = {
      glm::vec3(0.0f,  0.0f,  0.0f),
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
    glm::vec3 directLight = glm::vec3(-8.0f, 0.0f, 0.0f);
    glm::vec3 lampObjectColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 dotLightPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 lampPos = glm::vec3(1.0f, 1.0f, 1.0f);
    float angle[10] = { 0.0f };
    float lastTime = 0.0f;
    float deltaTime = 0.0f;

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

    Shader lighting_Shader = Shader("Shader_Light_07.vert", "Shader_Light_07_SpotLight.frag");


    //����VAO
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

    //��ԴVAO
    unsigned int VAO_02, VBO_02;
    glGenVertexArrays(1, &VAO_02);
    glBindVertexArray(VAO_02);

    glGenBuffers(1, &VBO_02);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_02);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture
    unsigned int texture_01, texture_02;
    texture_01 = loadTexture("wood_wall.png");
    //����ĳ�� ����Ԫ��ָ��һ���Ķ�����
    glActiveTexture(GL_TEXTURE0);
    //��glActiveTexture ֮�°�
    glBindTexture(GL_TEXTURE_2D, texture_01);

    texture_02 = loadTexture("wall_edge.png");
    //����ĳ�� ����Ԫ��ָ��һ���Ķ�����
    glActiveTexture(GL_TEXTURE1);
    //��glActiveTexture ֮�°�
    glBindTexture(GL_TEXTURE_2D, texture_02);




    lighting_Shader.use();

    lighting_Shader.setVec3("lampObjectColor", lampObjectColor);
    lighting_Shader.setInt("material.diffuse", 0);
    lighting_Shader.setInt("material.specular", 1);
    lighting_Shader.setFloat("material.shininess", 128 * 0.6f);
    lighting_Shader.setVec3("direction", directLight);
    lighting_Shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    lighting_Shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    lighting_Shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);  
    lighting_Shader.setVec3("dotLightPos", dotLightPos);
    lighting_Shader.setFloat("light.constant", 1.0f);
    lighting_Shader.setFloat("light.linear", 0.09f);
    lighting_Shader.setFloat("light.quadratic", 0.032f);
    lighting_Shader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
    lighting_Shader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));

    //������ȼ��
    glEnable(GL_DEPTH_TEST);

    glActiveTexture(GL_TEXTURE0);
    //��glActiveTexture ֮�°�
    glBindTexture(GL_TEXTURE_2D, texture_01);
    glActiveTexture(GL_TEXTURE1);
    //��glActiveTexture ֮�°�
    glBindTexture(GL_TEXTURE_2D, texture_02);

    while (!glfwWindowShouldClose(window))
    {

        //glm::vec3 spotLightPos = glm::vec3(0.0f, 0.0f, factor_unlimited);
        //glm::vec3 spotLightDir = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 spotLightPos = myCamera.getCameraPos();
        glm::vec3 spotLightDir = myCamera.getCameraFront();

        //ÿһ֡��ʱ���߼�
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glm::mat4 view;	// > �۲� ��ͨ���ƶ�ԭ�����ı�ռ䣩
        glm::mat4 projection;	// > �ü�

        processInput(window);

        glClearColor(0.2f, 0.7f, 0.3f, 0.3f);
        //�����ɫ�������Ȼ���
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        view = myCamera.getView();
        projection = myCamera.getProjection();

        //����VAO
        glBindVertexArray(VAO_01);

        lighting_Shader.use();
        lighting_Shader.setVec3("lampPos", lampPos);
        lighting_Shader.setMat4("view", glm::value_ptr(view));
        lighting_Shader.setMat4("projection", glm::value_ptr(projection));
        lighting_Shader.setVec3("spotLightPos", spotLightPos);
        lighting_Shader.setVec3("spotLightDir", spotLightDir);

        for (int i = 0; i < 10; i++)
        {
            glm::mat4 model_Lighting;	//�ֲ� > ���� (�������ǻ���ԭ�㶨��ģ��������������ġ� �ڱ�������û�б������ռ�)
            model_Lighting = glm::translate(model_Lighting, cubePositions[i]);
            if (rotate)
            {
                angle[i] += 1.0f * i * deltaTime;
            }
            else
                angle[i] += 0.0f;

            model_Lighting = glm::rotate(model_Lighting, glm::radians(angle[i]), glm::vec3(1.0f, 0.3f, 0.5f));
            lighting_Shader.setMat4("model_Lighting", glm::value_ptr(model_Lighting));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

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