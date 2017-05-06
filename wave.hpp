#pragma once
#include "monster.hpp"

class wave :public sf::Drawable
{
	friend class monster;

	sf::Texture texture;
	sf::Vector2f startPosition;
	void releaseMonsters();
	sf::Time timer;

	sf::Time timePeriod;
	int monsterDamage;
	int monstersAmount;
	float monsterSpeed;
	int monsterHP;
	int monsterGold;

	std::vector<std::shared_ptr<monster>> monsters;
	std::shared_ptr<monster> monsterTemplate;
	bool released;
	int monstersDied;
	int monstersDone;

public:
	wave(std::string fileName, int monstersA, int hp, float speed, float period, int gold, int monsterDmg);
	~wave();
	void setStartPosition(sf::Vector2f* startPos);
	void drawWave(sf::RenderWindow &window);
	void update();
	bool died();
	size_t size();

	void removeMonster(monster *m);
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	std::shared_ptr<monster> & operator[](int index);
};