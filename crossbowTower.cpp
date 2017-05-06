#include "pch.hpp"
#include "crossbowTower.hpp"
#include "mainGame.hpp"


crossbowTower::crossbowTower()
{
	textureName = "crossbowTower";
	loadTexture();
	setAttributes();
}

crossbowTower::~crossbowTower()
{
}

void crossbowTower::setAttributes()
{
	cost = 150;
	power = 200;
	range = 210.f;
	speed = 500.f;
	levelAcces = 5;
	bulletSpeed = 700.f;
	criticChance = 15;
	value = cost;
	timer = sf::milliseconds(sf::Int32(speed * 3 / 4));

	attackCircle.setRadius(range);
	sf::Vector2f circlePos;
	circlePos.x = getPosition().x + getSize().x / 2 - attackCircle.getGlobalBounds().width / 2;
	circlePos.y = getPosition().y + getSize().y / 2 - attackCircle.getGlobalBounds().height / 2;
	attackCircle.setPosition(circlePos);

	description = "Makes critical attacks";
	bulletTextureName = "crossbowTowerBullet";
}

void crossbowTower::loadTexture()
{
	texture = *mainGame::getInstance()->textures.getTowerTexture(textureName);
	sprite.setTexture(texture);

	sf::Vector2u textureSize = texture.getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 3, textureSize.y));

	sf::Texture *crossbowT = mainGame::getInstance()->textures.getTexture("crossbow");
	crossbow.setTexture(*crossbowT);  

	textureSize = crossbowT->getSize();
	crossbow.setTextureRect(sf::IntRect(0, 0, textureSize.x / 3, textureSize.y));
}

void crossbowTower::handleBullets()
{
	sf::FloatRect gameWindow(0, 0, WIDTH, HEIGHT);

	for (size_t i = 0; i < bullets.size(); ++i)
	{
		if (!bullets[i].getGlobalBounds().intersects(gameWindow))
		{
			bullets.erase(this->bullets.begin() + i);
			continue;
		}

		bullets[i].update();
	}

}

void crossbowTower::setPosition(sf::Vector2f position)
{
attackTower::setPosition(position);

sf::Vector2f crossbowPos;
crossbowPos.x = getCenter().x;;
crossbowPos.y = position.y + crossbow.getGlobalBounds().height / 2;;
crossbow.setPosition(crossbowPos);
crossbow.setOrigin(crossbow.getGlobalBounds().width / 2, crossbow.getGlobalBounds().height / 2);
}

void crossbowTower::shoot()
{
	sf::Vector2f v = targetingMonster->getCenter() - getCenter();

	sf::Vector2f dirVelocity;

	dirVelocity.x = bulletSpeed * v.x / (fabs(v.x) + fabs(v.y));
	dirVelocity.y = bulletSpeed * v.y / (fabs(v.x) + fabs(v.y));

	bullet bulletor(bulletTextureName, this);
	bulletor.setVelocity(dirVelocity);

	float rot = atan2(v.y, v.x);
	rot *= 180.f / 3.14f;
	rot += 90.f;

	bulletor.setRotation(rot);
	bulletor.setPosition(getStartBulletPosition());
	bullets.push_back(bulletor);

	crossbow.setRotation(rot);
}

void crossbowTower::upgrade()
{
	power = int(round(float(power) * 1.2f));
	range  = round(range *= 1.1f);
	attackCircle.setRadius(range + range * rangeBuffFactor);
	criticChance += 10;

	sf::Vector2f circlePos;
	circlePos.x = getCenter().x - attackCircle.getGlobalBounds().width / 2;
	circlePos.y = getCenter().y - attackCircle.getGlobalBounds().height / 2;
	attackCircle.setPosition(circlePos);

	value += getUpgradeCost();
	expand();
	upgradeLevel++;

	getWorkshopTemplate()->set();
}

void crossbowTower::attackMonster(std::shared_ptr<monster> monst)
{
	int random = rand() % 101;

	if (random <= criticChance)
	{
		monst->getDmg((int(float(power) + float(power) * powerBuffFactor) * 3/4));
		return;
	}
	attackTower::attackMonster(monst);
}

void crossbowTower::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);
	target.draw(crossbow);

	for (int i = 0; i < bullets.size(); ++i)
	{
		target.draw(bullets[i]);
	}

	if (HUDactive)
	{
		target.draw(attackCircle);
	}
}

void crossbowTower::removeBullet(bullet * rBullet)
{
	for (int i = 0; i<bullets.size(); ++i)
	{
		if (*rBullet == bullets[i])
		{
			bullets.erase(bullets.begin() + i);
		}
	}
}

std::shared_ptr<tower> crossbowTower::getClassObject()
{
	std::shared_ptr<tower> ptr = std::make_shared<crossbowTower>();
	return ptr;
}

tower::workshopHandler * crossbowTower::getWorkshopTemplate()
{
	if (!workshopTemplate)
	{
		workshopTemplate = std::make_unique<workshopHandler>(this);
	}
	return workshopTemplate.get();
}


////////////////////////// crossbowTower::bullet //////////////////////////
////////////////////////// crossbowTower::bullet //////////////////////////
////////////////////////// crossbowTower::bullet //////////////////////////


crossbowTower::bullet::bullet(std::string textureName, crossbowTower * ownr)
	: ::bullet(textureName)
{
	owner = ownr;
}

crossbowTower::bullet::~bullet()
{

}

void crossbowTower::bullet::setVelocity(sf::Vector2f v)
{
	velocity = v;
}

void crossbowTower::bullet::update()
{
	float time = game::getInstance()->getTimer().asSeconds();

	sprite.move(velocity * time);

	std::vector<wave*> & waves = mainGame::getInstance()->getWaves();

	for (size_t i = 0; i < waves.size(); ++i)
	{
		for (size_t j = waves[i]->size(); j-- > 0;)
		{
			if (waves[i]->operator[](int(j))->getGlobalBounds().intersects(sprite.getGlobalBounds()))
			{
				owner->attackMonster(waves[i]->operator[](int(j)));
				owner->removeBullet(this);
			}
		}
	}
}





//////////////////////////////////////////// WORKSHOP HANDLER ///////////////////////////////

void crossbowTower::workshopHandler::place()
{
	sf::Vector2f wsSize = workshopOwner->getSize();
	sf::Vector2f wsPos = workshopOwner->getPosition();

	sf::Vector2f upgraderPos;
	upgraderPos.x = wsPos.x + wsSize.x * 3 / 4 - upgrader.getSize().x / 2;
	upgraderPos.y = wsPos.y + wsSize.y / 2 - upgrader.getSize().y / 4;
	upgrader.setPosition(upgraderPos);

	power.setFont(*font);
	power.setCharacterSize(23);
	power.setColor(sf::Color::Red);
	sf::Vector2f powerPos;
	powerPos.x = wsPos.x + wsSize.x / 40;
	powerPos.y = wsPos.y + wsSize.y / 2 - power.getGlobalBounds().height * 3 / 4;
	power.setPosition(powerPos);

	powerBuff.setFont(*font);
	powerBuff.setCharacterSize(15);
	powerBuff.setColor(sf::Color(20, 255, 20));
	sf::Vector2f powerBuffPos;
	powerBuffPos.x = power.getPosition().x + power.getGlobalBounds().width + 3.f;
	powerBuffPos.y = power.getPosition().y + power.getGlobalBounds().height / 2 - powerBuff.getGlobalBounds().height / 2;
	powerBuff.setPosition(powerBuffPos);

	range.setFont(*font);
	range.setCharacterSize(23);
	range.setColor(sf::Color::Red);
	sf::Vector2f rangePos;
	rangePos.x = wsPos.x + wsSize.x /4;
	rangePos.y = wsPos.y + wsSize.y / 2 - range.getGlobalBounds().height * 3 / 4;
	range.setPosition(rangePos);

	rangeBuff.setFont(*font);
	rangeBuff.setCharacterSize(15);
	rangeBuff.setColor(sf::Color::Green);
	sf::Vector2f rangeBuffPos;
	rangeBuffPos.x = range.getPosition().x + range.getGlobalBounds().width + 3.f;
	rangeBuffPos.y = range.getPosition().y + range.getGlobalBounds().height / 2 - rangeBuff.getGlobalBounds().height / 2;
	rangeBuff.setPosition(rangeBuffPos);

	criticalChance.setFont(*font);
	criticalChance.setCharacterSize(23);
	criticalChance.setColor(sf::Color::Red);
	sf::Vector2f critChancePos;
	critChancePos.x = wsPos.x + wsSize.x * 10/21;
	critChancePos.y = wsPos.y + wsSize.y / 2 - criticalChance.getGlobalBounds().height * 3 / 4;
	criticalChance.setPosition(critChancePos);

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
}

void crossbowTower::workshopHandler::update()
{
	attackTower::workshopHandler::update();
}

void crossbowTower::workshopHandler::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	attackTower::workshopHandler::draw(target, states);
	target.draw(criticalChance);
}

void crossbowTower::workshopHandler::set()
{
	attackTower::workshopHandler::set();
	criticalChance.setString("CritChance = " + intToString(owner->criticChance) + "%");
}
