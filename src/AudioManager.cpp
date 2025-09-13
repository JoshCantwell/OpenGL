#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "AudioManager.h"
#include <iostream>

bool AudioManager::init() {
	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		std::cerr << "SDL_Init Audio failed: " << SDL_GetError() << std::endl;
		return false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cerr << "Mix_OpenAudio failed: " << Mix_GetError() << std::endl;
		return false;
	}
	return true;
}

void AudioManager::loadSound(const std::string& id, const std::string& path) {
	Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
	if (!chunk) {
		std::cerr << "Failed to load sound: " << path << " - " << Mix_GetError() << std::endl;
		return;
	}
	sounds[id] = chunk;
}

void AudioManager::playSound(const std::string& id) {
	auto it = sounds.find(id);
	if (it != sounds.end()) {
		Mix_PlayChannel(-1, it->second, 0);
	}
}

void AudioManager::cleanUp() {
	for (auto& pair : sounds) {
		Mix_FreeChunk(pair.second);
	}
	sounds.clear();
	Mix_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);  // Important: don't call SDL_Quit here unless you're done with all SDL
}


// Set volume globally for ALL playing channels
void AudioManager::setVolume(int volume) {
	// Clamp volume between 0 and MIX_MAX_VOLUME (128)
	if (volume < 0) volume = 0;
	if (volume > MIX_MAX_VOLUME) volume = MIX_MAX_VOLUME;

	Mix_Volume(-1, volume);  // -1 affects all channels
}

// Set volume for a specific sound BEFORE it's played
void AudioManager::setSoundVolume(const std::string& id, int volume) {
	if (volume < 0) volume = 0;
	if (volume > MIX_MAX_VOLUME) volume = MIX_MAX_VOLUME;

	auto it = sounds.find(id);
	if (it != sounds.end()) {
		Mix_VolumeChunk(it->second, volume);  // Future plays of this sound will use this volume
	} else {
		std::cerr << "Sound ID not found: " << id << std::endl;
	}
}
