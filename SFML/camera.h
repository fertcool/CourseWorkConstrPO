#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace sf;
struct SCamera
{
	float x, y, z;
	float Xrot, Zrot;
};
void WndResize(int x, int y);
void CameraAplly();
void CameraRotation(float xAngle, float zAngle);
void PlayerMove(Window& window);
void CameraAutoMoveByMouse(int conterX, int conterY, float speed, Window& window);
void CameraMoveDirection();
