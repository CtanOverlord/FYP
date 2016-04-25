#pragma once
#ifndef DREADNOUGHT_H
#define DREADNOUGHT_H

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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Level.h"

#include "WreckManager.h"

#include "RayCastCallBackCustom.h"

using namespace std;

class Turret;

class Level;

class CapPoint;

class Dreadnought : public Ship
{
private:
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

	int fuelTimer;

public:

	Dreadnought(b2World& World, sf::Vector2f position, string type, sf::RenderWindow & window);
	Dreadnought();
	void Update();
	void playerUpdate();
	void enemyUpdate();
	void allyUpdate();
	void Draw(sf::RenderWindow & window);
	void CreateBody();
	void setHealth(float h);
	vector<sf::Vector2f*> wreckPoint;
	void updateMissilePoints();
	void updateWreckPoints();
	void updateThrusterPoints();
	void updateBoosterPoints();
	void updateRayPoints();
	void DeleteAll();
	void chooseNextAction();
	void chooseNextActionTest();
	void chooseNextActionAlly();
	void AbilityOne();
	void AbilityTwo();
	void setFuel(float f);
};

#endif
