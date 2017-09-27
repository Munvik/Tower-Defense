#pragma once
#include "buffTower.hpp"
#define TOWER

class antennaTower :public buffTower
{
	void loadTexture();
	void setAttributes();

public:
	antennaTower();
	void update() override;
	void build() override;
	void buffOtherTowers() override;
	void debuffOtherTowers() override;
	void buf(attackTower *buffingTower) override;
	void sell() override;
	std::shared_ptr<tower> getClassObject() override;
};
