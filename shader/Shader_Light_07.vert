#version 330 core

//�ֲ�
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
//��3ά�ռ�
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
//����
uniform vec3 direction;
//done
//����
uniform vec3 dotLightPos;
//����
//done
uniform vec3 spotLightPos;
//����
//done
uniform vec3 spotLightDir;

void main()
{
	gl_Position =projection * view * model_Lighting * vec4(aPos, 1.0);
	//����������� ��ʵ���� ƽ�ƾ����ܷ�������
	ourDirection = vec3(view * vec4(direction, 0.0));
	ourFragPos = vec3(view * model_Lighting * vec4(aPos, 1.0));
	ourNormal = mat3(transpose(inverse(view * model_Lighting))) * aNormal;
	ourTexturePos = aTexturePos;
	ourDotLightPos = vec3(view * vec4(dotLightPos, 1.0));
	ourSpotLightPos = vec3(view * vec4(spotLightPos, 1.0));
	ourSpotLightDir = vec3(view * vec4(spotLightDir, 0.0));
}