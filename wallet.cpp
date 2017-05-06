#include "pch.hpp"
#include "wallet.hpp"
#include "mainGame.hpp"

wallet::wallet()
{
	if (!coinTexture.loadFromFile("Textury/coin.png"))
	{
		MessageBox(0, "Unable to open coinTexture, please call to BartekS0ft", 0, 0);
		return;
	}
	coin.setTexture(coinTexture);

	gold = 100;

	goldText.setFont(*game::getInstance()->getFont());
	goldText.setString(intToString(gold));
	goldText.setCharacterSize(30);
	goldText.setColor(sf::Color(30, 40, 30));
	sf::Vector2f textPos;
	textPos.x = coin.getPosition().x + coin.getGlobalBounds().width * 3 / 2;
	textPos.y = coin.getPosition().y + coin.getGlobalBounds().height / 2 - goldText.getGlobalBounds().height / 2;
	goldText.setPosition(textPos);

}

wallet::~wallet()
{
}

void wallet::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(coin);
	target.draw(goldText);
}

int wallet::getGold()
{
	return gold;
}

bool wallet::isAfford(int amount)
{
	if (this->gold >= amount)
		return true;

	return false;
}

void wallet::pay(int amount)
{
	gold -= amount;

	goldText.setString(intToString(gold));
}

void wallet::setPosition(const sf::Vector2f position)
{
	coin.setPosition(position);
	
	sf::Vector2f textPos;
	textPos.x = position.x + coin.getGlobalBounds().width * 3 / 2;
	textPos.y = position.y + coin.getGlobalBounds().height / 2 - goldText.getGlobalBounds().height*2/3;

	goldText.setPosition(textPos);
}

void wallet::deposit(int amount)
{
	gold += amount;
	goldText.setString(intToString(gold));
}

sf::Vector2f wallet::getSize()
{
	sf::Vector2f size;
	size.x = (goldText.getPosition().x + goldText.getGlobalBounds().width) - coin.getPosition().x;

	if (goldText.getGlobalBounds().height <= coin.getGlobalBounds().height)
		size.y = coin.getGlobalBounds().height;
	else size.y = goldText.getGlobalBounds().height;

	return size;
}
