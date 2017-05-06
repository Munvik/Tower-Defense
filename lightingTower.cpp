#include "pch.hpp"
#include "lightingTower.hpp"
#include "mainGame.hpp"
#include "monsterEffect.hpp"

lightingTower::lightingTower()
{
	textureName = "lightingTower";
	loadTexture();
	setAttributes();
}

lightingTower::~lightingTower()
{

}

void lightingTower::loadTexture()
{
	texture = *mainGame::getInstance()->textures.getTowerTexture("lightingTower");
	sprite.setTexture(texture);

	sf::Vector2u textureSize = texture.getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 3, textureSize.y));

	thunderTexture = mainGame::getInstance()->textures.getTowerBullet("thunder");
}

void lightingTower::setAttributes()
{
	cost = 600;
	power = 2200;
	range = 180.f;
	speed = 2000.f;
	levelAcces = 15;
	value = cost;
	timer = sf::milliseconds(sf::Int32(speed * 3 / 4));
	accumulator = sf::Time::Zero;
	slow = slowEffect::maxSlow;

	attackCircle.setRadius(range);
	sf::Vector2f circlePos;
	circlePos.x = getPosition().x + getSize().x / 2 - attackCircle.getGlobalBounds().width / 2;
	circlePos.y = getPosition().y + getSize().y / 2 - attackCircle.getGlobalBounds().height / 2;
	attackCircle.setPosition(circlePos);
	attackCircle.setFillColor(sf::Color(170, 80, 80, 100));
	description = "Big dmg\nSlows enemys";
}

std::shared_ptr<tower> lightingTower::getClassObject()
{
	std::shared_ptr<tower> obj = std::make_shared<lightingTower>();

	return obj;
}

void lightingTower::attack()
{
	thunder = std::make_shared<sf::Sprite>(*thunderTexture);
	sf::Vector2f thunderPos;
	thunderPos.x = getCenter().x;
	thunderPos.y = getPosition().y + getSize().y/8;

	thunder->setPosition(thunderPos);
	thunder->setOrigin(thunder->getGlobalBounds().width / 2, 0.f);

	sf::Vector2f v = targetingMonster->getCenter() - thunderPos;
	float rot = atan2(v.y, v.x);
	rot *= 180.f / 3.14f;
	rot += 270.f;
	thunder->setRotation(rot);

	float distance = sqrt(v.x * v.x + v.y * v.y);

	float scaler = distance / thunderTexture->getSize().y;
	thunder->setScale(1.f, scaler);

	attackMonster(targetingMonster);
}

void lightingTower::handleBullets()
{
	if(thunder)
	updateThunder();
}

void lightingTower::updateThunder()
{
	accumulator += game::getInstance()->getTimer();

	sf::Uint8 visibility = sf::Uint8((thunderFlashTime - accumulator) / thunderFlashTime * 255);
	thunder->setColor(sf::Color(255, 255, 255, visibility));

	if (accumulator >= thunderFlashTime)
	{
		thunder.reset();
		accumulator = sf::Time::Zero;
	}
}

void lightingTower::attackMonster(std::shared_ptr<monster> monst)
{
	std::shared_ptr<monsterEffect> slow = std::make_shared<slowEffect>(monst, this->slow, slowDuration);
	monst->getEffectHandler().addEffect(slow);
	attackTower::attackMonster(monst);
}

void lightingTower::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);

	if (thunder)
	{
		target.draw(*thunder);
	}

	if (HUDactive)
	{
		target.draw(attackCircle);
	}
}
