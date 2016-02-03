#pragma once
#ifndef WRECKMANAGER_H
#define WRECKMANAGER_H

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

#include "Wreck.h"

#include "AnimationManager.h"

using namespace std;

class WreckManager
{
private:
	b2World* world;
	vector<Wreck*> wrecks;
	bool checkDestroyed;

public:
	
	static WreckManager* GetInstance();
	WreckManager();
	void Update();
	void Draw(sf::RenderWindow & window);
	void CreateWreck(sf::Vector2f position, float angle, int type);
	void DeleteExpired();
	void setWorld(b2World& World);
};

#endif

