#pragma once
#include "attackTower.hpp"

class crossbowTower :public attackTower
{
	class bullet;

	void setAttributes();
	void loadTexture();
	std::vector<bullet> bullets;
	int criticChance;

	sf::Sprite crossbow;
public:
	crossbowTower();
	~crossbowTower();
	void handleBullets() override;
	void setPosition(sf::Vector2f position) override;
	void shoot() override;
	void upgrade() override;
	void attackMonster(std::shared_ptr<monster> monst) override;
	void removeBullet(bullet *rBullet);
	void draw(sf::RenderTarget & target, sf::RenderStates states)const;
	std::shared_ptr<tower> getClassObject();
	tower::workshopHandler *getWorkshopTemplate() override;

	class workshopHandler;

};

class crossbowTower::bullet :public ::bullet
{
	crossbowTower *owner;
	sf::Vector2f velocity;
public:
	bullet(std::string textureName, crossbowTower *ownr);
	~bullet();

	void setVelocity(sf::Vector2f v);
	void update();
	
};

class crossbowTower::workshopHandler :public attackTower::workshopHandler
{
	crossbowTower *owner;
	sf::Text criticalChance;
	void place() override;
	void set() override;
public:
	workshopHandler(crossbowTower *ownr) :owner(ownr) { upgradeAccesed = true; attackTower::workshopHandler::owner = ownr; };
	void update() override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};