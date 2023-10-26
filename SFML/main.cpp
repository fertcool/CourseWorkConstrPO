#include "camera.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace sf;

//float theta = 0.0f;
float vert[] = { 1,1,0,  1,-1,0,  -1,-1,0, -1,1,0 };//плоскость пола

extern SCamera camera;// :)

struct TCell
{
    float x, y, z;
};
struct TColor
{
    float r, g, b;
};

const GLuint mapW = 100;
const GLuint mapH = 100;

TCell map[mapW][mapH];
TColor mapCol[mapW][mapH];
GLuint mapInd[mapW - 1][mapH - 1][6];

int mapIndCnt = sizeof(mapInd) / sizeof(GLuint);

BOOL IsCoordInMap(float x, float y)
{
    return (x >= 0) && (x < mapW) && (y >= 0) && (y < mapH);
}
void MapCreateHill(int posX, int posY, int rad, int height)
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
                    map[i][j].z += cos(len) * height;
                }
            }
        }
    }
}
float MapGetHeight(float x, float y)
{
    if (!IsCoordInMap(x, y)) return 0;
    int cX = (int)x;
    int cY = (int)y;
    float h1 = ((1 - (x - cX)) * map[cX][cY].z + (x - cX) * map[cX + 1][cY].z);
    float h2 = ((1 - (x - cX)) * map[cX][cY+1].z + (x - cX) * map[cX + 1][cY+1].z);
    return (1 - (y - cY)) * h1 + (y - cY) * h2;
}
void Map_Init()
{
    for (int i = 0; i < mapW; ++i)
    {
        for (int j = 0; j < mapH; ++j)
        {
            float dc = (rand() % 20) * 0.01;
            mapCol[i][j].r = 0.31 + dc;
            mapCol[i][j].g = 0.5 + dc;
            mapCol[i][j].b = 0.13 + dc;

            map[i][j].x = i;
            map[i][j].y = j;
            map[i][j].z = (rand() % 10) * 0.05;
        }
    }
    for (int i = 0; i < mapW - 1; ++i)
    {
        int pos = i * mapH;
        for (int j = 0; j < mapH - 1; ++j)
        {
            mapInd[i][j][0] = pos;
            mapInd[i][j][1] = pos + 1;
            mapInd[i][j][2] = pos + 1 + mapH;

            mapInd[i][j][3] = pos + 1 + mapH;
            mapInd[i][j][4] = pos + mapH;
            mapInd[i][j][5] = pos;

            ++pos;
        }
    }
    for (int i = 0; i < 10; ++i)
    {
        MapCreateHill(rand() % mapW, rand() % mapH, rand()% 50, rand() % 10);
    }
    for (int i = 0; i < mapW - 1; ++i)
    {
        for (int j = 0; j < mapH - 1; ++j)
        {
            float dc = (map[i + 1][j + 1].z - map[i][j].z) * 0.2;
            mapCol[i][j].r += dc;
            mapCol[i][j].g += dc;
            mapCol[i][j].b += dc;
        }
    }
}

void MapShow()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, map);
    glColorPointer(3, GL_FLOAT, 0, mapCol);
    glDrawElements(GL_TRIANGLES, mapIndCnt, GL_UNSIGNED_INT, mapInd);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

}
// создаем окно
Window window(sf::VideoMode(900, 600), "OpenGL", Style::Default, sf::ContextSettings(24, 8, 4, 3, 3));

void ShowWorld()
{
    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &vert);
        for (int i = -10; i < 10; ++i)
        {
            for (int j = -10; j < 10; ++j)
            {
                glPushMatrix();
                    if ((i + j) % 2 == 0)
                    {
                        glColor3f(0, 0.5, 0);
                    }
                    else
                    {
                        glColor3f(1, 1, 1);
                    }
                    glTranslatef(i * 2, j * 2, 0);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
                glPopMatrix();
            }
        }
        glColor3f(0, 0.5, 0);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

int main()
{

    window.setVerticalSyncEnabled(true);
    
    // загружаем ресурсы, инициализируем состояния OpenGL

    glLoadIdentity();

    /*glOrtho(-2, 2, -2, 2, -1, 1);*/
    glFrustum(-1, 1, -1, 1, 1, 80);
    
    // запускаем главный цикл
    bool running = true;
    glEnable(GL_DEPTH_TEST);
    ShowCursor(FALSE);

    Map_Init();

    while (running)
    {

        // обрабатываем события
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
            {
                // пора закрывать приложение
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // применяем область просмотра, когда изменены размеры окна
                WndResize(event.size.width, event.size.height, event);
            }
        }



        // очищаем буферы
        glClearColor(0.0f, 1.0f, 0.7f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glPushMatrix();
            PlayerMove(window);
            camera.z = MapGetHeight(camera.x, camera.y) + 1.7;
            MapShow();
            
        glPopMatrix();
        





















        /*glTranslatef(0, 0, -0.01);

        glVertexPointer(3, GL_FLOAT, 0, &vert);
        glEnableClientState(GL_VERTEX_ARRAY);
            glColor3f(0, 1, 0);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glPushMatrix();
                glColor3f(1, 0, 0);
                glTranslatef(1, 0, -1);
                glDrawArrays(GL_TRIANGLES, 0, 3);
            glPopMatrix();
        glDisableClientState(GL_VERTEX_ARRAY);*/

        // конец текущего кадра (меняем местами передний и задний буферы)
        window.display();

        Sleep(1);
    }

    // освобождаем ресурсы

    return 0;
}