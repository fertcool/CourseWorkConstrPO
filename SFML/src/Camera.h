#ifndef CAMERA_H
#define CAMERA_H

#include "Map.h"


class Camera
{
public:

	float x, y, z;
	float Xrot, Zrot;
	bool OnJump;
	float speed, speedZ;
	float Angle;

	Camera(float x, float y, float z, float Xrot, float Zrot);
	~Camera();
	static void WndResize(int x, int y);
	void CameraAplly();
	void CameraRotation(float xAngle, float zAngle);
	void Move(Window& window);
	void CameraAutoMoveByMouse(int conterX, int conterY, float speed, Window& window);
	void CameraMoveDirection();
	void CameraJump(Map* map);
	bool Collision(Map* map);
	void UpdatePosition(Map* map);
};

#endif // !CAMERA_H

