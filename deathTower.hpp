#pragma once
#include "attackTower.hpp"

class deathTower :public attackTower
{
	void loadTexture();
	void setAttributes();
public:
	deathTower();
	~deathTower();
	void searchTarget() override;
	void handleBullets() override;
	std::shared_ptr<tower> getClassObject() override;
};