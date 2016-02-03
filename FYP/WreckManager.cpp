#include "WreckManager.h"

static bool instanceFlag = false;
static WreckManager* instance = NULL;

WreckManager::WreckManager()
{
	checkDestroyed = false;
}

WreckManager * WreckManager::GetInstance()
{
	if (!instanceFlag) {
		instance = new WreckManager();
		instanceFlag = true;
	}
	return instance;
}

void WreckManager::Update()
{
	for (int i = 0; i < wrecks.size(); i++)
	{
		wrecks.at(i)->Update();

		if (wrecks.at(i)->getTTL() <= 0)
		{
			checkDestroyed = true;
		}
	}

	if (checkDestroyed == true)
	{
		DeleteExpired();
	}
}

void WreckManager::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < wrecks.size(); i++)
	{
		wrecks.at(i)->Draw(window);
	}
}

void WreckManager::CreateWreck(sf::Vector2f position, float angle, int type)
{
	wrecks.push_back(new Wreck(*world, position, angle, type));
}

void WreckManager::setWorld(b2World& w)
{
	world = &w;
}

void WreckManager::DeleteExpired()
{
	vector<Wreck*>::iterator iter;
	vector<Wreck*>::iterator endIter;

	iter = wrecks.begin();
	endIter = wrecks.end();

	for (; iter != endIter; ++iter)
	{
		if ((*iter)->getTTL() <= 0)
		{
			if (wrecks.size() == 1)
			{
				AnimationManager::GetInstance()->CreateAnimation(wrecks.at(0)->getSprite().getPosition(), 5, 0);
				SoundManager::GetInstance()->CreateSound(wrecks.at(0)->getSprite().getPosition(), 5);
				world->DestroyBody(wrecks.at(0)->getBody());
				delete wrecks.at(0);
				wrecks.clear();
				break;
			}
			else
			{
				AnimationManager::GetInstance()->CreateAnimation((*iter)->getSprite().getPosition(), 5, 0);
				SoundManager::GetInstance()->CreateSound((*iter)->getSprite().getPosition(), 5);
				world->DestroyBody((*iter)->getBody());
				delete (*iter);
				iter = wrecks.erase(iter);
				iter = wrecks.begin();
				endIter = wrecks.end();
			}
		}
	}

	checkDestroyed = false;
}