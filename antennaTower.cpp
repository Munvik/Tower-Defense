#include "pch.hpp"
#include "antennaTower.hpp"
#include "mainGame.hpp"
#include "attackTower.hpp"

antennaTower::antennaTower()
{
	loadTexture();
	setAttributes();
}

void antennaTower::loadTexture()
{
	texture = *mainGame::getInstance()->textures.getTowerTexture("antennaTower");
	sprite.setTexture(texture);

	sf::Vector2u textureSize = texture.getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 3, textureSize.y));
}

void antennaTower::setAttributes()
{
	powerBuff = 0.1f;
	rangeBuff = 0.1f;
	range = 180.f;
	cost = 200;
	levelAcces = 8;
	value = cost;

	description = "Buffs power\nand range\nin itself range";
	buffArea.setRadius(range);
}

void antennaTower::update()
{
}

void antennaTower::build()
{
	builded = true;
	buffOtherTowers();
}

void antennaTower::buffOtherTowers()
{
	map *gameMap = mainGame::getInstance()->getMap();

	buff powerFactor(buff::power, powerBuff);
	buff rangeFactor(buff::range, rangeBuff);

	for (size_t i = 0; i < gameMap->towers.size(); ++i)
	{
		if (canBuff(gameMap->towers[i].get()))
		{
			gameMap->towers[i]->addBuff(powerFactor);
			gameMap->towers[i]->addBuff(rangeFactor);
		}
	}
}

void antennaTower::debuffOtherTowers()
{
	map *gameMap = mainGame::getInstance()->getMap();

	buff powerFactor(buff::power, powerBuff);
	buff rangeFactor(buff::range, rangeBuff);

	for (size_t i = 0; i < gameMap->towers.size(); ++i)
	{
		if (canBuff(gameMap->towers[i].get()))
		{
			gameMap->towers[i]->removeBuff(powerFactor);
			gameMap->towers[i]->removeBuff(rangeFactor);
		}
	}
}

void antennaTower::buf(attackTower * buffingTower)
{
	if (canBuff(buffingTower))
	{
		buff Pbuff(buff::power, powerBuff);
		buff Rbuff(buff::range, rangeBuff);
		buffingTower->addBuff(Pbuff);
		buffingTower->addBuff(Rbuff);
	}
}


void antennaTower::sell()
{
	debuffOtherTowers();

	tower::sell();
}


std::shared_ptr<tower> antennaTower::getClassObject()
{
	std::shared_ptr<tower> obj = std::make_shared<antennaTower>();

	return obj;
}

