#include "app.h"
#include <mainmenustate.h>

App::App(IAppState* state) : m_state { state } {}

App::~App() {
	delete m_state;
}

void App::ChangeState(IAppState* const newState) {
	delete m_state;
	GameplayState newestState { new GameplayState{} };
	m_state = &newestState;
}

void App::Update() {
	m_state->Update();
	m_screens.top().get().Update();
	m_audioManager.Update();
}

void App::Draw() {
	BeginDrawing();
	m_state->Draw();
	EndDrawing();
}

