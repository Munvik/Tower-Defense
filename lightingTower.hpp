#pragma once
#include "attackTower.hpp"

class lightingTower :public attackTower
{
	void loadTexture();
	void setAttributes();

	std::shared_ptr<sf::Sprite> thunder;
	sf::Texture *thunderTexture;

	sf::Time accumulator;

	const sf::Time thunderFlashTime = sf::seconds(0.3f);
	float slow;
	const float slowDuration = 200.f;

public:
	lightingTower();
	~lightingTower();

	std::shared_ptr<tower> getClassObject() override;
	void attack() override;
	void handleBullets() override;
	void updateThunder();
	void attackMonster(std::shared_ptr<monster> monst) override;

	void draw(sf::RenderTarget & target, sf::RenderStates states)const;
};