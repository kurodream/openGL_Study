#include"bx.h"
#include"shader.h"
#include"camera.h"
#include"stb_image.h"

float factor = 0.5f;
float factor_unlimited = 0.0f;
float deltaTime = 0.0f;
float lastTime = 0.0f;
float cameraSpeed;
bool rotate = false;
bool R_Flag = false;
extern Camera myCamera;
extern enum Camera_Move_Mode;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	bool isAD = true;

	float currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
	cameraSpeed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		factor += 0.01f;
		if (factor > 1.0f)
			factor = 1.0f;
		std::cout << factor << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		factor -= 0.01f;
		if (factor < 0.0f)
			factor = 0.0f;
		std::cout << factor << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		factor_unlimited -= deltaTime * 5.00f;
		std::cout << factor_unlimited << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		factor_unlimited += deltaTime * 5.0f;
		std::cout << factor_unlimited << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		myCamera.moveCamera(cameraSpeed, FORWARD);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		myCamera.moveCamera(cameraSpeed, BACKWARD);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		myCamera.moveCamera(cameraSpeed, LEFT);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		myCamera.moveCamera(cameraSpeed, RIGHT);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		myCamera.moveCamera(cameraSpeed, UP);
	}

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		myCamera.moveCamera(cameraSpeed, DOWN);
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		if (!R_Flag)
		{
			rotate = !rotate;
			R_Flag = true;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE) 
	{
		R_Flag = false;
	}

}


GLFWwindow* initializeWindow()
{
	//初始化glfw窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	//指定主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	//指定子版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//使用核心模式（可编程渲染管道的模式）

	GLFWwindow* window = glfwCreateWindow(1280, 720, "LearnOpenGL", NULL, NULL);	//创建窗口

	return window;
}

//float rotate_degree()
//{
//	return glm::radians(rotate_factor);
//}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	static float lastX = 400, lastY = 300;
	static float yaw = 0.0f, pitch = 0.0f;
	static bool firstMouse = true;
	
	if (firstMouse)	//用于防止初始位置不固定
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	//得到鼠标位移
	double xOffset = lastX - xpos;
	double yOffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	//换算灵敏度
	float sensitivity = 0.5f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	//限定抬头 低头角度
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	glm::vec3 front;
	front.x = -sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = -cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	myCamera.rotateCamera(glm::normalize(front));
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	float fov = myCamera.getFov();
	if (fov >= 1.0 && fov <= 45.0)
		myCamera.setFov(fov -= yoffset);
	if (fov <= 1.0)
		myCamera.setFov(1.0);
	if (fov >= 45.0)
		myCamera.setFov(45.0);
}

unsigned int loadTexture(const char* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	//激活在while中使用

	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &nrChannel, 0);
	if (data)
	{
		//这里相当于开辟一个空间并取名
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLint format = nrChannel == 3 ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "无法加载问题，请检查代码或资源是否有误。" << std::endl;
	}
	stbi_image_free(data);

	return textureID;
}

