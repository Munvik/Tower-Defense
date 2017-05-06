#include "pch.hpp"
#include "gameCompletedScreen.hpp"
#include "mainMenu.hpp"
#include "game.hpp"

gameCompletedScreen::gameCompletedScreen(const sf::Image wndImg)
{
	gameEndSpriteT.loadFromImage(wndImg);
	gameEndSprite.setTexture(gameEndSpriteT);

	if (!backgroundT.loadFromFile("Textury/ENDbackground.png"))
	{
		MessageBox(0, "Unable to open ENDBackground.png, please call to BartekS0ft", 0, 0);
		return;
	}
	background.setTexture(backgroundT);

	rects[0].setSize(sf::Vector2f(WIDTH, 0));
	rects[1].setSize(sf::Vector2f(WIDTH, 0));
	rects[0].setPosition(0, 0);
	rects[1].setPosition(0, HEIGHT);
	rects[0].setFillColor(sf::Color::Black);
	rects[1].setFillColor(sf::Color::Black);

	currentState = screenLocking;
}

gameCompletedScreen::~gameCompletedScreen()
{
}

void gameCompletedScreen::update()
{

	switch (currentState)
	{
	case screenLocking: 
		{
			sf::Time timer = game::getInstance()->getTimer();

			float nextRectMove = rectSpeed * timer.asSeconds();
			float heightRect1 = rects[0].getSize().y;
			heightRect1 += nextRectMove;
			rects[0].setSize(sf::Vector2f(WIDTH, heightRect1));

			float heightRect2 = rects[1].getSize().y;
			heightRect2 += nextRectMove;
			rects[1].setSize(sf::Vector2f(WIDTH, heightRect2));
			rects[1].move(0, -nextRectMove);

			if (rects[0].getGlobalBounds().intersects(rects[1].getGlobalBounds()))
			{
				currentState = screenOpening;
			}
		} break;

	case screenOpening: 
		{
			sf::Time timer = game::getInstance()->getTimer();

			float nextRectMove = rectSpeed * timer.asSeconds();
			float heightRect1 = rects[0].getSize().y;
			heightRect1 -= nextRectMove;
			rects[0].setSize(sf::Vector2f(WIDTH, heightRect1));

			float heightRect2 = rects[1].getSize().y;
			heightRect2 -= nextRectMove;
			rects[1].setSize(sf::Vector2f(WIDTH, heightRect2));
			rects[1].move(0, nextRectMove);

			if ((heightRect1 <= 0.f) || (heightRect2 <= 0.f))
			{
				currentState = screenOpened;
			}
		} break;
	case screenOpened:
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
			game::getInstance()->setController(std::make_unique<mainMenu>());
			}
		} break;
	}
}

void gameCompletedScreen::draw(sf::RenderWindow & window)
{
	switch(currentState)
	{
	case screenLocking:
		{
			window.draw(gameEndSprite);
			window.draw(rects[0]);
			window.draw(rects[1]);
		} break;

	case screenOpening:
		{
			window.draw(background);
			window.draw(rects[0]);
			window.draw(rects[1]);
		} break;

	case screenOpened:
		{
			window.draw(background);
		}
	}
}
