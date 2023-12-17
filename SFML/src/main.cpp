#include "Headers/stdafx.h"
#include "Headers/Camera.h"
#include "Headers/TextureManager.h"
#include "Headers/ReadJson.h"

int main()
{
    // ������� ����
    Window window(sf::VideoMode(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), "OpenGL", Style::Default, sf::ContextSettings(24, 8, 16, 3, 3));

    window.setVerticalSyncEnabled(true);
   
    // ��������� �������, �������������� ��������� OpenGL
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    ShowCursor(FALSE);

    //������� ������
    Camera camera(0, 0, 1.7, 0, 0);

    //������� �������� �������
    TextureManager TexM;
    //��������� ��������
    TexM.add("./assets/pole.png");
    TexM.add("./assets/trava.png");
    TexM.add("./assets/flower.png");
    TexM.add("./assets/flower2.png");
    TexM.add("./assets/grib.png");
    TexM.add("./assets/tree.png");
    TexM.add("./assets/tree2.png");

    //����������� ������������� ����������
    int mapH(0);
    int mapW(0);
    int HillsCount(0);
    float VegDensity(0);
    //��������� json �����
    ReadJson(&mapW, &mapH, &HillsCount, &VegDensity);

    //������� �����
    Map map(mapW, mapH, HillsCount, VegDensity, TexM);
    
    Camera::WndResize(window.getSize().x, window.getSize().y);

    Clock Clock;
    // ��������� ������� ����
    bool running = true;
    while (running)
    {
        float Framerate = 1.f / Clock.getElapsedTime().asSeconds();
        std::cout << Framerate<<std::endl;
        Clock.restart();
        // ������������ �������
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
            {
                // ���� ��������� ����������
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // ��������� ������� ���������, ����� �������� ������� ����
                Camera::WndResize(event.size.width, event.size.height);
            }
        }

        // ������� ������
        glClearColor(0.0f, 1.0f, 0.7f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //��������� ���� � ��������
        glPushMatrix();
            camera.Move(window);
            camera.UpdatePosition(&map);
            map.MapShow(window);
        glPopMatrix();

        
        // ����� �������� ����� (������ ������� �������� � ������ ������)
        window.display();

        Sleep(1);
    }

    // ����������� �������

    return 0;
}

