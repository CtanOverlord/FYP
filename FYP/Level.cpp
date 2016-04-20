#include "Level.h"

static bool instanceFlag = false;
static Level* instance = NULL;

Level::Level()
{
}

Level * Level::GetInstance()
{
	if (!instanceFlag) {
		instance = new Level();
		instanceFlag = true;
	}
	return instance;
}

void Level::createWorld()
{
	capPoints.push_back(new CapPoint(*world, sf::Vector2f(0, 0)));
	capPoints.push_back(new CapPoint(*world, sf::Vector2f(2075, 0)));
	capPoints.push_back(new CapPoint(*world, sf::Vector2f(-2075, 0)));

	bounds.push_back(new Bound(*world, sf::Vector2f(-2550, 2095), 90, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(-2550, 1095), 90, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(-2550, 95), 90, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(-2550, -905), 90, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(-2550, -1905), 90, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(-2550, -2655), 90, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(2720, 2575), 0, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(2720, -2575), 0, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(2550, 2095), 90, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(2550, 1095), 90, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(2550, 95), 90, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(2550, -905), 90, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(2550, -1905), 90, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(2550, -2655), 90, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(-2030, 2575), 0, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(-1030, 2575), 0, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(-30, 2575), 0, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(970, 2575), 0, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(1970, 2575), 0, 1));

	bounds.push_back(new Bound(*world, sf::Vector2f(-2030, -2575), 0, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(-1030, -2575), 0, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(-30, -2575), 0, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(970, -2575), 0, 1));
	bounds.push_back(new Bound(*world, sf::Vector2f(1970, -2575), 0, 1));

	bounds.push_back(new Bound(*world, sf::Vector2f(1000, -600), 0, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(1430, -435), 45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(570, -435), -45, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(405, 0), 90, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(1595, 0), 90, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(1000, 600), 0, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(1430, 435), -45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(570, 435), 45, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(-1000, -600), 0, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(-1430, -435), -45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(-570, -435), 45, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(-405, 0), 90, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(-1595, 0), 90, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(-1000, 600), 0, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(-1430, 435), 45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(-570, 435), -45, 2));

	/*bounds.push_back(new Bound(*world, sf::Vector2f(937, 435), -45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(570, 435), 45, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(937, 70), 45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(570, 70), -45, 2));*/

	bounds.push_back(new Bound(*world, sf::Vector2f(183.5, 1485.5), -45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(-183.5, 1485.5), 45, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(183.5, 1114.5), 45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(-183.5, 1114.5), -45, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(183.5, -1114.5), -45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(-183.5, -1114.5), 45, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(183.5, -1485.5), 45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(-183.5, -1485.5), -45, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(-1891.5, 1485.5), -45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(-2325, 950), 0, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(-1895.5, 1114.5), 45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(-2330, 1650), 0, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(-1891.5, -1114.5), -45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(-2325, -950), 0, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(-1895.5, -1485.5), 45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(-2330, -1650), 0, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(1891.5, 1485.5), 45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(2330, 1650), 0, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(1895.5, 1114.5), -45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(2330, 950), 0, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(1891.5, -1114.5), 45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(2330, -950), 0, 2));

	bounds.push_back(new Bound(*world, sf::Vector2f(1895.5, -1485.5), -45, 2));
	bounds.push_back(new Bound(*world, sf::Vector2f(2330, -1650), 0, 2));
}

void Level::setWorld(b2World& w)
{
	world = &w;
}

void Level::setWindow(sf::RenderWindow & w)
{
	Window = &w;
}

void Level::Update()
{
	for (int i = 0; i < capPoints.size(); i++)
	{
		capPoints.at(i)->Update();
	}
	for (int i = 0; i < bounds.size(); i++)
	{
		bounds.at(i)->Update();
	}
}

void Level::Draw()
{
	for (int i = 0; i < bounds.size(); i++)
	{
		bounds.at(i)->Draw(*Window);
	}
	for (int i = 0; i < capPoints.size(); i++)
	{
		capPoints.at(i)->Draw(*Window);
	}
}