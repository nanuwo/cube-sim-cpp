#include "audio.h"
#include "game.h"
#include <format>


enum class AppState {
	Menu,
	Running,
};

void SwitchFullscreen(int& windowWidth, int& windowHeight) {
	if (IsWindowFullscreen()) {
		ToggleFullscreen();
		SetWindowSize(windowWidth, windowHeight);
	} else {
		windowWidth = GetRenderWidth();
		windowHeight = GetRenderHeight();
		int monitor = GetCurrentMonitor();
		SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
		ToggleFullscreen();
	}
	
}

int main() {

	int windowWidth = 1024;
	int windowHeight = 640;

	InitWindow(windowWidth, windowHeight, "cube simulator 3d 2: it's cubin' time");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	DisableCursor();

	Game game{};
	AudioManager audioManager{};

	while (!WindowShouldClose()) {

		if (IsKeyPressed(KEY_F)) {
			SwitchFullscreen(windowWidth, windowHeight);
		}

		audioManager.Update();
		game.Update();
	}
	CloseWindow();
}