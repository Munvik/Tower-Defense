#pragma once
#include "attackTower.hpp"
#include "straightBullet.hpp"

class magmaTower :public attackTower
{
	void loadTexture();
	void setAttributes();

	sf::Vector2f magmaDestination;
	sf::Texture *lavaTexture;
	sf::IntRect startLavaRect;
	sf::Time _timer;
	sf::Time magmaTimer;

	

	bool magmaWorks;
	std::shared_ptr<straightBullet> magmaBullet;

	std::shared_ptr<sf::Sprite> magma;
	sf::Texture *magmaTexture;
	void updateMagma();

	const float magmaIncreaseTime = 0.2f;
	const float magmaExisting = 2.5f;

	void searchTarget() override;

public:
	magmaTower();
	~magmaTower();

	void removeBullet(bullet * rBullet);
	void shoot() override;
	void handleBullets() override;
	void update() override;

	std::shared_ptr<tower> getClassObject() override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

