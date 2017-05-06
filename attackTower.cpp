#include "pch.hpp"
#include "attackTower.hpp"
#include "buffTower.hpp"
#include "mainGame.hpp"

attackTower::attackTower()
{
	attackCircle.setFillColor(sf::Color(170, 80, 80, 55));
	powerBuffFactor = 0.f;
	rangeBuffFactor = 0.f;
}

attackTower::~attackTower()
{
}

void attackTower::makeVisualCircle()
{
	canShowCircle = true;
}

void attackTower::makeInvisibleCircle()
{
	canShowCircle = false;
}

bool attackTower::isMouseOnCircle(const sf::Vector2f mousePos)
{
	double distance;

	distance = sqrt((mousePos.x - getCenter().x)*(mousePos.x - getCenter().x) + (mousePos.y - getCenter().y)*(mousePos.y - getCenter().y));


	if (distance < attackCircle.getRadius())
	{
		return true;
	}

	return false;
}

bool attackTower::haveTarget()
{
	return bool(targetingMonster);
}

void attackTower::clearTarget()
{
	targetingMonster.reset();
}

void attackTower::build()
{
	builded = true;

	map *gameMap = mainGame::getInstance()->getMap();

	for (size_t i = 0; i < gameMap->towers.size(); ++i)
	{
		gameMap->towers[i]->buf(this);
	}
}

float attackTower::getBulletSpeed()
{
	return bulletSpeed;
}

float attackTower::getPowerBuffFactor()
{
	return powerBuffFactor;
}

float attackTower::getRangeBuffFactor()
{
	return rangeBuffFactor;
}

void attackTower::addBuff(buff buffer)
{
	switch (buffer.getType())
	{
	case buff::power: {powerBuffFactor += buffer.getFactor(); } break;
	case buff::range: {rangeBuffFactor += buffer.getFactor(); attackCircle.setRadius(range + range * rangeBuffFactor);
		attackCircle.setPosition(getMidlePosition(getCenter(), attackCircle.getGlobalBounds())); } break;
	}

	getWorkshopTemplate()->set();

}

void attackTower::removeBuff(buff unbuffer)
{
	switch (unbuffer.getType())
	{
	case buff::power: {powerBuffFactor -= unbuffer.getFactor(); } break;
	case buff::range: {rangeBuffFactor -= unbuffer.getFactor(); attackCircle.setRadius(range + range * rangeBuffFactor);
		attackCircle.setPosition(getMidlePosition(getCenter(), attackCircle.getGlobalBounds())); } break;
	}

	getWorkshopTemplate()->set();

}


void attackTower::searchTarget()
{
	unsigned long int steps = 0;
	std::vector<wave*> & monsters = mainGame::getInstance()->getWaves();
	for (size_t i = monsters.size(); i-- > 0;)

	{
		for (size_t j = monsters[i]->size(); j-- > 0;)
		{
			if (isTargetInRange(monsters[i]->operator[](int(j))))
			{
				if (monsters[i]->operator[](int(j))->getWaySteps() > steps)
				{
					targetingMonster = monsters[i]->operator[](int(j));
					steps = monsters[i]->operator[](int(j))->getWaySteps();
				}
			}
		}
	}
}

void attackTower::attack()
{
	shoot();
}

bool attackTower::canAttack()
{
	if (timer.asMilliseconds() >= speed)
		return true;

	return false;
}

void attackTower::update()
{
	timer += game::getInstance()->getTimer();

	if (haveTarget())
	{
		if ((isTargetOutofRange()) || (targetingMonster->isUnavailable()))
		{
			clearTarget();
		}
		else if (canAttack())
		{
			attack();
			timer = sf::Time::Zero;
		}
	}
	else
	{
		searchTarget();
	}

	handleBullets();
}

void attackTower::sell()
{
	bullets.clear();
	mainGame::getInstance()->getMap()->sellTower(this);

	int val = int(float(value) * 0.80f);
	mainGame::getInstance()->getWallet()->deposit(val);
}

void attackTower::shoot()
{
	bullet bulet(bulletTextureName, this);
	bullets.push_back(bulet);
}

void attackTower::handleBullets()
{
	for (int i = 0; i < bullets.size(); ++i)
	{
		bullets[i].update();
	}
}

void attackTower::attackMonster(std::shared_ptr<monster> monst)
{
	int pow = int(power + powerBuffFactor * power);
	monst->getDmg(int(pow));
}

void attackTower::removeBullet(bullet * rBullet)
{
	for (int i = 0; i<bullets.size(); ++i)
	{
		if (*rBullet == bullets[i])
		{
			bullets.erase(bullets.begin() + i);
		}
	}
}

void attackTower::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);

	sf::Vector2f circlePos = getMidlePosition(getCenter(), attackCircle.getGlobalBounds());
	attackCircle.setPosition(circlePos);

	sf::Vector2f bulletPos;
	bulletPos.x = position.x + sprite.getGlobalBounds().width / 2;
	bulletPos.y = position.y + sprite.getGlobalBounds().height / 6;

	startBulletPosition = bulletPos;
}

bool attackTower::mouseOnHUD(const sf::Vector2f mousePos)
{
	if ((sprite.getGlobalBounds().contains(mousePos) || (isPointInCircle(mousePos))))
			return true;

	return false;
}

bool attackTower::isTargetInRange(std::shared_ptr<monster> monstero)
{
	sf::Vector2f monsterPos = monstero->getPosition();
	sf::Vector2f monsterSize = monstero->getSize();

	sf::Vector2f monsterPoints[4];

	monsterPoints[0].x = monsterPos.x + monsterSize.x / 4;
	monsterPoints[0].y = monsterPos.y + monsterSize.y / 4;
	monsterPoints[1].x = monsterPos.x + monsterSize.x / 4 * 3;
	monsterPoints[1].y = monsterPos.y + monsterSize.y / 4;
	monsterPoints[2].x = monsterPos.x + monsterSize.x / 4;
	monsterPoints[2].y = monsterPos.y + monsterSize.y / 4 * 3;
	monsterPoints[3].x = monsterPos.x + monsterSize.x / 4 * 3;
	monsterPoints[3].y = monsterPos.y + monsterSize.y / 4 * 3;


	double distance;

	for (int i = 0; i < 4; ++i)
	{
		distance = sqrt((monsterPoints[i].x - getCenter().x)*(monsterPoints[i].x - getCenter().x) + (monsterPoints[i].y - getCenter().y)*(monsterPoints[i].y - getCenter().y));

		if (distance < range + range * rangeBuffFactor)
		{
			return true;
		}
	}

	return false;
}

bool attackTower::isTargetOutofRange()
{
	sf::Vector2f monsterCenter = targetingMonster->getCenter();

	double distance;
	
	distance = sqrt((monsterCenter.x - getCenter().x)*(monsterCenter.x - getCenter().x) + (monsterCenter.y - getCenter().y)*(monsterCenter.y - getCenter().y));

	if (distance > range + range * rangeBuffFactor)
		return true;

	return false;
}

bool attackTower::isPointInCircle(const sf::Vector2f point)
{
	float distance;

	distance = sqrt((getCenter().x - point.x) * (getCenter().x - point.x) + (getCenter().y - point.y) * (getCenter().y - point.y));

	if (distance < range + range * rangeBuffFactor)
		return true;

	return false;
}

void attackTower::activateHUD()
{
	HUDactive = true;
}

void attackTower::unactiveHUD()
{
	HUDactive = false;
}

void attackTower::unactivate()
{
	targetingMonster.reset();
}

sf::Vector2f attackTower::getStartBulletPosition()
{
	return startBulletPosition;
}


void attackTower::upgrade()
{
	power = int(round(float(power) * 1.3f));
	range = round(range *= 1.15f);
	attackCircle.setRadius(range + range * rangeBuffFactor);

	expand();

	sf::Vector2f circlePos;
	circlePos.x = getCenter().x - attackCircle.getGlobalBounds().width / 2;
	circlePos.y = getCenter().y - attackCircle.getGlobalBounds().height / 2;
	attackCircle.setPosition(circlePos);

	value += getUpgradeCost();
	upgradeLevel++;
}

void attackTower::expand()
{
	sf::IntRect currentRect = sprite.getTextureRect();
	const sf::Texture *texture = sprite.getTexture();

	currentRect.left += texture->getSize().x / 3;

	sprite.setTextureRect(currentRect);
}

std::shared_ptr<monster> attackTower::getTarget()
{
	return targetingMonster;
}

int attackTower::getPower()
{
	return power;
}

float attackTower::getRange()
{
	return range;
}

float attackTower::getSpeed()
{
	return speed;
}

auto attackTower::getWorkshopTemplate() -> tower::workshopHandler *
{
	if (!workshopTemplate)
	{
		workshopTemplate = std::make_unique<workshopHandler>(this);
	}
	return workshopTemplate.get();
}

tower::shopTemplate * attackTower::getShopTemplate()
{
	if (!storeTemplate)
	{
		storeTemplate = std::make_unique<shopTemplate>(this);
	}
	return storeTemplate.get();
}

void attackTower::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);

	for (int i = 0; i < bullets.size(); ++i)
	{
		target.draw(bullets[i]);
	}

	if (HUDactive)
	{
		target.draw(attackCircle);
	}
}


/////////////////////////////////////////////////////// ATTACKTOWER::WORKSHOPHANDLER //////////////////////////////
/////////////////////////////////////////////////////// ATTACKTOWER::WORKSHOPHANDLER //////////////////////////////
/////////////////////////////////////////////////////// ATTACKTOWER::WORKSHOPHANDLER //////////////////////////////
/////////////////////////////////////////////////////// ATTACKTOWER::WORKSHOPHANDLER //////////////////////////////

void attackTower::workshopHandler::place()
{
	sf::Vector2f wsSize = workshopOwner->getSize();
	sf::Vector2f wsPos = workshopOwner->getPosition();

	sf::Vector2f upgraderPos;
	upgraderPos.x = wsPos.x + wsSize.x * 3 / 4 - upgrader.getSize().x / 2;
	upgraderPos.y = wsPos.y + wsSize.y / 2 - upgrader.getSize().y / 4;
	upgrader.setPosition(upgraderPos);

	power.setFont(*font);
	power.setCharacterSize(30);
	power.setColor(sf::Color::Red);
	sf::Vector2f powerPos;
	powerPos.x = wsPos.x + wsSize.x / 10;
	powerPos.y = wsPos.y + wsSize.y / 2 - power.getGlobalBounds().height * 3/4;
	power.setPosition(powerPos);

	powerBuff.setFont(*font);
	powerBuff.setCharacterSize(18);
	powerBuff.setColor(sf::Color(20,255,20));
	sf::Vector2f powerBuffPos;
	powerBuffPos.x = power.getPosition().x + power.getGlobalBounds().width + 3.f;
	powerBuffPos.y = power.getPosition().y + power.getGlobalBounds().height / 2 - powerBuff.getGlobalBounds().height / 3;
	powerBuff.setPosition(powerBuffPos);

	range.setFont(*font);
	range.setCharacterSize(30);
	range.setColor(sf::Color::Red);
	sf::Vector2f rangePos;
	rangePos.x = wsPos.x + wsSize.x * 2 / 5;
	rangePos.y = wsPos.y + wsSize.y / 2 - range.getGlobalBounds().height * 3/4;
	range.setPosition(rangePos);

	rangeBuff.setFont(*font);
	rangeBuff.setCharacterSize(18);
	rangeBuff.setColor(sf::Color::Green);
	sf::Vector2f rangeBuffPos;
	rangeBuffPos.x = range.getPosition().x + range.getGlobalBounds().width + 3.f;
	rangeBuffPos.y = range.getPosition().y + range.getGlobalBounds().height / 2 - rangeBuff.getGlobalBounds().height / 3;
	rangeBuff.setPosition(rangeBuffPos);

	upgradeCost.setFont(*font);
	upgradeCost.setCharacterSize(20);
	upgradeCost.setColor(sf::Color::Red);
	sf::Vector2f costPos;
	costPos.x = upgrader.getPosition().x + upgrader.getSize().x / 2 - upgradeCost.getGlobalBounds().width / 2;
	costPos.y = upgrader.getPosition().y - upgradeCost.getGlobalBounds().height*1.4f;
	upgradeCost.setPosition(costPos);

	sellText.setFont(*font);
	sellText.setCharacterSize(20);
	sellText.setColor(sf::Color::Red);
	sellText.setString("SELL");
	sf::Vector2f sellTPos;
	sellTPos.x = wsPos.x + wsSize.x - sellText.getGlobalBounds().width;
	sellTPos.y = wsPos.y + wsSize.y - sellText.getGlobalBounds().height * 1.5f;
	sellText.setPosition(sellTPos);

	sf::Vector2f XPos;
	XPos.x = wsPos.x + wsSize.x - X.getGlobalBounds().width;
	XPos.y = wsPos.y;
	X.setPosition(XPos);


	placed = true;
}

void attackTower::workshopHandler::set()
{
	power.setString("power = " + intToString(owner->power));
	range.setString("range = " + floatToString(owner->range));


	if (owner->getPowerBuffFactor() != 0)
		powerBuff.setString("+ " + floatToString(round(owner->powerBuffFactor * (float)owner->power)));

	if (owner->getRangeBuffFactor() != 0.f)
		rangeBuff.setString("+ " + floatToString(round(owner->rangeBuffFactor * owner->range)));

	if (owner->isExtended())
	{
		upgradeCost.setString("MAX");
	}
	else
	upgradeCost.setString("upgrade cost = " + intToString(owner->getUpgradeCost()));

	sf::Vector2f powerBuffPos;
	powerBuffPos.x = power.getPosition().x + power.getGlobalBounds().width + 3.f;
	powerBuffPos.y = power.getPosition().y + power.getGlobalBounds().height / 2 - powerBuff.getGlobalBounds().height / 2;
	powerBuff.setPosition(powerBuffPos);

	sf::Vector2f rangeBuffPos;
	rangeBuffPos.x = range.getPosition().x + range.getGlobalBounds().width + 3.f;
	rangeBuffPos.y = range.getPosition().y + range.getGlobalBounds().height / 2 - rangeBuff.getGlobalBounds().height / 2;
	rangeBuff.setPosition(rangeBuffPos);

	sf::Vector2f costPos;
	costPos.x = upgrader.getPosition().x + upgrader.getSize().x / 2 - upgradeCost.getGlobalBounds().width / 2;
	costPos.y = upgrader.getPosition().y - upgradeCost.getGlobalBounds().height * 1.4f;
	upgradeCost.setPosition(costPos);
}

void attackTower::workshopHandler::configureUpgrader()
{
	if (owner->isExtended())
		return;

	if((!goldUpgradeAccesed()) && (owner->isAffordForUpgrade()))
	{
		upgrader.makeAccesibleBackr();
		upgradeAccesed = true;
	}
	else if((goldUpgradeAccesed()) && (!owner->isAffordForUpgrade()))
	{
		upgrader.makeUnaccesibleBackgr();
		upgradeAccesed = false;
	}
}

bool attackTower::workshopHandler::goldUpgradeAccesed()
{
	return upgradeAccesed;
}

void attackTower::workshopHandler::handleUpgrader()
{
	if ((upgrader.clicked()) && (upgradeAccesed))
	{
		mainGame::getInstance()->getWallet()->pay(owner->getUpgradeCost());
		owner->upgrade();
		upgrader.upgradeLevel();
		set();
	}
}

void attackTower::workshopHandler::handleSeller()
{
	if (objectClicked(sellText.getGlobalBounds()))
	{
		workshopOwner->leave();
		owner->sell();
	}
}

attackTower * attackTower::workshopHandler::getOwner()
{
	return owner;
}

void attackTower::workshopHandler::join(workshop *ws)
{
	workshopOwner = ws;	
	set();

	if (!Placed())
	{
		place();
	}

	configureUpgrader();
}


void attackTower::workshopHandler::update()
{
	tower::workshopHandler::update();

	if (!owner->isExtended())
	{
		configureUpgrader();
		handleUpgrader();
	}

	handleSeller();
}

void attackTower::workshopHandler::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(X);
	target.draw(power);
	target.draw(range);
	target.draw(upgrader);
	target.draw(upgradeCost);
	target.draw(sellText);

	if (owner->powerBuffFactor != 0)
		target.draw(powerBuff);
	if (owner->rangeBuffFactor != 0.f)
		target.draw(rangeBuff);
}

//////////////////////////////////////////////// ATTACKTOWER::SHOPTEMPLATE //////////////////////////////////////
//////////////////////////////////////////////// ATTACKTOWER::SHOPTEMPLATE //////////////////////////////////////
//////////////////////////////////////////////// ATTACKTOWER::SHOPTEMPLATE //////////////////////////////////////
//////////////////////////////////////////////// ATTACKTOWER::SHOPTEMPLATE //////////////////////////////////////

attackTower::shopTemplate::shopTemplate(attackTower * ownr)
	:tower::shopTemplate(ownr)
{
	owner = ownr;

	cost.setString("cost=" + intToString(owner->cost));
	cost.setCharacterSize(charSize);
	cost.setColor(sf::Color(240,24,24));

	power.setFont(*font);
	power.setString("power=" + intToString(owner->power));
	power.setCharacterSize(charSize);
	power.setColor(sf::Color(240, 24, 24));

	range.setFont(*font);
	range.setString("range=" + floatToString(owner->range));
	range.setCharacterSize(charSize);
	range.setColor(sf::Color(240, 24, 24));

}

void attackTower::shopTemplate::setPosition(sf::Vector2f position)
{
	towerSprite.setPosition(position);

	sf::Vector2f padlockPos = getMiddlePosition(towerSprite.getGlobalBounds(), padlock.getGlobalBounds());
	padlock.setPosition(padlockPos);

	sf::Vector2f costPos;
	costPos.x = towerSprite.getPosition().x + towerSprite.getGlobalBounds().width / 2 - cost.getGlobalBounds().width / 2;
	costPos.y = position.y + towerSprite.getGlobalBounds().height;
	cost.setPosition(costPos);

	sf::Vector2f powerPos;
	powerPos.x = towerSprite.getPosition().x + towerSprite.getGlobalBounds().width / 2 - power.getGlobalBounds().width / 2;
	powerPos.y = position.y + towerSprite.getGlobalBounds().height + cost.getGlobalBounds().height + 1.f;
	power.setPosition(powerPos);

	sf::Vector2f rangePos;
	rangePos.x = towerSprite.getPosition().x + towerSprite.getGlobalBounds().width / 2 - range.getGlobalBounds().width / 2;
	rangePos.y = position.y + towerSprite.getGlobalBounds().height + cost.getGlobalBounds().height + power.getGlobalBounds().height+1.f;
	range.setPosition(rangePos);
}

sf::Vector2f attackTower::shopTemplate::getSize()
{
	sf::Vector2f size;
	size.x = towerSprite.getGlobalBounds().width / 2;
	size.y = (range.getGlobalBounds().top + range.getGlobalBounds().height) - towerSprite.getGlobalBounds().top;

	return size;
}

void attackTower::shopTemplate::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	tower::shopTemplate::draw(target, states);
	target.draw(power);
	target.draw(range);
}