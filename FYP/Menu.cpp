#include "Menu.h"

Menu::Menu(sf::RenderWindow & window)
{
	currentState = State::SPLASH;

	Window = &window;

	if (!UITexture.loadFromFile("menuBG4.png"))
	{
		// error...
	}

	UITexture.setSmooth(true);

	UISprite.setTexture(UITexture);

	UISprite.setScale(sf::Vector2f(1.0f, 1.0f));

	UISprite.setPosition(sf::Vector2f(0, 0));

	UISprite.setOrigin(sf::Vector2f(UISprite.getTextureRect().width / 2, UISprite.getTextureRect().height / 2));

	UISprite.setColor(sf::Color(255, 255, 255, 255));

	if (!BGSTexture.loadFromFile("menuBG5.png"))
	{
		// error...
	}

	BGSTexture.setSmooth(true);

	BGSSprite.setTexture(BGSTexture);

	BGSSprite.setScale(sf::Vector2f(1.0f, 1.0f));

	BGSSprite.setPosition(sf::Vector2f(0, 0));

	BGSSprite.setOrigin(sf::Vector2f(BGSSprite.getTextureRect().width / 2, BGSSprite.getTextureRect().height / 2));

	BGSSprite.setColor(sf::Color(255, 255, 255, 255));

	if (!BGTexture.loadFromFile("menuBG3.png"))
	{
		// error...
	}

	BGTexture.setSmooth(true);

	BGSprite.setTexture(BGTexture);

	BGSprite.setScale(sf::Vector2f(1.0f, 1.0f));

	BGSprite.setPosition(sf::Vector2f(0, 0));

	BGSprite.setOrigin(sf::Vector2f(BGSprite.getTextureRect().width / 2, BGSprite.getTextureRect().height / 2));

	BGSprite.setColor(sf::Color(255, 255, 255, 255));

	if (!BGITexture.loadFromFile("InGameBG.png"))
	{
		// error...
	}

	BGITexture.setSmooth(true);

	BGISprite.setTexture(BGITexture);

	BGISprite.setScale(sf::Vector2f(1.0f, 1.0f));

	BGISprite.setPosition(sf::Vector2f(0, 0));

	BGISprite.setOrigin(sf::Vector2f(BGISprite.getTextureRect().width / 2, BGISprite.getTextureRect().height / 2));

	BGISprite.setColor(sf::Color(255, 255, 255, 255));

	if (!BGRTexture.loadFromFile("InGameBGR.png"))
	{
		// error...
	}

	BGRTexture.setSmooth(true);

	BGRSprite.setTexture(BGRTexture);

	BGRSprite.setScale(sf::Vector2f(1.0f, 1.0f));

	BGRSprite.setPosition(sf::Vector2f(0, 0));

	BGRSprite.setOrigin(sf::Vector2f(BGRSprite.getTextureRect().width / 2, BGRSprite.getTextureRect().height / 2));

	BGRSprite.setColor(sf::Color(255, 255, 255, 255));


	if (!BGETexture1.loadFromFile("menuBG6.png"))
	{
		// error...
	}

	BGETexture1.setSmooth(true);

	BGESprite1.setTexture(BGETexture1);

	BGESprite1.setScale(sf::Vector2f(1.0f, 1.0f));

	BGESprite1.setPosition(sf::Vector2f(0, 0));

	BGESprite1.setOrigin(sf::Vector2f(BGESprite1.getTextureRect().width / 2, BGESprite1.getTextureRect().height / 2));

	BGESprite1.setColor(sf::Color(255, 255, 255, 255));


	if (!BGETexture2.loadFromFile("menuBG7.png"))
	{
		// error...
	}

	BGETexture2.setSmooth(true);

	BGESprite2.setTexture(BGETexture2);

	BGESprite2.setScale(sf::Vector2f(1.0f, 1.0f));

	BGESprite2.setPosition(sf::Vector2f(0, 0));

	BGESprite2.setOrigin(sf::Vector2f(BGESprite2.getTextureRect().width / 2, BGESprite2.getTextureRect().height / 2));

	BGESprite2.setColor(sf::Color(255, 255, 255, 255));


	play = new Button(sf::Vector2f(0, -200), true, "Button", "Play");

	options = new Button(sf::Vector2f(0, 0), true, "Button", "Options");

	quit = new Button(sf::Vector2f(0, 200), true, "Button", "Quit");

	playIG = new Button(sf::Vector2f(0, -100), true, "Button", "Continue");

	optionsIG = new Button(sf::Vector2f(0, 0), true, "Button", "Options");

	quitIG = new Button(sf::Vector2f(0, 100), true, "Button", "Quit");

	optionsBack = new Button(sf::Vector2f(-570, -290), true, "Back", "Options");

	selectBack = new Button(sf::Vector2f(-570, -290), true, "Back", "Select");

	continueBT = new Button(sf::Vector2f(0, 200), true, "Button", "Click to Continue");
	
	ship1 = new Button(sf::Vector2f(-400, 0), true, "ShipBT1", "Dreadnought");

	ship2 = new Button(sf::Vector2f(0, 0), true, "ShipBT2", "Frigate");

	ship3 = new Button(sf::Vector2f(400, 0), true, "ShipBT3", "Sniper");

	shipR1 = new Button(sf::Vector2f(-400, 0), true, "ShipBT1", "Dreadnought");

	shipR2 = new Button(sf::Vector2f(0, 0), true, "ShipBT2", "Frigate");

	shipR3 = new Button(sf::Vector2f(400, 0), true, "ShipBT3", "Sniper");

	released = true;
}

void Menu::respawnState()
{
	currentState = State::RESPAWN;
}

void Menu::Update()
{
	switch (currentState) {

	case(State::SPLASH) :
		if (continueBT->clickedOn(*Window) && released == true) {
			currentState = State::MAIN;
			released = false;
		}
		/*else if (checkAsteroids()) {
			currentState = State::AVOIDASTEROID;
		}
		else if (checkPowerUps()) {
			currentState = State::POWERUP;
		}*/
		break;

	case(State::MAIN) :
		if (play->clickedOn(*Window) == true && released == true) {
			currentState = State::SELECT;
			released = false;
		}
		else if (options->clickedOn(*Window) == true && released == true) {
			currentState = State::OPTIONS;
			released = false;
		}
		else if (quit->clickedOn(*Window) == true && released == true) {
			currentState = State::QUIT;
			released = false;
		}
		//avoid(v);
		//if (!checkAsteroids()) {
		//	currentState = State::SEARCH;
		//}
		break;

	case(State::OPTIONS) :
		if (optionsBack->clickedOn(*Window) == true && released == true) {
			currentState = State::MAIN;
			released = false;
		}
		break;
	case(State::OPTIONSIG) :
		if (optionsBack->clickedOn(*Window) == true && released == true) {
			currentState = State::INGAME;
			released = false;
		}
						 break;
	case(State::SELECT) :
		if (ship1->clickedOn(*Window) == true && released == true) {
			currentState = State::GAME;
			shipType = "Dreadnought";
			SoundManager::GetInstance()->music.at(0)->play();
			SoundManager::GetInstance()->music.at(1)->pause();
			released = false;
		}
		else if (ship2->clickedOn(*Window) == true && released == true) {
			currentState = State::GAME;
			shipType = "Frigate";
			SoundManager::GetInstance()->music.at(0)->play();
			SoundManager::GetInstance()->music.at(1)->pause();
			released = false;
		}
		else if (ship3->clickedOn(*Window) == true && released == true) {
			currentState = State::GAME;
			shipType = "Sniper";
			SoundManager::GetInstance()->music.at(0)->play();
			SoundManager::GetInstance()->music.at(1)->pause();
			released = false;
		}
		if (selectBack->clickedOn(*Window) == true && released == true) {
			currentState = State::MAIN;
			released = false;
		}
		break;
	case(State::GAME) :
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			currentState = State::INGAME;
			released = true;
		}
		if (Globals::GetInstance()->blueScore >= 1000)
		{
			currentState = State::ENDGAME;
			winnerBlue = true;
			released = true;
		}
		else if (Globals::GetInstance()->redScore >= 1000)
		{
			currentState = State::ENDGAME;
			winnerBlue = false;
			released = true;
		}
		break;
	case(State::INGAME) :
		if (playIG->clickedOn(*Window) == true && released == true) {
			currentState = State::GAME;
			released = false;
		}
		else if (optionsIG->clickedOn(*Window) == true && released == true) {
			currentState = State::OPTIONSIG;
			released = false;
		}
		else if (quitIG->clickedOn(*Window) == true && released == true) {
			currentState = State::QUIT;
			released = false;
		}
		break;
	case(State::RESPAWN) :
		if (shipR1->clickedOn(*Window) == true && released == true) {
			currentState = State::GAME;
			ShipManager::GetInstance()->respawnPlayer("Dreadnought");
			released = false;
		}
		else if (shipR2->clickedOn(*Window) == true && released == true) {
			currentState = State::GAME;
			ShipManager::GetInstance()->respawnPlayer("Frigate");
			released = false;
		}
		else if (shipR3->clickedOn(*Window) == true && released == true) {
			currentState = State::GAME;
			ShipManager::GetInstance()->respawnPlayer("Sniper");
			released = false;
		}
	case(State::ENDGAME) :
		if (quit->clickedOn(*Window) == true && released == true) {
			currentState = State::QUIT;
			released = false;
		}
		break;
	}
}

void Menu::Draw()
{
	switch (currentState) {

	case(State::SPLASH) :
		Window->draw(UISprite);
		continueBT->Draw(*Window);
		break;

	case(State::MAIN) :
		Window->draw(BGSprite);
		play->Draw(*Window);
		options->Draw(*Window);
		quit->Draw(*Window);
		break;

	case(State::OPTIONS) :
		Window->draw(BGSprite);
		optionsBack->Draw(*Window);
		break;

	case(State::OPTIONSIG) :
		Window->draw(BGISprite);
		optionsBack->Draw(*Window);
		break;

	case(State::SELECT) :
		Window->draw(BGSSprite);
		ship1->Draw(*Window);
		ship2->Draw(*Window);
		ship3->Draw(*Window);
		selectBack->Draw(*Window);
		break;

	case(State::GAME) :

		break;
	case(State::INGAME) :
		Window->draw(BGISprite);
		playIG->Draw(*Window);
		optionsIG->Draw(*Window);
		quitIG->Draw(*Window);

		break;
	case(State::RESPAWN) :
		Window->draw(BGRSprite);
		shipR1->Draw(*Window);
		shipR2->Draw(*Window);
		shipR3->Draw(*Window);
		break;
	case(State::ENDGAME) :
		if (winnerBlue == true)
		{
			Window->draw(BGESprite1);
		}
		else
		{
			Window->draw(BGESprite2);
		}
		quit->Draw(*Window);
		break;
	}
}