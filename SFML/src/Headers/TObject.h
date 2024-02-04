//заголовок класса обьектов на карте
#ifndef TOBJECT_H
#define TOBJECT_H

#include "stdafx.h"
#include "TextureManager.h"
class TObject
{
public:
	TObject();
	TObject(float x, float y, float z, float scale, TexturePtr texture);
	float x, y, z;//координаты расположения 
	float scale;//масштаб
	TexturePtr texture;//текстура

	//ф-я отрисовки
	virtual void draw();
};
//классы обьектов 
class Grass : public TObject {
public: Grass(float x, float y, float z, float scale, TexturePtr texture); Grass();
};

class Flower : public TObject {
public:Flower(float x, float y, float z, float scale, TexturePtr texture); Flower();
};

class Mashroom : public TObject {
public:Mashroom(float x, float y, float z, float scale, TexturePtr texture); Mashroom();
};
class Tree : public TObject {
public:Tree(float x, float y, float z, float scale, TexturePtr texture); Tree();
};

#endif