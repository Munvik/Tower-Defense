#include "pch.hpp"
#include "base.hpp"
#include "mainGame.hpp"

base::base()
{
	loadTexture();
	setAttributes();
}

base::~base()
{
}

void base::setAttributes()
{
}

void base::loadTexture()
{
	if (!texture.loadFromFile("Textury/Towers/base.png"))
	{
		MessageBox(0, "Unable to load base.png", 0, 0);
		return;
	}

	sprite.setTexture(texture);
}

void base::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);
}

void base::update()
{
}

void base::upgrade()
{

}



void base::unactiveHUD()
{
}

void base::activateHUD()
{
}

/////////////////////////////////////////

auto base::getWorkshopTemplate() -> tower::workshopHandler *
{
	if (!workshopTemplate)
	{
		workshopTemplate = std::make_unique<workshopHandler>(this);
	}
	return workshopTemplate.get();
}

tower::shopTemplate * base::getShopTemplate()
{
	return nullptr;
}

std::shared_ptr<tower> base::getClassObject()
{
	std::shared_ptr<tower> obj = std::make_shared<base>();

	return obj;
}

bool base::mouseOnHUD(const sf::Vector2f mousePos)
{
	return false;
}

void base::addBuff(buff buffer)
{
}

base::workshopHandler::workshopHandler(base * ownr)
{
	owner = ownr;
}

void base::workshopHandler::join(workshop *ws)
{
	workshopOwner = ws;

	owner->activateHUD();
}


void base::workshopHandler::update()
{
	//
}

void base::workshopHandler::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

}

void base::workshopHandler::set()
{
	//
}
