#pragma once

enum Type {SMALL, MEDIUM, LARGE};

class button :public sf::Text
{
	bool isBoosted;

public:
	button(Type type = MEDIUM, sf::Vector2f position = sf::Vector2f(0.f,0.f), std::string caption = "Captio");
	~button() {};
	Type size;

	void increase();
	void decrease();
	bool isMouseOn(sf::Vector2f mousePosition);

	bool isIncreased();
	bool isClickOn(sf::Vector2f mousePosition);
};