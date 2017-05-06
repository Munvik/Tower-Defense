#pragma once
#include "attackTower.hpp"
#include "animationBullet.hpp"

class electricTower :public attackTower
{
	void loadTexture();
	void setAttributes();

	std::vector<animationBullet> bullets;
	float shockFactor;
	float shockDuration;

protected:
	void handleBullets() override;

public:
	electricTower();
	~electricTower();
	void shoot() override;
	void removeBullet(bullet *rBullet) override;
	void attackMonster(std::shared_ptr<monster> monst) override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void upgrade() override;

	std::shared_ptr<tower> getClassObject() override;
	tower::workshopHandler *getWorkshopTemplate() override;

	class workshopHandler;
};

class electricTower::workshopHandler :public attackTower::workshopHandler
{
	electricTower *owner;
	sf::Text shockEffect;
	void place() override;
public:
	workshopHandler(electricTower *ownr) : owner(ownr) { attackTower::workshopHandler::owner = ownr; };
	void set() override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

