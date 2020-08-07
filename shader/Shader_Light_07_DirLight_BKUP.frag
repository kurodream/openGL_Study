#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
};

//view�ռ�
//����ⷽ��
in vec3 ourDirection;
//ƬԪλ��
in vec3 ourFragPos;
//������
in vec3 ourNormal;
//UV����
in vec2 ourTexturePos;
//���Դλ��
in vec3 ourDotLightPos;
//�۹��λ��
in vec3 ourSpotLightPos;
//�۹�Ʒ���
in vec3 ourSpotLightDir;

out vec4 FragColor;


//done
uniform vec3 lampObjectColor;
//done
uniform Material material;
//done
uniform Light light;

vec3 CalcDirLight(Light light, vec3 ourDirection, vec3 normal_Dir, vec3 ourFragPos, Material material, vec2 ourTexture_Coord);	//������Ϣ��Ԫ��,ע�ⶼ��δ��һ����.�Լ�����

void main()
{
	//���������

	vec3 result = CalcDirLight(light, ourDirection, ourNormal, ourFragPos, material, ourTexturePos);
	FragColor = vec4(result, 1.0);

	
}

vec3 CalcDirLight(Light light, vec3 ourDirection, vec3 normal, vec3 ourFragPos, Material material, vec2 ourTexture_Coord)
{
	//�����

	// ���䷽��
	vec3 in_Light_Dir = normalize(ourDirection);
	// ������
	vec3 normal_Dir = normalize(ourNormal);
	//���䷽��
	vec3 out_Light_Dir = reflect(in_Light_Dir, normal_Dir);
	//���������
	vec3 camera_Dir = normalize(-ourFragPos);

	//���� + �����

	//ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, ourTexture_Coord));

	//diffuse
	float diffuseStrength = max(dot(out_Light_Dir, normal_Dir), 0.0);
	vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, ourTexture_Coord)) * diffuseStrength;

	//specular
	float specularStrength = pow(max(dot(out_Light_Dir, camera_Dir), 0.0), material.shininess);
	vec3 specular = light.specular * vec3(texture(material.specular, ourTexture_Coord)) * specularStrength;

	return (ambient + diffuse + specular);
}