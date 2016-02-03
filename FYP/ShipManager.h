#pragma once
#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

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

#include "Ship.h"
#include "AnimationManager.h"
#include "ProjectileManager.h"
#include "WreckManager.h"

using namespace std;

class ShipManager
{
private:
	b2World* world;
	sf::RenderWindow* Window;
	bool checkDestroyed;

public:
	
	static ShipManager* GetInstance();
	ShipManager();
	void Update();
	void Draw(sf::RenderWindow & window);
	void CreateShip(sf::Vector2f position, string t);
	void DeleteExpired();
	vector<Ship*> ships;
	void setWorld(b2World& World);
	void setWindow(sf::RenderWindow & window);
};

#endif
