#pragma once

#include "upgradeImage.hpp"
#include "healIcon.hpp"

class tower;

class workshop :public sf::Drawable
{
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	std::shared_ptr<tower> towerInWorkshop;

	sf::Text caption;
	void setTexts();

	bool busy() const;
	
public:
	workshop();
	~workshop();
	void update();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void join(std::shared_ptr<tower> tower);
	void leave();
	bool isMouseOn(sf::Vector2f mousePosition);
	sf::Vector2f getSize();
	sf::Vector2f getPosition();
	//bool XClicked();
};