//заголовок карты
#ifndef MAP_H
#define MAP_H
//директивы доступа к данным матриц
#define Access2(i, j) (i) * (mapH) + j //2х2
#define Access3(i, j, k) (i) * (mapH - 1) * 6 + (j) * 6 + k //3x3

#include "structs.h"
#include "TObject.h"
#include "TextureManager.h"

class Map
{
    int mapW, mapH;//размеры карты
    Texture* texfield;//текстура карты

    //матрицы 
    TCell* vertexes;//2х2 массив вершин
    TCell* normals;//2x2  массив нормалей
    GLuint* indexes;//3x3 массив индексов
    TUV* UV;//2x2 массив вершин для текстур

    TObject** objects;//массив указателей на обьекты
    int numObj;//количество обьектов

    void CalcNormals(TCell a, TCell b, TCell c, TCell* n);//ф-я вычисления нормалей
    void MapCreateHill(int posX, int posY, int rad, int height);// ф-я создания холмов

public:

    Map(int imapW, int imapH, TextureManager& TexM);
    ~Map();
    float MapGetHeight(float x, float y);//получить высоту по координатам x и y
    bool IsCoordInMap(float x, float y);//проверка существования координат x и y
    void MapShow(Window& window);//отрисовка карты

    static inline int jopa{};
    

};


#endif