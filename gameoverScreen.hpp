#pragma once
#include "gameCtrl.hpp"
#include "menuParticleSystem.hpp"
#include "button.hpp"

class gameoverScreen :public gameCtrl
{
	sf::Sprite background;
	sf::Texture backgroundT;
	button backButton;
	menuParticleSystem particleSystem;
	sf::Sound sound;
	sf::SoundBuffer soundBuffer;

public:
	gameoverScreen();
	~gameoverScreen();
	void update() override;
	void draw(sf::RenderWindow &window);
};