#pragma once


class fpsCounter :public sf::Drawable
{
	int fps;
	sf::Time timer;
	const sf::Time second = sf::seconds(1.f);
	sf::Text fpsText;
	sf::Font font;

public:
	fpsCounter();
	~fpsCounter();

	void draw(sf::RenderTarget & target, sf::RenderStates states) const;   
	void countTime(sf::Time &gameTimer);

	fpsCounter & operator++();
};