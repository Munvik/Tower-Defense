#include "pch.hpp"
#include "gameoverScreen.hpp"
#include "mainMenu.hpp"

gameoverScreen::gameoverScreen()
{
	if (!backgroundT.loadFromFile("Textury/GOBackground.png"))
	{
		MessageBox(0, "Unable to open gameOverBackground.png, please call to BartekS0ft", 0, 0);
		return;
	}
	background.setTexture(backgroundT);

	if (!soundBuffer.loadFromFile("Music/loseGameSound.wav"))
	{
		MessageBox(0, "Unable to open loseGame.wav, please call to BartekS0ft", 0, 0);
		return;
	}
	sound.setBuffer(soundBuffer);
	sound.setVolume(70);
	sound.play();

	backButton.setFont(*game::getInstance()->getFont());
	backButton.setCharacterSize(30);
	backButton.setString("Back");
	backButton.setColor(sf::Color::Red);
	backButton.setPosition(getMidlePosition(sf::Vector2f(WIDTH / 2, HEIGHT * 4 / 5), backButton.getGlobalBounds()));
}

gameoverScreen::~gameoverScreen()
{
}

void gameoverScreen::update()
{
	particleSystem.update();

	sf::Vector2f mousePos = getMousePos();

	if (backButton.getGlobalBounds().contains(mousePos))
	{
		if (!backButton.isIncreased())
		{
			backButton.increase();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			game::getInstance()->setController(std::make_unique<mainMenu>());
			return;
		}
	}
	else if(!backButton.getGlobalBounds().contains(mousePos))
	{
		if (backButton.isIncreased())
		{
			backButton.decrease();
		}
	}
}

void gameoverScreen::draw(sf::RenderWindow & window)
{
	window.draw(background);
	window.draw(backButton);
	window.draw(particleSystem);
}
