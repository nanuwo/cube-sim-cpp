#pragma once

#include <raylib.h>

class AudioManager {
public:
	AudioManager();
	~AudioManager();
	void Update();
private:
	Music doomMusic { LoadMusicStream(ASSETS_PATH"doom.ogg") };
};