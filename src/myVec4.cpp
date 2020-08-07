#include"shader.h"

Vec4::Vec4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Vec4::setVec4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float* Vec4::getVec4() const
{
	static float bx_vec4[4];
	bx_vec4[0] = x;
	bx_vec4[1] = y;
	bx_vec4[2] = z;
	bx_vec4[3] = w;

	return bx_vec4;
}