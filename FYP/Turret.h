#pragma once
#ifndef TURRET_H
#define TURRET_H

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
#include <Ship.h>
#include <ProjectileManager.h>
#include "SoundManager.h"
#include "RayCastCallBackCustom.h"
#include "Wreck.h"

using namespace std;

class Ship;

class Turret
{
private:

	sf::Sound laser;
	sf::SoundBuffer laserSound;
	sf::Sound steam;
	sf::SoundBuffer steamSound;
	sf::Sprite turretSprite;
	sf::Sprite laserBeam;
	sf::Sprite impact;
	sf::Sprite heat;
	sf::Sprite vent;
	sf::Texture turretTexture;
	sf::Texture laserTexture;
	sf::Texture impactTexture;
	sf::Texture heatTexture;
	sf::Texture ventTexture;
	sf::Vector2f position;
	sf::Vector2f position2;
	sf::Vector2f direction;
	sf::Vector2f firePoint1;
	sf::Vector2f firePoint2;
	sf::Vector2f firePoint3;
	sf::Vector2f firePoint4;
	RayCastCallBackCustom* rayCallBack;
	float rotation;
	float prevRotation;
	Ship* ship;
	float speed;
	vector<sf::Vector2f> firePoints;
	vector<sf::Vector2f> firePointOrig;
	sf::RenderWindow* window;
	float fireTimer;
	bool fireOnce1 = false;
	bool fireOnce2 = false;
	bool fireOnce3 = false;
	bool fireOnce4 = false;
	string type;
	string weaponType;
	b2World* world;
	sf::Vector2f beamImpact;
	sf::Vector2f prevImpact;
	int timer;
	bool released;
	bool released2;
	bool overheated;
	int heatTimer;
	bool laserActive;

public:
	Turret(sf::Vector2f position, Ship & ship, string type ,string weaponType, sf::RenderWindow & window, b2World& World);
	void Update();
	void Draw(sf::RenderWindow & window);
	void Draw2(sf::RenderWindow & window);
	float to_positive_angle(float angle);
	void Move();
	float CurveAngle(float from, float to, float step);
	sf::Vector2f Slerp(sf::Vector2f from, sf::Vector2f to, float step);
	sf::Vector2f normalize(sf::Vector2f source);
	float degreeToRadian(float angle);
	float radiansToDegrees(float angle);
	float dotProduct(sf::Vector2f v1, sf::Vector2f v2);
	bool destroyed;
	float distance(sf::Vector2f, sf::Vector2f);
};

#endif

