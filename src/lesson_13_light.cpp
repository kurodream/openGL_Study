#include"shader.h"
#include"bx.h"
#include"camera.h"
#include"stb_image.h"

//用于控制光源的距离
extern float factor_unlimited;
//用于控制是否开始旋转
extern bool rotate;
extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;
extern Camera myCamera;



int lesson_13_light()
{
    //变量初始化
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

    
    //光源
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 dir_Light_Dir;
    glm::vec3 pointLightPositions[] = {
glm::vec3(0.7f,  0.2f,  2.0f),
glm::vec3(2.3f, -3.3f, -4.0f),
glm::vec3(-4.0f,  2.0f, -12.0f),
glm::vec3(0.0f,  0.0f, -3.0f)
    };
    glm::vec3 spot_Light_Pos;
    glm::vec3 spot_Light_Dir;
    
    //旋转角度
    float angle[10] = { 0.0f };

    //每帧时间逻辑
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

    //注册回调函数
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	//设置鼠标不可见
    glfwSetCursorPosCallback(window, mouse_callback);	//非阻塞，异步（应该） 回调。这个glfwSetCursorPosCallback（）是注册回调函数。事件为鼠标移动。
    glfwSetScrollCallback(window, scroll_callback);
    
    Shader lighting_Shader = Shader("Shader_Light_09.vert", "Shader_Light_09.frag");
    Shader lamp_Shader = Shader("Shader_Light_08.vert", "Shader_Light_08.frag");

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
    unsigned int texture_01, texture_02;
    texture_01 = loadTexture("wood_wall.png");

    texture_02 = loadTexture("wall_edge.png");


    lighting_Shader.use();

    //material
    lighting_Shader.setInt("material.diffuse", 0);
    lighting_Shader.setInt("material.specular", 1);
    lighting_Shader.setFloat("material.shininess", 128 * 0.6f);

    //dirlight
    lighting_Shader.setVec3("dirlight.color", color);
    lighting_Shader.setVec3("dirlight.ambient", 0.2f, 0.2f, 0.2f);
    lighting_Shader.setVec3("dirlight.diffuse", 0.5f, 0.5f, 0.5f);
    lighting_Shader.setVec3("dirlight.specular", 1.0f, 1.0f, 1.0f);

    //pointlight * 4
    for (int i = 0; i < 4; i++)
    {
        //准备格式
        std::stringstream fmt;
        fmt << "pointlight[" << i << "].";
        std::string targetString = fmt.str();
        std::string str_color = targetString + "color";
        lighting_Shader.setVec3(str_color, color);

        std::string str_position = targetString + "position";
        lighting_Shader.setVec3(str_position, pointLightPositions[i]);

        std::string str_ambient = targetString + "ambient";
        lighting_Shader.setVec3(str_ambient, 0.2f, 0.2f, 0.2f);

        std::string str_diffuse = targetString + "diffuse";
        lighting_Shader.setVec3(str_diffuse, 0.5f, 0.5f, 0.5f);

        std::string str_specular = targetString + "specular";
        lighting_Shader.setVec3(str_specular, 1.0f, 1.0f, 1.0f);

        std::string str_constant = targetString + "constant";
        lighting_Shader.setFloat(str_constant, 1.0f);

        std::string str_linear = targetString + "linear";
        lighting_Shader.setFloat(str_linear, 0.09f);

        std::string str_quadratic = targetString + "quadratic";
        lighting_Shader.setFloat(str_quadratic, 0.032f);

    }

    //spotlight
    lighting_Shader.setVec3("spotlight.color", color);
    lighting_Shader.setVec3("spotlight.ambient", 0.2f, 0.2f, 0.2f);
    lighting_Shader.setVec3("spotlight.diffuse", 0.5f, 0.5f, 0.5f);
    lighting_Shader.setVec3("spotlight.specular", 1.0f, 1.0f, 1.0f);
    lighting_Shader.setFloat("spotlight.constant", 1.0f);
    lighting_Shader.setFloat("spotlight.linear", 0.09f);
    lighting_Shader.setFloat("spotlight.quadratic", 0.032f);
    lighting_Shader.setFloat("spotlight.cutOff", glm::cos(glm::radians(12.5f)));
    lighting_Shader.setFloat("spotlight.outerCutOff", glm::cos(glm::radians(17.5f)));

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
        /*
        -------------------------
        处理变量
         -------------------------
        */

        //检测输入
        processInput(window);

        //矩阵初始化
        //观察矩阵 和 投影矩阵
        glm::mat4 view;	// > 观察 （通过移动原点来改变空间）
        glm::mat4 projection;	// > 裁剪
        view = myCamera.getView();
        projection = myCamera.getProjection();
        //向量初始化
        glm::vec3 spot_Light_Pos = myCamera.getCameraPos();
        glm::vec3 spot_Light_Dir = myCamera.getCameraFront();
        //方向光模拟日升日落
        glm::vec3 dir_Light_Dir = glm::vec3(glm::cos(glm::radians(factor_unlimited)), glm::sin(glm::radians(factor_unlimited)), 0.0f);

        //每一帧的时间逻辑
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        /*
         -------------------------
        开始画图工作
         -------------------------
        */

        glClearColor(0.0f, 0.0f, 0.0f, 0.3f);
        //清除颜色缓存和深度缓存
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //更新VAO
        glBindVertexArray(VAO_01);

        lighting_Shader.use();
        lighting_Shader.setMat4("view", glm::value_ptr(view));
        lighting_Shader.setMat4("projection", glm::value_ptr(projection));
        lighting_Shader.setVec3("view_Pos", myCamera.getCameraPos());
        lighting_Shader.setVec3("spotlight.position", spot_Light_Pos);
        lighting_Shader.setVec3("spotlight.direction", spot_Light_Dir);
        lighting_Shader.setVec3("dirlight.direction", dir_Light_Dir);

        for (int i = 0; i < 10; i++)
        {
            //物体model
            glm::mat4 model_Obj;
            model_Obj = glm::translate(model_Obj, cubePositions[i]); 	//局部 > 世界 (本来点是基于原点定义的，即理解成物体中心。 在本例子中没有变成世界空间)

            if (rotate)
            {
                angle[i] += 1.0f * i * deltaTime;
            }
            else
                angle[i] += 0.0f;

            model_Obj = glm::rotate(model_Obj, glm::radians(angle[i]), glm::vec3(1.0f, 0.3f, 0.5f));
            lighting_Shader.setMat4("model_Obj", glm::value_ptr(model_Obj));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //用于标识点光源
        for (int i = 0; i < 4; i++)
        {
            glm::mat4 model_Lamp;
            model_Lamp = glm::translate(model_Lamp, pointLightPositions[i]);
            glBindVertexArray(VAO_02);
            lamp_Shader.use();
            lamp_Shader.setVec3("lampObjectColor", color);
            lamp_Shader.setMat4("model_Lamp", glm::value_ptr(model_Lamp));
            lamp_Shader.setMat4("view", glm::value_ptr(view));
            lamp_Shader.setMat4("projection", glm::value_ptr(projection));

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