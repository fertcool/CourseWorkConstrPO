#ifndef MAP_H
#define MAP_H

#define Access2(i, j) (i) * (mapH - 1) + j
#define Access3(i, j, k) (i) * (mapH - 1) * 6 + (j) * 6 + k

#include "structs.h"
#include "TObject.h"
#include "TextureManager.h"

class Map
{
    int mapW, mapH;
    Texture* texfield;

    //матрицы 
    TCell* vertexes;//2х2
    TCell* normals;//2x2
    GLuint* indexes;//3x3
    TUV* UV;//2x2

    TObject** objects;//массив указателей на обьекты
    int numObj;

    void CalcNormals(TCell a, TCell b, TCell c, TCell* n);
    void MapCreateHill(int posX, int posY, int rad, int height);

public:

    Map(int imapW, int imapH, TextureManager& TexM);
    ~Map();
    float MapGetHeight(float x, float y);
    bool IsCoordInMap(float x, float y);
    void MapShow(Window& window);

    

};
#endif