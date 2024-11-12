#include "audio.h"

AudioManager::AudioManager() {
	InitAudioDevice();
	doomMusic = LoadMusicStream(ASSETS_PATH"doom.ogg");
	PlayMusicStream(doomMusic);
}

AudioManager::~AudioManager() {
	UnloadMusicStream(doomMusic);
	CloseAudioDevice();
}

void AudioManager::Update() {
	UpdateMusicStream(doomMusic);
}
