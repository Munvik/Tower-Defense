#pragma once
#include "bullet.hpp"
#include "animation.hpp"

class explosionableBullet :public bullet
{
	animation explosion;

	sf::Vector2f velocity;
	int dmg;
	float speed;
	bool explosed;

	sf::Time timeExist;
	sf::Time timer;

public:
	explosionableBullet(std::string textureName, sf::Vector2f V, attackTower *ownr);
	~explosionableBullet();

	void update();
	void boom(sf::Vector2f position);

	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

};