#pragma once
#include "pch.hpp"

class Font
{
protected:
	sf::Font font;

public:
	Font() {
		if (!font.loadFromFile("Fonty/Anorexia.ttf")) {return;}}
};