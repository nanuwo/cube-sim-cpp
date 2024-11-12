#include "game.h"

#include <raylib.h>
#include <rcamera.h>
#include <format>

void Game::Update() {
	this->Draw();
	HandleInput();
}

void Game::HandleInput() {
	Vector2 mousePositionDelta{ GetMouseDelta() };

	constexpr bool moveInWorldPlane = true;
	constexpr bool rotateAroundTarget = true;
	constexpr bool lockView = true;
	constexpr bool rotateUp = false;

	// Camera speeds based on frame time
	float cameraMoveSpeed = (5.4f + m_currentSpeed) * GetFrameTime();

	// Mouse support
	CameraYaw(&m_camera, -mousePositionDelta.x * 0.003f, rotateAroundTarget);
	CameraPitch(&m_camera, -mousePositionDelta.y * 0.003f, lockView, rotateAroundTarget, rotateUp);

	// Keyboard support
	if (IsKeyDown(KEY_W)) CameraMoveForward(&m_camera, cameraMoveSpeed, moveInWorldPlane);
	if (IsKeyDown(KEY_A)) CameraMoveRight(&m_camera, -cameraMoveSpeed, moveInWorldPlane);
	if (IsKeyDown(KEY_S)) CameraMoveForward(&m_camera, -cameraMoveSpeed, moveInWorldPlane);
	if (IsKeyDown(KEY_D)) CameraMoveRight(&m_camera, cameraMoveSpeed, moveInWorldPlane);

	// Zoom target distance
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) CameraMoveToTarget(&m_camera, -0.2f);
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) CameraMoveToTarget(&m_camera, 0.2f);

	// Set current speed based on key/mouse movement
	if (IsKeyDown(KEY_Q) || GetMouseWheelMove() > 0) m_currentSpeed += 0.1f;
	if ((IsKeyDown(KEY_E) || GetMouseWheelMove() < 0) && m_currentSpeed > 1)  m_currentSpeed -= 0.1f;
}

void Game::Draw() {
	BeginDrawing();

	if (m_camera.position.y >= 0) {
		ClearBackground(DARKGREEN);
	} else {
		ClearBackground(DARKPURPLE);
	}

	// Draw the cube and grid
	BeginMode3D(m_camera);
	DrawCube(m_camera.target, 1.0f, 1.0f, 1.0f, RED);
	DrawCubeWires(m_camera.target, 1.0f, 1.0f, 1.0f, YELLOW);
	DrawGrid(1000, 1.0f);
	EndMode3D();

	// Draw HUD
	DrawText(std::format("speed: {:06} globules per hobgoblin", m_currentSpeed).c_str(), 10, 10, 40, YELLOW);
	DrawText(std::format("x: {} y: {} z: {}", m_camera.target.x, m_camera.target.y, m_camera.target.z).c_str(), 10, 100, 40, YELLOW);

	EndDrawing();
}
