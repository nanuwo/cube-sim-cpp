#pragma once
#include <raylib.h>

class Game {
public:
	void Update();
private:
	Camera3D m_camera = {
		.position = { 0.0f, 10.0f, 10.0f },
		.up = { 0.0f, 1.0f, 0.0f },         // Camera up vector (rotation towards target)
		.fovy = { 45.0f },					// Camera field-of-view Y
		.projection = CAMERA_PERSPECTIVE
	};
	float m_currentSpeed = 1.0f;

	void HandleInput();
	void Draw();
};