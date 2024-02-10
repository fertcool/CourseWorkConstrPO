#include "stdafx.h"
#include "Camera.h"
#include "TextureManager.h"
#include "ReadJson.h"

int main()
{
    // ������� ����
    Window window(sf::VideoMode(1280, 720), "OpenGL", Style::Default, sf::ContextSettings(24, 8, 16, 3, 3));

    //������������ �������������
    window.setVerticalSyncEnabled(true);
   
    // ��������� �������, �������������� ��������� OpenGL
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    // ShowCursor(FALSE);

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

    
    // ��������� ������� ����
    bool running = true;
    
    while (running)
    {
        

        // ������������ �������
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(sf::Keyboard::Escape))
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
        glClearColor(0.0f, 1.0f, 0.7f, 0.0f);//��������� ����
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //��������� ���� � ��������
        glPushMatrix();
            camera.Move(window);
            camera.UpdatePosition(map);
            map.MapShow(window);
        glPopMatrix();

        
        // ����� �������� ����� (������ ������� �������� � ������ ������)
        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    
    return 0;
}

