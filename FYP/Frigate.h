#pragma once
#ifndef FRIGATE_H
#define FRIGATE_H

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

#include "Ship.h"

#include "WreckManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Level.h"

#include "RayCastCallBackCustom.h"

using namespace std;

class Turret;

class Level;

class CapPoint;

class Frigate : public Ship
{
private:

	bool speedBoost;

	// AI Variables

	enum TurnState {
		LEFT,
		RIGHT,
		SLEFT,
		SRIGHT,
		FOLLOW,
		NONE
	};

	enum MoveState {
		FORWARD,
		BACKWARDS,
		NONE2
	};

	enum FireState {
		FIRING,
		NONE3
	};

	TurnState currentTState;
	MoveState currentMState;
	FireState currentFState;

	TurnState previousTState;
	MoveState previousMState;

	RayCastCallBackCustom* rayCallBackF1;
	RayCastCallBackCustom* rayCallBackF2;
	RayCastCallBackCustom* rayCallBackL1;
	RayCastCallBackCustom* rayCallBackL2;
	RayCastCallBackCustom* rayCallBackR1;
	RayCastCallBackCustom* rayCallBackR2;

	vector<sf::Vector2f*> rayPoints;
	vector<sf::Vector2f*> rayPointOrig;

	vector<sf::Vector2f*> rayEndPoints;
	vector<sf::Vector2f*> rayEndPointOrig;

	bool rayCollision;

	float desiredAngle;

	sf::Vector2f followPoint;

	CapPoint* targetCapPoint;

	int chooseTimer;

	Ship* targetShip;
public:

	Frigate(b2World& World, sf::Vector2f position, string type, sf::RenderWindow & window);
	Frigate();
	sf::Texture boosterTexture2;
	sf::Sprite boosterSprite2;
	sf::Sprite boosterSprite3;
	sf::Vector2f boosterPoint2;
	sf::Vector2f boosterPoint3;
	void Update();
	void Draw(sf::RenderWindow & window);
	void CreateBody();
	vector<sf::Vector2f*> wreckPoint;
	void updateMissilePoints();
	void updateWreckPoints();
	void updateThrusterPoints();
	void updateBoosterPoints();
	void DeleteAll();
	void chooseNextAction();
	void chooseNextActionAlly();
	void AbilityOne();
	void AbilityTwo();
	void updateRayPoints();
	void playerUpdate();
	void enemyUpdate();
};

#endif
