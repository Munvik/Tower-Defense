#include "pch.hpp"
#include "animationBullet.hpp"
#include "attackTower.hpp"

animationBullet::animationBullet(std::string textureName, attackTower * ownr)
	:energy(textureName, 5, 0.1f)
{
	owner = ownr;
	bulletSpeed = owner->getBulletSpeed();
	energy.setPosition(owner->getStartBulletPosition());

	target = owner->getTarget();
}

animationBullet::~animationBullet()
{
}

void animationBullet::update()
{
	float time = game::getInstance()->getTimer().asSeconds();

	sf::Vector2f distance = target->getCenter() - getCenter();

	sf::Vector2f velocity;
	velocity.x = distance.x * bulletSpeed / (fabs(distance.x) + fabs(distance.y));
	velocity.y = distance.y * bulletSpeed / (fabs(distance.x) + fabs(distance.y));

	sf::Vector2f V = velocity*time;
	energy.move(V);

	if (target->isUnavailable())
	{
		owner->removeBullet(this);
		return;
	}

	else if (targetAchieved(V))
	{
		owner->attackMonster(target);
		owner->removeBullet(this);
		return;
	}

	energy.update();
	if (energy.end())
	{
		energy.repeat();
	}
}

sf::Vector2f animationBullet::getCenter()
{
	return energy.getCenter();
}

void animationBullet::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(energy);
}

sf::Vector2f animationBullet::getSize()
{
	return energy.getSize();
}
