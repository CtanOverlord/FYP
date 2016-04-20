#pragma once
#ifndef TURRETMANAGER_H
#define TURRETMANAGER_H

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

#include "Turret.h"

#include "AnimationManager.h"
#include "SoundManager.h"

class Turret;

using namespace std;

class TurretManager
{
private:
	b2World* world;
	vector<Turret*> turrets;
	bool checkDestroyed;

public:

	static TurretManager* GetInstance();
	TurretManager();
	void Update();
	void Draw(sf::RenderWindow & window);
	void Draw2(sf::RenderWindow & window);
	void CreateTurret(Turret*);
	void DeleteExpired();
	void setWorld(b2World& World);
};

#endif

