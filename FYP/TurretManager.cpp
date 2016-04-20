#include "TurretManager.h"

static bool instanceFlag = false;
static TurretManager* instance = NULL;

TurretManager::TurretManager()
{
	checkDestroyed = false;
}

TurretManager * TurretManager::GetInstance()
{
	if (!instanceFlag) {
		instance = new TurretManager();
		instanceFlag = true;
	}
	return instance;
}

void TurretManager::Update()
{
	for (int i = 0; i < turrets.size(); i++)
	{
		turrets.at(i)->Update();
	}

	DeleteExpired();
}

void TurretManager::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < turrets.size(); i++)
	{
		turrets.at(i)->Draw(window);
	}
}

void TurretManager::Draw2(sf::RenderWindow & window)
{
	for (int i = 0; i < turrets.size(); i++)
	{
		turrets.at(i)->Draw2(window);
	}
}

void TurretManager::CreateTurret(Turret* t)
{
	turrets.push_back(t);
}

void TurretManager::setWorld(b2World& w)
{
	world = &w;
}

void TurretManager::DeleteExpired()
{
	for (int i = 0; i < turrets.size(); i++)
	{
		if (turrets[i]->destroyed == true)
		{
			delete turrets.at(i);
			turrets.erase(turrets.begin() + i);
			if (i != 0)
			{
				i--;
			}
		}
	}

	/*vector<Turret*>::iterator iter;
	vector<Turret*>::iterator endIter;

	iter = turrets.begin();
	endIter = turrets.end();

	for (; iter != endIter; ++iter)
	{
		if ((*iter)->destroyed == true)
		{
			if (turrets.size() == 1)
			{
				delete turrets.at(0);
				turrets.clear();
				break;
			}
			else
			{
				delete (*iter);
				iter = turrets.erase(iter);
				iter = turrets.begin();
				endIter = turrets.end();
			}
		}
	}*/
}