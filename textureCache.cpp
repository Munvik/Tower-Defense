#include "pch.hpp"
#include "textureCache.hpp"

textureCache::textureCache()
{
	loadTowerTextures();

	loadTowerBullets();
	loadAnimations();
	loadTextures();
	loadPadlock();
	loadMonsterEffects();
}

textureCache::~textureCache()
{
}

void textureCache::loadTowerTextures()
{
	if (!towerTextures["arcaneTower"].loadFromFile("Textury/Towers/arcaneTower/arcaneTower.png"))
	{
		MessageBox(0, "Unable to open tower texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerTextures["archerTower"].loadFromFile("Textury/Towers/archerTower/archerTower.png"))
	{
		MessageBox(0, "Unable to open tower texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerTextures["cannonTower"].loadFromFile("Textury/Towers/cannonTower/cannonTower.png"))
	{
		MessageBox(0, "Unable to open cannonTower texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerTextures["darkTower"].loadFromFile("Textury/Towers/darkTower/darkTower.png"))
	{
		MessageBox(0, "Unable to open darkTower texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerTextures["magmaTower"].loadFromFile("Textury/Towers/magmaTower/magmaTower.png"))
	{
		MessageBox(0, "Unable to open magmakTower texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerTextures["antennaTower"].loadFromFile("Textury/Towers/antennaTower/antennaTower.png"))
	{
		MessageBox(0, "Unable to open antennaTower texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerTextures["electricTower"].loadFromFile("Textury/Towers/electricTower/electricTower.png"))
	{
		MessageBox(0, "Unable to open electricTower texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerTextures["poisonTower"].loadFromFile("Textury/Towers/poisonTower/poisonTower.png"))
	{
		MessageBox(0, "Unable to open poisonTower texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerTextures["crossbowTower"].loadFromFile("Textury/Towers/crossbowTower/crossbowTower.png"))
	{
		MessageBox(0, "Unable to open crossbowTower texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerTextures["lightingTower"].loadFromFile("Textury/Towers/lightingTower/lightingTower.png"))
	{
		MessageBox(0, "Unable to open lightingTower texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerTextures["iceTower"].loadFromFile("Textury/Towers/iceTower/iceTower.png"))
	{
		MessageBox(0, "Unable to open iceTower texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerTextures["deathTower"].loadFromFile("Textury/Towers/deathTower/deathTower.png"))
	{
		MessageBox(0, "Unable to open death Tower texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerTextures["laserTower"].loadFromFile("Textury/Towers/laserTower/laserTower.png"))
	{
		MessageBox(0, "Unable to open laser Tower texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerTextures["signalTower"].loadFromFile("Textury/Towers/signalTower/signalTower.png"))
	{
		MessageBox(0, "Unable to open signal Tower texture, please call to Bartek", 0, 0);
		return;
	}
}

void textureCache::loadTowerBullets()
{
	if (!towerBullets["arcaneTowerBullet"].loadFromFile("Textury/Towers/arcaneTower/bullet.png"))
	{
		MessageBox(0, "Unable to open tower bullet texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerBullets["archerTowerBullet"].loadFromFile("Textury/Towers/archerTower/bullet.png"))
	{
		MessageBox(0, "Unable to open tower bullet texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerBullets["cannonTowerBullet"].loadFromFile("Textury/Towers/cannonTower/bullet.png"))
	{
		MessageBox(0, "Unable to open cannontower bullet texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerBullets["darkTowerBullet"].loadFromFile("Textury/Towers/darkTower/bullet.png"))
	{
		MessageBox(0, "Unable to open darktower bullet texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerBullets["magmaTowerBullet"].loadFromFile("Textury/Towers/magmaTower/bullet.png"))
	{
		MessageBox(0, "Unable to open magmatower bullet texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerBullets["poisonTowerBullet"].loadFromFile("Textury/Towers/poisonTower/bullet.png"))
	{
		MessageBox(0, "Unable to open poisontower bullet texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerBullets["crossbowTowerBullet"].loadFromFile("Textury/Towers/crossbowTower/bullet.png"))
	{
		MessageBox(0, "Unable to open crossbowtower bullet texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerBullets["thunder"].loadFromFile("Textury/Towers/lightingTower/thunder.png"))
	{
		MessageBox(0, "Unable to open thunder texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerBullets["iceTowerBullet"].loadFromFile("Textury/Towers/iceTower/bullet.png"))
	{
		MessageBox(0, "Unable to open iceTower bullet texture, please call to Bartek", 0, 0);
		return;
	}

	if (!towerBullets["deathTowerBullet"].loadFromFile("Textury/Towers/deathTower/bullet.png"))
	{
		MessageBox(0, "Unable to open death Tower bullet texture, please call to Bartek", 0, 0);
		return;
	}
}

void textureCache::loadAnimations()
{
	if (!animations["smallExplosion"].loadFromFile("Textury/Towers/cannonTower/explosion.png"))
	{
		MessageBox(0, "Unable to open tower bullet texture, please call to Bartek", 0, 0);
		return;
	}

	if (!animations["magmaExplosion"].loadFromFile("Textury/Towers/magmaTower/explosion.png"))
	{
		MessageBox(0, "Unable to open tower bullet texture, please call to Bartek", 0, 0);
		return;
	}

	if (!animations["bundleEnergy"].loadFromFile("Textury/Towers/electricTower/energy.png"))
	{
		MessageBox(0, "Unable to open tower bullet texture, please call to Bartek", 0, 0);
		return;
	}
}

void textureCache::loadPadlock()
{
	if (!padlock.loadFromFile("Textury/padlock.png"))
	{
		MessageBox(0, "Unable to open padlock.png, please call to Bartek", 0, 0);
		return;
	}
}

void textureCache::loadTextures()
{
	if (!textures["magma"].loadFromFile("Textury/Towers/magmaTower/magma.png"))
	{
		MessageBox(0, "Unable to open lava.png, please call to BartekSoft", 0, 0);
		return;
	}

	if(!textures["crossbow"].loadFromFile("Textury/Towers/crossbowTower/crossbow.png"))
	{
		MessageBox(0, "Unable to open crossbow.png, please call to BartekSoft", 0, 0);
		return;
	}

	if (!textures["laser"].loadFromFile("Textury/Towers/laserTower/laser.png"))
	{
		MessageBox(0, "Unable to open laser.png, please call to BartekSoft", 0, 0);
		return;
	}

	if (!textures["arrowDir"].loadFromFile("Textury/Towers/laserTower/arrow.png"))
	{
		MessageBox(0, "Unable to open arrowDir.png, please call to BartekSoft", 0, 0);
		return;
	}
}

void textureCache::loadMonsterEffects()
{
	if (!monsterEffects["poison"].loadFromFile("Textury/Towers/effects/poison.png"))
	{
		MessageBox(0, "Unable to open poison.png, please call to BartekSoft", 0, 0);
		return;
	}
	print("pobieramy poisona");
}


sf::Texture * textureCache::getPadlock()
{
	return &padlock;
}

sf::Texture *textureCache::getTowerTexture(std::string textureName)
{
	return &towerTextures[textureName];
}

sf::Texture * textureCache::getTowerBullet(std::string bulletName)
{
	return &towerBullets[bulletName];
}

sf::Texture * textureCache::getAnimation(std::string bulletExploName)
{
	return &animations[bulletExploName];
}

sf::Texture * textureCache::getTexture(std::string textureName)
{
	return &textures[textureName];
}

sf::Texture * textureCache::getMonsterEffectTexture(std::string effectName)
{
	return &monsterEffects[effectName];
}
