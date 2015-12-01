#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Projectile
{
private:

	sf::Sprite projSprite;
	sf::Vector2f velocity;
	sf::Vector2f velocity2;
	sf::Texture projTexture;
	float speed;
	b2Body* projBody;
	b2World* world;
	sf::Transform transform;
	float angle;
	bool onlyOnce = false;
	float ttl;

public:
	
	Projectile(b2World& World, sf::Vector2f position, sf::Vector2f pos2, float angle);
	void Update();
	void Draw(sf::RenderWindow & window);
	void CreateBody();
	sf::Sprite getSprite();
	float getTTL();
	void setTTL(float);
	b2Body* getBody();
};

#endif
