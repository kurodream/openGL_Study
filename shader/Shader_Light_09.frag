#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirLight
{
	vec3 color;
	//����
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};

struct PointLight
{
	vec3 color;
	//����
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec3 color;
	//����
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outerCutOff;
};

in vec3 ourFrag_Pos;
in vec3 ourView_Pos;
in vec3 ourNormal_Dir;
in vec2 ourTexture_Coord;

out vec4 FragColor;


//done
uniform Material material;
//done
uniform DirLight dirlight;
//done
#define NR_POINT_LIGHTS 4
uniform PointLight pointlight[NR_POINT_LIGHTS];
//done
uniform SpotLight spotlight;

vec3 CalcDirLight(DirLight light, vec3 normal_Dir, vec3 frag_Pos, vec3 view_Pos, Material material, vec2 ourTexture_Coord);	//������Ϣ��Ԫ��,ע�ⶼ��δ��һ����.�Լ�����
vec3 CalcPointLight(PointLight light, vec3 normal_Dir, vec3 frag_Pos, vec3 view_Pos, Material material, vec2 ourTexture_Coord);
vec3 CalcSpotLight(SpotLight light, vec3 normal_Dir, vec3 frag_Pos, vec3 view_Pos, Material material, vec2 ourTexture_Coord);



void main()
{
	vec3 result = vec3(0.0, 0.0, 0.0);
	vec3 dir_Light = CalcDirLight(dirlight, ourNormal_Dir, ourFrag_Pos, ourView_Pos, material, ourTexture_Coord);
	result += dir_Light;
	for(int i = 0; i < 4; i++)
	{
		vec3 point_Light = CalcPointLight(pointlight[i], ourNormal_Dir, ourFrag_Pos, ourView_Pos, material, ourTexture_Coord);
		result += point_Light;
	}
	vec3 spot_Light = CalcSpotLight(spotlight, ourNormal_Dir, ourFrag_Pos, ourView_Pos, material, ourTexture_Coord);
	result += spot_Light;
	
	FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal_Dir, vec3 frag_Pos, vec3 view_Pos, Material material, vec2 ourTexture_Coord)
{
	//����
	vec3 in_Dir = normalize(light.direction);
	//������
	normal_Dir = normalize(normal_Dir);
	//����
	vec3 out_Dir = reflect(in_Dir, normal_Dir);
	//�۲�
	vec3 view_Dir = normalize(view_Pos - frag_Pos);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, ourTexture_Coord));

	float diffuse_Str = max(dot(out_Dir, normal_Dir), 0.0);
	vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, ourTexture_Coord)) * diffuse_Str;

	float specular_Str = pow(max(dot(view_Dir, out_Dir),0.0), material.shininess);
	vec3 specular = light.specular * vec3(texture(material.specular, ourTexture_Coord)) * specular_Str;

	return (ambient + diffuse + specular) * light.color;
}

vec3 CalcPointLight(PointLight light, vec3 normal_Dir, vec3 frag_Pos, vec3 view_Pos, Material material, vec2 ourTexture_Coord)
{
	//����
	vec3 in_Dir = normalize(frag_Pos - light.position);
	//������
	normal_Dir = normalize(normal_Dir);
	//����
	vec3 out_Dir = reflect(in_Dir, normal_Dir);
	//�۲�
	vec3 view_Dir = normalize(view_Pos - frag_Pos);
	//���Դ����
	float distance = length(light.position - frag_Pos);
	//˥��
	float attenuation = 1 / (light.constant + light.linear * distance + light.quadratic *(distance * distance));

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, ourTexture_Coord));

	float diffuse_Str = max(dot(out_Dir, normal_Dir), 0.0);
	vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, ourTexture_Coord)) * diffuse_Str;

	float specular_Str = pow(max(dot(view_Dir, out_Dir),0.0), material.shininess);
	vec3 specular = light.specular * vec3(texture(material.specular, ourTexture_Coord)) * specular_Str;

	return (ambient + diffuse + specular) * attenuation * light.color;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal_Dir, vec3 frag_Pos, vec3 view_Pos, Material material, vec2 ourTexture_Coord)
{
	//����
	vec3 in_Dir = normalize(frag_Pos - light.position);
	//������
	normal_Dir = normalize(normal_Dir);
	//����
	vec3 out_Dir = reflect(in_Dir, normal_Dir);
	//�۲�
	vec3 view_Dir = normalize(view_Pos - frag_Pos);
	//�۹�ƹ�Դ����
	float distance = length(frag_Pos - light.position);
	//˥��
	float attenuation = 1 / (light.constant + light.linear * distance + light.quadratic *(distance * distance));
	//�۹�Ʒ����һ��
	vec3 spot_Dir = normalize(light.direction);
	//�۹��-ƬԪ�н�cosֵ
	float theta = dot(spot_Dir, in_Dir);
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon , 0.0, 1.0);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, ourTexture_Coord));

	float diffuse_Str = max(dot(out_Dir, normal_Dir), 0.0);
	vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, ourTexture_Coord)) * diffuse_Str;

	float specular_Str = pow(max(dot(view_Dir, out_Dir),0.0), material.shininess);
	vec3 specular = light.specular * vec3(texture(material.specular, ourTexture_Coord)) * specular_Str;

	diffuse *= intensity;
	specular *= intensity;

	return (ambient + diffuse + specular) * attenuation * light.color;

}