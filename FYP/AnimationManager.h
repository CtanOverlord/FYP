#pragma once
#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

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

#include "AnimatedSprite.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class AnimationManager
{
private:
	vector<AnimatedSprite*> animations;
	vector<Animation*> animationSheets;
	sf::Texture explosionTexture;
	sf::Texture fireEffectTexture;
	Animation explosion;
	Animation fireEffect;
	sf::Clock frameClock;

public:

	AnimationManager();
	void Update();
	void Draw(sf::RenderWindow & window);
	void CreateAnimation(sf::Vector2f position, float type, float angle);
	void DeleteExpired();
};

#endif
