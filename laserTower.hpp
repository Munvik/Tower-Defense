#pragma once
#include "attackTower.hpp"


class laserTower :public attackTower
{
	enum dir {up, right, down, left};

	void loadTexture();
	void setAttributes();
	std::map<dir, float> angles;
	dir currentDir;
	sf::Vector2f getLaserBeginingPos();
	sf::Sprite dirArrows[4];
	sf::RectangleShape laserField;
	bool dirChosen;
	bool canShowLaserField;
	void handleGun();
	void createField(dir d);
	void searchTarget() override;
	bool isTargetOutofRange() override;
	bool haveTarget() override;
	void clearTarget() override;
	bool mouseOnHUD(const sf::Vector2f mousePos) override;
	void handleLaser();
	bool isTargetInRange(std::shared_ptr<monster> monstero) override;
	std::shared_ptr<sf::Sprite> laser;
	sf::Texture *laserT;
	std::string laserTextureName;
	bool canAttk;

	const sf::Time laserFlashDuration = sf::seconds(0.2f);
	sf::Time accumulator;

public:
	laserTower();
	~laserTower();
	void handleBullets() override;
	void shoot() override;
	void setPosition(sf::Vector2f position) override;
	void update() override;
	void upgrade() override;
	void draw(sf::RenderTarget & target, sf::RenderStates states)const override;
	std::shared_ptr<tower> getClassObject() override;
};
