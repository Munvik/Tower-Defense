#define NOMINMAX
#include "pch.hpp"
#include "choiceLevelMenu.hpp"
#include "game.hpp"
#include <limits.h>
#include "mainMenu.hpp"
#include "mainGame.hpp"


choiceLevelMenu::choiceLevelMenu()
{
	loadTextures();
	makeSettings();

	fileName.clear();
}

choiceLevelMenu::~choiceLevelMenu()
{
}

void choiceLevelMenu::update()
{
	handleButton();
	handleScreens();
}

void choiceLevelMenu::draw(sf::RenderWindow & window)
{
	window.draw(background);
	window.draw(easyLevelScreen);
	window.draw(mediumLevelScreen);
	window.draw(hardLevelScreen);
	window.draw(text);
	window.draw(textEasy);
	window.draw(textMedium);
	window.draw(textHard);
	window.draw(buttonBack);
}

void choiceLevelMenu::loadTextures()
{
	if (!textureScreens[0].loadFromFile("Textury/EasyLevelScreen.png"))
	{
		MessageBox(0, "Unable to load EasyLvlScreen.png", 0, 0);
		return;
	}
	easyLevelScreen.setTexture(textureScreens[0]);

	if (!textureScreens[1].loadFromFile("Textury/MediumLevelScreen.png"))
	{
		MessageBox(0, "Unable to load MediumLvlScreen.png", 0, 0);
		return;
	}
	mediumLevelScreen.setTexture(textureScreens[1]);

	if (!textureScreens[2].loadFromFile("Textury/HardLevelScreen.png"))
	{
		MessageBox(0, "Unable to load HardLvlScreen.png", 0, 0);
		return;
	}
	hardLevelScreen.setTexture(textureScreens[2]);

	if (!tBackground.loadFromFile("Textury/background1.png"))
	{
		MessageBox(0, "Unable to load background1", 0, 0);
		return;
	}
	background.setTexture(tBackground);
}

void choiceLevelMenu::makeSettings()
{
	sf::Vector2f screen1(200, HEIGHT * 0.4f);
	easyLevelScreen.setPosition(screen1);

	sf::Vector2f screen2(200 + 200 + 100, HEIGHT * 0.4f);
	mediumLevelScreen.setPosition(screen2);

	sf::Vector2f screen3(200 + 200 + 100 + 200 + 100, HEIGHT * 0.4f);
	hardLevelScreen.setPosition(screen3);

	text.setFont(font);
	text.setCharacterSize(100);
	text.setColor(sf::Color::Blue);
	text.setString("Choose the level");
	text.setPosition(WIDTH / 2 - text.getGlobalBounds().width / 2, HEIGHT * 1 / 5);

	textEasy.setFont(font);
	textEasy.setCharacterSize(50);
	textEasy.setColor(sf::Color(190, 110, 50));
	textEasy.setString("Easy");
	sf::Vector2f textEasyPosition(easyLevelScreen.getPosition().x + easyLevelScreen.getGlobalBounds().width / 2 - textEasy.getGlobalBounds().width / 2, easyLevelScreen.getPosition().y - textEasy.getGlobalBounds().height * 1.5f);
	textEasy.setPosition(textEasyPosition);

	textMedium.setFont(font);
	textMedium.setCharacterSize(50);
	textMedium.setColor(sf::Color(190, 110, 50));
	textMedium.setString("Medium");
	sf::Vector2f textMediumPosition(mediumLevelScreen.getPosition().x + mediumLevelScreen.getGlobalBounds().width / 2 - textMedium.getGlobalBounds().width / 2, mediumLevelScreen.getPosition().y - textMedium.getGlobalBounds().height * 1.5f);
	textMedium.setPosition(textMediumPosition);

	textHard.setFont(font);
	textHard.setCharacterSize(50);
	textHard.setColor(sf::Color(190, 110, 50));
	textHard.setString("Hard");
	sf::Vector2f textHardPosition(hardLevelScreen.getPosition().x + hardLevelScreen.getGlobalBounds().width / 2 - textHard.getGlobalBounds().width / 2, hardLevelScreen.getPosition().y - textHard.getGlobalBounds().height * 1.5f);
	textHard.setPosition(textHardPosition);

	buttonBack.setFont(font);
	buttonBack.setCharacterSize(60);
	buttonBack.setColor(sf::Color(50, 110, 50));
	buttonBack.setString("Back to menu");
	sf::Vector2f buttonPosition(WIDTH*0.15f, HEIGHT - buttonBack.getGlobalBounds().height * 4.f);
	buttonBack.setPosition(buttonPosition);
}

void choiceLevelMenu::handleButton()
{
	sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(game::getInstance()->getWindow());

	if ((buttonBack.isMouseOn(mousePosition)) && (!buttonBack.isIncreased()))
	{
		buttonBack.increase();
	}

	else if (buttonBack.isClickOn(mousePosition))
	{
		game::getInstance()->setController(std::make_unique<mainMenu>());
	}

	else if (!buttonBack.isMouseOn(mousePosition) && (buttonBack.isIncreased()))
	{
		buttonBack.decrease();
		buttonBack.setColor(sf::Color::Blue);
	}
}

void choiceLevelMenu::handleScreens()
{
	sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(game::getInstance()->getWindow());

	if ((easyLevelScreen.getGlobalBounds().contains(mousePosition)) && (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))&&(buttonSwitcher::canClick()))
	{
		fileName = "easyLevel.txt";
	}
	else if ((mediumLevelScreen.getGlobalBounds().contains(mousePosition)) && (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) && (buttonSwitcher::canClick()))
	{
		fileName = "mediumLevel.txt";
	}
	else if ((hardLevelScreen.getGlobalBounds().contains(mousePosition)) && (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) && (buttonSwitcher::canClick()))
	{
		fileName = "hardLevel.txt";
	}

	if (!fileName.empty())
	{
		game::getInstance()->setController(std::make_unique<mainGame>(fileName));
	}
}
