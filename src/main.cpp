#include "audio.h"
#include "app.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <format>

// Workaround for raylib not fully going into fullscreen mode
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
	int windowWidth { 1024 };
	int windowHeight { 640 };

	InitWindow(windowWidth, windowHeight, "cube simulator 3d 2: it's cubin' time");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetConfigFlags(FLAG_WINDOW_HIGHDPI);
	SetExitKey(KEY_NULL);
	GuiSetStyle(DEFAULT, TEXT_SIZE, 50);

	App app {};

	while (!WindowShouldClose()) {

		if (IsKeyPressed(KEY_F)) {
			SwitchFullscreen(windowWidth, windowHeight);
		}

	}
	CloseWindow();
}