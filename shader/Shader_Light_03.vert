#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 ourFragPos;
out vec3 ourNormal;
out vec3 ourLampObjectPos;
//out vec3 ourCameraPos;

//done
uniform mat4 model_Lighting;
//donw
uniform mat4 view;
//done
uniform mat4 projection;
//done
uniform vec3 lampObjectPos;
//done
//uniform vec3 cameraPos;

void main()
{
	gl_Position = projection * view * model_Lighting * vec4(aPos, 1.0);
	ourFragPos = vec3(view * model_Lighting * vec4(aPos, 1.0));
	ourNormal = mat3(transpose(inverse(view * model_Lighting))) * aNormal;
	ourLampObjectPos = vec3(view * vec4(lampObjectPos, 1.0));
	//ourCameraPos = vec3(view * vec4(cameraPos, 1.0));
}