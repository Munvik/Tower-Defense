#pragma once
#include "gameCtrl.hpp"
#include "map.hpp"
#include "path.hpp"
#include "wave.hpp"
#include <queue>
#include "textureCache.hpp"
#include "workshop.hpp"
#include "wallet.hpp"
#include "pause.hpp"
#include "levelInterlude.hpp"
#include "gameLoader.hpp"

class mainGame :public gameCtrl
{
	friend class towerManagament;
	friend class upgradeImage;

	static mainGame* instance;

	map Map;
	std::vector <wave> waves;
	std::vector <wave*> _waves;
	void loadLevel(const std::string fileName);

	std::unique_ptr<towerManagament> shop;
	std::unique_ptr<levelInterlude> lvlInterlude;
	workshop towerHandler;

	wallet money;
	int level;
	sf::Text skipLevelText;
	sf::Text levelCounter;

	pause pauser;
	gameLoader loader;
	sf::RenderWindow  & wnd;

	std::shared_ptr<tower> _base;
	hpBar gameHPbar;
	sf::Music music;
	float musicVolume;
	std::string levelName;
	void prepareToNewWave();
	int lifes;
	const int maxLifes = 100;
	int wavesDied;
	int waveNumber;

public:
	mainGame(const std::string fileName);
	~mainGame();
	void update();
	void updateGame();
	void draw(sf::RenderWindow &window);
	map *getMap();
	path levelPath;
	textureCache textures;
	wallet *getWallet();
	int *getLevel();
	std::string getLevelName();
	std::vector<wave*> & getWaves();
	int getLifes();
	void subtractLife(int lifeAmount);

	int *getHP();
	sf::Music *getMusic();

	static mainGame* getInstance();
};
