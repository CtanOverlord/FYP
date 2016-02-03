#pragma once
#ifndef THRUSTER_H
#define THRUSTER_H

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
#include "SoundManager.h"

using namespace std;

class Thruster
{
private:

	sf::Texture turretTexture;
	float speed;

public:
	Thruster(sf::Vector2f position, float angle, bool active, string ori);
	void Update();
	void Draw(sf::RenderWindow & window);
	bool active;
	sf::Vector2f position;
	sf::Sprite turretSprite;
	string ori;
};

#endif
