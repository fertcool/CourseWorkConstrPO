#include "camera.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace sf;

SCamera camera = { 0,0,1.7,0,0 };

void PlayerMove(Window& window)
{
    CameraAutoMoveByMouse(400, 400, 0.2f, window);
    CameraMoveDirection();
    CameraAplly();
}

void WndResize(int x, int y, Event event)
{
    glViewport(0, 0, x, y);
    float k = x / (float)y;
    float sz = 0.1;
    glLoadIdentity();
    glFrustum(-k * sz, k * sz, -sz, sz, sz * 2, 100);
}

void CameraAplly()
{
	glRotatef(-camera.Xrot, 1, 0, 0);
	glRotatef(-camera.Zrot, 0, 0, 1);
	glTranslatef(-camera.x, -camera.y, -camera.z);
}

void CameraRotation(float xAngle, float zAngle)
{
    camera.Zrot += zAngle;
    if (camera.Zrot < 0) camera.Zrot += 360;
    if (camera.Zrot > 360) camera.Zrot -= 360;
    camera.Xrot += xAngle;
    if (camera.Xrot < 0) camera.Xrot = 0;
    if (camera.Xrot > 180) camera.Xrot = 180;
}

void CameraAutoMoveByMouse(int conterX, int conterY, float speed, Window& window)
{
    /*if (!window.hasFocus()) return;
    POINT cur = { Mouse::getPosition().x, Mouse::getPosition().y };
    static POINT base = { window.getSize().x / 2.0f, window.getSize().y / 2.0f };
    CameraRotation((base.y - cur.y) / 5.0f, (base.x - cur.x) / 5.0f);
    Mouse::setPosition(Vector2i(base.x, base.y));*/
    if (!window.hasFocus()) return;
    POINT cur = { Mouse::getPosition().x, Mouse::getPosition().y };
    POINT base = { conterX, conterY };
    CameraRotation((base.y - cur.y) * speed, (base.x - cur.x) * speed);
    Mouse::setPosition(Vector2i(base.x, base.y));
}
void CameraMoveDirection()
{
    float Angle = -camera.Zrot / 180 * M_PI;
    float speed = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        speed = 0.1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        speed = -0.1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        speed = 0.1; Angle -= M_PI_2;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        speed = 0.1; Angle += M_PI_2;
    }
    if (speed != 0)
    {
        camera.x += sin(Angle) * speed;
        camera.y += cos(Angle) * speed;
    }
}
