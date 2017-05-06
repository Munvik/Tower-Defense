#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif // !NOMINMAX

#define WIDTH 1200
#define HEIGHT 1000

#include <Windows.h>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <math.h>
#include "buttonSwitcher.hpp"
#include "game.hpp"
#include <algorithm>

template <typename T>
void print(T t)
{
	std::cout << t << std::endl;
}

template <typename T>
void print(std::string cap, T t)
{
	std::cout <<cap << " "<< t << std::endl;
}

std::string intToString(int number);
std::string floatToString(float number);

sf::Vector2f getMiddlePosition(sf::FloatRect pointObject, sf::FloatRect positioningObject);
sf::Vector2f getMidlePosition(sf::Vector2f pointPos, sf::FloatRect positioningObject);
sf::Vector2f getMousePos();

bool objectClicked(sf::FloatRect object);
bool isPositive(float number);
bool isNegative(float number);


