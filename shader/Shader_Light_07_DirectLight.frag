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

//view空间
//方向光方向
in vec3 ourDirection;
//片元位置
in vec3 ourFragPos;
//法向量
in vec3 ourNormal;
//UV坐标
in vec2 ourTexturePos;
//点光源位置
in vec3 ourDotLightPos;
//聚光灯位置
in vec3 ourSpotLightPos;
//聚光灯方向
in vec3 ourSpotLightDir;

out vec4 FragColor;


//done
uniform vec3 lampObjectColor;
//done
uniform Material material;
//done
uniform Light light;

void main()
{
	//入射光

	// 入射方向
	vec3 in_Light_Dir = normalize(ourDirection);
	// 法向量
	vec3 normal_Dir = normalize(ourNormal);
	//出射方向
	vec3 out_Light_Dir = reflect(in_Light_Dir, normal_Dir);
	//摄像机方向
	vec3 camera_Dir = normalize(-ourFragPos);


	//材质 + 出射光

	//ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, ourTexturePos));

	//diffuse
	float diffuseStrength = max(dot(out_Light_Dir, normal_Dir), 0.0);
	vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, ourTexturePos)) * diffuseStrength;

	//specular
	float specularStrength = pow(max(dot(out_Light_Dir, camera_Dir), 0.0), material.shininess);
	vec3 specular = light.specular * vec3(texture(material.specular, ourTexturePos)) * specularStrength;

	vec3 result =  lampObjectColor * (ambient + diffuse + specular);
	FragColor = vec4(result, 1.0);

	
}