#include "stdafx.h"
#include "Camera.h"

Camera::Camera(float x, float y, float z, float Xrot, float Zrot) :
    x(x), y(y), z(z), Xrot(Xrot), Zrot(Zrot), OnJump(false), speed(0), speedZ(0), Angle(0) {};

Camera::~Camera() {};

//основная функция движения камеры
void Camera::Move(Window& window)
{
    if(!OnJump)
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
    Angle = -Zrot / 180 * M_PI;
    speed = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        speed = 0.3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        speed = -0.3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        speed = 0.3; Angle -= M_PI_2;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        speed = 0.3; Angle += M_PI_2;
    }
    if (speed != 0)
    {
        x += sin(Angle) * speed;
        y += cos(Angle) * speed;
    }
}
void Camera::CameraJump(Map* map)
{
    const int speed_coef = 25;
    const int start_sZ = 10;

    static Clock clock;
    static bool firstin = true;

    if (firstin)
    {
        speed *= speed_coef;

        speedZ = speed  > 0 ? speed * 2 : start_sZ;
        clock.restart();
        firstin = false;
    };

    if (!Collision(map) || speedZ > 0)
    {
        float deltaT = clock.restart().asSeconds();
        x += sin(Angle) * deltaT * speed;
        y += cos(Angle) * deltaT * speed;
        z += deltaT * speedZ;

        speedZ -=  deltaT * 9.78 * 2;
        
    }
    else
    {
        firstin = true;
        OnJump = false;
    }
    
}
bool Camera::Collision(Map* map)
{
    if (abs(map->MapGetHeight(x, y) - z) < 1.71f)
        return true;
    return false;
}
void Camera::UpdatePosition(Map* map)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        OnJump = true;
    }
    if (OnJump)
        CameraJump(map);
    else
        z = map->MapGetHeight(x, y) + 1.7f;
}
