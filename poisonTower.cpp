#include "pch.hpp"
#include "poisonTower.hpp"
#include "mainGame.hpp"

poisonTower::poisonTower()
{
	loadTexture();
	setAttributes();
}

poisonTower::~poisonTower()
{

}

void poisonTower::setAttributes()
{
	cost = 150;
	power = 70;
	range = 140.f;
	speed = 1800.f;
	levelAcces = 3;
	bulletSpeed = 600.f;
	value = cost;
	timer = sf::milliseconds(sf::Int32(speed * 3 / 4));

	attackCircle.setRadius(range);
	sf::Vector2f circlePos;
	circlePos.x = getPosition().x + getSize().x / 2 - attackCircle.getGlobalBounds().width / 2;
	circlePos.y = getPosition().y + getSize().y / 2 - attackCircle.getGlobalBounds().height / 2;
	attackCircle.setPosition(circlePos);
	attackCircle.setFillColor(sf::Color(170, 80, 80, 100));
	description = "Poisoning enemys";
	bulletTextureName = "poisonTowerBullet";
}

void poisonTower::handleBullets()
{
	for (size_t i = 0; i < bullets.size(); ++i)
	{
		bullets[i].update();
	}
}

std::shared_ptr<tower> poisonTower::getClassObject()
{
	std::shared_ptr<tower> obj = std::make_shared<poisonTower>();

	return obj;
}

void poisonTower::attackMonster(std::shared_ptr<monster> monst)
{
	std::shared_ptr<monsterEffect> poison = std::make_shared<poisonEffect>(monst, power + int(power * powerBuffFactor), this);
	monst->getEffectHandler().addEffect(poison);
}

void poisonTower::searchTarget()
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

void poisonTower::loadTexture()
{
	texture = *mainGame::getInstance()->textures.getTowerTexture("poisonTower");
	sprite.setTexture(texture);

	sf::Vector2u textureSize = texture.getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 3, textureSize.y));
}
