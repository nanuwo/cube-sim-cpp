#pragma once
#include "audio.h"
#include "gameplay.h"
#include "mainmenustate.h"
#include "screens.h"
#include <memory>
#include <stack>

class IAppState {
public:
	virtual void Draw() = 0;
	virtual void Update() = 0;
};

class App {
private:
	IAppState* m_state {};
	std::stack<std::reference_wrapper<Screen>> m_screens {};
	AudioManager m_audioManager {};
public:
	App(IAppState* state);
	~App();
	void ChangeState(IAppState* const newState);
	void Update();
	void Draw();
};