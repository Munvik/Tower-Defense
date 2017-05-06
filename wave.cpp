#include "pch.hpp"
#include "wave.hpp"


wave::wave(std::string fileName, int monstersA, int hp, float speed, float period, int gold, int monsterDmg)
{
	if (!texture.loadFromFile("Textury/Monsters/" + fileName))
	{
		MessageBox(0, "Unable to load monster Texture", 0, 0);
		print("Nie ma ", fileName);
		return;
	}

	timePeriod = sf::milliseconds(sf::Int32(period));
	monsterDamage = monsterDmg;
	monstersAmount = monstersA;
	monsterSpeed = speed;
	monsterHP = hp;
	monsterGold = gold;

	monsterTemplate = std::make_shared<monster>(this, &texture, hp, monsterSpeed, gold);

	released = false;
	monstersDied = 0;
	monstersDone = 0;

}

wave::~wave()
{

}

void wave::setStartPosition(sf::Vector2f * startPos)
{
}

void wave::drawWave(sf::RenderWindow & window)
{

	for (size_t i = 0; i < monsters.size(); ++i)
	{
		window.draw(*monsters[i]);
	}
}

void wave::update()
{
	if(!released)
	releaseMonsters();

	for (size_t i = 0; i < monsters.size(); ++i)
	{
		monsters[i]->update(); // ew. (*this)[i] => tylko znowu¿ nie powinieneœ dziedziczyæ itd...
	}


}

bool wave::died()
{
	return (monstersDied == monstersAmount);
}

size_t wave::size()
{
	return monsters.size();
}

void wave::removeMonster(monster  *m)
{
	auto it = std::find_if(monsters.begin(), monsters.end(),
		[&](const std::shared_ptr<monster> & sptr) { return sptr.get() == m; });

	if (it != monsters.end())
	{
		monsters.erase(it);
		monstersDied++;
	}

}

void wave::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (size_t i = 0; i < monsters.size(); ++i)
	{
		target.draw(*monsters[i]);
	}
}

std::shared_ptr<monster>& wave::operator[](int index) 
{
	return monsters[index];
}

void wave::releaseMonsters()
{
	timer += game::getInstance()->getTimer();

	if (timer >= timePeriod)
	{
		monsters.push_back(std::make_shared<monster>(this, &texture, monsterHP, monsterSpeed, monsterGold));
		timer = sf::Time::Zero;
		monstersDone++;
	}

	if (monstersDone == monstersAmount)
	{
		released = true;
	}
}