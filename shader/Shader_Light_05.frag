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
};

in vec3 ourLampPos;
in vec3 ourFragPos;
in vec3 ourNormal;
in vec2 ourTexturePos;

out vec4 FragColor;


//done
uniform vec3 lampObjectColor;
//done
uniform Material material;
//done
uniform Light light;

void main()
{
	//³öÉä¹â
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, ourTexturePos));

	vec3 lightDir = normalize(ourLampPos - ourFragPos);
	vec3 normlDir = normalize(ourNormal);
	float diffuseStrength = max(dot(lightDir, normlDir), 0.0);
	vec3 diffuse = light.diffuse * (diffuseStrength * vec3(texture(material.diffuse, ourTexturePos)));

	
	vec3 reflectDir = reflect(-lightDir, normlDir);
	vec3 cameraDir = normalize(- ourFragPos);
	float specularStrength = pow(max(dot(reflectDir, cameraDir), 0.0), material.shininess);

	vec3 specular = light.specular * (specularStrength * vec3(texture(material.specular, ourTexturePos)));

	vec3 result = (ambient + diffuse + specular) * lampObjectColor;
	FragColor = vec4(result, 1.0);
}