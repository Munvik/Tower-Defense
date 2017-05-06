#pragma once
#include "monster.hpp"
#include "bullet.hpp"
#include "workshop.hpp"

class buff;

class tower :public sf::Drawable
{	
public:
	class workshopHandler;
	class shopTemplate;

protected:
	std::unique_ptr<workshopHandler> workshopTemplate;
	std::unique_ptr<shopTemplate> storeTemplate;
public:

	tower();
	virtual ~tower();

	short int cost;
	sf::Time timer;
	sf::Time *globalTimer;

	virtual void setPosition(sf::Vector2f position);
	sf::Vector2f getSize();
	sf::Vector2f getCenter();
	virtual sf::Vector2f getPosition();
	virtual bool mouseOnHUD(const sf::Vector2f mousePos) = 0;
	sf::FloatRect getGlobalBounds();

	bool canBuy();
	bool isAfford();
	int getLevelAcces();

	bool isClicked(const sf::Vector2f mousePos);
	
	bool isActive();

	static const int maxUpgradeLevel = 2;
	int getValue();
	int getUpgradeCost();
	int isAffordForUpgrade();
	int getUpgradeLevel();
	bool isExtended();
	virtual void sell();
	bool upgradeGoldAcces;
	virtual void addBuff(buff buffer) = 0;
	virtual void removeBuff(buff unbuffer);

	virtual void unactiveHUD() = 0;
	virtual void activateHUD() = 0;
	virtual void update() = 0;
	virtual void build();
	virtual void buf(attackTower *buffingTower);

	bool isBuffed();

	virtual workshopHandler *getWorkshopTemplate() = 0;
	virtual shopTemplate *getShopTemplate() = 0;
	virtual std::shared_ptr<tower> getClassObject()=0;
	
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	std::string description;

	int levelAcces;
	int upgradeLevel;
	int value;
	bool HUDactive;
	bool builded;
	void expand();
	bool buffed;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};


class tower::workshopHandler :public sf::Drawable
{
private:
	bool XClicked();

protected:
	sf::Font *font;
	sf::Sprite X;
	sf::Texture XTexture;
	sf::Text towerName;

	workshop *workshopOwner;

	bool placed;
	bool Placed();

public:
	workshopHandler();
	virtual void join(workshop *ws);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void update();
	virtual void set() = 0;
	workshop *getWorkshop();
};

class tower::shopTemplate :public sf::Drawable
{
private:
	tower *owner;
	void setDescription();
protected:
	sf::Text cost;
	sf::Sprite towerSprite;
	sf::Font *font;
	const unsigned int charSize = 12;

	sf::Sprite padlock;

	bool unlocked;
	bool goldAcces;
	const sf::Time holdingTime = sf::seconds(2.f);
	sf::Sprite textHaze;
	sf::Texture textHazeTexture;
	std::vector<sf::Text> description;
	sf::Time hazeTimer;
	bool canTextHazeDraw;

public:
	shopTemplate(tower *ownr);
	
	sf::Vector2f getPosition();
	bool isUnlocked();
	bool clicked();
	bool canUnlock();
	void unlock();

	void makeSpriteRed();
	void makeSpriteNormal();

	bool getGoldAcces() const;
	void setGoldAcces(bool switcher);
	virtual void setPosition(sf::Vector2f position) = 0;
	void setHazePosition();
	virtual sf::Vector2f getSize() = 0;
	bool isMouseOn(sf::Vector2f mousePos);
	void addHazeTime();
	void resetTimer();
	bool isHoldingTimeUp();
	void setHazeSwitcher(bool switcher);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};