#include "camera.h"
#include "map.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>

using namespace sf;


//void ShowWorld()
//{
//    glEnableClientState(GL_VERTEX_ARRAY);
//        glVertexPointer(3, GL_FLOAT, 0, &vert);
//        for (int i = -10; i < 10; ++i)
//        {
//            for (int j = -10; j < 10; ++j)
//            {
//                glPushMatrix();
//                    if ((i + j) % 2 == 0)
//                    {
//                        glColor3f(0, 0.5, 0);
//                    }
//                    else
//                    {
//                        glColor3f(1, 1, 1);
//                    }
//                    glTranslatef(i * 2, j * 2, 0);
//                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
//                glPopMatrix();
//            }
//        }
//        glColor3f(0, 0.5, 0);
//        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
//    glDisableClientState(GL_VERTEX_ARRAY);
//}

int main()
{
    Camera camera(0, 0, 1.7, 0, 0);

    // создаем окно
    Window window(sf::VideoMode(800, 600), "OpenGL", Style::Default, sf::ContextSettings(24, 8, 4, 3, 3));

    window.setVerticalSyncEnabled(true);
    
    // загружаем ресурсы, инициализируем состояния OpenGL
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    ShowCursor(FALSE);

    Texture texfield;
    Map::LoadTexture("pole.png", texfield);

    Map map(300, 300, &texfield);

    Camera::WndResize(window.getSize().x, window.getSize().y);

    
    // запускаем главный цикл
    bool running = true;
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
                Camera::WndResize(event.size.width, event.size.height);
            }
        }



        map.MapShow(camera, window);
        

        

        // конец текущего кадра (меняем местами передний и задний буферы)
        window.display();

        Sleep(1);
    }

    // освобождаем ресурсы

    return 0;
}