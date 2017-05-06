#include "pch.hpp"
#include "magmaTower.hpp"
#include "mainGame.hpp"

magmaTower::magmaTower()
{
	loadTexture();
	setAttributes();
}

magmaTower::~magmaTower()
{
}

void magmaTower::loadTexture()
{
	texture = *mainGame::getInstance()->textures.getTowerTexture("magmaTower");
	sprite.setTexture(texture);

	sf::Vector2u textureSize = texture.getSize();
	sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x / 3, textureSize.y));
	lavaTexture = mainGame::getInstance()->textures.getTexture("lava");
	magmaTexture = mainGame::getInstance()->textures.getTexture("magma");

	sf::Vector2u lavaTextureSize = lavaTexture->getSize();

	startLavaRect.left = 0;
	startLavaRect.top = 0;
	startLavaRect.width = lavaTextureSize.x;
	startLavaRect.height = lavaTexture->getSize().y * 1 / 10;
}

void magmaTower::setAttributes()
{
	cost = 200;
	power = 6;
	range = 100.f;
	speed = 3200.f;
	levelAcces = 8;
	bulletSpeed = 150.f;
	value = cost;
	timer = sf::milliseconds(sf::Int32(speed * 3 / 4));

	_timer = sf::Time::Zero;
	magmaTimer = sf::Time::Zero;
	magmaWorks = false;

	attackCircle.setRadius(range);
	sf::Vector2f circlePos;
	circlePos.x = getPosition().x + getSize().x / 2 - attackCircle.getGlobalBounds().width / 2;
	circlePos.y = getPosition().y + getSize().y / 2 - attackCircle.getGlobalBounds().height / 2;
	attackCircle.setPosition(circlePos);
	attackCircle.setFillColor(sf::Color(170, 80, 80, 100));
	description = "Spill magma";
	bulletTextureName = "magmaTowerBullet";

	bullet bullettor(bulletTextureName);

	sf::Vector2f bulletPos;
	bulletPos.x = getPosition().x + getSize().x / 2 - bullettor.getGlobalBounds().width / 2;
	bulletPos.y = getPosition().y + getSize().y / 8 - bullettor.getGlobalBounds().height / 2;

	startBulletPosition = bulletPos;
}

void magmaTower::removeBullet(bullet * rBullet)
{
	for (int i = 0; i<bullets.size(); ++i)
	{
		if (*rBullet == bullets[i])
		{
			bullets.erase(bullets.begin() + i);
		}
	}
}

void magmaTower::shoot()
{
	//float lavaDist = sqrt((magmaDestination.x - startBulletPosition.x)*(magmaDestination.x - startBulletPosition.x) + (magmaDestination.y - startBulletPosition.y)*(magmaDestination.y - startBulletPosition.y));

	sf::Vector2f vector = magmaDestination - startBulletPosition;
	sf::Vector2f bulletV;
	bulletV.x = vector.x * bulletSpeed / (fabs(vector.x) + fabs(vector.y));
	bulletV.y = vector.y * bulletSpeed / (fabs(vector.x) + fabs(vector.y));

	magmaBullet = std::make_shared<straightBullet>(bulletTextureName, bulletV, magmaDestination, startBulletPosition);

	magmaWorks = true;
}

void magmaTower::handleBullets()
{
	if (magmaBullet)
	{
		magmaBullet->update();
		if (magmaBullet->achieved())
		{
			magmaBullet.reset();
			magma = std::make_shared<sf::Sprite>(*magmaTexture);

			magma->setPosition(getMidlePosition(magmaDestination, magma->getGlobalBounds()));
		}
	}
}

void magmaTower::update()
{
	timer += game::getInstance()->getTimer();
	_timer += game::getInstance()->getTimer();


		if (timer.asMilliseconds() >= speed)
		{
			if(!magmaWorks)
			searchTarget();


			if ((haveTarget()) && (canAttack()))
			{
				timer = sf::Time::Zero;
				shoot();
				targetingMonster.reset();
			}
		}

		if (magma)
		{
			magmaTimer += game::getInstance()->getTimer();
			updateMagma();
		}

		handleBullets();
}

std::shared_ptr<tower> magmaTower::getClassObject()
{
	std::shared_ptr<tower> obj = std::make_shared<magmaTower>();

	return obj;
}

void magmaTower::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);

	if (HUDactive)
	{
		target.draw(attackCircle);
	}

	if (magmaBullet)
		target.draw(*magmaBullet);
	else if (magma)
	{
			target.draw(*magma);
	}

}

void magmaTower::updateMagma()
{
	if (magmaTimer.asSeconds() >= magmaExisting)
	{
		magma.reset();
		magmaTimer = sf::Time::Zero;
		magmaWorks = false;
		return;
	}

	sf::FloatRect magmaRects = magma->getGlobalBounds();

	if (_timer.asSeconds() >= magmaIncreaseTime)
	{

		if ((magmaRects.width < path::width) && (magmaRects.height <= path::width))
		{
			magma->scale(1.1f, 1.1f);
			_timer = sf::Time::Zero;
			magma->setPosition(getMidlePosition(magmaDestination, magmaRects));
		}
	}

	sf::FloatRect monsterRect;

	std::vector<wave*> &waves = mainGame::getInstance()->getWaves();

	for (size_t i = 0; i < waves.size(); ++i)
	{
		for (size_t j = waves[i]->size(); j-- > 0;)
		{
			monsterRect = waves[i]->operator[](int(j))->getGlobalBounds();

			if (magmaRects.intersects(monsterRect))
			{
				waves[i]->operator[](int(j))->getDmg(power);
			}
		}
	}
}
void magmaTower::searchTarget()
{

	std::vector<wave*> & monsters = mainGame::getInstance()->getWaves();

	for (size_t i = monsters.size(); i-- > 0;)
	{
		for (size_t j = monsters[i]->size(); j-- > 0;)
		{
			if (isTargetInRange(monsters[i]->operator[](int(j))))
			{
				targetingMonster = monsters[i]->operator[](int(j));
				magmaDestination = targetingMonster->getCenter();
			}
		}
	}
}