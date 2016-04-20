#pragma once
#ifndef UIELEMENT_H
#define UIELEMENT_H

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
#include "ShipManager.h"
#include "Globals.h"

using namespace std;

class UIElement
{
private:

	sf::Texture UITexture;
	sf::Texture UIAltTexture;
	sf::Vector2f initPos;
	int type;
	sf::Font font;

public:
	UIElement(sf::Vector2f position, float angle, bool active, int type);
	UIElement();
	void Update();
	void Draw(sf::RenderWindow & window);
	bool active;
	sf::Vector2f position;
	sf::Sprite UISprite;
	sf::Text blueText;
	sf::Text redText;
};

#endif
