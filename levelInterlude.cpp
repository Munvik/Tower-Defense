#include "pch.hpp"
#include "levelInterlude.hpp"
#include "game.hpp"
#include "mainGame.hpp"

levelInterlude::levelInterlude(int currentlevel)
{
	setFont(*game::getInstance()->getFont());
	setCharacterSize(200);
	setColor(sf::Color(90, 90, 140));
	setString("Level " + intToString(currentlevel));
	sf::FloatRect backgroundRect = mainGame::getInstance()->getMap()->getBackgroundBounds();
	setPosition(getMiddlePosition(backgroundRect,getGlobalBounds()));

	timer = sf::Time::Zero;
	skip = false;
}

levelInterlude::~levelInterlude()
{
}

void levelInterlude::update()
{
	timer += game::getInstance()->getTimer();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		skip = true;
	}
}

bool levelInterlude::skipped()
{
	if ((timer >= period) || (skip))
		return true;

	return false;
}
