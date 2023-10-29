#pragma once
#include "structs.h"
#include "TObject.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace sf;

enum TObjType
{
    grass, flower1, flower2,
    mashroom, ree1, tree2
};
class Map
{
    int mapW, mapH;
    Texture* texfield;

    std::vector<std::vector<TCell>> vertexes;
    std::vector<std::vector<TCell>> normals;
    std::vector<std::vector<std::vector<GLuint>>> indexes;
    /*[mapW - 1] [mapH - 1] [6]*/
    std::vector<std::vector<TUV>> UV;

    TObject** objects;

    void CalcNormals(TCell a, TCell b, TCell c, TCell* n);
    void MapCreateHill(int posX, int posY, int rad, int height);

public:

    Map(int mapW, int mapH, Texture* texfield);
    float MapGetHeight(float x, float y);
    bool IsCoordInMap(float x, float y);
    void MapShow();

};