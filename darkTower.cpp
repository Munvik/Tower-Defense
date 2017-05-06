#include "pch.hpp"
#include "darkTower.hpp"
#include "mainGame.hpp"

darkTower::darkTower()
{
	textureName = "darkTower";

	loadTexture();
	setAttributes();
	
}


void darkTower::setAttributes()
{
	cost = 300;
	power = 1000;
	range = 220.f;
	speed = 1400.f;
	levelAcces = 10;
	bulletSpeed = 250.f;
	value = cost;
	timer = sf::milliseconds(sf::Int32(speed * 3 / 4));

	attackCircle.setRadius(range);
	sf::Vector2f circlePos;
	circlePos.x = getPosition().x + getSize().x / 2 - attackCircle.getGlobalBounds().width / 2;
	circlePos.y = getPosition().y + getSize().y / 2 - attackCircle.getGlobalBounds().height / 2;
	attackCircle.setPosition(circlePos);

	bulletTextureName = "darkTowerBullet";

	bullet bullettor(bulletTextureName);

	sf::Vector2f bulletPos;
	bulletPos.x = getPosition().x + getSize().x / 2 - bullettor.getGlobalBounds().width / 2;
	bulletPos.y = getPosition().y + getSize().y / 8 - bullettor.getGlobalBounds().height / 2;
	description = "Big dmg";
	startBulletPosition = bulletPos;
}

void darkTower::loadTexture()
{
	texture = *mainGame::getInstance()->textures.getTowerTexture(textureName);
	sprite.setTexture(texture);

	sf::Vector2u textureSize = texture.getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 3, textureSize.y));
}

std::shared_ptr<tower> darkTower::getClassObject()
{
	std::shared_ptr<tower> obj = std::make_shared<darkTower>();

	return obj;
}
