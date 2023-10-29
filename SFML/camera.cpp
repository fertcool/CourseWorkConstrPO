#include "camera.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace sf;



Camera::Camera(float x, float y, float z, float Xrot, float Zrot) :
    x(x), y(y), z(z), Xrot(Xrot), Zrot(Zrot){};

Camera::~Camera() {};

//основная функция движения камеры
void Camera::Move(Window& window)
{
    CameraMoveDirection();
    CameraAutoMoveByMouse(400, 400, 0.2f, window);
    CameraAplly();
}

//ф-я адаптации камеры при изменении размера окна
void Camera::WndResize(int x, int y)
{
    glViewport(0, 0, x, y);
    float k = x / (float)y;
    float sz = 0.1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-k * sz, k * sz, -sz, sz, sz * 2, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//ф-я применения позиции и поворота камеры
void Camera::CameraAplly()
{
	glRotatef(-Xrot, 1, 0, 0);
	glRotatef(-Zrot, 0, 0, 1);
	glTranslatef(-x, -y, -z);
}

//ф-я поворота камеры
void Camera::CameraRotation(float xAngle, float zAngle)
{
    Zrot += zAngle;
    if (Zrot < 0) Zrot += 360;
    if (Zrot > 360) Zrot -= 360;
    Xrot += xAngle;
    if (Xrot < 0) Xrot = 0;
    if (Xrot > 180) Xrot = 180;
}

//ф-я движения камеры мышкой
void Camera::CameraAutoMoveByMouse(int conterX, int conterY, float speed, Window& window)
{
    
    if (!window.hasFocus()) return;
    POINT cur = { Mouse::getPosition().x, Mouse::getPosition().y };
    POINT base = { conterX, conterY };
    CameraRotation((base.y - cur.y) * speed, (base.x - cur.x) * speed);
    Mouse::setPosition(Vector2i(base.x, base.y));
}

//ф-я передвижения камеры в пространстве с помощью клавиатуры
void Camera::CameraMoveDirection()
{
    float Angle = -Zrot / 180 * M_PI;
    float speed = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        speed = 0.5;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        speed = -0.5;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        speed = 0.5; Angle -= M_PI_2;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        speed = 0.5; Angle += M_PI_2;
    }
    if (speed != 0)
    {
        x += sin(Angle) * speed;
        y += cos(Angle) * speed;
    }
}
