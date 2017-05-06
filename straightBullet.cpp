#include "pch.hpp"
#include "straightBullet.hpp"
#include "mainGame.hpp"

straightBullet::straightBullet(std::string textureName, sf::Vector2f vel, sf::Vector2f destination, sf::Vector2f startPos)
	:bullet(textureName)
{
	sf::Vector2f thisPos = getMidlePosition(startPos, getGlobalBounds());
	sprite.setPosition(thisPos);
	destinationPoint = destination;
	velocity = vel;

	this->targetAchieved = false;
}

void straightBullet::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);

}

void straightBullet::update()
{
	float time = game::getInstance()->getTimer().asSeconds();

	sf::Vector2f movement = velocity * time;

	if (destinationAchieved(movement))
	{
		targetAchieved = true;
		return;
	}

	sprite.move(movement);

}

bool straightBullet::achieved()
{
	return targetAchieved;
}


bool straightBullet::destinationAchieved(sf::Vector2f movement)
{
	sf::Vector2f currVector = destinationPoint - getCenter();
	sf::Vector2f nextVector = destinationPoint - (getCenter() + movement);

	double currentDist = sqrt(currVector.x * currVector.x + currVector.y * currVector.y);

	double nextDist = sqrt(nextVector.x * nextVector.x + nextVector.y * nextVector.y);

	if (nextDist > currentDist)
		return true;

	return false;

	/*if (sprite.getGlobalBounds().contains(destinationPoint))
		return true;

	return false;*/
}
