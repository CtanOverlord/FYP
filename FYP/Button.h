#pragma once
#ifndef BUTTON_H
#define BUTTON_H

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

using namespace std;

class Button
{
private:

	sf::Texture UITexture;
	bool active;
	sf::Vector2f position;
	int type;
	string content;
	sf::Font font;

public:
	Button(sf::Vector2f position, bool active, string content, string text);
	Button();
	void Update();
	void Draw(sf::RenderWindow & window);
	bool clickedOn(sf::RenderWindow & window);
	sf::Text text;

	sf::Sprite UISprite;

};

#endif

