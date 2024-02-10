#include "stdafx.h"
#include "Camera.h"

struct POINT
{
    int x,y;
};
Camera::Camera(float x, float y, float z, float Xrot, float Zrot) :
    x(x), y(y), z(z), Xrot(Xrot), Zrot(Zrot), OnJump(false), speed(0), speedZ(0) {};

Camera::~Camera() {};

//�������� ������� �������� ������
void Camera::Move(Window& window)
{
    if(!OnJump)//���� �� ������� - ������������ (����������)
        CameraMoveDirection();
    CameraAutoMoveByMouse(1280/2, 720/2, 0.02f, window);//������� ������ (������)
    CameraAplly();//���������
}

//�-� ��������� ������ (�����������) ��� ��������� ������� ����
void Camera::WndResize(int x, int y)
{
    glViewport(0, 0, x, y);
    float k = x / (float)y;
    float sz = 0.1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-k * sz, k * sz, -sz, sz, sz * 2, 1000);//1000 - ��������� ����������
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//�-� ���������� ������� � �������� ������
void Camera::CameraAplly()
{
	glRotatef(-Xrot, 1, 0, 0);
	glRotatef(-Zrot, 0, 0, 1);
	glTranslatef(-x, -y, -z);
}

//�-� �������� ������
void Camera::CameraRotation(float xAngle, float zAngle)
{
    Zrot += zAngle;
    if (Zrot < 0) Zrot += 360;
    if (Zrot > 360) Zrot -= 360;
    Xrot += xAngle;
    if (Xrot < 0) Xrot = 0;
    if (Xrot > 180) Xrot = 180;
}

//�-� �������� ������ ������
void Camera::CameraAutoMoveByMouse(int conterX, int conterY, float speed, Window& window)
{
    
    if (!window.hasFocus()) return;//���� �� � ������ - �� �������
    POINT cur = { Mouse::getPosition().x, Mouse::getPosition().y };
    POINT base = { conterX, conterY };
    CameraRotation((base.y - cur.y) * speed, (base.x - cur.x) * speed);//�������� ������������ ������� ���������
    Mouse::setPosition(Vector2i(base.x, base.y));
    
}

//�-� ������������ ������ � ������������ � ������� ����������
void Camera::CameraMoveDirection()
{
    float AngleRad = -Zrot / 180 * M_PI;//������� � �������

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
        speed = 0.3; AngleRad -= M_PI_2;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        speed = 0.3; AngleRad += M_PI_2;
    }
    if (speed != 0)//�����������
    {
        x += sin(AngleRad) * speed;
        y += cos(AngleRad) * speed;
    }
}
//�-� ���������� ����� ������
void Camera::CameraJump(Map& map)
{
    const float speed_coef = 25;
    const float start_sZ = 10;
    const float fall_coef = 2;

    static Clock clock;
    static bool firstin = true;
    
   
    if (firstin)//����� 1 �����
    {
        speed *= speed_coef;

        speedZ = speed  > 0 ? speed * 2 : start_sZ;
        clock.restart();
        firstin = false;
    };

    if (!Collision(map) || speedZ > 0)//���� �� ����������� � ������ ��� ������ �� �������
    {
        float AngleRad = -Zrot / 180 * M_PI;//������� � �������
        float deltaT = clock.restart().asSeconds();//���������� �������� �������(� ���.)
        x += sin(AngleRad) * deltaT * speed;
        y += cos(AngleRad) * deltaT * speed;//��������� ����������
        z += deltaT * speedZ;

        speedZ -= deltaT * 9.78 * fall_coef;//��������� �������� �� Z
        
    }
    else //����� ������
    {
        firstin = true;
        OnJump = false;
    }
    
}
//�-� �������� ������������ � ������
bool Camera::Collision(Map& map)
{
    if (abs(map.MapGetHeight(x, y) - z) < 1.71f)
        return true;
    return false;
}
//�-� ���������� ������� ������
void Camera::UpdatePosition(Map& map)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))//������ ������
    {
        OnJump = true;
    }
    if (OnJump)//������
        CameraJump(map);
    else //������ �����������
        z = map.MapGetHeight(x, y) + 1.7f;//1.7 - ������ ���������
}
