#include "stdafx.h"
#include "Camera.h"
#include "TextureManager.h"


int main()
{
    Camera camera(0, 0, 1.7, 0, 0);

    // создаем окно
    Window window(sf::VideoMode(800, 600), "OpenGL", Style::Default, sf::ContextSettings(24, 8, 4, 3, 3));

    window.setVerticalSyncEnabled(true);
    
    // загружаем ресурсы, инициализируем состояния OpenGL
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    /*ShowCursor(FALSE);*/

    TextureManager TexM;

    TexM.add("./assets/pole.png");
    TexM.add("./assets/trava.png");
    TexM.add("./assets/flower.png");
    TexM.add("./assets/flower2.png");
    TexM.add("./assets/grib.png");
    TexM.add("./assets/tree.png");
    TexM.add("./assets/tree2.png");

    Map map(200, 300, TexM);

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

        // очищаем буферы
        glClearColor(0.0f, 1.0f, 0.7f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
            camera.Move(window);
            camera.UpdatePosition(&map);
            map.MapShow(window);
        glPopMatrix();

        
        

        // конец текущего кадра (меняем местами передний и задний буферы)
        window.display();

        Sleep(1);
    }

    // освобождаем ресурсы

    return 0;
}