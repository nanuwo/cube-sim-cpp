#include "App.hpp"
#include "Gameplay.hpp"
#include <raygui.h>
#include <raylib.h>
#include <format>
#include <memory>
#include <print>

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

void App::setState(std::unique_ptr<AppState> newState) {
	m_currentState = std::move(newState);
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
	m_currentState->handleInput();
}

void App::update() {
	UpdateMusicStream(m_music);
	m_currentState->update();
}

void App::draw() {
	BeginDrawing();
	m_currentState->draw();
	EndDrawing();
}

void App::toggleFullscreen() {
	if (!IsWindowFullscreen()) {
		int monitor = GetCurrentMonitor();
		SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
		ToggleFullscreen();

	} else {
		ToggleFullscreen();
		SetWindowSize(m_windowWidth, m_windowHeight);
	}
}

BeeModel& App::getBeeModel() {
	return m_beeModel;
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
	ClearBackground(GREEN);
	const char* title = "cube simulator 3d 2";
	const char* subtitle = "it's cubin' time";
	const int titleSize = 100;
	const int subtitleSize = 50;
	const int screenCentreX = GetRenderWidth() / 2;
	const int screenCentreY = GetRenderHeight() / 2;
	DrawText(title, screenCentreX - MeasureText(title, titleSize) / 2, screenCentreY + 50, titleSize, YELLOW);
	DrawText(subtitle, screenCentreX - MeasureText(subtitle, subtitleSize) / 2, screenCentreY - 50, subtitleSize, ORANGE);
	if (GuiButton(Rectangle {100.0f, 100.0f, 600.0f, 100.0f}, "play the game")) {
		App::getInstance().setState(std::make_unique<Gameplay>());
	}

	if (GuiButton(Rectangle {GetRenderWidth() - 700.0f, GetRenderHeight() - 200.0f, 600.0f, 100.0f}, "unplay the game")) {
		App::getInstance().close();
	}
}
