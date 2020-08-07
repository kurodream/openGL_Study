#version 330 core

//局部
layout (location = 0) in vec3 aPos;
//局部
layout (location = 1) in vec3 aNormal;

layout (location = 2) in vec2 aTextureCoord;

//世界
out vec3 ourFrag_Pos;
//世界
out vec3 ourView_Pos;
//世界
out vec3 ourNormal_Dir;

out vec2 ourTexture_Coord;

//done
uniform mat4 model_Obj;
//done
uniform mat4 view;
//done
uniform mat4 projection;
//done
uniform vec3 view_Pos;

void main()
{
	gl_Position = projection * view * model_Obj * vec4(aPos, 1.0);
	ourFrag_Pos = vec3(model_Obj * vec4(aPos, 1.0));
	ourView_Pos = view_Pos;
	ourNormal_Dir = mat3(transpose(inverse(model_Obj))) * aNormal;
	ourTexture_Coord = aTextureCoord;
}