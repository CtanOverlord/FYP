#pragma once
#ifndef CAPPOINT_H
#define CAPPOINT_H

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
#include "AnimationManager.h"
#include "SoundManager.h"
#include "Globals.h"
#include "ShipManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Ship;

class ShipManager;

class CapPoint
{
private:

	sf::Sprite capSprite;
	sf::Sprite capSprite2;
	sf::Sprite capSprite3;
	sf::Texture capTexture1;
	sf::Texture capTexture2;
	sf::Texture capTexture3;
	sf::Sprite capZoneSprite;
	sf::Texture capZoneTexture;
	sf::Sprite capZoneSprite2;
	sf::Texture capZoneTexture2;
	sf::Sprite capZoneSprite3;
	sf::Texture capZoneTexture3;
	sf::Sprite capAreaSprite;
	sf::Texture capAreaTexture;
	sf::Sprite capAreaSprite2;
	sf::Texture capAreaTexture2;
	sf::Sprite capAreaSprite3;
	sf::Texture capAreaTexture3;
	float rotSpeed;
	float rotSpeed2;
	b2Body* capBody;
	b2Body* capZoneBody;
	b2World* world;
	vector<string> occupants;
	bool contested;
	int reds;
	int blues;

public:
	
	CapPoint(b2World& World, sf::Vector2f position);
	void Update();
	void Draw(sf::RenderWindow & window);
	void CreateBody();
	sf::Sprite getSprite();
	b2Body* getBody();
	void Capture(string ali);
	void addOccupant(string);
	void removeOccupant(string);
	float nuetralCount;
	float blueCount;
	float redCount;
	string owner;
	float distance(sf::Vector2f, sf::Vector2f);
};

#endif

