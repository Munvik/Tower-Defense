#include "pch.hpp"
#include "healIcon.hpp"

healIcon::healIcon()
{
	if (!texture.loadFromFile("Textury/healIcon.png"))
	{
		MessageBox(0, "Unable to open healIcon, please call to BartekS0ft", 0, 0);
		return;
	}
	icone.setTexture(texture);

	if (!syringeTexture.loadFromFile("Textury/syringe.png"))
	{
		MessageBox(0, "Unable to open syringePng, please call to BartekS0ft", 0, 0);
		return;
	}
	for (int i = 0; i < 3; ++i)
	{
		syringes[i].setTexture(syringeTexture);
	}

	lighting = false;
	heals = 3;
}

bool healIcon::clicked()
{
	sf::FloatRect rect = icone.getGlobalBounds();

	if ((rect.contains(getMousePos())) && (buttonSwitcher::canClick())&& (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		return true;
	}

	return false;
}

bool healIcon::mouseOn()
{
	return icone.getGlobalBounds().contains(getMousePos());
}

bool healIcon::isLighting()
{
	return lighting;
}

void healIcon::light()
{
	lighting = true;

	icone.setColor(sf::Color(255, 255, 255, 255));
}

void healIcon::turnOffLight()
{
	lighting = false;

	icone.setColor(sf::Color(210, 210, 215, 255));
}

void healIcon::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(icone);

	for (int i = 0; i < heals; ++i)
	{
		target.draw(syringes[i]);
	}
}

sf::FloatRect healIcon::getGlobalBounds()
{
	sf::FloatRect rect = icone.getGlobalBounds();
	rect.height = icone.getGlobalBounds().height + syringes[0].getGlobalBounds().height;

	return rect;
}

void healIcon::setPosition(sf::Vector2f position)
{
	icone.setPosition(position);

	float posX;
	float posY = icone.getGlobalBounds().top + icone.getGlobalBounds().height;

	for (int i = 0; i < 3; ++i)
	{
		posX = icone.getGlobalBounds().left + icone.getGlobalBounds().width / 3 * i;

		syringes[i].setPosition(posX,posY);
	}
}

void healIcon::removeSyringe()
{
	heals--;
}
