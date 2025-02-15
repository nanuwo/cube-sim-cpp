#include "App.hpp"
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <format>
#include <print>

int main() {
	constexpr int windowWidth = 1024;
	constexpr int windowHeight = 640;

	InitWindow(windowWidth, windowHeight, "cube simulator 3d 2: it's cubin' time");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetConfigFlags(FLAG_WINDOW_HIGHDPI);
	GuiSetStyle(DEFAULT, TEXT_SIZE, 50);
	InitAudioDevice();
	SetTargetFPS(60);

	App& app = App::getInstance();
	app.setState(std::make_unique<MainMenu>());
	while (!WindowShouldClose() && !app.shouldClose()) {
		app.handleInput();
		app.update();
		app.draw();
	}
	CloseWindow();
	CloseAudioDevice();
}