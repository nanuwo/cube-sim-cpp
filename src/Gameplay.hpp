#pragma once
#include "App.hpp"
#include <raylib.h>


class Gameplay : public AppState {
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
	virtual ~Gameplay();
	Gameplay(const Gameplay&) = delete;
	Gameplay operator=(const Gameplay&) = delete;

	void handleInput() override;
	void update() override;
	void draw() override;
};