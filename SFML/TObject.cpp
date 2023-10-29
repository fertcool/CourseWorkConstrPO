#include "TObject.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace sf;

TObject::TObject(float x, float y, float z, float scale, Texture* texture) : x(x), y(y), z(z), scale(scale), texture(texture) {};

void TObject::draw()
{
	GLuint plantInd[] = { 0, 1, 2,  2, 3, 0,  4, 5, 6,  6, 7, 4 };
	int plantIndCnt = sizeof(plantInd) / sizeof(GLuint);
	Texture::bind(texture);
	glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(scale, scale, scale);
		glDrawElements(GL_TRIANGLES, plantIndCnt, GL_UNSIGNED_INT, plantInd);
	glPopMatrix();
}
Field::Field(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};

Grass::Grass(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};

Flower1::Flower1(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};

Flower2::Flower2(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};

Mashroom::Mashroom(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};

Tree1::Tree1(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};

Tree2::Tree2(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};
