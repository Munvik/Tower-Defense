#include "pch.hpp"
#include "explosionableBullet.hpp"
#include "mainGame.hpp"
#include "attackTower.hpp"

explosionableBullet::explosionableBullet(std::string textureName, sf::Vector2f V, attackTower * ownr)
	:bullet(textureName),
	explosion("smallExplosion",25,1/10)
{
	velocity = V;
	owner = ownr;
	dmg = owner->getPower();

	explosed = false;
	timer = sf::Time::Zero;
	timeExist = sf::seconds(1.8f);
	speed = 0.001f;
}

explosionableBullet::~explosionableBullet()
{
}

void explosionableBullet::update()
{
	sf::Time time = game::getInstance()->getTimer();

	sf::FloatRect monsterRect;

	std::vector<wave*> &waves = mainGame::getInstance()->getWaves();

	if (!explosed)
	{
		timer += time;

		if (timer >= timeExist)
		{
			sf::Vector2f explosionPoint;
			explosionPoint.x = getGlobalBounds().left + getGlobalBounds().width / 2;
			explosionPoint.y = getGlobalBounds().top + getGlobalBounds().height / 2;
			boom(explosionPoint);
		}

		sf::Vector2f bulletPoints[4];

		bulletPoints[0].x = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 5;
		bulletPoints[0].y = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 5;
		bulletPoints[1].x = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width * 4/5;
		bulletPoints[1].y = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 5;
		bulletPoints[2].x = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 5;
		bulletPoints[2].y = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height * 4 / 5;
		bulletPoints[3].x = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width * 4 / 5;
		bulletPoints[3].y = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height * 4 / 5;

		sf::FloatRect floatRect = sprite.getGlobalBounds();

		for (size_t i = 0; i < waves.size(); ++i)
		{
			for (size_t j = waves[i]->size(); j-- > 0;)
			{
				monsterRect = waves[i]->operator[](int(j))->getGlobalBounds();
		

				for (int k = 0; k < 4; ++k)
				{
					if (monsterRect.contains(bulletPoints[k])) //BOOOOM
					{
						sf::Vector2f explosionPoint;
						explosionPoint.x = (getCenter().x + waves[i]->operator[](int(j))->getCenter().x) / 2;
						explosionPoint.y = (getCenter().y + waves[i]->operator[](int(j))->getCenter().y) / 2;
						owner->attackMonster(waves[i]->operator[](int(j)));
						boom(explosionPoint);
						return;
					}
				}
			}
		}


		if (speed <= 1.f)
			speed += 0.04f;

		sf::Vector2f newV;

		newV.x = velocity.x * speed;
		newV.y = velocity.y * speed;
		sprite.move(newV * time.asSeconds());
	}
	else
	{
		explosion.update();

		if (explosion.end())
		{
			owner->removeBullet(this);
			return;
		}
	}
}

void explosionableBullet::boom(sf::Vector2f position)
{
	explosed = true;

	sf::Vector2f animationPos;
	animationPos.x = position.x - explosion.getGlobalBounds().width / 2;
	animationPos.y = position.y - explosion.getGlobalBounds().height / 2;
	explosion.setPosition(animationPos);

	sf::FloatRect monsterRect;
	std::vector<wave*> &waves = mainGame::getInstance()->getWaves();

	for (size_t i = 0; i < waves.size(); ++i)
	{
		for (size_t j = waves[i]->size(); j-- > 0;)
		{
			monsterRect = waves[i]->operator[](int(j))->getGlobalBounds();

			if (monsterRect.intersects(explosion.getGlobalBounds())) //BOOOOM
			{
					waves[i]->operator[](int(j))->getDmg(int(float(dmg)*owner->getPowerBuffFactor()) * 3 / 4);
			}	
		}
	}
}


void explosionableBullet::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if(!explosed)
	target.draw(sprite);

	else
	{
		target.draw(explosion);
	}
}
