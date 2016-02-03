#include "ShipManager.h"

static bool instanceFlag = false;
static ShipManager* instance = NULL;

ShipManager::ShipManager()
{
	checkDestroyed = false;
}

ShipManager * ShipManager::GetInstance()
{
	if (!instanceFlag) {
		instance = new ShipManager();
		instanceFlag = true;
	}
	return instance;
}

void ShipManager::Update()
{
	for (int i = 0; i < ships.size(); i++)
	{
		ships.at(i)->Update();

		if (ships.at(i)->destroyed == true)
		{
			checkDestroyed = true;
		}
	}

	if (checkDestroyed == true)
	{
		DeleteExpired();
	}
}

void ShipManager::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < ships.size(); i++)
	{
		ships.at(i)->Draw(window);
	}
}

void ShipManager::CreateShip(sf::Vector2f position, string t)
{
	ships.push_back(new Ship(*world, position, t, *Window));
}

void ShipManager::setWorld(b2World& w)
{
	world = &w;
}

void ShipManager::setWindow(sf::RenderWindow & w)
{
	Window = &w;
}

void ShipManager::DeleteExpired()
{
	vector<Ship*>::iterator iter;
	vector<Ship*>::iterator endIter;

	iter = ships.begin();
	endIter = ships.end();

	for (; iter != endIter; ++iter)
	{
		if ((*iter)->destroyed == true)
		{
			if (ships.size() == 1)
			{
				for (int i = 0; i < ships.at(0)->wreckPoint.size(); i++)
				{
					WreckManager::GetInstance()->CreateWreck(sf::Vector2f(ships.at(0)->wreckPoint.at(i)->x, ships.at(0)->wreckPoint.at(i)->y), ships.at(0)->getSprite().getRotation(), i);
				}
				AnimationManager::GetInstance()->CreateAnimation(ships.at(0)->getSprite().getPosition(), 3, 0);
				world->DestroyBody(ships.at(0)->getBody());
				ships.at(0)->DeleteAll();
				delete ships.at(0);
				ships.clear();
				break;
			}
			else
			{
				for (int i = 0; i < (*iter)->wreckPoint.size(); i++)
				{
					WreckManager::GetInstance()->CreateWreck(sf::Vector2f((*iter)->wreckPoint.at(i)->x, (*iter)->wreckPoint.at(i)->y), (*iter)->getSprite().getRotation(), i);
				}
				AnimationManager::GetInstance()->CreateAnimation((*iter)->getSprite().getPosition(), 3, 0);
				world->DestroyBody((*iter)->getBody());
				(*iter)->DeleteAll();
				delete (*iter);
				iter = ships.erase(iter);
				iter = ships.begin();
				endIter = ships.end();
			}
		}
	}
	checkDestroyed = false;
}