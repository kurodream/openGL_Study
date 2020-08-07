#version 330 core

in vec3 ourFragPos;
in vec3 ourNormal;
in vec3 ourLampObjectPos;
//in vec3 ourCameraPos; 因为就是在view空间原点

out vec4 FragColor;

//材质对每个光的强度
struct Material 
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

//光源对每个光的强度
struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

//done
uniform vec3 lightingObjectColor;
//done
uniform vec3 lampObjectColor;
//done
uniform Material material;
//done
uniform Light light;

void main()
{
	//ambient
	vec3 ambient = lampObjectColor * light.ambient * lightingObjectColor * material.ambient;
	//diff
	vec3 lampDir = normalize(ourLampObjectPos - ourFragPos);
	vec3 normal = normalize(ourNormal);
	float diffStrength = max(dot(lampDir, normal), 0.0);
	vec3 diff = lampObjectColor * light.diffuse * lightingObjectColor * material.diffuse * diffStrength;
	//specular
	vec3 cameraDir = normalize(-ourFragPos);
	vec3 reflectDir = reflect(-lampDir, normal);
	float specularStrength = pow(max(dot(cameraDir, reflectDir), 0.0), material.shininess);
	vec3 specular = lampObjectColor* light.specular * lightingObjectColor * material.specular * specularStrength;

	vec3 result = ambient + diff + specular;
	FragColor = vec4(result, 1.0);
}

