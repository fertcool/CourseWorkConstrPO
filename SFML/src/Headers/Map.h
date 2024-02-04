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
    int HillsCount;//количество холмов
    float VegDensity;//плотность растительности
    TexturePtr texfield;//текстура карты

    //матрицы 
    std::vector<TCell> vertexes;//2х2 массив вершин
    std::vector<TCell> normals;//2x2  массив нормалей
    std::vector<GLuint> indexes;//3x3 массив индексов
    std::vector<TUV> UV;//2x2 массив вершин для текстур

    std::vector<std::unique_ptr<TObject>> objects;//массив указателей на обьекты

    int numObj;//количество обьектов

    void CalcNormals(TCell a, TCell b, TCell c, TCell* n);//ф-я вычисления нормалей
    void MapCreateHill(int posX, int posY, int rad, int height);// ф-я создания холмов

public:

    Map(int imapW, int imapH, int iHillsCount, float iVegDensity, TextureManager& TexM);
    ~Map();
    float MapGetHeight(float x, float y);//получить высоту по координатам x и y
    bool IsCoordInMap(float x, float y);//проверка существования координат x и y
    void MapShow(Window& window);//отрисовка карты

};


#endif