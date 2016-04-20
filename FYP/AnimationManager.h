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
#include "SoundManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class AnimationManager
{
private:
	vector<AnimatedSprite*> animations;
	vector<Animation*> animationSheets;
	vector<sf::Sprite*> burns;
	sf::Texture burnTexture;
	sf::Texture explosionTexture;
	sf::Texture largeExplosionTexture;
	sf::Texture smallExplosionTexture;
	sf::Texture smallExplosionDrainTexture;
	sf::Texture fireEffectTexture;
	sf::Texture fireEffectTexture2;
	sf::Texture smokeEffectTexture;
	sf::Texture smokeEffectSlugTexture;
	sf::Texture smokeEffectDrainTexture;
	sf::Texture zapTexture;
	Animation explosion;
	Animation largeExplosion;
	Animation smallExplosion;
	Animation smallDrainExplosion;
	Animation fireEffect;
	Animation fireEffect2;
	Animation smokeEffect;
	Animation smokeEffectDrain;
	Animation smokeEffectSlug;
	Animation zap;
	sf::Clock frameClock;
	bool checkDestroyed;

public:

	static AnimationManager* GetInstance();
	AnimationManager();
	void Update();
	void Draw(sf::RenderWindow & window);
	void Draw2(sf::RenderWindow & window);
	void Draw3(sf::RenderWindow & window);
	void CreateAnimation(sf::Vector2f position, float type, float angle);
	void DeleteExpired();
	void AddBurn(sf::Vector2f, sf::Vector2f);
};

#endif
