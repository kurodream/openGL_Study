#version 330 core

out vec4 FragColor;

uniform vec3 sourceObject;

void main()
{
	FragColor = vec4(sourceObject, 1.0);
}