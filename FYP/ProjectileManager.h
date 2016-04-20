#pragma once
#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")
#endif

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"

#include "Projectile.h"

#include "AnimationManager.h"
#include "SoundManager.h"

using namespace std;

class ProjectileManager
{
private:
	b2World* world;
	vector<Projectile*> projectiles;
	bool checkDestroyed;

public:
	
	static ProjectileManager* GetInstance();
	ProjectileManager();
	void Update();
	void Draw(sf::RenderWindow & window);
	void Draw2(sf::RenderWindow & window);
	void CreateProjectile(sf::Vector2f position, sf::Vector2f pos2, float angle, bool e);
	void CreateMissile(sf::Vector2f position, sf::Vector2f pos2, float angle, bool e);
	void CreateDrain(sf::Vector2f position, sf::Vector2f pos2, float angle, bool e);
	void CreateSlug(sf::Vector2f position, sf::Vector2f pos2, float angle, bool e);
	void CreateMine(sf::Vector2f position, sf::Vector2f pos2, float angle, bool e);
	void DeleteExpired();
	void setWorld(b2World& World);
};

#endif
