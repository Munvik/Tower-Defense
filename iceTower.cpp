#include "pch.hpp"
#include "iceTower.hpp"
#include "mainGame.hpp"


iceTower::iceTower()
{
	textureName = "iceTower";

	loadTexture();
	setAttributes();
}

iceTower::~iceTower()
{
}

void iceTower::setAttributes()
{
	cost = 150;
	power = 0;
	slow = 0.10f;
	range = 160.f;
	speed = 400.f;
	levelAcces = 5;
	bulletSpeed = 700.f;
	value = cost;
	timer = sf::milliseconds(sf::Int32(speed * 3 / 4));

	attackCircle.setRadius(range);
	sf::Vector2f circlePos;
	circlePos.x = getPosition().x + getSize().x / 2 - attackCircle.getGlobalBounds().width / 2;
	circlePos.y = getPosition().y + getSize().y / 2 - attackCircle.getGlobalBounds().height / 2;
	attackCircle.setPosition(circlePos);

	description = "Slows enemys";
	bulletTextureName = "iceTowerBullet";
}

void iceTower::loadTexture()
{
	texture = *mainGame::getInstance()->textures.getTowerTexture(textureName);
	sprite.setTexture(texture);

	sf::Vector2u textureSize = texture.getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 3, textureSize.y));
}

void iceTower::handleBullets()
{
	for (size_t i = 0; i < bullets.size(); ++i)
	{
		bullets[i].update();
	}
}

void iceTower::searchTarget()
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

void iceTower::attackMonster(std::shared_ptr<monster> monst)
{
	std::shared_ptr<monsterEffect> slow = std::make_shared<slowEffect>(monst, this->slow, slowDur);
	monst->getEffectHandler().addEffect(slow);

}

void iceTower::shoot()
{
	bullet bulet(bulletTextureName, this);
	bullets.push_back(bulet);

	targetingMonster.reset();
}

void iceTower::upgrade()
{
	slow = round(slow * 1.4f * 100.f) / 100;
	range *= 1.2f;

	attackCircle.setRadius(range);
	sf::Vector2f circlePos;
	circlePos.x = getCenter().x - attackCircle.getGlobalBounds().width / 2;
	circlePos.y = getCenter().y - attackCircle.getGlobalBounds().height / 2;
	attackCircle.setPosition(circlePos);

	expand();
	value += getUpgradeCost();
	upgradeLevel++;

}

std::shared_ptr<tower> iceTower::getClassObject()
{
	std::shared_ptr<tower> obj = std::make_shared<iceTower>();

	return obj;
}

tower::workshopHandler * iceTower::getWorkshopTemplate()
{
	if (!workshopTemplate)
	{
		workshopTemplate = std::make_unique<workshopHandler>(this);
	}
	return workshopTemplate.get();
}

tower::shopTemplate * iceTower::getShopTemplate()
{
	if (!storeTemplate)
	{
		storeTemplate = std::make_unique<shopTemplate>(this);
	}
	return storeTemplate.get();
}


////////////////////// ICEtower:: workshophandler ////////////////////////////
////////////////////// ICEtower:: workshophandler ////////////////////////////
////////////////////// ICEtower:: workshophandler ////////////////////////////

void iceTower::workshopHandler::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(X);
	target.draw(slow);
	target.draw(range);
	target.draw(upgrader);
	target.draw(upgradeCost);
	target.draw(sellText);

	if (owner->rangeBuffFactor != 0.f)
		target.draw(rangeBuff);
}

void iceTower::workshopHandler::place()
{
	sf::Vector2f wsSize = workshopOwner->getSize();
	sf::Vector2f wsPos = workshopOwner->getPosition();

	sf::Vector2f upgraderPos;
	upgraderPos.x = wsPos.x + wsSize.x * 3 / 4 - upgrader.getSize().x / 2;
	upgraderPos.y = wsPos.y + wsSize.y / 2 - upgrader.getSize().y / 4;
	upgrader.setPosition(upgraderPos);

	slow.setFont(*font);
	slow.setCharacterSize(25);
	slow.setColor(sf::Color::Red);
	sf::Vector2f slowPos;
	slowPos.x = wsPos.x + wsSize.x / 20;
	slowPos.y = wsPos.y + wsSize.y / 2 - slow.getGlobalBounds().height * 3 / 4;
	slow.setPosition(slowPos);

	range.setFont(*font);
	range.setCharacterSize(30);
	range.setColor(sf::Color::Red);
	sf::Vector2f rangePos;
	rangePos.x = wsPos.x + wsSize.x * 2 / 5;
	rangePos.y = wsPos.y + wsSize.y / 2 - range.getGlobalBounds().height * 3 / 4;
	range.setPosition(rangePos);

	rangeBuff.setFont(*font);
	rangeBuff.setCharacterSize(18);
	rangeBuff.setColor(sf::Color::Green);
	sf::Vector2f rangeBuffPos;
	rangeBuffPos.x = range.getPosition().x + range.getGlobalBounds().width + 3.f;
	rangeBuffPos.y = range.getPosition().y + range.getGlobalBounds().height / 2 - rangeBuff.getGlobalBounds().height * 0.3f;
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

void iceTower::workshopHandler::set()
{
	slow.setString("slowFactor = " + floatToString(owner->slow* 100.f) + "%");
	range.setString("range = " + floatToString(owner->range));

	if (owner->getRangeBuffFactor() != 0.f)
		rangeBuff.setString("+ " + floatToString(round(owner->rangeBuffFactor * owner->range)));

	if (owner->isExtended())
	{
		upgradeCost.setString("MAX");
	}
	else
		upgradeCost.setString("upgrade cost = " + intToString(owner->getUpgradeCost()));

	sf::Vector2f costPos;
	costPos.x = upgrader.getPosition().x + upgrader.getSize().x / 2 - upgradeCost.getGlobalBounds().width / 2;
	costPos.y = upgrader.getPosition().y - upgradeCost.getGlobalBounds().height * 1.4f;
	upgradeCost.setPosition(costPos);
}


////////////////////// ICEtower:: shoptemplate ////////////////////////////

////////////////////// ICEtower:: shoptemplate ////////////////////////////

////////////////////// ICEtower:: shoptemplate ////////////////////////////

iceTower::shopTemplate::shopTemplate(iceTower *ownr)
	:owner(ownr),
	attackTower::shopTemplate::shopTemplate(ownr)
{
	cost.setString("cost=" + intToString(owner->cost));
	cost.setCharacterSize(charSize);
	cost.setColor(sf::Color(240, 24, 24));

	slow.setFont(*font);
	slow.setString("slow =" + floatToString(owner->slow * 100.f) + "%");
	slow.setCharacterSize(charSize);
	slow.setColor(sf::Color(240, 24, 24));

	range.setFont(*font);
	range.setString("range=" + floatToString(owner->range));
	range.setCharacterSize(charSize);
	range.setColor(sf::Color(240, 24, 24));
}

void iceTower::shopTemplate::setPosition(sf::Vector2f position)
{
	towerSprite.setPosition(position);

	sf::Vector2f padlockPos = getMiddlePosition(towerSprite.getGlobalBounds(), padlock.getGlobalBounds());
	padlock.setPosition(padlockPos);

	sf::Vector2f costPos;
	costPos.x = towerSprite.getPosition().x + towerSprite.getGlobalBounds().width / 2 - cost.getGlobalBounds().width / 2;
	costPos.y = position.y + towerSprite.getGlobalBounds().height;
	cost.setPosition(costPos);

	sf::Vector2f slowPos;
	slowPos.x = towerSprite.getPosition().x + towerSprite.getGlobalBounds().width / 2 - slow.getGlobalBounds().width / 2;
	slowPos.y = position.y + towerSprite.getGlobalBounds().height + cost.getGlobalBounds().height + 1.f;
	slow.setPosition(slowPos);

	sf::Vector2f rangePos;
	rangePos.x = towerSprite.getPosition().x + towerSprite.getGlobalBounds().width / 2 - range.getGlobalBounds().width / 2;
	rangePos.y = position.y + towerSprite.getGlobalBounds().height + cost.getGlobalBounds().height + power.getGlobalBounds().height + 1.f;
	range.setPosition(rangePos);
}

void iceTower::shopTemplate::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	tower::shopTemplate::draw(target, states);
	target.draw(slow);
	target.draw(range);
}