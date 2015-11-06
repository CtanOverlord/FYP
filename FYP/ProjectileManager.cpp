#include "ProjectileManager.h"

ProjectileManager::ProjectileManager(b2World& World, AnimationManager& a)
{
	world = &World;
	aniMan = &a;
}

void ProjectileManager::Update()
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles.at(i)->Update();
	}

	DeleteExpired();
}

void ProjectileManager::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles.at(i)->Draw(window);
	}
}

void ProjectileManager::CreateProjectile(sf::Vector2f position, sf::Vector2f pos2, float angle)
{
	projectiles.push_back(new Projectile(*world, position, pos2, angle));
}

void ProjectileManager::DeleteExpired()
{
	vector<Projectile*>::iterator iter;
	vector<Projectile*>::iterator endIter;

	iter = projectiles.begin();
	endIter = projectiles.end();

	for (; iter != endIter; ++iter)
	{
		if ((*iter)->getTTL() <= 0)
		{
			if (projectiles.size() == 1)
			{
				aniMan->CreateAnimation(projectiles.at(0)->getSprite().getPosition(), 1, 0);
				world->DestroyBody(projectiles.at(0)->getBody());
				projectiles.clear();
				break;
			}
			else
			{
				aniMan->CreateAnimation((*iter)->getSprite().getPosition(), 1, 0);
				world->DestroyBody((*iter)->getBody());
				iter = projectiles.erase(iter);
				iter = projectiles.begin();
				endIter = projectiles.end();
			}
		}
	}
}