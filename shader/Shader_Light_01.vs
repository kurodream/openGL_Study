#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 ourNormal;
out vec3 fragPos;
out vec3 ourCameraPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPos;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	fragPos = vec3( model * vec4(aPos, 1.0));
	// Õý¹æ¾ØÕó
	ourNormal = mat3(transpose(inverse(model))) * aNormal;
	ourCameraPos = cameraPos;

}