#include "pch.hpp"
#include "monsterEffect.hpp"
#include "mainGame.hpp"

//class attackTower;

monsterEffect::monsterEffect()
{
	timer = sf::Time::Zero;
	periodTimer = sf::Time::Zero;
}

monsterEffect::~monsterEffect()
{
}

bool monsterEffect::end()
{
	if (timer >= duration)
		return true;

	return false;
}

attackTower * monsterEffect::getGiver()
{
	return giver;
}


//attackTower * monsterEffect::getGiver()
//{
//	return giver;
//}

//////////////////////////// POISON ///////////////////////////
//////////////////////////// POISON ///////////////////////////
//////////////////////////// POISON ///////////////////////////

poisonEffect::poisonEffect(std::shared_ptr<monster> monst, int poisonStrenght, attackTower *pGiver)
	:period(sf::milliseconds(200)),
	strength(poisonStrenght)
{
	texture = mainGame::getInstance()->textures.getMonsterEffectTexture("poison");
	effect.setTexture(*texture);
	owner = monst;
	monsterSize = owner->getSize();
	duration = sf::seconds(3.f);
	giver = pGiver;

	sf::Vector2f poisonPos = getMidlePosition(owner->getCenter(), effect.getGlobalBounds());
	poisonPos.y += owner->getSize().y / 4;
	effect.setPosition(poisonPos);
}

poisonEffect::~poisonEffect()
{
}

void poisonEffect::update(sf::Time _timer)
{
	timer += _timer;
	periodTimer += _timer;

	sf::Vector2f poisonPos = getMidlePosition(owner->getCenter(), effect.getGlobalBounds());
	effect.setPosition(poisonPos);

	if (periodTimer >= period)
	{	
		owner->getDmg(strength);
		periodTimer = sf::Time::Zero;
	}
}

monsterEffect::effectType poisonEffect::getType()
{
	return poison;
}


void poisonEffect::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(effect);
}

//////////////////////////////////////////////// MONSTEREFFECT::sLOW ////////////////////////////
//////////////////////////////////////////////// MONSTEREFFECT::sLOW ////////////////////////////
//////////////////////////////////////////////// MONSTEREFFECT::sLOW ////////////////////////////
const float slowEffect::maxSlow = 0.7f;

slowEffect::slowEffect(std::shared_ptr<monster> monst, float _slow, float dur)
	:factor(_slow)
{
	owner = monst;
	duration = sf::milliseconds((sf::Int32(dur)));
	float allowedSlow = maxSlow - monst->getSlow();
	if (allowedSlow < factor)
	{
		factor = allowedSlow;
	}
	
	owner->slow(factor);
}

slowEffect::~slowEffect()
{
	owner->unslow(factor);
}

void slowEffect::update(sf::Time _timer)
{
	timer += _timer;
}

monsterEffect::effectType slowEffect::getType()
{
	return slow;
}

void slowEffect::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}


/////////////////////////////SHOCKEFFECT ////////////////////////////////
const float shockEffect::maxShock = 0.15f;

shockEffect::shockEffect(std::shared_ptr<monster> monst, float _factor, float dur, attackTower *sGiver)
{
	factor = _factor;
	duration = sf::milliseconds((sf::Int32(dur)));
	owner = monst;
	giver = sGiver;

	float allowedShock = maxShock - monst->getShock();

	if (allowedShock < factor)
	{
		factor = allowedShock;
	}

	owner->shock(factor);
}

shockEffect::~shockEffect()
{
	owner->unshock(factor);
}

void shockEffect::update(sf::Time _timer)
{
	timer += _timer;
}

monsterEffect::effectType shockEffect::getType()
{
	return shock;
}

void shockEffect::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}
