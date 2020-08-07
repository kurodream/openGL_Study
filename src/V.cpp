#include"bx.h"
#include"shader.h"
#include"V.h"

myVAO::myVAO()
{
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}
int myVAO::getID() const
{
	return ID;
}

myVBO::myVBO(void* vertext)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertext), vertext, GL_STATIC_DRAW);
}

int myVBO::getID() const
{
	return ID;
}

myEBO::myEBO(float* indice)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indice), indice, GL_STATIC_DRAW);
}

int myEBO::getID() const
{
	return ID;
}