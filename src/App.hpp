#pragma once
#include <raylib.h>
#include <memory>
#include <variant>

class MainMenu {
public:
	void handleInput();
	void update();
	void draw();
};


class Gameplay {
private:
	bool m_showMenu = false;
	float m_currentSpeed = 0;
	Camera3D m_camera {
		.position {10.0f, 10.0f, 10.0f},
		.target {0.0f, 0.0f, 0.0f},
		.up {0.0f, 1.0f, 0.0f},
		.fovy = 70.0f,
		.projection = CameraProjection::CAMERA_PERSPECTIVE,
	};

	void toggleMenu();
	
public:
	Gameplay();

	void handleInput();
	void update();
	void draw();
};


class App {
private:
	int m_windowWidth = GetScreenWidth();
	int m_windowHeight = GetScreenHeight();
	std::variant<MainMenu, Gameplay> m_currentState;
	Music m_music = LoadMusicStream(ASSETS_PATH"doom.ogg");

	App();
	~App();

	// Delete the copy constructor and assignment operator: this class is a singleton
	App(const App&) = delete;
	App& operator=(const App&) = delete;

public:
	static App& getInstance();

	template <typename State>
	void setState() {
		m_currentState = State {};
	}

	void handleInput();
	void update();
	void draw();
	void toggleFullscreen();
};

