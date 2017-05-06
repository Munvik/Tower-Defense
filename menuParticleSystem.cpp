#include "pch.hpp"
#include "menuParticleSystem.hpp"
#include "game.hpp"

menuParticleSystem::menuParticleSystem()
{
	backgroundVertexes.resize(bVertexesCount);
	bckgVertexes.resize(bVertexesCount);
	backgroundVertexes.setPrimitiveType(sf::Points);

	for (int i = 0; i < bVertexesCount; i++)
	{
		backgroundVertexes[i].color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
		backgroundVertexes[i].position = (sf::Vector2f)sf::Vector2i(rand() % WIDTH, rand() % HEIGHT);
		bckgVertexes[i].lifeTime = sf::milliseconds((rand() % 2000) + 2000);
		bckgVertexes[i].velocity = Vertex::getRandomVelocity();
	}

	cursorVertexes.resize(cVertexesCount);
	crsVertexes.resize(cVertexesCount);
	cursorVertexes.setPrimitiveType(sf::Points);

	for (int i = 0; i < cVertexesCount; ++i)
	{
		cursorVertexes[i].color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
		cursorVertexes[i].position = (sf::Vector2f)sf::Mouse::getPosition(game::getInstance()->getWindow());
		crsVertexes[i].lifeTime = sf::milliseconds((rand() % 200) + 200);
		crsVertexes[i].velocity = Vertex::getRandomVelocity();
		crsVertexes[i].slowVelocity();
	}


}

menuParticleSystem::~menuParticleSystem()
{
}

void menuParticleSystem::resetBackgroundParticle(int index)
{
	sf::Vector2f newPointPos;
	newPointPos.x = (float)(rand() % WIDTH);
	newPointPos.y = (float)(rand() % HEIGHT);
	backgroundVertexes[index].position = newPointPos;

	sf::Color newPointColor(rand() % 255, rand() % 255, rand() % 255);
	backgroundVertexes[index].color = newPointColor;

	sf::Time newPointLifeTime = sf::milliseconds((std::rand() % 2000) + 2000);
	bckgVertexes[index].lifeTime = newPointLifeTime;

	bckgVertexes[index].velocity = Vertex::getRandomVelocity();
}

void menuParticleSystem::resetCursorParticle(int index)
{
	sf::Vector2f newPointPos;
	newPointPos.x = (float)(rand() % WIDTH);
	newPointPos.y = (float)(rand() % HEIGHT);
	cursorVertexes[index].position = (sf::Vector2f)sf::Mouse::getPosition(game::getInstance()->getWindow());

	sf::Color newPointColor(rand() % 255, rand() % 255, rand() % 255);
	cursorVertexes[index].color = newPointColor;

	sf::Time newPointLifeTime = sf::milliseconds((std::rand() % 800) + 500);
	crsVertexes[index].lifeTime = newPointLifeTime;

	crsVertexes[index].velocity = Vertex::getRandomVelocity();
}

void menuParticleSystem::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = NULL;

	target.draw(backgroundVertexes, states);
	target.draw(cursorVertexes,states);
}

void menuParticleSystem::update()
{
	sf::Time elapsedTime = game::getInstance()->getTimer();

	for (int i = 0; i < bVertexesCount; ++i)
	{
		bckgVertexes[i].lifeTime -= elapsedTime;

		if (bckgVertexes[i].lifeTime <= sf::Time::Zero)
		{
			resetBackgroundParticle(i);
		}

		backgroundVertexes[i].position += bckgVertexes[i].velocity * elapsedTime.asSeconds();
	}

	for (int i = 0; i < cVertexesCount; ++i)
	{
		crsVertexes[i].lifeTime -= elapsedTime;

		if (crsVertexes[i].lifeTime <= sf::Time::Zero)
		{
			resetCursorParticle(i);
		}

		cursorVertexes[i].position += crsVertexes[i].velocity * elapsedTime.asSeconds();
	}
}






sf::Vector2f Vertex::getRandomVelocity()
{
	float angle = (std::rand() % 360) * 3.14f / 180.f;
	float speed = (std::rand() % 30) + 50.f;

	sf::Vector2f velocity(std::cos(angle) * speed, std::sin(angle) * speed);

	return velocity;
}

void Vertex::slowVelocity()
{
	velocity /= 4.f;
}
