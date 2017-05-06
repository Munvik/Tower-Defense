#include "pch.hpp"
#include "gameLoader.hpp"

gameLoader::gameLoader()
{
	frame.setSize(sf::Vector2f(WIDTH * 3 / 5, HEIGHT / 15));
	frame.setFillColor(sf::Color(20,20,20));
	frame.setOutlineThickness(difference);
	frame.setOutlineColor(sf::Color::Red);

	loaderWidth = frame.getSize().x - 2 * difference;
	loader.setSize(sf::Vector2f(1.f, frame.getSize().y - 2 * difference));
	loader.setFillColor(sf::Color(90,90,90));

}

gameLoader::~gameLoader()
{
}

void gameLoader::setPosition(sf::Vector2f position)
{
	frame.setPosition(position);
	loader.setPosition(position.x + difference, position.y + difference);
}

sf::Vector2f gameLoader::getSize()
{
	return frame.getSize();
}

sf::FloatRect gameLoader::getGlobalBounds()
{
	return frame.getGlobalBounds();
}

void gameLoader::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(frame);
	target.draw(loader);
}

void gameLoader::load(float procent)
{
	loader.setSize(sf::Vector2f(procent * loaderWidth, loader.getSize().y));
}
