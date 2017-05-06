#pragma once
class attackTower;

class monster;

class monsterEffect :public sf::Drawable
{

protected:
	sf::Time timer;
	sf::Time periodTimer;
	sf::Time duration;
	std::shared_ptr<monster> owner;
	sf::Sprite effect;
	sf::Texture *texture;
	sf::Vector2f monsterSize;
	attackTower *giver;

public:
	enum effectType { poison, slow, shock};

	monsterEffect();
	virtual ~monsterEffect();
	virtual void update(sf::Time _timer) = 0;
	virtual effectType getType() = 0;
	bool end();
	attackTower *getGiver();
};

////////////////

class poisonEffect :public monsterEffect
{
	int strength;
	sf::Time period;
public:
	poisonEffect(std::shared_ptr<monster> monst, int poisonStrenght, attackTower *pGiver);
	~poisonEffect();

	void update(sf::Time _timer) override;
	monsterEffect::effectType getType() override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

///////////////

class slowEffect :public monsterEffect
{
	float factor;
public:
	slowEffect(std::shared_ptr<monster> monst, float _slow, float dur);
	~slowEffect();
	void update(sf::Time _timer) override;
	monsterEffect::effectType getType() override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	const static float maxSlow;
};

class shockEffect :public monsterEffect
{
	float factor;
public:
	shockEffect(std::shared_ptr<monster> monst, float _factor, float dur, attackTower *sGiver);
	~shockEffect();
	void update(sf::Time _timer) override;
	monsterEffect::effectType getType() override;
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	const static float maxShock;
};