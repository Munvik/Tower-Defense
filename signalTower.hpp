#pragma once
#include "buffTower.hpp"

class signalTower :public buffTower
{
	void loadTexture();
	void setAttributes();
public:
	signalTower();
	~signalTower();
	void buffOtherTowers() override;
	void debuffOtherTowers() override;
	void upgrade() override;
	void build() override;
	void buf(attackTower *buffingTower);
	void sell() override;
	void update() override;

	std::shared_ptr<tower> getClassObject() override;
};