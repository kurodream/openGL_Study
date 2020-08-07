//片元着色器代码
#version 330 core
out vec4 FragColor;
//in vec3 ourColor;
uniform vec4 ourColor;
void main()
{
	FragColor = ourColor;
}