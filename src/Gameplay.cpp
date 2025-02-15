#include "Gameplay.hpp"
#include "App.hpp"
#include <raylib.h>
#include <raygui.h>
#include <rcamera.h>
#include <format>

Gameplay::Gameplay() {
	DisableCursor();
	SetExitKey(KEY_NULL);
}

Gameplay::~Gameplay() {
	
}

void Gameplay::update() {
	if (!m_showMenu) {
		App::getInstance().getBeeModel().update();
	}
}

void Gameplay::draw() {
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
	DrawModel(App::getInstance().getBeeModel().getModel(), Vector3 {1.0f, 1.0f, 1.0f}, 100.0f, WHITE);

	EndMode3D();

	// Draw HUD
	DrawText(std::format("speed: {:.2f} globules per hobgoblin", m_currentSpeed).c_str(), 10, 10, 40, YELLOW);
	DrawText(std::format("x: {:.2f} y: {:.2f} z: {:.2f}", m_camera.target.x, m_camera.target.y, m_camera.target.z).c_str(), 10, 50, 40, YELLOW);
	DrawFPS(10, 90);

	//Draw pause menu
	if (m_showMenu) {
		DrawRectangle(0, 0, GetRenderWidth(), GetRenderHeight(), Fade(BLACK, 0.5));
		if (GuiButton(Rectangle {100, 100, 500, 100}, "go bac to menu")) {
			App::getInstance().setState(std::make_unique<MainMenu>());
		}

		if (GuiButton(Rectangle {GetRenderWidth() - 1000.0f, GetRenderHeight() - 200.0f, 900.0f, 100.0f}, "play more of hit game cube simulator 3d 2")) {
			this->toggleMenu();
		}
	}
}

void Gameplay::handleInput() {
	if (IsKeyPressed(KEY_ESCAPE))
		this->toggleMenu();

	// Handle input if not in menu state
	if (!m_showMenu) {
		Vector2 mousePositionDelta = GetMouseDelta();

		constexpr bool moveInWorldPlane = true;
		constexpr bool rotateAroundTarget = true;
		constexpr bool lockView = true;
		constexpr bool rotateUp = false;

		// Camera speeds based on frame time
		const float cameraMoveSpeed = (5.4f + m_currentSpeed) * GetFrameTime();

		// Mouse support
		CameraYaw(&m_camera, -mousePositionDelta.x * 0.003f, rotateAroundTarget);
		CameraPitch(&m_camera, -mousePositionDelta.y * 0.003f, lockView, rotateAroundTarget, rotateUp);

		// Keyboard support
		if (IsKeyDown(KEY_W)) CameraMoveForward(&m_camera, cameraMoveSpeed, moveInWorldPlane);
		if (IsKeyDown(KEY_A)) CameraMoveRight(&m_camera, -cameraMoveSpeed, moveInWorldPlane);
		if (IsKeyDown(KEY_S)) CameraMoveForward(&m_camera, -cameraMoveSpeed, moveInWorldPlane);
		if (IsKeyDown(KEY_D)) CameraMoveRight(&m_camera, cameraMoveSpeed, moveInWorldPlane);

		//Jumping
		if (IsKeyDown(KEY_SPACE)) {
			CameraMoveUp(&m_camera, cameraMoveSpeed);
		} else if (m_camera.target.y > 0) {
			CameraMoveUp(&m_camera, -cameraMoveSpeed);
		}

		// Zoom target distance
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) CameraMoveToTarget(&m_camera, -0.2f);
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) CameraMoveToTarget(&m_camera, 0.2f);

		// Set current speed based on key/mouse movement
		if (IsKeyDown(KEY_Q) || GetMouseWheelMove() > 0) m_currentSpeed += 0.1f;
		if ((IsKeyDown(KEY_E) || GetMouseWheelMove() < 0) && m_currentSpeed > 1) m_currentSpeed -= 0.1f;

		if (IsKeyPressed(KEY_P)) {
			if (m_camera.projection == CAMERA_PERSPECTIVE) {
				m_camera.projection = CAMERA_ORTHOGRAPHIC;
			} else {
				m_camera.projection = CAMERA_PERSPECTIVE;
			}
		}
	}
}

void Gameplay::toggleMenu() {
	if (m_showMenu) {
		DisableCursor();
	} else {
		EnableCursor();
	}
	m_showMenu = !m_showMenu;
}