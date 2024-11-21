#pragma once

class Screen {
public:
	virtual void Update() = 0;
};

class ScreenMain : public Screen {
public:
	void Update();
};

class ScreenPause : public Screen {
public:
	void Update();
};

