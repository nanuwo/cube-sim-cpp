#pragma once
#include "BeeModel.hpp"
#include <raylib.h>
#include <memory>

class AppState {
public:
	virtual ~AppState() = default;
	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};

class MainMenu : public AppState {
public:
	MainMenu();
	
	void handleInput() override;
	void update() override;
	void draw() override;
};

class App {
private:
	int m_windowWidth = GetScreenWidth();
	int m_windowHeight = GetScreenHeight();
	bool m_shouldClose = false;
	std::unique_ptr<AppState> m_currentState;
	Music m_music = LoadMusicStream(ASSETS_PATH"doom.ogg");
	BeeModel m_beeModel {};

	App();
	~App();

	// Delete the copy constructor and assignment operator: this class is a singleton
	App(const App&) = delete;
	App& operator=(const App&) = delete;

public:
	static App& getInstance();

	void setState(std::unique_ptr<AppState> newState);
	bool shouldClose();
	void close();
	void handleInput();
	void update();
	void draw();
	void toggleFullscreen();
	BeeModel& getBeeModel();
};

