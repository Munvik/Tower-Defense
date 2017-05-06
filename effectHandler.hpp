#pragma once
#include "monsterEffect.hpp"

class attackTower;

class effectHandler :public sf::Drawable
{
	std::vector<std::shared_ptr<monsterEffect>> poisons;
	std::vector<std::shared_ptr<monsterEffect>> slows;
	std::vector<std::shared_ptr<monsterEffect>> shocks;

public:
	effectHandler();
	~effectHandler();

	void addEffect(std::shared_ptr<monsterEffect> eff);
	void update();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	std::vector<std::shared_ptr<monsterEffect>>::iterator poisonGiverExists(attackTower *g);
	std::vector<std::shared_ptr<monsterEffect>>::iterator shockGiverExists(attackTower *g);
};