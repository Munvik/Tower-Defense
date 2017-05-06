#pragma once
#include "pch.hpp"
#include "gameCtrl.hpp"
#include "buttonSwitcher.hpp"
#include "fpsCounter.h"
#define mainLoop

class game
{
	static game *instance;

	sf::RenderWindow window;
	sf::Event evnt;
	sf::Font font;
	sf::Image icon;

	std::unique_ptr <gameCtrl> gameController;

	sf::Time accumulator;
	const sf::Time frameTime = sf::seconds(1.f / 120.f);
	sf::Clock clock;

	sf::Time timer;
	sf::Clock clocker;

	fpsCounter fpser;
	sf::Music music;
	void loadFont();


public:
	game();
	~game();

	void run();

	static game *getInstance();
	sf::RenderWindow & getWindow();
	sf::Font *getFont();
	sf::Time getTimer();
	void setController(std::unique_ptr <gameCtrl> newController);
	void exit();
	sf::Music * getMusic();
	void hurryUpTime();
};