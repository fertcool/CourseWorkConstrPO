//заголовок камеры
#ifndef CAMERA_H
#define CAMERA_H

#include "Map.h"


class Camera
{
public:

	float x, y, z;//координаты в пространстве
	float Xrot, Zrot;//повороты по X и по Z
	bool OnJump;//флаг прыжка
	float speed, speedZ;//скорость в плоскости перемещения и вертикальная скорость
	//float Angle;//угол направляющего вектора в радианах

	Camera(float x, float y, float z, float Xrot, float Zrot);
	~Camera();
	static void WndResize(int x, int y);//ф-я адаптации камеры при изменении размера окна
	void CameraAplly();//ф-я применения позиции и поворота камеры
	void CameraRotation(float xAngle, float zAngle);//ф-я поворота камеры
	void Move(Window& window);//основная функция движения камеры
	void CameraAutoMoveByMouse(int conterX, int conterY, float speed, Window& window);//ф-я движения камеры мышкой
	void CameraMoveDirection();//ф-я передвижения камеры в пространстве с помощью клавиатуры
	void CameraJump(Map* map);
	bool Collision(Map* map);
	void UpdatePosition(Map* map);
};

#endif // !CAMERA_H

