#pragma once

#include "towerManagement.hpp"
class map :public sf::Drawable, public sf::Transformable
{
	friend class mainGame;
	friend class towerManagament;

	sf::Texture texture;
	sf::Sprite background;


public:
	map();
	~map();
	std::vector <std::shared_ptr<tower>> towers;
	void loadMap(const std::string fileName);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void update();
	bool canTowerBuild(std::shared_ptr<tower> &activeTower);

	std::vector <sf::FloatRect> unBuildable;
	void buildTower(std::shared_ptr<tower> &activeTower);
	void sellTower(tower* sellingTower);

	sf::FloatRect getBackgroundBounds();
};
