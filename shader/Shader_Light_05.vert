#version 330 core

//局部
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
//非3维空间
layout (location = 2) in vec2 aTexturePos;

out vec3 ourLampPos;
out vec3 ourFragPos;
out vec3 ourNormal;
out vec2 ourTexturePos;

//done
uniform mat4 model_Lighting;
//done
uniform mat4 view;
//done
uniform mat4 projection;
//done
//世界
uniform vec3 lampPos;

void main()
{
	gl_Position =projection * view * model_Lighting * vec4(aPos, 1.0);
	ourLampPos = vec3(view * vec4(lampPos, 1.0));
	ourFragPos = vec3(view * model_Lighting * vec4(aPos, 1.0));
	ourNormal = mat3(transpose(inverse(view * model_Lighting))) * aNormal;
	ourTexturePos = aTexturePos;
}