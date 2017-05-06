#pragma once
#include <queue>
#include "game.hpp"
#include "hpBar.hpp"
#include "monsterEffect.hpp"
#include "effectHandler.hpp"

class monster :public sf::Drawable
{
	friend class wave;
	wave * owner;

	sf::Sprite sprite;
	int goldWorth;
	hpBar HPbar;
	float speed;
	float currentSpeed;
	int hp;
	float steps;
	unsigned long int waySteps;
	const float maxSteps = 1800.f;
	sf::Vector2f velocity;
	std::queue<sf::Vector2f> waypoints;
	sf::Vector2f *currentWaypoint;
	sf::Vector2u spriteSize;
	float currentSlow;
	float currentShock;

	void setVelocity();
	bool isWaypointPassed(sf::Vector2f movement);
	void findNewWaypoint();
	void move(sf::Vector2f movement);

	enum direction {down =0, left = 1, right = 2, top = 3};
	direction currDirection;
	bool isActive;
	void activate();
	void die();
	sf::Time time;
	effectHandler effects;

public:
	monster();
	monster(wave *const _wave, sf::Texture* texture, int hp, float speed, int gold);
	~monster();
	void setTexture(sf::Texture* texture);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void update();
	sf::Vector2f getCenter();
	bool wentInBase();
	void getDmg(int dmg);
	int h;
	bool dead;
	bool isActivated();
	bool isUnavailable();
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getSize();
	sf::Vector2f getPosition();
	sf::Sprite *getSprite();
	effectHandler &getEffectHandler();
	bool operator == (const monster & mon);
	float getSlow();
	void slow(float factor);
	void unslow(float factor);
	float getShock();
	void shock(float factor);
	void unshock(float factor);
	unsigned long int getWaySteps();
};