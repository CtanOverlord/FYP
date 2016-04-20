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

#include "TurretManager.h"
#include <ProjectileManager.h>
#include <Thruster.h>
#include "SoundManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Turret;

class Ship
{
private:

public:

	// Variables

	sf::Sprite shipSprite;
	sf::Vector2f velocity;
	sf::Vector2f velocity2;
	sf::Vector2f worldMousePos;
	sf::Texture shipTexture;
	sf::Texture bayTexture;
	sf::Sprite baySprite;
	sf::Texture boosterTexture;
	sf::Sprite boosterSprite;
	sf::Texture shieldTexture;
	sf::Sprite shieldSprite;
	sf::Texture healthBoxTexture;
	sf::Sprite healthBox;
	sf::Texture healthBarTexture;
	sf::Sprite healthBar;
	sf::Texture powerTexture;
	sf::Sprite power;
	float speed;
	float health;
	float fuel;
	float rotation;
	float prevRotation;
	b2Body* shipBody;
	b2World* world;
	vector<Turret*> turrets;
	sf::RenderWindow* Window;
	sf::Vector2f boosterPoint;
	vector<Thruster*> thrusters;
	vector<sf::Vector2f*> wreckPoint;
	vector<sf::Vector2f*> wreckPointOrig;
	vector<sf::Vector2f*> missilePoints;
	vector<sf::Vector2f*> missilePointOrig;
	string type;
	int destructionTimer;
	int delayTimer;
	int delay;
	bool shield;
	int fireCount;
	int missileStep;
	int soundTimer;
	bool onlyOnce;
	string shipType;
	sf::Vector2f targetPos;
	bool firing;
	float maxHealth;
	bool noFuel;
	float maxFuel;
	int fireTimer;
	int fireTimerMax;
	bool manual;


	//Methods


	Ship(b2World& World, sf::Vector2f position, string type, sf::RenderWindow & window);
	Ship();
	virtual void Update();
	virtual void Draw(sf::RenderWindow & window);
	void Draw2(sf::RenderWindow & window);
	float to_positive_angle(float angle);
	void Move(sf::Vector2f targetPos);
	virtual void CreateBody();
	sf::Sprite getSprite();
	virtual void setHealth(float);
	float getHealth();
	void setFuel(float);
	virtual float getFuel();
	b2Body* getBody();
	bool destroyed;
	virtual void updateMissilePoints();
	virtual void updateWreckPoints();
	virtual void updateThrusterPoints();
	virtual void updateBoosterPoints();
	sf::Vector2f normalize(sf::Vector2f source);
	float degreeToRadian(float angle);
	float radiansToDegrees(float angle);
	bool missileFiring;
	int missileTimer;
	int shieldTimer;
	int shieldDuration;
	virtual void DeleteAll();
	float distance(sf::Vector2f, sf::Vector2f);
};

#endif
