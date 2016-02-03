#pragma once
#ifndef WRECK_H
#define WRECK_H

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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Wreck
{
private:

	sf::Sprite wreckSprite;
	sf::Vector2f velocity;
	sf::Vector2f velocity2;
	sf::Texture wreckTexture;
	float speed;
	b2Body* wreckBody;
	b2World* world;
	sf::Transform transform;
	float angle;
	bool onlyOnce = false;
	float ttl;

public:
	
	Wreck(b2World& World, sf::Vector2f position, float angle, int type);
	void Update();
	void Draw(sf::RenderWindow & window);
	void CreateBody();
	sf::Sprite getSprite();
	float getTTL();
	void setTTL(float);
	b2Body* getBody();
};

#endif
