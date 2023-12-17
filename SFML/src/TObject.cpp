#include "stdafx.h"
#include "TObject.h"

TObject::TObject() :x(0), y(0), z(0), scale(0), texture(nullptr) {};
TObject::TObject(float x, float y, float z, float scale, Texture* texture) :
	x(x), y(y), z(z), scale(scale), texture(texture)
{};

//базовая ф-я отрисовки
void TObject::draw()
{
	float plant[] = { -0.5, 0, 0,  0.5, 0, 0,  0.5, 0, 1,  -0.5, 0, 1,
					0, -0.5, 0,  0, 0.5, 0,  0, 0.5, 1,  0, -0.5, 1 };//массив вершин (две перекрестные плоскости)
	float plantUV[] = { 0, 1,  1, 1,  1, 0,  0, 0,  0, 1,  1, 1,  1, 0,  0, 0 };//массив вершин текстур
	GLuint plantInd[] = { 0, 1, 2,  2, 3, 0,  4, 5, 6,  6, 7, 4 };//массив индексов
	int plantIndCnt = sizeof(plantInd) / sizeof(GLuint);//количество индексов
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, plant);//загрузка вершин
	glTexCoordPointer(2, GL_FLOAT, 0, plantUV);//загрузка координат текстур
	glNormal3f(0, 0, 1);//нормаль
	Texture::bind(texture);//связб с текстурой
	glPushMatrix();
		glTranslatef(x, y, z);//перемещение по заданным координатам
		glScalef(scale, scale, scale);//масштабирование
		glDrawElements(GL_TRIANGLES, plantIndCnt, GL_UNSIGNED_INT, plantInd);//отрисовка
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

Grass::Grass(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};
Grass::Grass() :TObject() {};

Flower::Flower(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};
Flower::Flower() :TObject() {};

Mashroom::Mashroom(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};
Mashroom::Mashroom() :TObject() {};

Tree::Tree(float x, float y, float z, float scale, Texture* texture) :TObject(x, y, z, scale, texture) {};
Tree::Tree() :TObject() {};
