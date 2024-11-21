#include "audio.h"

AudioManager::AudioManager() {
	InitAudioDevice();
	PlayMusicStream(doomMusic);
}

AudioManager::~AudioManager() {
	UnloadMusicStream(doomMusic);
	CloseAudioDevice();
}

void AudioManager::Update() {
	UpdateMusicStream(doomMusic);
}
