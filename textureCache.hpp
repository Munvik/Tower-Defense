#pragma once


class textureCache
{
	std::map<std::string, sf::Texture> towerTextures;
	std::map<std::string, sf::Texture> towerBullets;
	std::map<std::string, sf::Texture> animations;
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Texture> monsterEffects;
	sf::Texture padlock;

	void loadTowerTextures();
	void loadTowerBullets();
	void loadAnimations();
	void loadPadlock();
	void loadTextures();
	void loadMonsterEffects();

public:
	textureCache();
	~textureCache();
	
	sf::Texture *getPadlock();
	sf::Texture *getTowerTexture(std::string textureName);
	sf::Texture *getTowerBullet(std::string bulletName);
	sf::Texture *getAnimation(std::string animationName);
	sf::Texture *getTexture(std::string textureName);
	sf::Texture *getMonsterEffectTexture(std::string effectName);
};

