#include"shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	/*��ȡ�ļ�*/
		//in
	std::string vertexCode;
	std::string fragmentCode;
	//out
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//ȷ���ļ���������쳣
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//���ļ�
		vShaderFile.open(vertexPath); // �������ļ����ݶ���buffer��
		fShaderFile.open(fragmentPath);
		std::stringstream vertexStream, fragmentStream;
		//��ȡ
		vertexStream << vShaderFile.rdbuf();	//��buffer�е����ݷ��� stringstream������
		fragmentStream << fShaderFile.rdbuf();
		//�ر��ļ�
		vShaderFile.close();
		fShaderFile.close();
		//��stringstream���string
		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "��ȡ����" << std::endl;
	}

	/*�����ļ�*/
	const char* vertexCode_C = vertexCode.c_str();
	const char* fragmentCode_C = fragmentCode.c_str();
	unsigned int vertexShader, fragmentShader;
	int success;
	char infolog[512];

	// shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode_C, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode_C, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
	}

	//program
	ID = glCreateProgram(); // ������� glCreateProgram() �ᴴ��һ������������ Shader���캯����program���󡣴�������VS��FSҲһ����
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infolog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec4(const std::string& name, glm::vec4 value) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
}
void Shader::setVec4(const std::string& name, float value[]) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value[0], value[1], value[2], value[3]);
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()),value.x, value.y, value.z);
}

void Shader::setVec3(const std::string& name, float value0, float value1, float value2) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value0, value1, value2);
}

void Shader::setMat4(const std::string& name, float value[]) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value);
}