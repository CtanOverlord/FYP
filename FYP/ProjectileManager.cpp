#include "ProjectileManager.h"

static bool instanceFlag = false;
static ProjectileManager* instance = NULL;

ProjectileManager::ProjectileManager()
{
	checkDestroyed = false;
}

ProjectileManager * ProjectileManager::GetInstance()
{
	if (!instanceFlag) {
		instance = new ProjectileManager();
		instanceFlag = true;
	}
	return instance;
}

void ProjectileManager::Update()
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles.at(i)->Update();
		if (projectiles.at(i)->type == "missile")
		{
			AnimationManager::GetInstance()->CreateAnimation(projectiles.at(i)->getSprite().getPosition(), 6, projectiles.at(i)->getSprite().getRotation());
		}
		if (projectiles.at(i)->getTTL() <= 0)
		{
			checkDestroyed = true;
		}
	}

	if (checkDestroyed == true)
	{
		DeleteExpired();
	}
}

void ProjectileManager::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles.at(i)->type != "missile")
		{
			projectiles.at(i)->Draw(window);
		}
	}
}

void ProjectileManager::Draw2(sf::RenderWindow & window)
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles.at(i)->type == "missile")
		{
			projectiles.at(i)->Draw(window);
		}
	}
}

void ProjectileManager::CreateProjectile(sf::Vector2f position, sf::Vector2f pos2, float angle)
{
	projectiles.push_back(new Projectile(*world, position, pos2, angle, "plasma"));
}

void ProjectileManager::CreateMissile(sf::Vector2f position, sf::Vector2f pos2, float angle)
{
	projectiles.push_back(new Projectile(*world, position, pos2, angle, "missile"));
}

void ProjectileManager::setWorld(b2World& w)
{
	world = &w;
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
				if (projectiles.at(0)->type == "plasma")
				{
					AnimationManager::GetInstance()->CreateAnimation(projectiles.at(0)->getSprite().getPosition(), 1, 0);
					SoundManager::GetInstance()->CreateSound(projectiles.at(0)->getSprite().getPosition(), 7);
				}
				if (projectiles.at(0)->type == "missile")
				{
					AnimationManager::GetInstance()->CreateAnimation(projectiles.at(0)->getSprite().getPosition(), 7, 0);
					SoundManager::GetInstance()->CreateSound(projectiles.at(0)->getSprite().getPosition(), 6);
				}
				world->DestroyBody(projectiles.at(0)->getBody());
				delete projectiles.at(0);
				projectiles.clear();
				break;
			}
			else
			{
				if ((*iter)->type == "plasma")
				{
					AnimationManager::GetInstance()->CreateAnimation((*iter)->getSprite().getPosition(), 1, 0);
					SoundManager::GetInstance()->CreateSound((*iter)->getSprite().getPosition(), 7);
				}
				if ((*iter)->type == "missile")
				{
					AnimationManager::GetInstance()->CreateAnimation((*iter)->getSprite().getPosition(), 7, 0);
					SoundManager::GetInstance()->CreateSound((*iter)->getSprite().getPosition(), 6);
				}
				world->DestroyBody((*iter)->getBody());
				delete (*iter);
				iter = projectiles.erase(iter);
				iter = projectiles.begin();
				endIter = projectiles.end();
			}
		}
	}
}