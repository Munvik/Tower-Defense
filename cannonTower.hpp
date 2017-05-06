#pragma once
#include "attackTower.hpp"
#include "explosionableBullet.hpp"
#include "mainGame.hpp"

class cannonTower :public attackTower
{
	std::vector<explosionableBullet> bullets;

	void loadTexture();
	void setAttributes();
	void shoot() override;

public:
	cannonTower();
	~cannonTower();
	void handleBullets() override;
	void removeBullet(bullet *rBullet);

	std::shared_ptr<tower> getClassObject() override;

	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};