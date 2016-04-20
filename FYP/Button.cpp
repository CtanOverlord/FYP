#include "Button.h"

Button::Button()
{
}

Button::Button(sf::Vector2f p, bool a, string c, string t)
{
	position = p;
	active = a;
	content = c;

	if (content == "Button" || content == "Back")
	{
		if (!UITexture.loadFromFile(content + ".png"))
		{
			// error...
		}

		UITexture.setSmooth(true);

		UISprite.setTexture(UITexture);

		if (t == "Click to Continue")
		{
			UISprite.setScale(sf::Vector2f(1.0f, 0.5f));
		}
		else
		{
			UISprite.setScale(sf::Vector2f(0.5f, 0.5f));
		}

		UISprite.setPosition(position);

		UISprite.setOrigin(sf::Vector2f(UISprite.getLocalBounds().width / 2, UISprite.getLocalBounds().height / 2));

		UISprite.setColor(sf::Color(255, 255, 255, 255));

		// Load it from a file
		if (!font.loadFromFile("RAZEROBLIQUE.ttf"))
		{
			// error...
		}
		// Create a text which uses our font
		text.setFont(font);
		text.setCharacterSize(45);
		text.setStyle(sf::Text::Regular);
		text.setPosition(position);
		text.setString(t);
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height);
	}
	else
	{
		if (!UITexture.loadFromFile(content + ".png"))
		{
			// error...
		}

		UITexture.setSmooth(true);

		UISprite.setTexture(UITexture);

		if (t == "Click to Continue")
		{
			UISprite.setScale(sf::Vector2f(1.0f, 0.5f));
		}
		else
		{
			UISprite.setScale(sf::Vector2f(1.3f, 1.3f));
		}

		UISprite.setPosition(position);

		UISprite.setOrigin(sf::Vector2f(UISprite.getLocalBounds().width / 2, UISprite.getLocalBounds().height / 2));

		UISprite.setColor(sf::Color(255, 255, 255, 255));

		// Load it from a file
		if (!font.loadFromFile("RAZEROBLIQUE.ttf"))
		{
			// error...
		}
		// Create a text which uses our font
		text.setFont(font);
		text.setCharacterSize(30);
		text.setStyle(sf::Text::Regular);
		text.setPosition(sf::Vector2f(position.x, position.y + 130));
		text.setString(t);
		text.setOrigin(text.getLocalBounds().width / 2, 0);
	}
}

void Button::Update()
{
	
}

bool Button::clickedOn(sf::RenderWindow & window)
{
	//sf::Event event;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
	//while (window.pollEvent(event))
	//{
		//if (event.type == sf::Event::MouseButtonReleased)
		//{
			//if (event.mouseButton.button == sf::Mouse::Left)
			//{
				// transform the mouse position from window coordinates to world coordinates
				sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

				// retrieve the bounding box of the sprite
				sf::FloatRect bounds = UISprite.getGlobalBounds();

				// hit test
				if (bounds.contains(mouse))
				{
					return true;// mouse is on sprite!
				}
				else
				{
					return false;
				}
			}
	//}
}

void Button::Draw(sf::RenderWindow & window)
{
	window.draw(UISprite);

	if (content != "Back")
	{
		window.draw(text);
	}
}