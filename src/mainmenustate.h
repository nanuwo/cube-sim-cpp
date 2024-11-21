#pragma once
#include "app.h"
#include <optional>

class MainMenu : public IAppState {

public:
	void Draw() override;
	void Update() override;
};