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

void ShipManager::prepare()
{
	allySpawns.push_back(sf::Vector2f(500, 2200));

	allySpawns.push_back(sf::Vector2f(1250, 2200));

	allySpawns.push_back(sf::Vector2f(1800, 2200));

	allySpawns.push_back(sf::Vector2f(-500, 2200));

	allySpawns.push_back(sf::Vector2f(-1250, 2200));

	allySpawns.push_back(sf::Vector2f (-1800, 2200));

	enemySpawns.push_back(sf::Vector2f(500, -2200));

	enemySpawns.push_back(sf::Vector2f(1250, -2200));

	enemySpawns.push_back(sf::Vector2f(1800, -2200));

	enemySpawns.push_back(sf::Vector2f(-500, -2200));

	enemySpawns.push_back(sf::Vector2f(-1250, -2200));

	enemySpawns.push_back(sf::Vector2f(-1800, -2200));

	respawnTimer = 0;

	enemies = 0;
	allies = 0;
	dreadnoughtCount = 0;
}

void ShipManager::respawnPlayer(string t)
{
	ships.at(0)->DeleteAll();
	if (ships.at(0)->shipType == "Frigate")
	{
		AnimationManager::GetInstance()->CreateAnimation(ships.at(0)->getSprite().getPosition(), 10, 0);
	}
	else if (ships.at(0)->shipType == "Dreadnought")
	{
		AnimationManager::GetInstance()->CreateAnimation(ships.at(0)->getSprite().getPosition(), 3, 0);
	}
	else if (ships.at(0)->shipType == "Sniper")
	{
		AnimationManager::GetInstance()->CreateAnimation(ships.at(0)->getSprite().getPosition(), 3, 0);
	}
	world->DestroyBody(ships.at(0)->getBody());
	delete ships.at(0);

	if (t == "Dreadnought")
	{
		Dreadnought* temp = new Dreadnought(*world, allySpawns.at(3), "player", *Window);
		ships.at(0) = temp;
	}
	else if (t == "Frigate")
	{
		Frigate* temp = new Frigate(*world, allySpawns.at(3), "player", *Window);
		ships.at(0) = temp;
	}
	else if (t == "Sniper")
	{
		Sniper* temp = new Sniper(*world, allySpawns.at(3), "player", *Window);
		ships.at(0) = temp;
	}
}

void ShipManager::Update()
{
	respawnTimer++;

	if (respawnTimer == 600)
	{
		respawnTimer = 0;
		enemies = 0;
		allies = 0;
		dreadnoughtCount = 0;

		for (int i = 0; i < ships.size(); i++)
		{
			if (ships.at(i)->type == "enemy")
			{
				enemies++;
			}
			else if (ships.at(i)->type == "ally")
			{
				allies++;
			}
			if (ships.at(i)->shipType == "Dreadnought")
			{
				dreadnoughtCount++;
			}
		}
		if (enemies < 6)
		{
			for (int i = 0; i < (6 - enemies); i++)
			{
				float randShip = rand() % 30 + 1;
				float randPos = rand() % 6;

				if (randShip <= 10)
				{
					if (dreadnoughtCount < 4)
					{
						CreateShip(enemySpawns.at(randPos), "enemy", "Dreadnought");
					}
					else
					{
						float randShip2 = rand() % 10 + 1;
						if (randShip <= 5)
						{
							CreateShip(enemySpawns.at(randPos), "enemy", "Frigate");
						}
						else
						{
							CreateShip(enemySpawns.at(randPos), "enemy", "Sniper");
						}
					}
				}
				else if (randShip <= 20 && randShip >= 11)
				{
					CreateShip(enemySpawns.at(randPos), "enemy", "Frigate");
				}
				else if (randShip <= 30 && randShip >= 21)
				{
					CreateShip(enemySpawns.at(randPos), "enemy", "Sniper");
				}
			}
		}
		if (allies < 5)
		{
			for (int i = 0; i < (5 - allies); i++)
			{
				float randShip = rand() % 30 + 1;
				float randPos = rand() % 5;

				if (randShip <= 10)
				{
					if (dreadnoughtCount < 4)
					{
						CreateShip(allySpawns.at(randPos), "ally", "Dreadnought");
					}
					else
					{
						float randShip2 = rand() % 10 + 1;
						if (randShip <= 5)
						{
							CreateShip(allySpawns.at(randPos), "ally", "Frigate");
						}
						else
						{
							CreateShip(allySpawns.at(randPos), "ally", "Sniper");
						}
					}
				}
				else if (randShip <= 20 && randShip >= 11)
				{
					CreateShip(allySpawns.at(randPos), "ally", "Frigate");
				}
				else if (randShip <= 30 && randShip >= 21)
				{
					CreateShip(allySpawns.at(randPos), "ally", "Sniper");
				}
			}
		}
	}
	for (int i = 0; i < ships.size(); i++)
	{
		if (ships.at(i)->destroyed == false)
		{
			ships.at(i)->Update();
		}

		if (ships.at(i)->destroyed == true)
		{
			checkDestroyed = true;
		}
	}

	if (checkDestroyed == true)
	{
		//DeleteExpiredDreadnoughts();
		//DeleteExpiredFrigates();
		DeleteExpiredShips();
	}
}

void ShipManager::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < ships.size(); i++)
	{
		if (ships.at(i)->destroyed == false)
		{
			ships.at(i)->Draw(window);
		}
	}
}

void ShipManager::Draw2(sf::RenderWindow & window)
{
	for (int i = 0; i < ships.size(); i++)
	{
		if (ships.at(i)->destroyed == false)
		{
			ships.at(i)->Draw2(window);
		}
	}
}

void ShipManager::CreateShip(sf::Vector2f position, string t, string c)
{
	if (c == "Dreadnought")
	{
		Dreadnought* temp = new Dreadnought(*world, position, t, *Window);
		ships.push_back(temp);
		dreadnoughts.push_back(temp);
	}
	else if (c == "Frigate")
	{
		Frigate* temp = new Frigate(*world, position, t, *Window);
		ships.push_back(temp);
		frigates.push_back(temp);
	}
	else if (c == "Sniper")
	{
		Sniper* temp = new Sniper(*world, position, t, *Window);
		ships.push_back(temp);
		//frigates.push_back(temp);
	}
}

void ShipManager::setWorld(b2World& w)
{
	world = &w;
}

void ShipManager::setWindow(sf::RenderWindow & w)
{
	Window = &w;
}

void ShipManager::DeleteExpiredDreadnoughts()
{
	vector<Dreadnought*>::iterator iter;
	vector<Dreadnought*>::iterator endIter;

	iter = dreadnoughts.begin();
	endIter = dreadnoughts.end();

	for (; iter != endIter; ++iter)
	{
		if ((*iter)->destroyed == true)
		{
			if (dreadnoughts.size() == 1)
			{
				for (int i = 0; i < dreadnoughts.at(0)->wreckPoint.size(); i++)
				{
					WreckManager::GetInstance()->CreateWreck(sf::Vector2f(dreadnoughts.at(0)->wreckPoint.at(i)->x, dreadnoughts.at(0)->wreckPoint.at(i)->y), dreadnoughts.at(0)->getSprite().getRotation(), i);
				}
				AnimationManager::GetInstance()->CreateAnimation(dreadnoughts.at(0)->getSprite().getPosition(), 3, 0);
				world->DestroyBody(dreadnoughts.at(0)->getBody());
				dreadnoughts.at(0)->DeleteAll();
				delete dreadnoughts.at(0);
				dreadnoughts.clear();
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
				iter = dreadnoughts.erase(iter);
				iter = dreadnoughts.begin();
				endIter = dreadnoughts.end();
			}
		}
	}
	checkDestroyed = false;
}

void ShipManager::DeleteExpiredFrigates()
{
	vector<Frigate*>::iterator iter;
	vector<Frigate*>::iterator endIter;

	iter = frigates.begin();
	endIter = frigates.end();

	for (; iter != endIter; ++iter)
	{
		if ((*iter)->destroyed == true)
		{
			if (frigates.size() == 1)
			{
				for (int i = 0; i < frigates.at(0)->wreckPoint.size(); i++)
				{
					WreckManager::GetInstance()->CreateWreck(sf::Vector2f(frigates.at(0)->wreckPoint.at(i)->x, frigates.at(0)->wreckPoint.at(i)->y), frigates.at(0)->getSprite().getRotation(), i);
				}
				AnimationManager::GetInstance()->CreateAnimation(frigates.at(0)->getSprite().getPosition(), 3, 0);
				world->DestroyBody(frigates.at(0)->getBody());
				frigates.at(0)->DeleteAll();
				delete frigates.at(0);
				frigates.clear();
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
				iter = frigates.erase(iter);
				iter = frigates.begin();
				endIter = frigates.end();
			}
		}
	}
	checkDestroyed = false;
}

void ShipManager::DeleteExpiredShips()
{
	for (int i = 0; i < ships.size(); i++)
	{
		if (ships[i]->destroyed == true)
		{
			if (i != 0)
			{
				ships.at(i)->DeleteAll();
				if (ships.at(i)->shipType == "Frigate")
				{
					AnimationManager::GetInstance()->CreateAnimation(ships.at(i)->getSprite().getPosition(), 10, 0);
				}
				else if (ships.at(i)->shipType == "Dreadnought")
				{
					AnimationManager::GetInstance()->CreateAnimation(ships.at(i)->getSprite().getPosition(), 3, 0);
				}
				else if (ships.at(i)->shipType == "Sniper")
				{
					AnimationManager::GetInstance()->CreateAnimation(ships.at(i)->getSprite().getPosition(), 3, 0);
				}
				world->DestroyBody(ships.at(i)->getBody());
				delete ships.at(i);
				ships.erase(ships.begin() + i);
				if (i != 0)
				{
					i--;
				}
			}
		}
	}

	/*vector<Ship*>::iterator iter;
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
	}*/
	checkDestroyed = false;
}