#pragma once
#include "attackTower.hpp"

class arcaneTower :public attackTower // tu tak samo //ale zobacz
{
	void setAttributes();
	void loadTexture();

public:
	arcaneTower();
	~arcaneTower();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void handleBullets() override;

	std::shared_ptr<tower> getClassObject() override;
};