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

#include "Dreadnought.h"
#include "Frigate.h"
#include "Sniper.h"
#include "AnimationManager.h"
#include "ProjectileManager.h"
#include "WreckManager.h"

using namespace std;

class Dreadnought;
class Frigate;
class Sniper;
class Level;
class CapPoint;

class ShipManager
{
private:
	b2World* world;
	sf::RenderWindow* Window;
	bool checkDestroyed;
	vector<sf::Vector2f> enemySpawns;
	vector<sf::Vector2f> allySpawns;
	int respawnTimer;
	int allies;
	int enemies;
	int dreadnoughtCount;

public:
	
	static ShipManager* GetInstance();
	ShipManager();
	void Update();
	void Draw(sf::RenderWindow & window);
	void Draw2(sf::RenderWindow & window);
	void CreateShip(sf::Vector2f position, string t, string c);
	void DeleteExpiredDreadnoughts();
	void DeleteExpiredShips();
	void DeleteExpiredFrigates();
	vector<Ship*> ships;
	vector<Dreadnought*> dreadnoughts;
	vector<Frigate*> frigates;
	void setWorld(b2World& World);
	void setWindow(sf::RenderWindow & window);
	void prepare();
	void respawnPlayer(string t);
};

#endif
