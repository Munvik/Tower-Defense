#pragma once


class gameLoader :public sf::Drawable
{

	sf::RectangleShape frame, loader;
	const float difference = 2.f;
	float loaderWidth;

public:
	gameLoader();
	~gameLoader();
	void setPosition(sf::Vector2f position);
	sf::Vector2f getSize();
	sf::FloatRect getGlobalBounds();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void load(float procent);
};