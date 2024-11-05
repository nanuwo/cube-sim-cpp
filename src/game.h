#pragma once
#include <raylib.h>

class Game {
public:
	Game();
	~Game();
private:
	int m_windowWidth;
	int m_windowHeight;
	Camera3D camera;
	void UpdateThirdPersonCamera(Camera* camera, float currentSpeed);
	void HandleInput();
	void ToggleFullscreen();
	
};
