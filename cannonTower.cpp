#include "pch.hpp"
#include "cannonTower.hpp"

cannonTower::cannonTower()
{
	loadTexture();
	setAttributes();
}

cannonTower::~cannonTower()
{
}
void cannonTower::loadTexture()
{
	texture = *mainGame::getInstance()->textures.getTowerTexture("cannonTower");
	sprite.setTexture(texture);

	sf::Vector2u textureSize = texture.getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 3, textureSize.y));
}

void cannonTower::setAttributes()
{
	cost = 100;
	power = 300;
	range = 180.f;
	speed = 900.f;
	levelAcces = 1;
	bulletSpeed = 400.f;
	value = cost;
	timer = sf::milliseconds(sf::Int32(speed * 3 / 4));

	attackCircle.setRadius(range);
	sf::Vector2f circlePos;
	circlePos.x = getPosition().x + getSize().x / 2 - attackCircle.getGlobalBounds().width / 2;
	circlePos.y = getPosition().y + getSize().y / 2 - attackCircle.getGlobalBounds().height / 2;
	attackCircle.setPosition(circlePos);
	attackCircle.setFillColor(sf::Color(170, 80, 80, 100));

	bulletTextureName = "cannonTowerBullet";

	bullet bullettor(bulletTextureName);

	sf::Vector2f bulletPos;
	bulletPos.x = getPosition().x + getSize().x / 2 - bullettor.getGlobalBounds().width / 2;
	bulletPos.y = getPosition().y + getSize().y / 8 - bullettor.getGlobalBounds().height / 2;

	description = "AOE explosion";
	startBulletPosition = bulletPos;
}

void cannonTower::handleBullets()
{
	for (size_t i = 0; i < bullets.size(); ++i)
	{
		bullets[i].update();
	}
}

void cannonTower::removeBullet(bullet * rBullet)
{
	for (int i = 0; i<bullets.size(); ++i)
	{
		if (*rBullet == bullets[i])
		{
			bullets.erase(bullets.begin() + i);
		}
	}
}

std::shared_ptr<tower> cannonTower::getClassObject()
{
	std::shared_ptr<tower> obj = std::make_shared<cannonTower>();

	return obj;
}

void cannonTower::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);

	if (HUDactive)
		target.draw(attackCircle);

	for (size_t i = 0; i < bullets.size(); ++i)
	{
		target.draw(bullets[i]);
	}
}



void cannonTower::shoot()
{
	sf::Vector2f v = targetingMonster->getCenter()- getCenter();

	sf::Vector2f dirVelocity;

	dirVelocity.x = bulletSpeed * v.x / (fabs(v.x) + fabs(v.y));
	dirVelocity.y = bulletSpeed * v.y / (fabs(v.x) + fabs(v.y));

	explosionableBullet exploBullet(bulletTextureName, dirVelocity, this);
	float rot = atan2(v.y, v.x);
	rot *= 180.f / 3.14f;
	rot += 90.f;
	exploBullet.setRotation(rot);
	sf::Vector2f bulletPos;
	bulletPos.x = getCenter().x + getSize().x/2;
	bulletPos.y = getCenter().y + getSize().y/2 ;
	exploBullet.setPosition(startBulletPosition);
	bullets.push_back(exploBullet);
}
