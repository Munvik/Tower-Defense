#pragma once
#include <map>
#include "workshop.hpp"
//#include "map.hpp"

class map;

class towerManagament :public sf::Drawable
{
	friend class arcaneTower;

	std::vector <std::shared_ptr<tower>> towerShopTemplates;

	sf::RectangleShape frame;
	sf::RectangleShape background;
	sf::Texture recTexture;

	void produceTowers();
	void loadTextures();
	std::shared_ptr<tower> currentTower;

	std::shared_ptr<tower> activeTower;

	map* gameMap;

	workshop * Workshop;

	void handleShop();
	void handleTowers();
	void workTowers();
	bool isTowerOnMouse();
	bool greenFrame;
	void setFrame();
	void updateFrame();
	

public:
	towerManagament(workshop * Workshop);
	~towerManagament();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	void update();
};