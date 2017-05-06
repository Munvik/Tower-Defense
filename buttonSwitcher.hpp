#pragma once


class buttonSwitcher
{
	static bool isButtonActive;
	static std::map<sf::Keyboard::Key, bool> buttons;
	int INt;

public:
	buttonSwitcher();
	~buttonSwitcher();
	static void update();
	static bool canClick();
	static bool canClickKey(sf::Keyboard::Key key);
};