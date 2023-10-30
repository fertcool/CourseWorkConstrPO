#ifndef TOBJECT_H
#define TOBJECT_H


#include "stdafx.h"

using namespace sf;

class TObject
{
public:
    TObject();
    TObject(float x, float y, float z, float scale, Texture* texture);
    float x, y, z;
    float scale;
    sf::Texture* texture;
    virtual void draw();
};

class Grass : public TObject { public: Grass(float x, float y, float z, float scale, Texture* texture); Grass(); };
class Flower1 :public TObject { public: Flower1(float x, float y, float z, float scale, Texture* texture); Flower1(); };
class Flower2 : public TObject { public:Flower2(float x, float y, float z, float scale, Texture* texture); Flower2(); };
class Mashroom : public TObject { public:Mashroom(float x, float y, float z, float scale, Texture* texture); Mashroom(); };
class Tree1 : public TObject { public:Tree1(float x, float y, float z, float scale, Texture* texture); Tree1(); };
class Tree2 : public TObject { public:Tree2(float x, float y, float z, float scale, Texture* texture); Tree2(); };

#endif