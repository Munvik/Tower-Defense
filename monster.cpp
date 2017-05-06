#include "pch.hpp"
#include "monster.hpp"
#include "mainGame.hpp"
#include "path.hpp"

monster::monster()
{

}

monster::monster(wave *const _wave, sf::Texture* texture, int hp, float speed, int gold)
	: owner(_wave),
	isActive(false)
{
	spriteSize = sf::Vector2u(texture->getSize().x / 4,texture->getSize().y / 4);
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y));
	this->hp = hp;
	this->speed = speed;
	currentSpeed = speed;
	steps = 0.f;
	waySteps = 0;
	currentSlow = 0.f;
	currentShock = 0.f;

	waypoints = mainGame::getInstance()->levelPath.waypoints;
	sprite.setPosition(waypoints.front().x - sprite.getGlobalBounds().width / 2, waypoints.front().y - sprite.getGlobalBounds().height / 2);

	HPbar.setWidth(sprite.getGlobalBounds().width);
	HPbar.setFullHp(this->hp);

	sf::Vector2f hpBarPos;
	hpBarPos.x = sprite.getPosition().x + sprite.getGlobalBounds().width / 2 - HPbar.getSize().x / 2;
	hpBarPos.y = sprite.getPosition().y - HPbar.getSize().y;
	HPbar.setPosition(hpBarPos);

	findNewWaypoint();
	setVelocity();

	dead = false;
	goldWorth = gold;
	time = sf::Time::Zero;
}

monster::~monster()
{

}


void monster::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);
	target.draw(HPbar);
	target.draw(effects);
}

void monster::update()
{
	
	time = game::getInstance()->getTimer();
	sf::Vector2f movement = velocity*time.asSeconds();
	movement -= velocity * currentSlow * time.asSeconds();
	move(movement);

	if (isWaypointPassed(movement))
	{
		findNewWaypoint();
		setVelocity();
		steps = 0.f;
	}

	effects.update();
}

void monster::setTexture(sf::Texture * texture)
{
	sprite.setTexture(*texture);
}

sf::Vector2f monster::getCenter()
{
	sf::Vector2f center;
	center.x = sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
	center.y = sprite.getPosition().y + sprite.getGlobalBounds().height / 2;

	return center;
}

bool monster::wentInBase()
{
	return waypoints.empty();
}

void monster::getDmg(int dmg)
{
	int damage = int(dmg + currentShock * float(dmg));
	hp -= damage;
	
	HPbar.shrinkBar(dmg);

	if (hp <= 0)
	{
		die();
		return;
	}
}

bool monster::isActivated()
{
	return isActive;
}

bool monster::isUnavailable()
{
	if (dead) 
		return true;

	if (wentInBase())
		return true;

	return false;
}

sf::FloatRect monster::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

sf::Vector2f monster::getSize()
{
	sf::Vector2f monsterSize;
	monsterSize.x = sprite.getGlobalBounds().width;
	monsterSize.y = sprite.getGlobalBounds().height;
	return monsterSize;
}

sf::Vector2f monster::getPosition()
{
	return sprite.getPosition();
}


sf::Sprite * monster::getSprite()
{
	return &sprite;
}

effectHandler & monster::getEffectHandler()
{
	return effects;
}


bool monster::operator==(const monster & mon)
{
	return (this == &mon);
}

float monster::getSlow()
{
	return currentSlow;
}

void monster::slow(float factor)
{
	currentSlow += factor;
	currentSpeed -= factor * speed;
}

void monster::unslow(float factor)
{
	currentSlow -= factor;
	currentSpeed += factor * speed;
}

float monster::getShock()
{
	return currentShock;
}

void monster::shock(float factor)
{
	currentShock += factor;
}

void monster::unshock(float factor)
{
	currentShock -= factor;
}

unsigned long int monster::getWaySteps()
{
	return waySteps;
}

void monster::setVelocity()
{
	sf::Vector2f distanceVector;
	distanceVector = *currentWaypoint - getCenter();

	velocity.x = distanceVector.x * speed / fabs(distanceVector.x + distanceVector.y);
	velocity.y = distanceVector.y * speed / fabs(distanceVector.x + distanceVector.y);

	if (fabs(velocity.x) > fabs(velocity.y))
	{
		if (isPositive(velocity.x))
		{
			velocity.x = speed;
			velocity.y = 0.f;
			currDirection = right;
		}
		else
		{
			velocity.x = -speed;
			velocity.y = 0.f;
			currDirection = left;
		}
	}
	else
	{
		if (isPositive(velocity.y))
		{
			velocity.x = 0.f;
			velocity.y = speed;
			currDirection = down;
		}
		else
		{
			velocity.x = 0.f;
			velocity.y = -speed;
			currDirection = top;
		}
	}


}

bool monster::isWaypointPassed(sf::Vector2f movement)
{
	float actualDistance;
	actualDistance = fabs(getCenter().x - currentWaypoint->x) + 
		fabs(getCenter().y - currentWaypoint->y);

	float nextDistance;
	nextDistance = fabs(getCenter().x + movement.x - currentWaypoint->x) +
		fabs(getCenter().y + movement.y - currentWaypoint->y);

	if (nextDistance < actualDistance)
		return false;

	return true;
}

void monster::findNewWaypoint()
{
	waypoints.pop();
	
	if (wentInBase())
	{
		mainGame::getInstance()->subtractLife(owner->monsterDamage);
		int random = rand() % 3 + 1;
		mainGame::getInstance()->getWallet()->deposit(goldWorth * random / 4);
		return owner->removeMonster(this);
	}

	currentWaypoint = &waypoints.front();
}

void monster::move(sf::Vector2f movement)
{
	sprite.move(movement);
	HPbar.move(movement);
	waySteps += int(currentSpeed);
	steps += currentSpeed;

	if (steps >= maxSteps)
		steps = 0.f;

	sf::IntRect textureCords((int)(steps / (maxSteps/4)) * spriteSize.x, currDirection * spriteSize.y, spriteSize.x, spriteSize.y);
	sprite.setTextureRect(textureCords);
}

void monster::activate()
{
	isActive = true;
}

void monster::die()
{
	mainGame::getInstance()->getWallet()->deposit(goldWorth);
	dead = true;
	owner->removeMonster(this);
}

