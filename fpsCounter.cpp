#include "pch.hpp"
#include "fpsCounter.h"

fpsCounter::fpsCounter()
{
	if (!font.loadFromFile("Fonty/Lato-Medium.ttf"))
	{
		MessageBox(0, "Unable to load Anorexia.ttf", 0, 0);
	}

	fps = 0;
	timer = sf::Time::Zero;

	fpsText.setFont(font);
	fpsText.setCharacterSize(30);
	fpsText.setColor(sf::Color(200, 200, 220));
	fpsText.setString("fps = ");
}

fpsCounter::~fpsCounter()
{
}

void fpsCounter::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(fpsText);
}

void fpsCounter::countTime(sf::Time & gameTimer)
{
	timer += gameTimer;

	if (timer >= second)
	{
		fpsText.setString("fps = " + intToString(fps));
		fps = 0;
		timer = sf::Time::Zero;
	}
}

fpsCounter & fpsCounter::operator++()
{
	fps++;
	return *this;
}
