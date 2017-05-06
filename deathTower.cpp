#include "pch.hpp"
#include "deathTower.hpp"
#include "mainGame.hpp"

deathTower::deathTower()
{
	textureName = "deathTower";
	loadTexture();
	setAttributes();
}

deathTower::~deathTower()
{
}

void deathTower::setAttributes()
{
	cost = 2000;
	power = 5000;
	range = 200.f;
	speed = 1000.f;
	levelAcces = 18;
	bulletSpeed = 700.f;
	value = cost;
	timer = sf::milliseconds(sf::Int32(speed * 3 / 4));

	attackCircle.setRadius(range);
	sf::Vector2f circlePos;
	circlePos.x = getPosition().x + getSize().x / 2 - attackCircle.getGlobalBounds().width / 2;
	circlePos.y = getPosition().y + getSize().y / 2 - attackCircle.getGlobalBounds().height / 2;
	attackCircle.setPosition(circlePos);
	description = "Biggest dmg\nAttacks randomly";
	bulletTextureName = "deathTowerBullet";
}

void deathTower::loadTexture()
{
	texture = *mainGame::getInstance()->textures.getTowerTexture(textureName);
	sprite.setTexture(texture);

	sf::Vector2u textureSize = texture.getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 3, textureSize.y));
}


void deathTower::searchTarget()
{
	std::vector<wave*> & monsters = mainGame::getInstance()->getWaves();
	std::vector<std::shared_ptr<monster>> monsts;

	for (size_t i = monsters.size(); i-- > 0;)
	{
		for (size_t j = monsters[i]->size(); j-- > 0;)
		{
			if (monsters[i]->operator[](int(j))->isUnavailable())
				continue;

			else if (isTargetInRange(monsters[i]->operator[](int(j))))
			{
				monsts.push_back(monsters[i]->operator[](int(j)));
			}
		}
	}

	if (monsts.empty())
		return;
	else
	{
		targetingMonster = monsts[rand() % monsts.size()];
	}
}

void deathTower::handleBullets()
{
	for (size_t i = 0; i < bullets.size(); ++i)
	{
		bullets[i].rotate();
		bullets[i].update();
	}
}

std::shared_ptr<tower> deathTower::getClassObject()
{
	std::shared_ptr<tower> obj = std::make_shared<deathTower>();

	return obj;
}


