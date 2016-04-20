#pragma once
#ifndef BOUND_H
#define BOUND_H

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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Bound
{
private:

	sf::Sprite boundSprite;
	sf::Texture boundTexture;
	b2Body* boundBody;
	b2World* world;
	int type;
	float angle;

public:

	Bound(b2World& World, sf::Vector2f position, float rotation, int t);
	void Update();
	void Draw(sf::RenderWindow & window);
	void CreateBody();
	sf::Sprite getSprite();
	b2Body* getBody();
};

#endif


