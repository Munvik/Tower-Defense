#pragma once


class hpBar :public sf::Drawable
{
	sf::RectangleShape border;
	sf::RectangleShape bar;
	int fullHP;
	int currentHP;
	float width;
	float thicknessSize;

public:
	hpBar();
	~hpBar();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void setPosition(sf::Vector2f position);
	void move(sf::Vector2f movement);
	void setFullHp(int hp);
	void shrinkBar(int dmg);
	void increaseBar(int hp);
	void setWidth(const float barWidth);
	bool empty();
	int *getHP();
	sf::Vector2f getSize();
};