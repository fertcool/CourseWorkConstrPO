#include "stdafx.h"
#include "TObject.h"

TObject::TObject() :x(0), y(0), z(0), scale(0), texture(nullptr) {};
TObject::TObject(float x, float y, float z, float scale, Texture* texture) :
	x(x), y(y), z(z), scale(scale), texture(texture)
{};

void TObject::draw()
{
	float plant[] = { -0.5, 0, 0,  0.5, 0, 0,  0.5, 0, 1,  -0.5, 0, 1,
					0, -0.5, 0,  0, 0.5, 0,  0, 0.5, 1,  0, -0.5, 1 };
	float plantUV[] = { 0, 1,  1, 1,  1, 0,  0, 0,  0, 1,  1, 1,  1, 0,  0, 0 };
	GLuint plantInd[] = { 0, 1, 2,  2, 3, 0,  4, 5, 6,  6, 7, 4 };
	int plantIndCnt = sizeof(plantInd) / sizeof(GLuint);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, plant);
	glTexCoordPointer(2, GL_FLOAT, 0, plantUV);
	glColor3f(0.7, 0.7, 0.7);
	glNormal3f(0, 0, 1);
	Texture::bind(texture);
	glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(scale, scale, scale);
		glDrawElements(GL_TRIANGLES, plantIndCnt, GL_UNSIGNED_INT, plantInd);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

Grass::Grass(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};
Grass::Grass() :TObject() {};

Flower1::Flower1(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};
Flower1::Flower1() :TObject() {};

Flower2::Flower2(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};
Flower2::Flower2() :TObject() {};

Mashroom::Mashroom(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};
Mashroom::Mashroom() :TObject() {};

Tree1::Tree1(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};
Tree1::Tree1() :TObject() {};

Tree2::Tree2(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};
Tree2::Tree2() :TObject() {};
