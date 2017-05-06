#pragma once
#include "attackTower.hpp"

class poisonTower :public attackTower
{
	void loadTexture();
	void setAttributes();
public:
	poisonTower();
	~poisonTower();

	void handleBullets() override;
	std::shared_ptr<tower> getClassObject() override;
	void attackMonster(std::shared_ptr<monster> monst) override;
	void searchTarget() override;
};