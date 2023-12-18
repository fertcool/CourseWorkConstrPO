#include "Headers/stdafx.h"
#include "Headers/Camera.h"

Camera::Camera(float x, float y, float z, float Xrot, float Zrot) :
    x(x), y(y), z(z), Xrot(Xrot), Zrot(Zrot), OnJump(false), speed(0), speedZ(0) {};

Camera::~Camera() {};

//основна€ функци€ движени€ камеры
void Camera::Move(Window& window)
{
    if(!OnJump)//если не прыгаем - перемещаемс€ (клавиатура)
        CameraMoveDirection();
    CameraAutoMoveByMouse(GetSystemMetrics(SM_CXSCREEN)/2, GetSystemMetrics(SM_CYSCREEN)/2, 0.2f, window);//поворот камеры (мышкой)
    CameraAplly();//примен€ем
}

//ф-€ адаптации камеры (перспективы) при изменении размера окна
void Camera::WndResize(int x, int y)
{
    glViewport(0, 0, x, y);
    float k = x / (float)y;
    float sz = 0.1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-k * sz, k * sz, -sz, sz, sz * 2, 1000);//1000 - дальность прорисовки
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//ф-€ применени€ позиции и поворота камеры
void Camera::CameraAplly()
{
	glRotatef(-Xrot, 1, 0, 0);
	glRotatef(-Zrot, 0, 0, 1);
	glTranslatef(-x, -y, -z);
}

//ф-€ поворота камеры
void Camera::CameraRotation(float xAngle, float zAngle)
{
    Zrot += zAngle;
    if (Zrot < 0) Zrot += 360;
    if (Zrot > 360) Zrot -= 360;
    Xrot += xAngle;
    if (Xrot < 0) Xrot = 0;
    if (Xrot > 180) Xrot = 180;
}

//ф-€ движени€ камеры мышкой
void Camera::CameraAutoMoveByMouse(int conterX, int conterY, float speed, Window& window)
{
    
    if (!window.hasFocus()) return;//если не в фокусе - не двигаем
    POINT cur = { Mouse::getPosition().x, Mouse::getPosition().y };
    POINT base = { conterX, conterY };
    CameraRotation((base.y - cur.y) * speed, (base.x - cur.x) * speed);//движение относительно базовых координат
    Mouse::setPosition(Vector2i(base.x, base.y));
    
}

//ф-€ передвижени€ камеры в пространстве с помощью клавиатуры
void Camera::CameraMoveDirection()
{
    Angle = -Zrot / 180 * M_PI;//перевод в радианы

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
    if (speed != 0)//перемещение
    {
        x += sin(Angle) * speed;
        y += cos(Angle) * speed;
    }
}
//ф-€ обновлени€ кадра прыжка
void Camera::CameraJump(Map* map)
{
    const float speed_coef = 25;
    const float start_sZ = 10;
    const float fall_coef = 2;

    static Clock clock;
    static bool firstin = true;
    
   
    if (firstin)//точка 1 входа
    {
        speed *= speed_coef;

        speedZ = speed  > 0 ? speed * 2 : start_sZ;
        clock.restart();
        firstin = false;
    };

    if (!Collision(map) || speedZ > 0)//если не столкнулись с картой или прыжок не окончен
    {
        float deltaT = clock.restart().asSeconds();//вычисление разности времени(в сек.)
        x += sin(Angle) * deltaT * speed;
        y += cos(Angle) * deltaT * speed;//обновл€ем координаты
        z += deltaT * speedZ;

        speedZ -= deltaT * 9.78 * fall_coef;//изменение скорости по Z
        
    }
    else //конец прыжка
    {
        firstin = true;
        OnJump = false;
    }
    
}
//ф-€ проверки столкновени€ с картой
bool Camera::Collision(Map* map)
{
    if (abs(map->MapGetHeight(x, y) - z) < 1.71f)
        return true;
    return false;
}
//ф-€ обновлени€ позиции игрока
void Camera::UpdatePosition(Map* map)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))//начало прыжка
    {
        OnJump = true;
    }
    if (OnJump)//прыжок
        CameraJump(map);
    else //просто перемещение
        z = map->MapGetHeight(x, y) + 1.7f;//1.7 - высота персонажа
}
