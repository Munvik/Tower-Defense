#pragma once
#include "gameCtrl.hpp"
#include "DefaultFont.hpp"
#include "menuParticleSystem.hpp"
#include "button.hpp"
#include <thread>

#define MAINMENU

class mainMenu :public gameCtrl, private Font
{
	std::thread loadingThread;
	sf::Text title;
	menuParticleSystem particleSystem;

	std::vector <button> buttons;
	void handleButtons();

	int currentButton;
	void followFunc(int index);

public:
	mainMenu();
	~mainMenu();

	void update();
	void draw(sf::RenderWindow &window);
};