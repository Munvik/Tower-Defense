#pragma once

class wallet :public sf::Drawable
{
	int gold;
	sf::Text goldText;
	sf::Sprite coin;
	sf::Texture coinTexture;

public:
	wallet();
	~wallet();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	int getGold();
	bool isAfford(int amount);
	void pay(int amount);
	void setPosition(const sf::Vector2f position);
	void deposit(int amount);

	sf::Vector2f getSize();
};