#include "pch.hpp"
#include "laserTower.hpp"
#include "mainGame.hpp"



laserTower::laserTower()
{
	angles[up] = 0.f;
	angles[right] = 90.f;
	angles[down] = 180.f;
	angles[left] = 270.f;

	loadTexture();
	setAttributes();

	laserField.setFillColor(sf::Color(255, 0, 0, 55));

	accumulator = sf::Time::Zero;
}

laserTower::~laserTower()
{
}


void laserTower::loadTexture()
{
	textureName = "laserTower";
	texture = *mainGame::getInstance()->textures.getTowerTexture(textureName);
	sprite.setTexture(texture);

	sf::Vector2u textureSize = texture.getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 3, textureSize.y));

	laserT = mainGame::getInstance()->textures.getTexture("laser");

	sf::Texture *arrowDirT = mainGame::getInstance()->textures.getTexture("arrowDir");
	sf::Vector2f arrowCenter;
	arrowCenter.x = float(arrowDirT->getSize().x / 2);
	arrowCenter.y = float(arrowDirT->getSize().y / 2);
	for (int i = 0; i < 4; ++i)
	{
		dirArrows[i].setTexture(*arrowDirT);
		dirArrows[i].setOrigin(arrowCenter);
		dirArrows[i].setRotation(i * 90.f);
	}
}

void laserTower::setAttributes()
{
	cost = 1400;
	power = 1100;
	range = 500.f;
	speed = 1800.f;
	levelAcces = 25;
	value = cost;
	timer = sf::milliseconds(sf::Int32(speed * 3 / 4));
	dirChosen = false;
	canAttk = false;

	description = "Creates \na bundle of laser";
}

void laserTower::handleBullets()
{
	if (laser)
	{
		handleLaser();
	}
}

void laserTower::handleGun()
{
	for (int i = 0; i < 4; ++i)
	{
		if (objectClicked(dirArrows[i].getGlobalBounds()))
		{
			createField(dir(i));
			dirChosen = true;
			return;
		}
	}
}

void laserTower::createField(dir d)
{
	sf::Vector2f pion(10.f, range);
	sf::Vector2f poziom(range, 10.f);
	currentDir = d;
	switch (d)
	{
		case up:
		{
			laserField.setSize(pion);
			sf::Vector2f pos(getCenter().x - pion.x/2, getLaserBeginingPos().y - pion.y);
			laserField.setPosition(pos);
		}break;

		case right:
		{
			laserField.setSize(poziom);
			sf::Vector2f pos(getCenter().x, getLaserBeginingPos().y - poziom.y/2);
			laserField.setPosition(pos);
		}break;

		case down:
		{
			laserField.setSize(pion);
			sf::Vector2f pos(getCenter().x- pion.x / 2, getLaserBeginingPos().y);
			laserField.setPosition(pos);
		}break;

		case left:
		{
			laserField.setSize(poziom);
			sf::Vector2f pos(getCenter().x - poziom.x, getLaserBeginingPos().y - poziom.y / 2);
			laserField.setPosition(pos);
		}break;
	}
}

void laserTower::searchTarget()
{
	std::vector<wave*> & monsters = mainGame::getInstance()->getWaves();
	for (size_t i = monsters.size(); i-- > 0;)

	{
		for (size_t j = monsters[i]->size(); j-- > 0;)
		{
			if (isTargetInRange(monsters[i]->operator[](int(j))))
			{	
				targetingMonster = monsters[i]->operator[](int(j));
				canAttk = true;
			}
		}
	}
}

bool laserTower::isTargetOutofRange()
{
	int counter = 0;

	sf::Vector2f monsterPoints[5];
	monsterPoints[0].x = targetingMonster->getPosition().x + targetingMonster->getSize().x / 4;
	monsterPoints[0].y = targetingMonster->getPosition().y + targetingMonster->getSize().y / 4;
	monsterPoints[1].x = targetingMonster->getPosition().x + targetingMonster->getSize().x * 3 / 4;
	monsterPoints[1].y = targetingMonster->getPosition().y + targetingMonster->getSize().y / 4;
	monsterPoints[2].x = targetingMonster->getPosition().x + targetingMonster->getSize().x / 4;
	monsterPoints[2].y = targetingMonster->getPosition().y + targetingMonster->getSize().y * 3 / 4;
	monsterPoints[3].x = targetingMonster->getPosition().x + targetingMonster->getSize().x * 3 / 4;
	monsterPoints[3].y = targetingMonster->getPosition().y + targetingMonster->getSize().y * 3 / 4;
	monsterPoints[4] = targetingMonster->getCenter();

	for (int i = 0; i < 5; ++i)
	{
		if (!laserField.getGlobalBounds().contains(monsterPoints[i]))
			counter++;
	}

	if (counter == 5)
		return true;

	return false;
}

bool laserTower::haveTarget()
{
	return canAttk;
}

void laserTower::clearTarget()
{
	canAttk = false;
}

bool laserTower::mouseOnHUD(const sf::Vector2f mousePos)
{
	if ((sprite.getGlobalBounds().contains(mousePos) || (laserField.getGlobalBounds().contains(mousePos))))
		return true;

	return false;
}

void laserTower::handleLaser()
{
	accumulator += game::getInstance()->getTimer();

	if (accumulator >= laserFlashDuration)
	{
		accumulator = sf::Time::Zero;
		laser.reset();
		return;
	}

	sf::Uint8 alphaColor = sf::Uint8((laserFlashDuration - accumulator) / laserFlashDuration * 255);

	laser->setColor(sf::Color(255, 255, 255, alphaColor));
}

bool laserTower::isTargetInRange(std::shared_ptr<monster> monstero)
{
	sf::Vector2f monsterPoints[5];
	monsterPoints[0].x = monstero->getPosition().x + monstero->getSize().x / 4;
	monsterPoints[0].y = monstero->getPosition().y + monstero->getSize().y / 4;
	monsterPoints[1].x = monstero->getPosition().x + monstero->getSize().x * 3 /4;
	monsterPoints[1].y = monstero->getPosition().y + monstero->getSize().y / 4;
	monsterPoints[2].x = monstero->getPosition().x + monstero->getSize().x / 4;
	monsterPoints[2].y = monstero->getPosition().y + monstero->getSize().y * 3 / 4;
	monsterPoints[3].x = monstero->getPosition().x + monstero->getSize().x * 3 / 4;
	monsterPoints[3].y = monstero->getPosition().y + monstero->getSize().y * 3 / 4;
	monsterPoints[4] = monstero->getCenter();


	for (int i = 0; i < 5; ++i)
	{
		if (laserField.getGlobalBounds().contains(monsterPoints[i]))
 			return true;
	}

	return false;
}


void laserTower::shoot()
{
	laser = std::make_shared<sf::Sprite>(*laserT);

	sf::Vector2f laserPos;
	laserPos.x = getLaserBeginingPos().x;
	laserPos.y = getLaserBeginingPos().y;

	laser->setPosition(laserPos);

	sf::Vector2f laserOrigin;
	laserOrigin.x = laser->getGlobalBounds().width / 2;
	laserOrigin.y = laser->getGlobalBounds().height;

	laser->setOrigin(laserOrigin);

	laser->setRotation(angles[currentDir]);

	sf::Vector2f scaler(1.f, range / laserT->getSize().y);
	laser->setScale(scaler);

	std::vector<wave*> & waves = mainGame::getInstance()->getWaves();

	for (size_t i = 0; i < waves.size(); ++i)
	{
		for (size_t j = waves[i]->size(); j-- > 0;)
		{
			if (waves[i]->operator[](int(j))->getGlobalBounds().intersects(laser->getGlobalBounds()))
			{
				attackMonster(waves[i]->operator[](int(j)));
			}
		}
	}
}

void laserTower::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);

	dirArrows[0].setPosition(sf::Vector2f(getCenter().x - dirArrows[0].getGlobalBounds().width / 4, getPosition().y));
	dirArrows[1].setPosition(sf::Vector2f(getPosition().x + getSize().x - dirArrows[1].getGlobalBounds().width/2, getCenter().y - dirArrows[1].getGlobalBounds().height / 3));
	dirArrows[2].setPosition(sf::Vector2f(getCenter().x - dirArrows[2].getGlobalBounds().width / 4, getPosition().y + getSize().y - dirArrows[2].getGlobalBounds().height / 2));
	dirArrows[3].setPosition(sf::Vector2f(getPosition().x + getSize().x / 25, getCenter().y - dirArrows[3].getGlobalBounds().height / 3));
}

void laserTower::update()
{
	attackTower::update();

	if (!dirChosen)
	{
		handleGun();
	}
}

void laserTower::upgrade()
{
	power = int(round(float(power) * 1.3f));
	range = round(range *= 1.15f);

	createField(currentDir);
	expand();
	value += getUpgradeCost();
	upgradeLevel++;
}

void laserTower::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);

	if (laser)
		target.draw(*laser);

	if (HUDactive)
	{
		if (builded && !dirChosen)
		{
			for (int i = 0; i < 4; ++i)
			{
				target.draw(dirArrows[i]);
			}
		}
		else target.draw(laserField);
	}

}

std::shared_ptr<tower> laserTower::getClassObject()
{
	std::shared_ptr<tower> obj = std::make_shared<laserTower>();

	return obj;
}

sf::Vector2f laserTower::getLaserBeginingPos()
{
	sf::Vector2f laserStart;
	laserStart.x = getCenter().x;
	laserStart.y = getPosition().y + getSize().y / 8;

	return laserStart;
}
