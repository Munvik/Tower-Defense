#include "pch.hpp"
#include "effectHandler.hpp"


effectHandler::effectHandler()
{
	poisons.reserve(30);
	slows.reserve(30);
}

effectHandler::~effectHandler()
{
}

void effectHandler::addEffect(std::shared_ptr<monsterEffect> eff)
{
	switch (eff->getType())
	{
	case monsterEffect::effectType::poison:
		{
			std::vector<std::shared_ptr<monsterEffect>>::iterator it = poisonGiverExists(eff->getGiver());
			if (it != poisons.end())
				poisons.erase(it);

			poisons.push_back(eff);
		}
		break;
		case monsterEffect::effectType::slow: slows.push_back(eff); break;
		case monsterEffect::effectType::shock:
		{
			std::vector<std::shared_ptr<monsterEffect>>::iterator it = shockGiverExists(eff->getGiver());
			if (it != shocks.end())
				shocks.erase(it);

			shocks.push_back(eff);
		}
		break;
	}
}

void effectHandler::update()
{
	sf::Time timer = game::getInstance()->getTimer();

	for (size_t i = 0; i < poisons.size(); ++i)
	{
		poisons[i]->update(timer);

		if (poisons[i]->end())
			poisons.erase(poisons.begin() + i);	
	}

	for (size_t i = 0; i < slows.size(); ++i)
	{
		slows[i]->update(timer);

		if (slows[i]->end())
		{
			slows.erase(slows.begin() + i);
		}
	}

	for (size_t i = 0; i < shocks.size(); ++i)
	{
		shocks[i]->update(timer);

		if (shocks[i]->end())
		{
			shocks.erase(shocks.begin() + i);
		}
	}
}

void effectHandler::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (size_t i = 0; i < poisons.size(); ++i)
	{
		target.draw(*poisons[i]);
	}
}

std::vector<std::shared_ptr<monsterEffect>>::iterator effectHandler::poisonGiverExists(attackTower * g)
{
	std::vector<std::shared_ptr<monsterEffect>>::iterator i = poisons.begin();

	while (i != poisons.end())
	{
		if (i->get()->getGiver() == g)
		{
			break;
		}
		i++;
	}

	return i;
}

std::vector<std::shared_ptr<monsterEffect>>::iterator effectHandler::shockGiverExists(attackTower * g)
{
	std::vector<std::shared_ptr<monsterEffect>>::iterator i = shocks.begin();

	while (i != shocks.end())
	{
		if (i->get()->getGiver() == g)
		{
			break;
		}
		i++;
	}

	return i;
}

