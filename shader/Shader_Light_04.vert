#version 330 core

layout (location = 0) in vec3 aPos;

//done
uniform mat4 model_Lamp;
//doen
uniform mat4 view;
//done
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model_Lamp * vec4(aPos, 1.0);
}