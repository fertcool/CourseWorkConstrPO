#pragma once
#include "map.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Camera
{
public:

	float x, y, z;
	float Xrot, Zrot;

	Camera(float x, float y, float z, float Xrot, float Zrot);
	~Camera();
	static void WndResize(int x, int y);
	void CameraAplly();
	void CameraRotation(float xAngle, float zAngle);
	void Move(Window& window);
	void CameraAutoMoveByMouse(int conterX, int conterY, float speed, Window& window);
	void CameraMoveDirection();

	void UpdatePosition(Map* map);
};


