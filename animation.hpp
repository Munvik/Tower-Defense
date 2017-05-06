#pragma once


class animation :public sf::Sprite
{
	sf::Texture *texture;
	sf::Time frameTime;
	int frames;
	int frameCounter;

	sf::Time timer;
	unsigned int spriteHeight;
	unsigned int spriteWidth;

	void nextFrame();

public:
	animation(std::string animationName, int _frames, float frameTim);
	~animation();
	void update();
	bool end();
	void repeat();
	sf::Vector2f getCenter();
	sf::Vector2f getSize();
};