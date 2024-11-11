#include "game.h"

#include <raylib.h>
#include <rcamera.h>
#include <iostream>
#include <print>
#include <algorithm>
#include <format>

Game::Game() {

	m_windowWidth = 1024;
	m_windowHeight = 640;

	InitWindow(m_windowWidth, m_windowHeight, "cube simulator 3d 2: it's cubin' time");
	SetWindowState(FLAG_WINDOW_RESIZABLE);

	camera = { 0 };
	camera.position = { 0.0f, 10.0f, 10.0f };  // Camera position
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;						// Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;

	DisableCursor();

	InitAudioDevice();
	Music doomMusic = LoadMusicStream(ASSETS_PATH"doom.ogg");
	PlayMusicStream(doomMusic);

	float currentSpeed = 1.0f;

	while (!WindowShouldClose()) {

		UpdateMusicStream(doomMusic);

		UpdateThirdPersonCamera(&camera, currentSpeed);

		if (IsKeyDown(KEY_Q) || GetMouseWheelMove() > 0) currentSpeed += 0.1f;
		if ((IsKeyDown(KEY_E) || GetMouseWheelMove() < 0) && currentSpeed > 1)  currentSpeed -= 0.1f;

		BeginDrawing();

		if (camera.position.y >= 0) {
			ClearBackground(DARKGREEN);
		} else {
			ClearBackground(DARKPURPLE);
		}

		// Draw the cube and grid
		BeginMode3D(camera);
		DrawCube(camera.target, 1.0f, 1.0f, 1.0f, RED);
		DrawCubeWires(camera.target, 1.0f, 1.0f, 1.0f, YELLOW);
		DrawGrid(1000, 1.0f);
		EndMode3D();
		
		DrawText(std::format("speed: {:06} globules per hobgoblin", currentSpeed).c_str(), 10, 10, 40, YELLOW);
		DrawText(std::format("x: {} y: {} z: {}", camera.position.x, camera.position.y, camera.position.z).c_str(), 10, 100, 40, YELLOW);
		
		EndDrawing();
	}

	CloseWindow();
}

Game::~Game() {
	CloseAudioDevice();
}

void Game::ToggleFullscreen() {

	if (IsWindowFullscreen()) {
		SetWindowSize(m_windowWidth, m_windowHeight);
	} else {
		m_windowWidth = GetScreenWidth();
		m_windowHeight = GetScreenHeight();
		int currentMonitor = GetCurrentMonitor();
		SetWindowSize(GetMonitorWidth(currentMonitor), GetMonitorHeight(currentMonitor));
	}
	::ToggleFullscreen();
}


void Game::UpdateThirdPersonCamera(Camera* camera, float currentSpeed) {
	Vector2 mousePositionDelta = GetMouseDelta();

	constexpr bool moveInWorldPlane = true;
	constexpr bool rotateAroundTarget = true;
	constexpr bool lockView = true;
	constexpr bool rotateUp = false;

	// Camera speeds based on frame time
	float cameraMoveSpeed = (5.4f + currentSpeed) * GetFrameTime();

	// Mouse support
	CameraYaw(camera, -mousePositionDelta.x * 0.003f, rotateAroundTarget);
	CameraPitch(camera, -mousePositionDelta.y * 0.003f, lockView, rotateAroundTarget, rotateUp);


	// Keyboard support
	if (IsKeyDown(KEY_W)) CameraMoveForward(camera, cameraMoveSpeed, moveInWorldPlane);
	if (IsKeyDown(KEY_A)) CameraMoveRight(camera, -cameraMoveSpeed, moveInWorldPlane);
	if (IsKeyDown(KEY_S)) CameraMoveForward(camera, -cameraMoveSpeed, moveInWorldPlane);
	if (IsKeyDown(KEY_D)) CameraMoveRight(camera, cameraMoveSpeed, moveInWorldPlane);


	// Zoom target distance
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) CameraMoveToTarget(camera, -0.2f);
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) CameraMoveToTarget(camera, 0.2f);

}


