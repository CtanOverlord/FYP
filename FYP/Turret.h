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
#include<Ship.h>
#include<ProjectileManager.h>
#include "SoundManager.h"

using namespace std;

class Ship;

class Turret
{
private:

	sf::Sprite turretSprite;
	sf::Texture turretTexture;
	sf::Vector2f position;
	sf::Vector2f position2;
	sf::Vector2f direction;
	sf::Vector2f firePoint1;
	sf::Vector2f firePoint2;
	sf::Vector2f firePoint3;
	sf::Vector2f firePoint4;
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

public:
	Turret(sf::Vector2f position, Ship & ship, string type, sf::RenderWindow & window);
	void Update();
	void Draw(sf::RenderWindow & window);
	float to_positive_angle(float angle);
	void Move();
	float CurveAngle(float from, float to, float step);
	sf::Vector2f Slerp(sf::Vector2f from, sf::Vector2f to, float step);
	sf::Vector2f normalize(sf::Vector2f source);
	float degreeToRadian(float angle);
	float radiansToDegrees(float angle);
	float dotProduct(sf::Vector2f v1, sf::Vector2f v2);
};

#endif

