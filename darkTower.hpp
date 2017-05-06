#pragma once
#include "arcaneTower.hpp"

class darkTower :public arcaneTower
{
	void setAttributes();
	void loadTexture();
public:
	darkTower();
	std::shared_ptr<tower> getClassObject() override;
};