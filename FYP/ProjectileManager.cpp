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
		if (projectiles.at(i)->type == "missile" || projectiles.at(i)->type == "missileE")
		{
			AnimationManager::GetInstance()->CreateAnimation(projectiles.at(i)->getSprite().getPosition(), 6, projectiles.at(i)->getSprite().getRotation());
		}
		else if (projectiles.at(i)->type == "drain" || projectiles.at(i)->type == "drainE")
		{
			AnimationManager::GetInstance()->CreateAnimation(projectiles.at(i)->getSprite().getPosition(), 8, projectiles.at(i)->getSprite().getRotation());
		}
		else if (projectiles.at(i)->type == "slug" || projectiles.at(i)->type == "slugE")
		{
			AnimationManager::GetInstance()->CreateAnimation(projectiles.at(i)->getSprite().getPosition(), 12, projectiles.at(i)->getSprite().getRotation());
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
		if (projectiles.at(i)->type != "missile" && projectiles.at(i)->type != "drain" && projectiles.at(i)->type != "slug" && projectiles.at(i)->type != "mine" && projectiles.at(i)->type != "missileE" && projectiles.at(i)->type != "drainE" && projectiles.at(i)->type != "slugE" && projectiles.at(i)->type != "mineE")
		{
			projectiles.at(i)->Draw(window);
		}
	}
}

void ProjectileManager::Draw2(sf::RenderWindow & window)
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles.at(i)->type == "missile" || projectiles.at(i)->type == "drain" || projectiles.at(i)->type == "slug" || projectiles.at(i)->type == "mine" || projectiles.at(i)->type == "missileE" || projectiles.at(i)->type == "drainE" || projectiles.at(i)->type == "slugE" || projectiles.at(i)->type == "mineE")
		{
			projectiles.at(i)->Draw(window);
		}
	}
}

void ProjectileManager::CreateProjectile(sf::Vector2f position, sf::Vector2f pos2, float angle, bool e)
{
	if (e == false)
	{
		projectiles.push_back(new Projectile(*world, position, pos2, angle, "plasma"));
	}
	else
	{
		projectiles.push_back(new Projectile(*world, position, pos2, angle, "plasmaE"));
	}
}

void ProjectileManager::CreateMissile(sf::Vector2f position, sf::Vector2f pos2, float angle, bool e)
{
	if (e == false)
	{
		projectiles.push_back(new Projectile(*world, position, pos2, angle, "missile"));
	}
	else
	{
		projectiles.push_back(new Projectile(*world, position, pos2, angle, "missileE"));
	}
}

void ProjectileManager::CreateDrain(sf::Vector2f position, sf::Vector2f pos2, float angle, bool e)
{
	if (e == false)
	{
		projectiles.push_back(new Projectile(*world, position, pos2, angle, "drain"));
	}
	else
	{
		projectiles.push_back(new Projectile(*world, position, pos2, angle, "drainE"));
	}
}

void ProjectileManager::CreateSlug(sf::Vector2f position, sf::Vector2f pos2, float angle, bool e)
{
	if (e == false)
	{
		projectiles.push_back(new Projectile(*world, position, pos2, angle, "slug"));
	}
	else
	{
		projectiles.push_back(new Projectile(*world, position, pos2, angle, "slugE"));
	}
}

void ProjectileManager::CreateMine(sf::Vector2f position, sf::Vector2f pos2, float angle, bool e)
{
	if (e == false)
	{
		projectiles.push_back(new Projectile(*world, position, pos2, angle, "mine"));
	}
	else
	{
		projectiles.push_back(new Projectile(*world, position, pos2, angle, "mineE"));
	}
}


void ProjectileManager::setWorld(b2World& w)
{
	world = &w;
}

void ProjectileManager::DeleteExpired()
{

	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i]->getTTL() <= 0)
		{
			if (projectiles.at(i)->type == "plasma" || projectiles.at(i)->type == "plasmaE")
			{
				AnimationManager::GetInstance()->CreateAnimation(projectiles.at(i)->getSprite().getPosition(), 1, i);
				SoundManager::GetInstance()->CreateSound(projectiles.at(i)->getSprite().getPosition(), 7);
			}
			if (projectiles.at(i)->type == "missile" || projectiles.at(i)->type == "missileE")
			{
				AnimationManager::GetInstance()->CreateAnimation(projectiles.at(i)->getSprite().getPosition(), 7, i);
				SoundManager::GetInstance()->CreateSound(projectiles.at(i)->getSprite().getPosition(), 6);
			}
			if (projectiles.at(i)->type == "drain" || projectiles.at(i)->type == "drainE")
			{
				AnimationManager::GetInstance()->CreateAnimation(projectiles.at(i)->getSprite().getPosition(), 9, i);
				SoundManager::GetInstance()->CreateSound(projectiles.at(i)->getSprite().getPosition(), 6);
			}
			if (projectiles.at(i)->type == "slug" || projectiles.at(i)->type == "slugE")
			{
				//AnimationManager::GetInstance()->CreateAnimation(projectiles.at(i)->getSprite().getPosition(), 9, i);
				//SoundManager::GetInstance()->CreateSound(projectiles.at(i)->getSprite().getPosition(), 6);
			}
			if (projectiles.at(i)->type == "mine" || projectiles.at(i)->type == "mineE")
			{
				AnimationManager::GetInstance()->CreateAnimation(projectiles.at(i)->mineSprite.getPosition(), 7, i);
				SoundManager::GetInstance()->CreateSound(projectiles.at(i)->mineSprite.getPosition(), 6);
			}
			world->DestroyBody(projectiles.at(i)->getBody());
			delete projectiles.at(i);
			projectiles.erase(projectiles.begin() + i);
			if (i != 0)
			{
				i--;
			}
		}
	}

	//vector<Projectile*>::iterator iter;
	//vector<Projectile*>::iterator endIter;

	//iter = projectiles.begin();
	//endIter = projectiles.end();

	//for (; iter != endIter; ++iter)
	//{
	//	if ((*iter)->getTTL() <= 0)
	//	{
	//		if (projectiles.size() == 1)
	//		{
	//			if (projectiles.at(0)->type == "plasma" || projectiles.at(0)->type == "plasmaE")
	//			{
	//				AnimationManager::GetInstance()->CreateAnimation(projectiles.at(0)->getSprite().getPosition(), 1, 0);
	//				SoundManager::GetInstance()->CreateSound(projectiles.at(0)->getSprite().getPosition(), 7);
	//			}
	//			if (projectiles.at(0)->type == "missile" || projectiles.at(0)->type == "missileE")
	//			{
	//				AnimationManager::GetInstance()->CreateAnimation(projectiles.at(0)->getSprite().getPosition(), 7, 0);
	//				SoundManager::GetInstance()->CreateSound(projectiles.at(0)->getSprite().getPosition(), 6);
	//			}
	//			if (projectiles.at(0)->type == "drain" || projectiles.at(0)->type == "drainE")
	//			{
	//				AnimationManager::GetInstance()->CreateAnimation(projectiles.at(0)->getSprite().getPosition(), 9, 0);
	//				SoundManager::GetInstance()->CreateSound(projectiles.at(0)->getSprite().getPosition(), 6);
	//			}
	//			if (projectiles.at(0)->type == "slug" || projectiles.at(0)->type == "slugE")
	//			{
	//				//AnimationManager::GetInstance()->CreateAnimation(projectiles.at(0)->getSprite().getPosition(), 9, 0);
	//				//SoundManager::GetInstance()->CreateSound(projectiles.at(0)->getSprite().getPosition(), 6);
	//			}
	//			if (projectiles.at(0)->type == "mine" || projectiles.at(0)->type == "mineE")
	//			{
	//				AnimationManager::GetInstance()->CreateAnimation(projectiles.at(0)->mineSprite.getPosition(), 7, 0);
	//				SoundManager::GetInstance()->CreateSound(projectiles.at(0)->mineSprite.getPosition(), 6);
	//			}
	//			world->DestroyBody(projectiles.at(0)->getBody());
	//			delete projectiles.at(0);
	//			projectiles.clear();
	//			break;
	//		}
	//		else
	//		{
	//			if ((*iter)->type == "plasma" || (*iter)->type == "plasmaE")
	//			{
	//				AnimationManager::GetInstance()->CreateAnimation((*iter)->getSprite().getPosition(), 1, 0);
	//				SoundManager::GetInstance()->CreateSound((*iter)->getSprite().getPosition(), 7);
	//			}
	//			if ((*iter)->type == "missile" || (*iter)->type == "missileE")
	//			{
	//				AnimationManager::GetInstance()->CreateAnimation((*iter)->getSprite().getPosition(), 7, 0);
	//				SoundManager::GetInstance()->CreateSound((*iter)->getSprite().getPosition(), 6);
	//			}
	//			if ((*iter)->type == "drain" || (*iter)->type == "drainE")
	//			{
	//				AnimationManager::GetInstance()->CreateAnimation((*iter)->getSprite().getPosition(), 9, 0);
	//				SoundManager::GetInstance()->CreateSound((*iter)->getSprite().getPosition(), 6);
	//			}
	//			if ((*iter)->type == "slug" || (*iter)->type == "slugE")
	//			{ 
	//				//AnimationManager::GetInstance()->CreateAnimation((*iter)->getSprite().getPosition(), 9, 0);
	//				//SoundManager::GetInstance()->CreateSound((*iter)->getSprite().getPosition(), 6);
	//			}
	//			if ((*iter)->type == "mine" || (*iter)->type == "mineE")
	//			{
	//				AnimationManager::GetInstance()->CreateAnimation((*iter)->mineSprite.getPosition(), 7, 0);
	//				SoundManager::GetInstance()->CreateSound((*iter)->mineSprite.getPosition(), 6);
	//			}
	//			world->DestroyBody((*iter)->getBody());
	//			delete (*iter);
	//			iter = projectiles.erase(iter);
	//			iter = projectiles.begin();
	//			endIter = projectiles.end();
	//		}
	//	}
	//}
}