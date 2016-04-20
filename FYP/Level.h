#pragma once
#ifndef LEVEL_H
#define LEVEL_H

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
#include "Button.h"
#include "CapPoint.h"
#include "Bound.h"

using namespace std;

class CapPoint;

class Level
{
private:
	sf::RenderWindow* Window;
	vector<Bound*> bounds;
	b2World* world;

public:
	static Level* GetInstance();
	Level();
	void Update();
	void Draw();
	void setWorld(b2World& World);
	void setWindow(sf::RenderWindow & window);
	void createWorld();
	vector<CapPoint*> capPoints;
};

#endif


