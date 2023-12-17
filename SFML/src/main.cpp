#include "Headers/stdafx.h"
#include "Headers/Camera.h"
#include "Headers/TextureManager.h"
#include "Headers/ReadJson.h"

int main()
{
    // создаем окно
    Window window(sf::VideoMode(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), "OpenGL", Style::Default, sf::ContextSettings(24, 8, 16, 3, 3));

    window.setVerticalSyncEnabled(true);
   
    // загружаем ресурсы, инициализируем состояния OpenGL
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    ShowCursor(FALSE);

    //создаем камеру
    Camera camera(0, 0, 1.7, 0, 0);

    //создаем менеджер текстур
    TextureManager TexM;
    //добавляем текстуры
    TexM.add("./assets/pole.png");
    TexM.add("./assets/trava.png");
    TexM.add("./assets/flower.png");
    TexM.add("./assets/flower2.png");
    TexM.add("./assets/grib.png");
    TexM.add("./assets/tree.png");
    TexM.add("./assets/tree2.png");

    //определение настраиваемых переменных
    int mapH(0);
    int mapW(0);
    int HillsCount(0);
    float VegDensity(0);
    //прочтение json файла
    ReadJson(&mapW, &mapH, &HillsCount, &VegDensity);

    //создаем карту
    Map map(mapW, mapH, HillsCount, VegDensity, TexM);
    
    Camera::WndResize(window.getSize().x, window.getSize().y);

    Clock Clock;
    // запускаем главный цикл
    bool running = true;
    while (running)
    {
        float Framerate = 1.f / Clock.getElapsedTime().asSeconds();
        std::cout << Framerate<<std::endl;
        Clock.restart();
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

        //отрисовка мира в движении
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

