#include "stdafx.h"
#include "Map.h"

Map::Map(int imapW, int imapH, int iHillsCount, float iVegDensity, TextureManager& TexM) :mapW(imapW), mapH(imapH)
{
    //инициализация переменных
    mapH = imapH;
    mapW = imapW;
    HillsCount = iHillsCount;
    VegDensity = iVegDensity;
    texfield = TexM.get("./assets/pole.png");
    TexturePtr tex_grass = TexM.get("./assets/trava.png");
    TexturePtr tex_flower1 = TexM.get("./assets/flower.png");
    TexturePtr tex_flower2 = TexM.get("./assets/flower2.png");
    TexturePtr tex_mashroom = TexM.get("./assets/grib.png");
    TexturePtr tex_tree1 = TexM.get("./assets/tree.png");
    TexturePtr tex_tree2 = TexM.get("./assets/tree2.png");
 
    //выделение памяти под массивы
    vertexes.resize(mapW*mapH);
    normals.resize(mapW*mapH);
    UV.resize(mapW*mapH);
    indexes.resize((mapW - 1) * (mapH-1) * 6);
    
    //включаем необходимые режимы opengl
    glEnable(GL_LIGHTING);//освещение
    glEnable(GL_LIGHT0);//0 источник света
    glEnable(GL_NORMALIZE);//режим нормалей
    glEnable(GL_ALPHA_TEST);//альфа канал(для png текстур)
    glAlphaFunc(GL_GREATER, 0.99);

    texfield->setRepeated(true);//включаем повторение текстуры карты
    
    //инициализация вершин и координат текстур
    for (int i = 0; i < mapW; ++i)
    {
        for (int j = 0; j < mapH; ++j)
        {
            vertexes[Access2(i, j)].x = i;
            vertexes[Access2(i, j)].y = j;
            vertexes[Access2(i, j)].z = (rand() % 10) * 0.02;//рельефность карты

            UV[Access2(i, j)].u = i;
            UV[Access2(i, j)].v = j;

        }
    }
    //инициализация массива индексов
    for (int i = 0; i < mapW - 1; ++i)
    {
        int pos = i * mapH;
        for (int j = 0; j < mapH - 1; ++j)
        {
            //6 вершин для отрисовки квадрата
            indexes[Access3(i, j, 0)] = pos;
            indexes[Access3(i, j, 1)] = pos + 1;
            indexes[Access3(i, j, 2)] = pos + 1 + mapH;

            indexes[Access3(i, j, 3)] = pos + 1 + mapH;
            indexes[Access3(i, j, 4)] = pos + mapH;
            indexes[Access3(i, j, 5)] = pos;

            ++pos;
        }
    }
    //инициализация массива нормалей
    for (int i = 0; i < mapW - 1; ++i)
    {
        for (int j = 0; j < mapH - 1; ++j)
        {
            CalcNormals(vertexes[Access2(i, j)], vertexes[Access2(i + 1, j)], vertexes[Access2(i, j + 1)], &normals[Access2(i, j)]);
        }
    }

    //создание холмов
    for (int i = 0; i < HillsCount; ++i)
    {
        MapCreateHill(rand() % mapW, rand() % mapH, rand() % 50, rand() % 10);
    }


    
    int travaN = int(VegDensity * 0.2   * mapH * mapW);//количество травы и цветов
    int gribN =  int(VegDensity * 0.003 * mapH * mapW);//количество грибов
    int treeN =  int(VegDensity * 0.004 * mapH * mapW);//количество деревьев

    numObj = travaN + gribN + treeN;//количество всех обьектов

    objects.resize(numObj);//выделение памяти под массив указателей на обьекты

    for (int i = 0; i < numObj; ++i)
    {
        if (i < travaN)//выделение памяти под траву или цветок
        {
            if (rand() % 100 != 0)
            {
                objects[i] = std::make_unique<Grass>();
                objects[i]->texture = tex_grass;
            }
            else if (rand() % 2 == 0)
            {
                objects[i] = std::make_unique<Flower>();
                objects[i]->texture = tex_flower1;
            }
            else
            {
                objects[i] = std::make_unique<Flower>();
                objects[i]->texture = tex_flower2;
            }
            
            objects[i]->scale = 0.7 + (rand() % 5) * 0.1;
        }
        else if (i < (travaN + gribN)) // выделение памяти под гриб
        {
            objects[i] = std::make_unique<Mashroom>();
            objects[i]->texture = tex_mashroom;
            objects[i]->scale = 0.2 + (rand() % 10) * 0.01;
        }
        else // выделение памяти под дерево
        {
            objects[i] = std::make_unique<Tree>();
            if (rand() % 2 == 0)
            {
                objects[i]->texture = tex_tree1;
            }
            else 
            {
                objects[i]->texture = tex_tree2;
            }
            
            
            objects[i]->scale = 4 + (rand() % 14);
        }
        //инициализация расположения обьекта
        objects[i]->x = rand() % mapW;
        objects[i]->y = rand() % mapH;
        objects[i]->z = MapGetHeight(objects[i]->x, objects[i]->y);

    }
}
Map::~Map()
{
    
}

//ф-я отрисовки карты
void Map::MapShow(Window& window)
{
    int mapIndCnt = indexes.size();//количество индексов

    glEnable(GL_TEXTURE_2D);
    GLfloat Lposition[] = { 1,0,1,0 };//расположение света
    glLightfv(GL_LIGHT0, GL_POSITION, Lposition);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertexes.data());//загрузка вершин
        glTexCoordPointer(2, GL_FLOAT, 0, UV.data());//загрузка координат текстур
        glNormalPointer(GL_FLOAT, 0, normals.data());//загрузка нормалей
        Texture::bind(texfield.get());//связывание с текстурой sfml
        glDrawElements(GL_TRIANGLES, mapIndCnt, GL_UNSIGNED_INT, indexes.data());//отрисовка
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    //отрисовка обьектов
    for (int i = 0; i < numObj; ++i)
    {
        objects[i]->draw();
    }
}

//проверка существования координат x и y
bool Map::IsCoordInMap(float x, float y)
{
    return (x >= 0) && (x < mapW) && (y >= 0) && (y < mapH);
}

//ф-я вычисления нормалей
void Map::CalcNormals(TCell a, TCell b, TCell c, TCell* n)
{
    float wrki;
    TCell v1, v2;

    v1.x = a.x - b.x;
    v1.y = a.y - b.y;
    v1.z = a.z - b.z;

    v2.x = b.x - c.x;
    v2.y = b.y - c.y;
    v2.z = b.z - c.z;

    n->x = (v1.y * v2.z - v1.z * v2.y);
    n->y = (v1.z * v2.x - v1.x * v2.z);
    n->z = (v1.x * v2.y - v1.y * v2.x);

    wrki = sqrt(pow(n->x, 2) + pow(n->y, 2) + pow(n->z, 2));

    n->x /= wrki;
    n->y /= wrki;
    n->z /= wrki;

}
// ф-я создания холмов
void Map::MapCreateHill(int posX, int posY, int rad, int height)
{
    for (int i = posX - rad; i <= posX + rad; ++i)
    {
        for (int j = posY - rad; j <= posY + rad; ++j)
        {
            if (IsCoordInMap(i, j))
            {
                float len = sqrt(pow(posX - i, 2) + pow(posY - j, 2));
                if (len < rad)
                {
                    len = len / rad * M_PI_2;
                    vertexes[Access2(i, j)].z += cos(len)*height;
                    
                }
            }
        }
    }
}
//получить высоту по координатам x и y
float Map::MapGetHeight(float x, float y)
{
    if (!IsCoordInMap(x, y)) return 0;
    int cX = (int)x;
    int cY = (int)y;

    if (cX == mapW - 1)
        --cX;
    if (cY == mapH - 1)
        --cY;

    float h1 = ((1 - (x - cX)) * vertexes[Access2(cX, cY)].z + (x - cX) * vertexes[Access2(cX + 1, cY)].z);
    float h2 = ((1 - (x - cX)) * vertexes[Access2(cX, cY + 1)].z + (x - cX) * vertexes[Access2(cX + 1, cY + 1)].z);
    return (1 - (y - cY)) * h1 + (y - cY) * h2;
}
