#include "pch.hpp"
#include "signalTower.hpp"
#include "mainGame.hpp"
#include "attackTower.hpp"

signalTower::signalTower()
{
	loadTexture();
	setAttributes();
}

signalTower::~signalTower()
{
}

void signalTower::loadTexture()
{
	texture = *mainGame::getInstance()->textures.getTowerTexture("signalTower");
	sprite.setTexture(texture);

	sf::Vector2u textureSize = texture.getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 3, textureSize.y));
}

void signalTower::setAttributes()
{
	powerBuff = 0.08f;
	rangeBuff = 0.f;
	range = 0.f;
	levelAcces = 30;
	cost = 1000;
	value = cost;
	description = "Buffs turrets\non the whole map";
}

void signalTower::buffOtherTowers()
{
	map *gameMap = mainGame::getInstance()->getMap();

	buff powerFactor(buff::power, powerBuff);

	for (size_t i = 0; i < gameMap->towers.size(); ++i)
	{
			gameMap->towers[i]->addBuff(powerFactor);
	}
}

void signalTower::debuffOtherTowers()
{
	map *gameMap = mainGame::getInstance()->getMap();

	buff powerFactor(buff::power, powerBuff);

	for (size_t i = 0; i < gameMap->towers.size(); ++i)
	{
		gameMap->towers[i]->removeBuff(powerFactor);
	}
}

void signalTower::upgrade()
{
	debuffOtherTowers();
	
	powerBuff = round(powerBuff * 1.2f * 100.f) / 100.f;
	value += getUpgradeCost();
	upgradeLevel++;
	expand();

	buffOtherTowers();
}

void signalTower::build()
{
	builded = true;
	buffOtherTowers();
}

void signalTower::buf(attackTower * buffingTower)
{
	buff Pbuff(buff::power, powerBuff);
	buffingTower->addBuff(Pbuff);
}

void signalTower::sell()
{
	debuffOtherTowers();

	tower::sell();
}

void signalTower::update()
{
}

std::shared_ptr<tower> signalTower::getClassObject()
{
	 std::shared_ptr<tower> obj = std::make_shared<signalTower>();

	 return obj;
}

