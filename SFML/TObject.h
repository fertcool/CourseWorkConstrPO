#pragma once
using namespace sf;
class TObject
{
public:
    TObject(float x, float y, float z, float scale, Texture* texture);
    float x, y, z;
    float scale;
    Texture* texture;
    virtual void draw();
};
class Field : TObject { Field(float x, float y, float z, float scale, Texture* texture); };
class Grass : TObject { Grass(float x, float y, float z, float scale, Texture* texture); };
class Flower1 : TObject { Flower1(float x, float y, float z, float scale, Texture* texture); };
class Flower2 : TObject { Flower2(float x, float y, float z, float scale, Texture* texture); };
class Mashroom : TObject { Mashroom(float x, float y, float z, float scale, Texture* texture); };
class Tree1 : TObject { Tree1(float x, float y, float z, float scale, Texture* texture); };
class Tree2 : TObject { Tree2(float x, float y, float z, float scale, Texture* texture); };
