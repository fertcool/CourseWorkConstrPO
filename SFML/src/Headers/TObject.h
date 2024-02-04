//��������� ������ �������� �� �����
#ifndef TOBJECT_H
#define TOBJECT_H

#include "stdafx.h"
#include "TextureManager.h"
class TObject
{
public:
	TObject();
	TObject(float x, float y, float z, float scale, TexturePtr texture);
	float x, y, z;//���������� ������������ 
	float scale;//�������
	TexturePtr texture;//��������

	//�-� ���������
	virtual void draw();
};
//������ �������� 
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