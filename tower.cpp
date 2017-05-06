#include "pch.hpp"
#include "tower.hpp"
#include "mainGame.hpp"
#include "game.hpp"
#include <iomanip>
#include "buffTower.hpp"
tower::tower()
{
	upgradeLevel = 0;
	value = cost;
	upgradeGoldAcces = false;
	HUDactive = false;
	builded = false;

	globalTimer = &game::getInstance()->getTimer();
}

tower::~tower()
{
}


void tower::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

sf::Vector2f tower::getSize()
{
	sf::Vector2f size;
	size.x = sprite.getGlobalBounds().width;
	size.y = sprite.getGlobalBounds().height;
	return size;
}

sf::Vector2f tower::getCenter()
{
	sf::Vector2f center;
	center.x = sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
	center.y = sprite.getPosition().y + sprite.getGlobalBounds().height / 2;

	return center;
}

sf::Vector2f tower::getPosition()
{
	return sprite.getPosition();
}

sf::FloatRect tower::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

bool tower::canBuy()
{
	if ((mainGame::getInstance()->getWallet()->isAfford(cost)) && (getShopTemplate()->isUnlocked()))
		return true;

	return false;
}

bool tower::isAfford()
{
	if (mainGame::getInstance()->getWallet()->isAfford(cost))
		return true;

	return false;
}

int tower::getLevelAcces()
{
	return levelAcces;
}

bool tower::isClicked(const sf::Vector2f mousePos)
{
	if ((sprite.getGlobalBounds().contains(mousePos)) && (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)))
	{
		return true;
	}

	return false;
}

bool tower::isActive()
{
	return HUDactive;
}

int tower::getValue()
{
	return value;
}

int tower::getUpgradeCost()
{
	return value;
}

int tower::isAffordForUpgrade()
{
	int gold = mainGame::getInstance()->getWallet()->getGold();

	if (gold >= getUpgradeCost())
	{
		return true;
	}

	return false;
}

int tower::getUpgradeLevel()
{
	return upgradeLevel;
}

bool tower::isExtended()
{
	if (upgradeLevel == maxUpgradeLevel)
		return true;

	return false;
}

void tower::sell()
{
	int val = int(float(value) * 0.70f);
	mainGame::getInstance()->getWallet()->deposit(val);
	mainGame::getInstance()->getMap()->sellTower(this);
}

void tower::removeBuff(buff unbuffer)
{

}

void tower::build()
{
	builded = true;
}

void tower::buf(attackTower * buffingTower)
{

}

bool tower::isBuffed()
{
	return buffed;
}

void tower::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);
}

void tower::expand()
{
	int newTextureXPos = int(sprite.getTextureRect().left +texture.getSize().x / 3);

	sprite.setTextureRect(sf::IntRect(newTextureXPos, 0, texture.getSize().x / 3, texture.getSize().y));
}



///////////////////////////////// TOWER::WORKSHOPHANDLER /////////////////////////////////////////
///////////////////////////////// TOWER::WORKSHOPHANDLER /////////////////////////////////////////
///////////////////////////////// TOWER::WORKSHOPHANDLER /////////////////////////////////////////

bool tower::workshopHandler::XClicked()
{
	return objectClicked(X.getGlobalBounds());
}

bool tower::workshopHandler::Placed()
{
	return placed;
}

tower::workshopHandler::workshopHandler()
{
	font = game::getInstance()->getFont();

	if (!XTexture.loadFromFile("Textury/pcCross.png"))
	{
		MessageBox(0, "Unable to open pcCross, please call to BartekS0ft", 0, 0);
		return;
	}
	X.setTexture(XTexture);
}

void tower::workshopHandler::join(workshop *ws)
{
	workshopOwner = ws;
}

void tower::workshopHandler::update()
{
	if (XClicked())
	{
		workshopOwner->leave();
	}
}

workshop * tower::workshopHandler::getWorkshop()
{
	return nullptr;
}

void tower::workshopHandler::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(X);
}



///////////////////////////////////////////////// TOWER::SHOPTEMPLATE //////////////////////////////////
tower::shopTemplate::shopTemplate(tower *ownr)
{
	owner = ownr;
	towerSprite = owner->sprite;

	if (!textHazeTexture.loadFromFile("Textury/haze.png"))
	{
		MessageBox(0, "Unable to open textHaze.png, please call to BartekS0ft", 0, 0);
		return;
	}
	textHaze.setTexture(textHazeTexture);

	hazeTimer = sf::Time::Zero;

	font = game::getInstance()->getFont();
	cost.setFont(*font);

	sf::Texture *padLTexture = mainGame::getInstance()->textures.getPadlock();
	padlock.setTexture(*padLTexture);

	unlocked = false;
	goldAcces = true;
	canTextHazeDraw = false;
}

sf::Vector2f tower::shopTemplate::getPosition()
{
	return towerSprite.getPosition();
}

bool tower::shopTemplate::isUnlocked()
{
	return unlocked;
}

bool tower::shopTemplate::clicked()
{
	if ((towerSprite.getGlobalBounds().contains(getMousePos())) && (buttonSwitcher::canClick()) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		return true;
	}

	return false;
}

bool tower::shopTemplate::canUnlock()
{
	if (*mainGame::getInstance()->getLevel() >= owner->levelAcces)
		return true;

	return false;
}

void tower::shopTemplate::unlock()
{
	unlocked = true;
}

void tower::shopTemplate::makeSpriteRed()
{
	towerSprite.setColor(sf::Color::Red);
	print("o chuj nie ma kasy");
}

void tower::shopTemplate::makeSpriteNormal()
{
	towerSprite.setColor(sf::Color(255, 255, 255));
}

bool tower::shopTemplate::getGoldAcces() const
{
	return goldAcces;
}

void tower::shopTemplate::setGoldAcces(bool switcher)
{
	goldAcces = switcher;
}

void tower::shopTemplate::setHazePosition()
{
	sf::Vector2f hazePos;
	hazePos.x = towerSprite.getPosition().x - textHaze.getGlobalBounds().width;
	hazePos.y = towerSprite.getPosition().y + towerSprite.getGlobalBounds().height / 2 - textHaze.getGlobalBounds().height / 2;

	textHaze.setPosition(hazePos);

	setDescription();
}

void tower::shopTemplate::setDescription()
{
	std::string descr = owner->description;
	sf::Text text;
	text.setCharacterSize(14);
	text.setFont(*font);
	text.setColor(sf::Color::Black);
	float hazeXCenter = textHaze.getPosition().x + textHaze.getGlobalBounds().width / 2 - 8.f;

	int cache = 0;

	for (size_t i = 0; i < descr.size(); ++i)
	{
		if (descr[i] == '\n')
		{
			sf::Text t = text;
			int diff = i - cache;
			t.setString(descr.substr(cache, diff));
			cache = i;
			description.push_back(t);
		}
	}

	text.setString(descr.substr(cache, descr.size()));
	text.setPosition(hazeXCenter - text.getGlobalBounds().width / 2, 0);
	description.push_back(text);

	size_t descriptionSize = description.size();
	print("size = ", descriptionSize);

	for (size_t i = 1; i <= description.size(); i++)
	{
		float descrYPos = textHaze.getPosition().y + textHaze.getGlobalBounds().height  / (descriptionSize*2) * i - description[i-1].getGlobalBounds().height/2;
		float width = description[i-1].getGlobalBounds().width;
		description[i-1].setPosition(hazeXCenter - width/2, descrYPos);
	}

}

bool tower::shopTemplate::isMouseOn(sf::Vector2f mousePos)
{
	if (towerSprite.getGlobalBounds().contains(mousePos))
		return true;

	return false;
}

void tower::shopTemplate::addHazeTime()
{
	hazeTimer += game::getInstance()->getTimer();
}

void tower::shopTemplate::resetTimer()
{
	hazeTimer = sf::Time::Zero;
}

bool tower::shopTemplate::isHoldingTimeUp()
{
	if (hazeTimer >= holdingTime)
		return true;

	return false;
}

void tower::shopTemplate::setHazeSwitcher(bool switcher)
{
	canTextHazeDraw = switcher;
}


void tower::shopTemplate::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(towerSprite);
	target.draw(cost);

	if (!unlocked)
		target.draw(padlock);

	if (canTextHazeDraw)
	{
		target.draw(textHaze);

		for (size_t i = 0; i < description.size(); ++i)
		{
			target.draw(description[i]);
		}
	}
}

