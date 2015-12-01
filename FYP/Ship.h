#pragma once
#ifndef SHIP_H
#define SHIP_H

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

#include <Turret.h>
#include <ProjectileManager.h>
#include <Thruster.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Turret;

class Ship
{
private:

	sf::Sprite shipSprite;
	sf::Vector2f velocity;
	sf::Vector2f velocity2;
	sf::Texture shipTexture;
	sf::Texture boosterTexture;
	sf::Sprite boosterSprite;
	float speed;
	float health;
	float fuel;
	float rotation;
	float prevRotation;
	b2Body* shipBody;
	b2World* world;
	ProjectileManager* projMan;
	vector<Turret*> turrets;
	AnimationManager* aniMan;
	sf::Vector2f boosterPoint;
	vector<Thruster*> thrusters;
	string type;
	int destructionTimer;
	int delayTimer;
	int delay;

public:

	Ship(b2World& World, sf::Vector2f position, string type, ProjectileManager & projManager, AnimationManager& aniMan);
	void Update();
	void Draw(sf::RenderWindow & window);
	float to_positive_angle(float angle);
	void Move(sf::Vector2f targetPos);
	void CreateBody();
	sf::Sprite getSprite();
	void setHealth(float);
	float getHealth();
	b2Body* getBody();
	bool destroyed;
};

#endif
