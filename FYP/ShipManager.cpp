#include "ShipManager.h"

ShipManager::ShipManager(b2World& World, AnimationManager& a, ProjectileManager& p)
{
	world = &World;
	aniMan = &a;
	projMan = &p;
}

void ShipManager::Update()
{
	for (int i = 0; i < ships.size(); i++)
	{
		ships.at(i)->Update();
	}

	DeleteExpired();
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
	ships.push_back(new Ship(*world, position, t, *projMan, *aniMan));
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
				aniMan->CreateAnimation(ships.at(0)->getSprite().getPosition(), 3, 0);
				world->DestroyBody(ships.at(0)->getBody());
				ships.clear();
				break;
			}
			else
			{
				aniMan->CreateAnimation((*iter)->getSprite().getPosition(), 3, 0);
				world->DestroyBody((*iter)->getBody());
				iter = ships.erase(iter);
				iter = ships.begin();
				endIter = ships.end();
			}
		}
	}
}