#pragma once
#include "attackTower.hpp"

class archerTower :public attackTower
{
	void setAttributes();
	void loadTexture();

public:
	archerTower();
	~archerTower();

	void handleBullets() override;
	std::shared_ptr<tower> getClassObject() override;
};