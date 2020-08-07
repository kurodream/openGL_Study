#version 330 core

//局部
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
//非3维空间
layout (location = 2) in vec2 aTexturePos;

out vec3 ourDirection;
out vec3 ourFragPos;
out vec3 ourNormal;
out vec2 ourTexturePos;
out vec3 ourDotLightPos;
out vec3 ourSpotLightPos;
out vec3 ourSpotLightDir;


//done
uniform mat4 model_Lighting;
//done
uniform mat4 view;
//done
uniform mat4 projection;
//done
//世界
uniform vec3 direction;
//done
//世界
uniform vec3 dotLightPos;
//世界
//done
uniform vec3 spotLightPos;
//世界
//done
uniform vec3 spotLightDir;

void main()
{
	gl_Position =projection * view * model_Lighting * vec4(aPos, 1.0);
	//齐次坐标有无 其实就是 平移矩阵能否发生作用
	ourDirection = vec3(view * vec4(direction, 0.0));
	ourFragPos = vec3(view * model_Lighting * vec4(aPos, 1.0));
	ourNormal = mat3(transpose(inverse(view * model_Lighting))) * aNormal;
	ourTexturePos = aTexturePos;
	ourDotLightPos = vec3(view * vec4(dotLightPos, 1.0));
	ourSpotLightPos = vec3(view * vec4(spotLightPos, 1.0));
	ourSpotLightDir = vec3(view * vec4(spotLightDir, 0.0));
}