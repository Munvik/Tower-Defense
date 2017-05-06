#include "pch.hpp"
#include "hpBar.hpp"

hpBar::hpBar()
{
	border.setSize(sf::Vector2f(50.f, 8.f));
	border.setFillColor(sf::Color(130, 110, 90));
	thicknessSize = 1.f;
	border.setOutlineThickness(thicknessSize);
	border.setOutlineColor(sf::Color(111,222,111));

	sf::Vector2f barSize;
	barSize.x = border.getSize().x - 2 * thicknessSize;
	barSize.y = border.getSize().y - 2 * thicknessSize;
	bar.setSize(barSize);
	bar.setFillColor(sf::Color::Red);
	sf::Vector2f barPos;
	barPos.x = border.getPosition().x + thicknessSize;
	barPos.y = border.getPosition().y + thicknessSize;
	bar.setPosition(barPos);


}

hpBar::~hpBar()
{
}

void hpBar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(border);
	target.draw(bar);
}

void hpBar::setPosition(sf::Vector2f position)
{
	border.setPosition(position);
	bar.setPosition(position + sf::Vector2f(1.f, 1.f));
}

void hpBar::move(sf::Vector2f movement)
{
	border.move(movement);
	bar.move(movement);
}

void hpBar::setFullHp(int hp)
{
	fullHP = hp;
	currentHP = hp;
}

void hpBar::shrinkBar(int dmg)
{
	currentHP -= dmg;

	sf::Vector2f newBarSize;
	newBarSize.x = width * (float(currentHP) / float(fullHP));
	newBarSize.y = border.getSize().y - 2 * thicknessSize;

	bar.setSize(newBarSize);
}

void hpBar::increaseBar(int hp)
{
	currentHP += hp;

	if (currentHP > fullHP)
	{
		currentHP = fullHP;
	}

	sf::Vector2f newBarSize;
	newBarSize.x = width * (float(currentHP) / (fullHP));
	newBarSize.y = border.getSize().y - 2 * thicknessSize;

	bar.setSize(newBarSize);
}

void hpBar::setWidth(const float barWidth)
{
	border.setSize(sf::Vector2f(barWidth, 8.f));
	width = border.getSize().x - 2 *thicknessSize;

	sf::Vector2f barSize;
	barSize.x = width;
	barSize.y = border.getSize().y - 2 * thicknessSize;

	bar.setSize(barSize);
}

bool hpBar::empty()
{
	if (currentHP <= 0)
		return true;

	return false;
}

int * hpBar::getHP()
{
	return &currentHP;
}


sf::Vector2f hpBar::getSize()
{
	return border.getSize();
}
