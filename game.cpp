#include "pch.hpp"
#include "game.hpp"
#include "mainMenu.hpp"

game *game::instance = nullptr;

game::game()
 :window(sf::VideoMode(WIDTH, HEIGHT), "Tower Defense 1.0 by Monf")
{
	if (instance == nullptr)
	{
		instance = this;
	}

	if (!music.openFromFile("Music/mainMenuTheme.wav"))
	{
		MessageBox(0, "Nie mozna otworzyc mainMenuTheme.wav, brak pliku", 0, 0);
		exit();
	}

	if (!icon.loadFromFile("Textury/icon.png"))
	{
		MessageBox(0, "Nie mozna otworzyc icon.png, brak pliku", 0, 0);
		exit();
	}
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	music.play();
	music.setLoop(true);

	gameController = std::make_unique<mainMenu>();


	accumulator = sf::Time::Zero;
	clock.restart();

	timer = sf::Time::Zero;
	clocker.restart();

	loadFont();
}

game::~game()
{
	instance = nullptr;
}

void game::run()
{
	sf::Time deltaTime = sf::Time::Zero;
	sf::Clock deltaClock;

	while (window.isOpen())
	{
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				window.close();

		}

		deltaTime = deltaClock.restart();
		accumulator += clock.restart();

		if (accumulator > frameTime)
		{
			timer = clocker.restart();
			gameController->update();
			buttonSwitcher::update();


			accumulator -= frameTime;
		}
		fpser.countTime(deltaTime);

		window.clear(sf::Color::Black);
		gameController->draw(window);
		window.draw(fpser);
		window.display();

		++fpser;

	}
}

game * game::getInstance()
{
	return instance;
}

sf::RenderWindow & game::getWindow()
{
	return window;
}

sf::Font  *game::getFont()
{
	return &font;
}

sf::Time game::getTimer()
{
	return timer;
}


void game::setController(std::unique_ptr <gameCtrl> newController)
{
	gameController = std::move(newController);
}

void game::exit()
{
	window.close();
}

sf::Music * game::getMusic()
{
	return &music;
}

void game::hurryUpTime()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		for (int i = 0; i < 3; ++i)
		{
			timer += timer;
		}
	}
}

void game::loadFont()
{
	if (!font.loadFromFile("Fonty/Lato-Medium.ttf"))
	{
		MessageBox(0, "Unable to load Anorexia.ttf", 0, 0);
	}

}