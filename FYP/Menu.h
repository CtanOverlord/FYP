#pragma once
#ifndef MENU_H
#define MENU_H

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
#include "Button.h"
#include "ShipManager.h"
#include "Globals.h"
#include "SoundManager.h"

using namespace std;

class Menu
{
private:

	sf::Texture UITexture;
	sf::Texture BGTexture;
	sf::Texture BGSTexture;
	sf::Texture BGRTexture;
	sf::Texture BGITexture;
	sf::Texture BGETexture1;
	sf::Texture BGETexture2;
	sf::Vector2f initPos;
	int type;
	Button* play;
	Button* options;
	Button* quit;
	Button* ship1;
	Button* ship2;
	Button* ship3;
	Button* continueBT;
	Button* playBack;
	Button* selectBack;
	sf::Vector2f position;
	sf::Sprite UISprite;
	sf::Sprite BGSprite;
	sf::Sprite BGSSprite;
	sf::Sprite BGESprite1;
	sf::Sprite BGESprite2;
	sf::RenderWindow* Window;
	bool winnerBlue;

public:
	Menu(sf::RenderWindow & window);
	void Update();
	void Draw();
	void DrawIG();
	bool active;
	enum State {
		SPLASH,
		MAIN,
		OPTIONS,
		OPTIONSIG,
		GAME,
		INGAME,
		QUIT,
		SELECT,
		RESPAWN,
		ENDGAME,
	};
	State currentState;

	bool released;

	string shipType;

	sf::Sprite BGISprite;

	Button* playIG;
	Button* optionsIG;
	Button* quitIG;
	Button* optionsBack;
	sf::Sprite BGRSprite;
	Button* shipR1;
	Button* shipR2;
	Button* shipR3;

	void respawnState();
};

#endif

