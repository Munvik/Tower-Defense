#pragma once

#include "gameCtrl.hpp"

class gameCompletedScreen :public gameCtrl
{
	enum state {screenLocking, screenOpening, screenOpened};

	sf::Sprite background;
	sf::Texture backgroundT;
	
	sf::Sprite gameEndSprite;
	sf::Texture gameEndSpriteT;

	sf::RectangleShape rects[2];
	const float rectSpeed = 500;

	state currentState;
public:
	gameCompletedScreen(const sf::Image wndImg);
	~gameCompletedScreen();

	void update() override;
	void draw(sf::RenderWindow &window) override;
};