#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

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

#include <SFML/Audio.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

using namespace std;

class SoundManager
{
private:
	vector<sf::Sound*> sounds;
	sf::SoundBuffer missileLaunch;
	sf::SoundBuffer cannonFire;
	sf::SoundBuffer explosion1;
	sf::SoundBuffer explosion2;
	sf::SoundBuffer explosion3;
	sf::SoundBuffer explosion4;
	sf::SoundBuffer wreckExplosion;
	sf::SoundBuffer missileExplosion;
	sf::SoundBuffer thrusterSound;
	sf::SoundBuffer engineSound;
	sf::SoundBuffer laserSound;
	sf::SoundBuffer cloakOnSound;
	sf::SoundBuffer cloakOffSound;
	sf::SoundBuffer mineSound;
	sf::Sound engine;
	sf::Sound laser;
	sf::SoundBuffer thrustersSound;
	sf::Sound thrusters;
	sf::SoundBuffer shieldSound;
	sf::Sound shield;
	bool checkDestroyed;
	float speed;
	bool shieldsActive;
	int thrusterSpeed;
	bool laserActive;

public:

	static SoundManager* GetInstance();
	SoundManager();
	void Update();
	void CreateSound(sf::Vector2f position, float type);
	void DeleteExpired();
	void ShieldsOn();
	void ShieldsOff();
	void LaserOn();
	void LaserOff();
	void setShipPos(sf::Vector2f p);
	vector<sf::Music*> music;
};

#endif
