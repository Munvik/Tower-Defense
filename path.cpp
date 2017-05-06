#include "pch.hpp"
#include "path.hpp"
#include "mainGame.hpp"

const float path::width = 70.f;

path::path()
{
}

path::~path()
{
}

void path::makeUnBuildablePath()
{
	sf::FloatRect partofStreet;

	for (size_t i = 0; i < wayPoints.size() - 1; ++i)
	{
		sf::Vector2f vector;

		vector.x = wayPoints[i + 1].x - wayPoints[i].x;
		vector.y = wayPoints[i + 1].y - wayPoints[i].y;

		if ((vector.x >= 0.f) && (vector.y >= 0.f))
		{
			partofStreet.left = wayPoints[i].x - width / 2;
			partofStreet.top = wayPoints[i].y - width / 2;
			partofStreet.width = vector.x + width;
			partofStreet.height = vector.y + width;
		}
		else if ((vector.x < 0.f) || (vector.y < 0))
		{
			partofStreet.left = wayPoints[i+1].x - width / 2;
			partofStreet.top = wayPoints[i+1].y - width / 2;
			partofStreet.width = fabs(vector.x) + width;
			partofStreet.height = fabs(vector.y) + width;
		}

		mainGame::getInstance()->getMap()->unBuildable.push_back(partofStreet);
	}
	wayPoints.clear();
}