#pragma once

#include "SFML/Audio.hpp"

class Audio {
private:
	sf::Sound sound;

	sf::Music SOUNDTRACK;
	sf::SoundBuffer SWITCH_SOUND;
	sf::SoundBuffer RESULT_SOUND;
public:
	Audio() {
		SWITCH_SOUND.loadFromFile("./assets/audio/Switch.wav");
		RESULT_SOUND.loadFromFile("./assets/audio/win.wav");
		SOUNDTRACK.openFromFile("./assets/audio/music.ogg");
	}
	void PlaySwitchSound() {
		sound.setBuffer(SWITCH_SOUND);
		sound.play();
	}
	void PlayResultSound() {
		sound.setBuffer(RESULT_SOUND);
		sound.play();
	}
	void PlaySoundtrack() {
		SOUNDTRACK.setVolume(5.0f);
		SOUNDTRACK.play();
		SOUNDTRACK.setLoop(true);
	}
	void StopSoundtrack() {
		SOUNDTRACK.stop();
	}
};