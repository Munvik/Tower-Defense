#pragma once
#include "bullet.hpp"
#include "animation.hpp"

class animationBullet :public bullet
{
	animation energy;
public:
	animationBullet(std::string textureName, attackTower *ownr);
	~animationBullet();
	void update();
	sf::Vector2f getCenter() override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	sf::Vector2f getSize();
};