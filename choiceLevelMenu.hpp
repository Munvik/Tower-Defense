#pragma once
#include "gameCtrl.hpp"
#include "button.hpp"
#include "DefaultFont.hpp"

class choiceLevelMenu :public gameCtrl, private Font
{
	sf::Sprite easyLevelScreen;
	sf::Sprite mediumLevelScreen;
	sf::Sprite hardLevelScreen;
	sf::Texture textureScreens[3];

	sf::Sprite background;
	sf::Texture tBackground;

	sf::Text text;
	sf::Text textEasy;
	sf::Text textMedium;
	sf::Text textHard;

	button buttonBack;
	std::string fileName;

	void loadTextures();
	void makeSettings();
	void handleButton();
	void handleScreens();

public:
	choiceLevelMenu();
	~choiceLevelMenu();
	void update();
	void draw(sf::RenderWindow &window);
};