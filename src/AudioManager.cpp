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

