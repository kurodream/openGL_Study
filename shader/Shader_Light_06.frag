#version 330 core

out vec4 FragColor;

//done
uniform vec3 lampObjectColor;

void main()
{
	
	FragColor = vec4(lampObjectColor, 1.0f);
}