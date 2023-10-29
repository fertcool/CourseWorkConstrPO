#include "map.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace sf;

Map::Map(int mapW, int mapH, Texture* texfield)
{
    //TCell** vertexes;
    //TCell** normals;
    //GLuint*** indexes;
    ///*[mapW - 1] [mapH - 1] [6]*/
    //TUV** UV;

    
    for (int i = 0; i < mapW; ++i)
    {
        vertexes[i].reserve(mapH);
        normals[i].reserve(mapH);
        UV[i].reserve(mapH);
        indexes[i].reserve(mapH);
        for (int j = 0; j < mapH; ++j)
        {
            indexes[i][j].reserve(6);
        }
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.99);

    texfield->setRepeated(true);
    /*texcat.setSmooth(true);*/

    for (int i = 0; i < mapW; ++i)
    {
        for (int j = 0; j < mapH; ++j)
        {
            vertexes[i][j].x = i;
            vertexes[i][j].y = j;
            vertexes[i][j].z = (rand() % 10) * 0.05;

            UV[i][j].u = i;
            UV[i][j].v = j;

        }
    }
    for (int i = 0; i < mapW - 1; ++i)
    {
        int pos = i * mapH;
        for (int j = 0; j < mapH - 1; ++j)
        {
            indexes[i][j][0] = pos;
            indexes[i][j][1] = pos + 1;
            indexes[i][j][2] = pos + 1 + mapH;

            indexes[i][j][3] = pos + 1 + mapH;
            indexes[i][j][4] = pos + mapH;
            indexes[i][j][5] = pos;

            ++pos;
        }
    }
    for (int i = 0; i < 10; ++i)
    {
        MapCreateHill(rand() % mapW, rand() % mapH, rand() % 50, rand() % 10);
    }
    for (int i = 0; i < mapW - 1; ++i)
    {
        for (int j = 0; j < mapH - 1; ++j)
        {
            CalcNormals(vertexes[i][j], vertexes[i + 1][j], vertexes[i][j + 1], &normals[i][j]);
        }
    }


    int travaN = 2000;
    int gribN = 30;
    int treeN = 40;
    int plantCnt = travaN + gribN + treeN;

    objects = new TObject*[plantCnt];

    for (int i = 0; i < plantCnt; ++i)
    {
        if (i < travaN)
        {
            if (rand() % 100 != 0)
            {
                objects[i] = new Grass;
            }
            plantMas[i].type = rand() % 100 != 0 ? grass :
                (rand() % 2 == 0 ? flower1 : flower2);
            plantMas[i].scale = 0.7 + (rand() % 5) * 0.1;
        }
        else if (i < (travaN + gribN))
        {
            plantMas[i].type = mashroom;
            plantMas[i].scale = 0.2 + (rand() % 10) * 0.01;
        }
        else
        {
            plantMas[i].type = rand() % 2 == 0 ? tree1 : tree2;
            plantMas[i].scale = 4 + (rand() % 14);
        }
        plantMas[i].x = rand() % mapW;
        plantMas[i].y = rand() % mapH;
        plantMas[i].z = MapGetHeight(plantMas[i].x, plantMas[i].y);

    }
}