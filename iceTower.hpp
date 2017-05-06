#pragma once
#include "attackTower.hpp"

class iceTower :public attackTower
{
	void setAttributes();
	void loadTexture();
	float slow;
	const float slowDur = 1500.f;
public:
	iceTower();
	~iceTower();
	void handleBullets() override;
	void searchTarget() override;
	void attackMonster(std::shared_ptr<monster> monst) override;
	void shoot() override;
	void upgrade() override;
	std::shared_ptr<tower> getClassObject() override;
	tower::workshopHandler *getWorkshopTemplate() override;
	tower::shopTemplate *getShopTemplate() override;

	class workshopHandler;
	class shopTemplate;
};

class iceTower::workshopHandler :public attackTower::workshopHandler
{
	iceTower *owner;
	sf::Text slow;
public:
	workshopHandler(iceTower *ownr) :owner(ownr) { upgradeAccesed = true; attackTower::workshopHandler::owner = ownr; };
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void place() override;
	void set() override;
};

class iceTower::shopTemplate :public attackTower::shopTemplate
{
	iceTower *owner;
	sf::Text slow;
public:
	shopTemplate(iceTower *ownr);
	void setPosition(sf::Vector2f position) override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};