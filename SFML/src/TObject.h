//заголовок класса обьектов на карте
#ifndef TOBJECT_H
#define TOBJECT_H

#include "stdafx.h"

class TObject
{
public:
	TObject();
	TObject(float x, float y, float z, float scale, Texture* texture);
	float x, y, z;//координаты расположения 
	float scale;//масштаб
	Texture* texture;//текстура

	//ф-я отрисовки
	virtual void draw();
};
//классы обьектов 
class Grass : public TObject {
public: Grass(float x, float y, float z, float scale, Texture* texture); Grass();
};

class Flower : public TObject {
public:Flower(float x, float y, float z, float scale, Texture* texture); Flower();
};

class Mashroom : public TObject {
public:Mashroom(float x, float y, float z, float scale, Texture* texture); Mashroom();
};
class Tree : public TObject {
public:Tree(float x, float y, float z, float scale, Texture* texture); Tree();
};

#endif