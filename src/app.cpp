#include "App.hpp"
#include "Game.hpp"
#include <raygui.h>
#include <raylib.h>
#include <rcamera.h>
#include <format>
#include <memory>
#include <print>

template<class... Ts> struct Overload : Ts... {
	using Ts::operator()...;
};

App& App::getInstance() {
	static App s_instance {};
	return s_instance;
}

App::App() {
	PlayMusicStream(m_music);
}

App::~App() {
	UnloadMusicStream(m_music);
}

bool App::shouldClose() {
	return m_shouldClose;
}

void App::close() {
	m_shouldClose = true;
}

void App::handleInput() {
	if (IsKeyPressed(KEY_F11)) {
		this->toggleFullscreen();
	}
	std::visit(Overload {
			[](MainMenu& menu) {
				menu.handleInput();
			},
			[](Gameplay& gameplay) {
				gameplay.handleInput();
			}
		}, m_currentState);
}

void App::update() {
	UpdateMusicStream(m_music);
	std::visit(Overload {
			[](MainMenu& menu) {
				menu.update();
			},
			[](Gameplay& gameplay) {
				gameplay.update();
			}
		}, m_currentState);
}

void App::draw() {
	BeginDrawing();
	std::visit(Overload {
			[](MainMenu& menu) {
				menu.draw();
			},
			[](Gameplay& gameplay) {
				gameplay.draw();
			}
		}, m_currentState);
	EndDrawing();
}

void App::toggleFullscreen() {
	if (IsWindowFullscreen()) {
		ToggleFullscreen();
		SetWindowSize(m_windowWidth, m_windowHeight);
	} else {
		m_windowWidth = GetScreenWidth();
		m_windowHeight = GetScreenHeight();
		int monitor = GetCurrentMonitor();
		SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
		ToggleFullscreen();
	}
}

MainMenu::MainMenu() {
	SetExitKey(KEY_ESCAPE);
}

void MainMenu::handleInput() {
	//TODO: idk
}

void MainMenu::update() {
	//TODO: add something here maybe?
}

void MainMenu::draw() {
	ClearBackground(BLACK);
	const float centreX = static_cast<float>(GetRenderWidth() / 2);
	const float centreY = static_cast<float>(GetRenderHeight() / 2);
	const Rectangle centredRectangle {
		.x = centreX - 250,
		.y = centreY - 60,
		.width = centreX + 250,
		.height = centreY + 60
	};
	
	if (GuiButton(centredRectangle, "play the game")) {
		std::println("HELLO MAN");
		App::getInstance().setState<Gameplay>();
	}

	if (GuiButton(Rectangle {600, 600, 100, 100}, "do not play the game")) {
		App::getInstance().shouldClose();
	}
	
}

void Gameplay::update() {
	//TODO: add physics logic here
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
	EndMode3D();

	// Draw HUD
	DrawText(std::format("speed: {:.2f} globules per hobgoblin", m_currentSpeed).c_str(), 10, 10, 40, YELLOW);
	DrawText(std::format("x: {:.2f} y: {:.2f} z: {:.2f}", m_camera.target.x, m_camera.target.y, m_camera.target.z).c_str(), 10, 50, 40, YELLOW);

	//Draw pause menu
	if (m_showMenu) {
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5));
		if (GuiButton(Rectangle {100, 100, 500, 100}, "go bac to menu")) {
			App::getInstance().setState<MainMenu>();
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
		if ((IsKeyDown(KEY_E) || GetMouseWheelMove() < 0) && m_currentSpeed > 1) m_currentSpeed -= 0.1f;
	}
}


Gameplay::Gameplay() {
	DisableCursor();
	SetExitKey(KEY_NULL);
}


void Gameplay::toggleMenu() {
	if (m_showMenu) {
		DisableCursor();
	} else {
		EnableCursor();
	}
	m_showMenu = !m_showMenu;
}


