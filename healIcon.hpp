#pragma once


class healIcon :public sf::Drawable
{
	sf::Sprite icone;
	sf::Texture texture;
	bool lighting;

	sf::Sprite syringes[3];
	sf::Texture syringeTexture;
	int heals;

public:
	healIcon();
	bool clicked();
	bool mouseOn();
	bool isLighting();
	void light();
	void turnOffLight();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	sf::FloatRect getGlobalBounds();
	void setPosition(sf::Vector2f position);
	void removeSyringe();
};