#include "pch.hpp"
#include "arcaneTower.hpp"
#include "mainGame.hpp"
#include "explosionableBullet.hpp"

arcaneTower::arcaneTower()
{
	textureName = "arcaneTower";

	loadTexture();
	setAttributes();
}

arcaneTower::~arcaneTower()
{

}

void arcaneTower::setAttributes()
{

	cost = 30;
	power = 70;
	range = 150.f;
	speed = 250.f;
	levelAcces = 1;
	bulletSpeed = 300.f;
	value = cost;
	timer = sf::milliseconds(sf::Int32(speed * 3 / 4));

	attackCircle.setRadius(range);
	sf::Vector2f circlePos;
	circlePos.x = getPosition().x + getSize().x / 2 - attackCircle.getGlobalBounds().width / 2;
	circlePos.y = getPosition().y + getSize().y / 2 - attackCircle.getGlobalBounds().height / 2;
	attackCircle.setPosition(circlePos);
	description = "Simple turret";
	bulletTextureName = "arcaneTowerBullet";
}

void arcaneTower::loadTexture()
{
	texture = *mainGame::getInstance()->textures.getTowerTexture(textureName);
	sprite.setTexture(texture);

	sf::Vector2u textureSize = texture.getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 3, textureSize.y));

}

void arcaneTower::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	attackTower::draw(target, states);
}

void arcaneTower::handleBullets()
{
	for (size_t i = 0; i < bullets.size(); ++i)
	{
		bullets[i].update();
	}
}

std::shared_ptr<tower> arcaneTower::getClassObject()
{
	std::shared_ptr<tower> obj = std::make_shared<arcaneTower>();

	return obj;
}

