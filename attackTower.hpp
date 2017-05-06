#pragma once
#include "tower.hpp"

class monster;
class attackTower :public tower
{
	friend class bullet;

protected:
	int power;
	float range;
	float speed;
	float powerBuffFactor;
	float rangeBuffFactor;


	float bulletSpeed;

	std::shared_ptr<monster> targetingMonster;

	std::vector<bullet> bullets;
	sf::Vector2f startBulletPosition;
	std::string textureName;
	std::string bulletTextureName;


	sf::CircleShape attackCircle;
	bool canShowCircle;
	void makeVisualCircle();
	void makeInvisibleCircle();
	bool isMouseOnCircle(const sf::Vector2f mousePos);

	virtual bool haveTarget();
	virtual void clearTarget();
	void build() override;
	sf::Sound sound;

public:
	attackTower();
	~attackTower();

	int getPower();
	float getRange();
	float getSpeed();
	float getBulletSpeed();
	float getPowerBuffFactor();
	float getRangeBuffFactor();

	void addBuff(buff buffer) override;
	void removeBuff(buff unbuffer) override;

	virtual void searchTarget();
	virtual void attack();
	virtual bool canAttack();
	virtual void shoot();
	virtual void handleBullets() = 0;
	virtual void attackMonster(std::shared_ptr<monster> monst);
	virtual void removeBullet(bullet *rBullet);
	virtual void setPosition(sf::Vector2f position) override;
	
	virtual bool mouseOnHUD(const sf::Vector2f mousePos) override;
	virtual bool isTargetInRange(std::shared_ptr<monster> monstero);
	virtual bool isTargetOutofRange();
	bool isPointInCircle(const sf::Vector2f point);
	void activateHUD() override;
	void unactiveHUD() override;
	void unactivate();

	sf::Vector2f getStartBulletPosition();

	void update();
	void sell() override;
	virtual void upgrade();

	void expand();
	std::shared_ptr<monster> getTarget();
	virtual  void draw(sf::RenderTarget & target, sf::RenderStates states)const;
	tower::workshopHandler *getWorkshopTemplate() override;
	virtual tower::shopTemplate *getShopTemplate() override;

	class workshopHandler;
	class shopTemplate;

};

class attackTower::workshopHandler : public tower::workshopHandler
{
protected:	
	attackTower *owner;

	sf::Text power;
	sf::Text powerBuff;
	sf::Text range;
	sf::Text rangeBuff;

	sf::Text sellText;
	sf::Text upgradeCost;
	upgradeImage upgrader;
	virtual void place();
	void configureUpgrader();
	bool upgradeAccesed;
	bool goldUpgradeAccesed();
	void handleUpgrader();
	void handleSeller();

public:
	workshopHandler(attackTower *o) : owner(o) { upgradeAccesed = true; }
	workshopHandler() {};
	attackTower *getOwner();
	void join(class workshop *ws) override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void update() override;
	virtual void set() override;
};

class attackTower::shopTemplate :public tower::shopTemplate
{
protected:
	attackTower *owner;

	sf::Text power;
	sf::Text range;

public:
	shopTemplate(attackTower *ownr);
	virtual void setPosition(sf::Vector2f position) override;
	virtual sf::Vector2f getSize() override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};