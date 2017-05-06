#include "pch.hpp"
#include "mainGame.hpp"
#include <fstream>
#include <string>
#include <json\json.h>
#include "base.hpp"
#include "gameoverScreen.hpp"
#include "gameCompletedScreen.hpp"

#ifndef MAINMENU
#include "mainMenu.hpp"
#endif

mainGame *mainGame::instance = nullptr;


mainGame::mainGame(const std::string fileName)
	:wnd(game::getInstance()->getWindow())
{

	instance = this;

	loader.setPosition(getMidlePosition(sf::Vector2f(WIDTH / 2, HEIGHT / 2), loader.getGlobalBounds()));
	wnd.clear(sf::Color(10,10,10));
	wnd.draw(loader);
	wnd.display();
	
	wavesDied = 0;
	waveNumber = 0;

	loadLevel(fileName);

	sf::Music *mainMenuMusic = game::getInstance()->getMusic();
	mainMenuMusic->stop();

	level = 1;
	lifes = maxLifes;
	

	_waves.push_back(&waves[level-1]);

	shop = std::make_unique<towerManagament>(&towerHandler);
	lvlInterlude = std::make_unique<levelInterlude>(level);

	sf::Vector2f walletPos;

	walletPos.x = shop->getPosition().x + shop->getSize().x / 2 - money.getSize().x/2;
	walletPos.y = 10.f;
	money.setPosition(walletPos);

	float baseWidth = _base->getSize().x;
	gameHPbar.setWidth(baseWidth);

	gameHPbar.setFullHp(lifes);
	sf::Vector2f hpBarPos;
	hpBarPos.x = _base->getCenter().x - gameHPbar.getSize().x / 2;
	hpBarPos.y = _base->getPosition().y - gameHPbar.getSize().y * 1.1f;
	gameHPbar.setPosition(hpBarPos);

	skipLevelText.setFont(*game::getInstance()->getFont());
	skipLevelText.setString("Skip Level");
	skipLevelText.setCharacterSize(18);
	skipLevelText.setColor(sf::Color(30, 30, 60));
	sf::Vector2f skipLevelPos;
	skipLevelPos.x = shop->getPosition().x - skipLevelText.getGlobalBounds().width*1.2f;
	skipLevelPos.y = HEIGHT / 100;
	skipLevelText.setPosition(skipLevelPos);

	levelCounter.setFont(*game::getInstance()->getFont());
	levelCounter.setString("Level 1");
	levelCounter.setCharacterSize(18);
	levelCounter.setColor(sf::Color(30, 30, 30));
	sf::Vector2f levelCounterPos;
	levelCounterPos.x = skipLevelText.getPosition().x - 2 * levelCounter.getGlobalBounds().width;
	levelCounterPos.y = HEIGHT / 100;
	levelCounter.setPosition(levelCounterPos);

	loader.load(1.f);
	wnd.clear(sf::Color(96, 96, 96));
	wnd.draw(loader);
	wnd.display();
}

mainGame::~mainGame()
{
	if (instance == this)
	{
		instance = nullptr;
	}
}


void mainGame::update()
{
	if (!pauser.isOn())
	{
		updateGame();
	}
	else
		pauser.update();

}

void mainGame::updateGame()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		game::getInstance()->hurryUpTime();
	}

	if (!lvlInterlude)
	{
		if ((skipLevelText.getGlobalBounds().contains(getMousePos())) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))&&(buttonSwitcher::canClick()))
		{
			if((_waves.size() <= 3)&&(level< waves.size()))
			prepareToNewWave();
		}

		for (size_t i = 0; i < _waves.size(); ++i)
		{
			_waves[i]->update();

			if (_waves[i]->died())
			{
				_waves.erase(_waves.begin() + i);
				wavesDied++;
			}
		}
		
		if (_waves.empty())
		{
			if (wavesDied == waveNumber)
			{
				sf::Image wndImage = game::getInstance()->getWindow().capture();
				game::getInstance()->setController(std::make_unique<gameCompletedScreen>(wndImage));
				print("Koniec gry");
				return;
			}
       			prepareToNewWave();
			lvlInterlude = std::make_unique<levelInterlude>(level);
		}

		
	}
	else
	{
		lvlInterlude->update();
		if (lvlInterlude->skipped())
		{
			lvlInterlude.reset();
		}
	}

	Map.update();
	shop->update();
	towerHandler.update();

	if (gameHPbar.empty())
	{
		game::getInstance()->setController(std::make_unique<gameoverScreen>());
		return;
	}

	if ((buttonSwitcher::canClickKey(sf::Keyboard::Escape))&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
	{
		pauser.turnOn();
	}


}

void mainGame::prepareToNewWave()
{
  	_waves.push_back(&waves[level]);

	level++;
	levelCounter.setString("Level " + intToString(level));
}

void mainGame::draw(sf::RenderWindow & window)
{
	window.draw(Map);
	window.draw(gameHPbar);
	window.draw(towerHandler);
	window.draw(*shop);
	window.draw(money);
	window.draw(skipLevelText);
	window.draw(levelCounter);

	for (size_t i =0; i<_waves.size(); i++)
	{
		window.draw(*_waves[i]);
	}


	if (lvlInterlude)
	{
		window.draw(*lvlInterlude);
	}

	if (pauser.isOn())
	{
		window.draw(pauser);
	}
}

map * mainGame::getMap()
{
	return &Map;
}

wallet * mainGame::getWallet()
{
	return &money;
}

int * mainGame::getLevel()
{
	return &level;
}

std::string mainGame::getLevelName()
{
	return levelName;
}

std::vector<wave*>& mainGame::getWaves()
{
	return _waves;
}


int mainGame::getLifes()
{
	return lifes;
}

void mainGame::subtractLife(int lifeAmount)
{
	lifes -= lifeAmount;
	gameHPbar.shrinkBar(lifeAmount);

}

int * mainGame::getHP()
{
	return gameHPbar.getHP();
}

sf::Music * mainGame::getMusic() 
{
	return &music;
}

mainGame * mainGame::getInstance()
{
	return instance;
}


void mainGame::loadLevel(const std::string fileName)
{
	std::ifstream file;

	file.open("Levele/" + fileName);

	if (!file.is_open())
	{
		MessageBox(0, "Unable to open fileName.txt to read Level, please call to Bartek", 0, 0);
		return;
	}

	loader.load(20.f / 100.f);
	wnd.clear(sf::Color(20, 20, 20));
	wnd.draw(loader);
	wnd.display();

	std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	Json::Reader reader;
	Json::Value root;

	bool isParsed = reader.parse(data, root);

	if (!isParsed)
	{
		print("nie da sie zparsowac");
		print(reader.getFormatedErrorMessages());
		return;
	}

	std::string mapBackgroundName = root["backgroundName"].asString();

	if (!Map.texture.loadFromFile("Textury/" + mapBackgroundName))
	{
		MessageBox(0, "Unable to open map texture, please call to Bartek", 0, 0);
		return;
	}
	Map.background.setTexture(Map.texture);

	std::string musicName = root["music"].asString();

	if (!music.openFromFile("Music/" + musicName))
	{
		MessageBox(0, "Unable to open music, please call to Bartek", 0, 0);
		return;
	}

	musicVolume = 20;
	music.setLoop(true);
	music.setVolume(musicVolume);
	music.play();

	loader.load(40.f / 100.f);
	wnd.clear(sf::Color(30, 30, 30));
	wnd.draw(loader);
	wnd.display();

	Json::Value waypointsCount = root["waypoints"];

	for (Json::ArrayIndex i = 0; i < waypointsCount.size(); ++i)
	{
		sf::Vector2f waypoint;
		waypoint.x = waypointsCount[i]["x"].asFloat();
		waypoint.y = waypointsCount[i]["y"].asFloat();

		levelPath.wayPoints.push_back(waypoint);
		levelPath.waypoints.push(waypoint);
	}

	loader.load(55.f / 100.f);
	wnd.clear(sf::Color(40,40, 40));
	wnd.draw(loader);
	wnd.display();

	levelPath.makeUnBuildablePath();

	Json::Value monsters = root["monsters"];

	for (Json::ArrayIndex i = 0; i < monsters.size(); ++i)
	{
		std::string fileName = monsters[i]["texture"].asString();
		int waveAmount = monsters[i]["waveAmount"].asInt();
		int hp = monsters[i]["hp"].asInt();
		float speed = monsters[i]["speed"].asFloat();
		float period = monsters[i]["period"].asFloat();
		int goldWorth = monsters[i]["goldWorth"].asInt();
		int monsterDmg = monsters[i]["dmg"].asInt();
		
		waves.emplace_back(fileName, waveAmount, hp, speed, period, goldWorth, monsterDmg);
		waveNumber++;
		print("wavesNumber = ", waveNumber);
	}

	loader.load(80.f / 100.f);
	wnd.clear(sf::Color(60, 60, 60));
	wnd.draw(loader);
	wnd.display();

	_base = std::make_shared<base>();
	sf::Vector2f basePos;
	basePos.x = root["basePosx"].asFloat();
	basePos.y = root["basePosy"].asFloat();
	sf::Vector2f basePosition = getMidlePosition(basePos, _base->getGlobalBounds());
	_base->setPosition(basePosition);
	Map.towers.push_back(_base);
	

	file.close();

	levelName = fileName;

	loader.load(90.f / 100.f);
	wnd.clear(sf::Color(75, 75, 75));
	wnd.draw(loader);
	wnd.display();
}