#include "pch.hpp"
#include "electricTower.hpp"
#include "mainGame.hpp"


electricTower::electricTower()
{
	textureName = "electricTower";

	loadTexture();
	setAttributes();
}

electricTower::~electricTower()
{

}

void electricTower::loadTexture()
{
	texture = *mainGame::getInstance()->textures.getTowerTexture(textureName);
	sprite.setTexture(texture);

	sf::Vector2u textureSize = texture.getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 3, textureSize.y));
}

void electricTower::setAttributes()
{
	cost = 300;
	power = 300;
	range = 150.f;
	speed = 550.f;
	levelAcces = 12;
	bulletSpeed = 500;
	shockFactor = 0.05f;
	shockDuration = 1400.f;
	value = cost;
	timer = sf::milliseconds(sf::Int32(speed * 3 / 4));

	attackCircle.setRadius(range);
	sf::Vector2f circlePos;
	circlePos.x = getPosition().x + getSize().x / 2 - attackCircle.getGlobalBounds().width / 2;
	circlePos.y = getPosition().y + getSize().y / 2 - attackCircle.getGlobalBounds().height / 2;
	attackCircle.setPosition(circlePos);
	description = "Causes electric shock\nfor short time\nshocked monsters\ngains more dmg";
	bulletTextureName = "bundleEnergy"; //animationName
}

void electricTower::shoot()
{
	bullets.push_back(animationBullet(bulletTextureName, this));
	print("shoot");
}

void electricTower::removeBullet(bullet * rBullet)
{
	for (int i = 0; i<bullets.size(); ++i)
	{
		if (*rBullet == bullets[i])
		{
			bullets.erase(bullets.begin() + i);
		}
	}
}

void electricTower::attackMonster(std::shared_ptr<monster> monst)
{
	std::shared_ptr<monsterEffect> shock = std::make_shared<shockEffect>(monst, shockFactor, shockDuration, this);
	monst->getEffectHandler().addEffect(shock);
	attackTower::attackMonster(monst);
}


void electricTower::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);

	if (HUDactive)
	{
		target.draw(attackCircle);
	}

	for (size_t i = 0; i < bullets.size(); ++i)
	{
		target.draw(bullets[i]);
	}
}

void electricTower::upgrade()
{
	power = int(round(float(power) * 1.1f));
	shockFactor += 0.05f;
	range *= 1.1f;

	sf::Vector2f circlePos;
	circlePos.x = getCenter().x - attackCircle.getGlobalBounds().width / 2;
	circlePos.y = getCenter().y - attackCircle.getGlobalBounds().height / 2;
	attackCircle.setPosition(circlePos);

	expand();
	value += getUpgradeCost();
	upgradeLevel++;
}

std::shared_ptr<tower> electricTower::getClassObject()
{
	std::shared_ptr<tower> ptr = std::make_shared<electricTower>();
	return ptr;
}

tower::workshopHandler * electricTower::getWorkshopTemplate()
{
	if (!workshopTemplate)
	{
		workshopTemplate = std::make_unique<workshopHandler>(this);
	}
	return workshopTemplate.get();
}

void electricTower::handleBullets()
{
	for (size_t i = 0; i < bullets.size(); ++i)
	{
		bullets[i].update();
	}
}

/////////////////////////////////ELECTRICTOWER::workshopHandler /////////////////////////////////

void electricTower::workshopHandler::set()
{
	attackTower::workshopHandler::set();
	shockEffect.setString("shockFactor =" + floatToString(owner->shockFactor * 100.f) + " %");
}

void electricTower::workshopHandler::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(X);
	target.draw(power);
	target.draw(range);
	target.draw(shockEffect);
	target.draw(upgrader);
	target.draw(upgradeCost);
	target.draw(sellText);
	

	if (owner->powerBuffFactor != 0)
		target.draw(powerBuff);
	if (owner->rangeBuffFactor != 0.f)
		target.draw(rangeBuff);
}

void electricTower::workshopHandler::place()
{
	sf::Vector2f wsSize = workshopOwner->getSize();
	sf::Vector2f wsPos = workshopOwner->getPosition();

	sf::Vector2f upgraderPos;
	upgraderPos.x = wsPos.x + wsSize.x * 3 / 4 - upgrader.getSize().x / 2;
	upgraderPos.y = wsPos.y + wsSize.y / 2 - upgrader.getSize().y / 4;
	upgrader.setPosition(upgraderPos);

	power.setFont(*font);
	power.setCharacterSize(24);
	power.setColor(sf::Color::Red);
	sf::Vector2f powerPos;
	powerPos.x = wsPos.x + wsSize.x / 30;
	powerPos.y = wsPos.y + wsSize.y / 2 - power.getGlobalBounds().height * 3 / 4;
	power.setPosition(powerPos);

	powerBuff.setFont(*font);
	powerBuff.setCharacterSize(18);
	powerBuff.setColor(sf::Color(20, 255, 20));
	sf::Vector2f powerBuffPos;
	powerBuffPos.x = power.getPosition().x + power.getGlobalBounds().width + 3.f;
	powerBuffPos.y = power.getPosition().y + power.getGlobalBounds().height / 2 - powerBuff.getGlobalBounds().height / 3;
	powerBuff.setPosition(powerBuffPos);

	range.setFont(*font);
	range.setCharacterSize(24);
	range.setColor(sf::Color::Red);
	sf::Vector2f rangePos;
	rangePos.x = wsPos.x + wsSize.x / 4;
	rangePos.y = wsPos.y + wsSize.y / 2 - range.getGlobalBounds().height * 3 / 4;
	range.setPosition(rangePos);

	rangeBuff.setFont(*font);
	rangeBuff.setCharacterSize(18);
	rangeBuff.setColor(sf::Color::Green);
	sf::Vector2f rangeBuffPos;
	rangeBuffPos.x = range.getPosition().x + range.getGlobalBounds().width + 3.f;
	rangeBuffPos.y = range.getPosition().y + range.getGlobalBounds().height / 2 - rangeBuff.getGlobalBounds().height / 3;
	rangeBuff.setPosition(rangeBuffPos);

	shockEffect.setFont(*font);
	shockEffect.setCharacterSize(24);
	shockEffect.setColor(sf::Color::Red);
	sf::Vector2f shockEffectPos;
	shockEffectPos.x = wsPos.x + wsSize.x * 4 / 9 ;
	shockEffectPos.y = wsPos.y + wsSize.y / 2 - shockEffect.getGlobalBounds().height * 3 / 4 - 3.f;
	shockEffect.setPosition(shockEffectPos);

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