#ifndef MAP_H
#define MAP_H

#include "camera.h"
#include "structs.h"
#include "TObject.h"

#include "stdafx.h"

using namespace sf;

//enum TObjType
//{
//    grass, flower1, flower2,
//    mashroom, ree1, tree2
//};
class Map
{
    int mapW, mapH;
    Texture* texfield;

    TCell** vertexes;
    TCell** normals;
    GLuint*** indexes;
    TUV** UV;

    TObject** objects;
    int numObj;

    void CalcNormals(TCell a, TCell b, TCell c, TCell* n);
    void MapCreateHill(int posX, int posY, int rad, int height);



public:

    Map(int mapW, int mapH, Texture* texfield);
    ~Map();
    float MapGetHeight(float x, float y);
    bool IsCoordInMap(float x, float y);
    void MapShow(Camera& camera, Window& window);

    static void LoadTexture(std::string filename, Texture& texture);

};
#endif