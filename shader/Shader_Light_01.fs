#version 330 core

in vec3 ourNormal;
in vec3 fragPos;
in vec3 ourCameraPos;

out vec4 FragColor;

uniform vec3 reflectObject;
uniform vec3 sourceObject;
uniform vec3 sourcePos;

void main()
{
	//ambient
	float ambientStrength = 0.3;
	vec3 ambient = sourceObject * ambientStrength;

	//diff
	vec3 normal = normalize(ourNormal);
	vec3 lightDir = normalize(sourcePos - fragPos);
	float diffStrength = max(dot(normal, lightDir), 0.0);
	vec3 diff = sourceObject * diffStrength;

	//specular
	float specularFactor = 1.0;
	vec3 cameraDir = normalize(ourCameraPos - fragPos);
	//计算出射向量
	vec3 reflectDir  = reflect(-lightDir, normal);
	float specularStrength = pow(max(dot(reflectDir, cameraDir), 0.0), 32);
	vec3 specular = sourceObject * specularStrength * specularFactor;

	vec3 result = reflectObject * (ambient + diff + specular);
	FragColor = vec4(result, 1.0);
}