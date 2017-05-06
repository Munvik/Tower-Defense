#include "pch.hpp"
#include "animation.hpp"
#include "mainGame.hpp"

animation::animation(std::string animationName, int _frames, float frameTim)
{
	frames = _frames;
	frameTime = sf::seconds(frameTim);

	texture = mainGame::getInstance()->textures.getAnimation(animationName);

	spriteWidth = texture->getSize().x / 5;

	if (frames >= 21)
	{
		spriteHeight = texture->getSize().y / 5;
	}
	else if (frames >= 16)
	{
		spriteHeight = texture->getSize().y / 4;
	}
	else if (frames >= 11)
	{
		spriteHeight = texture->getSize().y / 3;
	}
	else if (frames >= 6)
	{
		spriteHeight = texture->getSize().y / 2;
	}
	else spriteHeight = texture->getSize().y;

	setTexture(*texture);

	setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteHeight));


	timer = sf::Time::Zero;
	frameCounter = 1;
}


animation::~animation()
{
}

void animation::update()
{
	timer += game::getInstance()->getTimer();

	if (timer >= frameTime)
	{
		nextFrame();
		timer = sf::Time::Zero;
		frameCounter++;
	}
}

bool animation::end()
{
	return (frameCounter == frames);
}

void animation::repeat()
{
	setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteHeight));

	timer = sf::Time::Zero;
	frameCounter = 1;
}

sf::Vector2f animation::getCenter()
{
	sf::Vector2f center;
	center.x = getPosition().x + getGlobalBounds().width / 2;
	center.y = getPosition().y + getGlobalBounds().height / 2;

	return center;
}

sf::Vector2f animation::getSize()
{
	sf::Vector2f size;
	size.x = getGlobalBounds().width;
	size.y = getGlobalBounds().height;

	return size;
}

void animation::nextFrame()
{
	sf::IntRect currentRect = getTextureRect();

	if (frameCounter % 5 == 0)
	{
		currentRect.top += spriteHeight;
		currentRect.left = 0;
	}
	else
		currentRect.left += spriteWidth;

	setTextureRect(currentRect);
}