#include "pch.hpp"
#include "archerTower.hpp"
#include "mainGame.hpp"
#include <math.h>

archerTower::archerTower()
{
	loadTexture();
	setAttributes();
}

archerTower::~archerTower()
{
}

void archerTower::handleBullets()
{
	for (size_t i = 0; i < bullets.size(); ++i)
	{
		bullets[i].rotate();
		bullets[i].update();
	}
}

std::shared_ptr<tower> archerTower::getClassObject()
{
	std::shared_ptr<tower> obj = std::make_shared<archerTower>();

	return obj;
}

void archerTower::setAttributes()
{
	cost = 40;
	power = 60;
	range = 210.f;
	speed = 250.f;
	levelAcces = 1;
	bulletSpeed = 900.f;
	value = cost;

	attackCircle.setRadius(range);
	sf::Vector2f circlePos;
	circlePos.x = getPosition().x + getSize().x / 2 - attackCircle.getGlobalBounds().width / 2;
	circlePos.y = getPosition().y + getSize().y / 2 - attackCircle.getGlobalBounds().height / 2;
	attackCircle.setPosition(circlePos);
	timer = sf::milliseconds(sf::Int32(speed * 3 / 4));

	description = "Simple turret";
	bulletTextureName = "archerTowerBullet";
}

void archerTower::loadTexture()
{
	texture.loadFromFile("Textury/Towers/archerTower/archerTower.png");
	sprite.setTexture(texture);

	sf::Vector2u textureSize = texture.getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 3, textureSize.y));
}