#include "pch.hpp"
#include <sstream>

std::string intToString(int number)
{
	std::stringstream ss;

	ss << number;
	return ss.str();
}

std::string floatToString(float number)
{
	std::ostringstream ss;

	ss << number;

	return ss.str();
}

sf::Vector2f getMiddlePosition(sf::FloatRect pointObject, sf::FloatRect positioningObject)
{
	sf::Vector2f middlePos;
	middlePos.x = pointObject.left + pointObject.width / 2 - positioningObject.width / 2;
	middlePos.y = pointObject.top + pointObject.height / 2 - positioningObject.height / 2;

	return middlePos;
}

sf::Vector2f getMidlePosition(sf::Vector2f pointPos, sf::FloatRect positioningObject)
{
	sf::Vector2f middlePos;
	middlePos.x = pointPos.x - positioningObject.width / 2;
	middlePos.y = pointPos.y - positioningObject.height / 2;

	return middlePos;
}

sf::Vector2f getMousePos()
{
	return sf::Vector2f(sf::Mouse::getPosition(game::getInstance()->getWindow()));
}

bool objectClicked(sf::FloatRect object)
{
	if ((object.contains(getMousePos())) && (buttonSwitcher::canClick()) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
		return true;

	return false;
}

bool isPositive(float number)
{
	if (number > 0)
		return true;

	return false;
}

bool isNegative(float number)
{
	if (number < 0)
		return true;

	return false;
}

