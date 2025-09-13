#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>
#include <unordered_map>

class AudioManager {


	public:
		bool init();
		void loadSound(const std::string& id, const std::string& path);
		void playSound(const std::string& id);
		void cleanUp();
		void setVolume(int volume);
		void setSoundVolume(const std::string& id, int volume);


	private:
		std::unordered_map<std::string, Mix_Chunk*> sounds;
};

