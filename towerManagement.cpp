#include "pch.hpp"
#include "towerManagement.hpp"
#include "mainGame.hpp"

//towers
#include "arcaneTower.hpp"
#include "archerTower.hpp"
#include "cannonTower.hpp"
#include "darkTower.hpp"
#include "magmaTower.hpp"
#include "electricTower.hpp"
#include "poisonTower.hpp"
#include "crossbowTower.hpp"
#include "lightingTower.hpp"
#include "iceTower.hpp"
#include "deathTower.hpp"
#include "laserTower.hpp"
#include "antennaTower.hpp"
#include "signalTower.hpp"

towerManagament::towerManagament(workshop *Workshop)
{

	if (!recTexture.loadFromFile("Textury/shop.png"))
	{
		MessageBox(0, "Unable to open shopTexture, please call to BartekS0ft", 0, 0);
		return;
	}

	this->Workshop = Workshop;

	sf::Vector2f position;
	position.x = 1000.f;
	position.y = 0.f;

	background.setPosition(position);
	background.setSize(sf::Vector2f(WIDTH - background.getPosition().x, HEIGHT));
	background.setTexture(&recTexture);
	background.setOutlineThickness(-6);
	background.setOutlineColor(sf::Color(80,50,3));
	greenFrame = false;
	frame.setFillColor(sf::Color(255, 255, 255, 0));
	frame.setOutlineThickness(1.f);
	frame.setOutlineColor(sf::Color::Red);

	loadTextures();
	produceTowers();

	gameMap = mainGame::getInstance()->getMap();

}

towerManagament::~towerManagament()
{
}

void towerManagament::update()
{
	handleShop();

	handleTowers();

	workTowers();
}



void towerManagament::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background);

	for (size_t i = 0; i < towerShopTemplates.size(); ++i)
	{
		target.draw(*towerShopTemplates[i]->getShopTemplate());
	}

	if (currentTower)
	{
		target.draw(frame);
		target.draw(*currentTower);
	}
}

sf::Vector2f towerManagament::getPosition()
{
	return background.getPosition();
}

sf::Vector2f towerManagament::getSize()
{
	return background.getSize();
}


void towerManagament::produceTowers()
{
	std::shared_ptr<tower> t1 = std::make_shared<arcaneTower>();
	std::shared_ptr<tower> t2= std::make_shared<archerTower>();
	std::shared_ptr<tower> t3 = std::make_shared<cannonTower>();
	std::shared_ptr<tower> t4 = std::make_shared<poisonTower>();
	std::shared_ptr<tower> t5 = std::make_shared<iceTower>();
	std::shared_ptr<tower> t6 = std::make_shared<crossbowTower>();
	std::shared_ptr<tower> t8 = std::make_shared<magmaTower>();
	std::shared_ptr<tower> t9 = std::make_shared<darkTower>();
	std::shared_ptr<tower> t11 = std::make_shared<lightingTower>();
	std::shared_ptr<tower> t10 = std::make_shared<electricTower>();
	std::shared_ptr<tower> t13 = std::make_shared<deathTower>();
	std::shared_ptr<tower> t12 = std::make_shared<laserTower>();
	std::shared_ptr<tower> t7 = std::make_shared<antennaTower>();
	std::shared_ptr<tower> t14 = std::make_shared<signalTower>();
	
	towerShopTemplates.push_back(t1);
	towerShopTemplates.push_back(t2);
	towerShopTemplates.push_back(t3);
	towerShopTemplates.push_back(t4);
	towerShopTemplates.push_back(t5);
	towerShopTemplates.push_back(t6);
	towerShopTemplates.push_back(t7);
	towerShopTemplates.push_back(t8);
	towerShopTemplates.push_back(t9);
	towerShopTemplates.push_back(t10);
	towerShopTemplates.push_back(t11);
	towerShopTemplates.push_back(t12);
	towerShopTemplates.push_back(t13);
	towerShopTemplates.push_back(t14);

	sf::Vector2f towerPosition;

	for (size_t i = 0; i < towerShopTemplates.size(); ++i)
	{
	
		towerPosition.x = getPosition().x + getSize().x * 4/15 + (i % 2 * getSize().x * 7/15) - towerShopTemplates[i]->getShopTemplate()->getSize().x;

		if (i >= 2)
		{
			towerPosition.y = towerShopTemplates[i - 2]->getShopTemplate()->getPosition().y + towerShopTemplates[i - 2]->getShopTemplate()->getSize().y + 20.f;
		}
		else
			towerPosition.y = 50.f;

		towerShopTemplates[i]->getShopTemplate()->setPosition(towerPosition);
		towerShopTemplates[i]->getShopTemplate()->setHazePosition();

	}
}

void towerManagament::loadTextures()
{
	
}

void towerManagament::handleShop()
{
	std::shared_ptr<tower> currentSignature;

	for (size_t i = 0; i < towerShopTemplates.size(); ++i)
	{
		currentSignature = towerShopTemplates[i];

		if (currentSignature->getShopTemplate()->clicked())
		{
			if (currentSignature->canBuy())
			{
				if (activeTower)
				{
					activeTower->unactiveHUD();
					activeTower.reset();
				}
				currentTower = currentSignature->getClassObject();
				setFrame();
				currentTower->activateHUD();
			}
		}

		if (!currentSignature->getShopTemplate()->isUnlocked())
		{
			if (currentSignature->getShopTemplate()->canUnlock())
			{
				currentSignature->getShopTemplate()->unlock();
			}
		}

		else if (currentSignature->getShopTemplate()->getGoldAcces())
		{
			if (!currentSignature->isAfford())
			{
				currentSignature->getShopTemplate()->setGoldAcces(false);
				currentSignature->getShopTemplate()->makeSpriteRed();
			}
		}
		else if (!currentSignature->getShopTemplate()->getGoldAcces())
		{
			if (currentSignature->isAfford())
			{
				currentSignature->getShopTemplate()->setGoldAcces(true);
				currentSignature->getShopTemplate()->makeSpriteNormal();
			}
		}

		if (currentSignature->getShopTemplate()->isMouseOn(getMousePos()))
		{
			currentSignature->getShopTemplate()->addHazeTime();

			if (currentSignature->getShopTemplate()->isHoldingTimeUp())
			{
				currentSignature->getShopTemplate()->setHazeSwitcher(true);
			}
		}
		else
		{
			currentSignature->getShopTemplate()->resetTimer();
			currentSignature->getShopTemplate()->setHazeSwitcher(false);
		}

	}

	if (isTowerOnMouse())
	{
		sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(game::getInstance()->getWindow());
		mousePosition.x -= currentTower->getSize().x / 2;
		mousePosition.y -= currentTower->getSize().y / 2;

		currentTower->setPosition(mousePosition);
		frame.setPosition(mousePosition);
		
		if ((!greenFrame)&&((gameMap->canTowerBuild(currentTower))))
		{
			greenFrame = true;
			frame.setOutlineColor(sf::Color::Green);
		}
		else if ((greenFrame) && ((!gameMap->canTowerBuild(currentTower))))
		{
			greenFrame = false;
			frame.setOutlineColor(sf::Color::Red);
		}

		if ((buttonSwitcher::canClick())&&(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))&&(gameMap->canTowerBuild(currentTower)))
		{
			
				mainGame::getInstance()->getWallet()->pay(currentTower->cost);
				gameMap->buildTower(currentTower);
				currentTower.reset();
				return;
		}

		if ((buttonSwitcher::canClickKey(sf::Keyboard::Escape)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
		{
			currentTower.reset();
			return;
		}
	}
}

void towerManagament::handleTowers()
{
	sf::Vector2f mousePosition = getMousePos();



	for (int i = 0; i < gameMap->towers.size(); ++i)
	{

		if ((gameMap->towers[i]->isClicked(mousePosition)) && (activeTower!= gameMap->towers[i]))
		{
			if (activeTower)
			{
				activeTower->unactiveHUD();
				Workshop->leave();
			}

			currentTower.reset();
			activeTower = gameMap->towers[i];
			activeTower->activateHUD();
			Workshop->join(activeTower);
		}
	}

	if (activeTower)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if ((!activeTower->mouseOnHUD(mousePosition)) && (!Workshop->isMouseOn(mousePosition)))
			{
				activeTower->unactiveHUD();
				Workshop->leave();
				activeTower.reset();
			}
		}
	}



}

void towerManagament::workTowers()
{

	for (int i = 0; i < gameMap->towers.size(); ++i)
	{
		gameMap->towers[i]->update();
	}
}

bool towerManagament::isTowerOnMouse()
{
	return bool(currentTower);
}

void towerManagament::setFrame()
{
	frame.setPosition(currentTower->getPosition());
	frame.setSize(currentTower->getSize());
}

void towerManagament::updateFrame()
{

}
