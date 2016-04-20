#include "SoundManager.h"

static bool instanceFlag = false;
static SoundManager* instance = NULL;

SoundManager::SoundManager()
{
	checkDestroyed = false;

	if (!missileLaunch.loadFromFile("missileLaunch.ogg"))
	{

	}

	if (!cannonFire.loadFromFile("cannon.ogg"))
	{

	}

	if (!explosion1.loadFromFile("plasmaExplosion.ogg"))
	{

	}
	if (!explosion2.loadFromFile("explosion2.ogg"))
	{

	}
	if (!explosion3.loadFromFile("explosion5.ogg"))
	{

	}
	if (!explosion4.loadFromFile("explosion7.ogg"))
	{

	}
	if (!wreckExplosion.loadFromFile("wreckExplosion2.ogg"))
	{

	}
	if (!missileExplosion.loadFromFile("missileExplosion2.ogg"))
	{

	}
	if (!thrusterSound.loadFromFile("thruster4.ogg"))
	{

	}
	if (!engineSound.loadFromFile("engine5.ogg"))
	{

	}
	if (shieldSound.loadFromFile("shields2.ogg"))
	{

	}
	if (!thrustersSound.loadFromFile("engine5.ogg"))
	{

	}
	if (!laserSound.loadFromFile("laser.ogg"))
	{

	}
	if (!cloakOnSound.loadFromFile("cloakOn.ogg"))
	{

	}
	if (!cloakOffSound.loadFromFile("cloakOff.ogg"))
	{

	}
	if (!mineSound.loadFromFile("launchMine.ogg"))
	{

	}


	engine.setBuffer(engineSound);
	engine.play();
	//sound->setPosition(sf::Vector3f(position.x, position.y, 0));
	engine.setLoop(true);
	engine.setVolume(0);
	engine.setRelativeToListener(false);
	engine.setAttenuation(20);
	engine.setMinDistance(1000);
	engine.setPitch(1.5);

	thrusters.setBuffer(engineSound);
	thrusters.play();
	//sound->setPosition(sf::Vector3f(position.x, position.y, 0));
	thrusters.setLoop(true);
	thrusters.setVolume(0);
	thrusters.setRelativeToListener(false);
	thrusters.setAttenuation(20);
	thrusters.setMinDistance(1000);
	thrusters.setPitch(1.2);

	shield.setBuffer(shieldSound);
	shield.pause();
	//sound->setPosition(sf::Vector3f(position.x, position.y, 0));
	shield.setLoop(true);
	shield.setVolume(70);
	shield.setRelativeToListener(false);
	shield.setAttenuation(20);
	shield.setMinDistance(1000);
	shield.setPitch(0.7);

	laser.setBuffer(laserSound);
	laser.pause();
	//sound->setPosition(sf::Vector3f(position.x, position.y, 0));
	laser.setLoop(true);
	laser.setVolume(40);
	laser.setPitch(1.1);

	music.push_back(new sf::Music());

	if (!music.at(0)->openFromFile("background2.ogg"))
	{
		// Error...
	}

	music.at(0)->setLoop(true);

	music.at(0)->setVolume(20);

	//music.at(0)->play();

	music.push_back(new sf::Music());

	if (!music.at(1)->openFromFile("background1.ogg"))
	{
		// Error...
	}

	music.at(1)->setLoop(true);

	music.at(1)->setVolume(20);

	music.at(1)->play();

	speed = 0;

	shieldsActive = false;

	thrusterSpeed = 0;

	srand(time(NULL));
}

SoundManager * SoundManager::GetInstance()
{
	if (!instanceFlag) {
		instance = new SoundManager();
		instanceFlag = true;
	}
	return instance;
}

void SoundManager::setShipPos(sf::Vector2f p)
{
	sf::Listener::setPosition(sf::Vector3f(p.x, 0, p.y));
	engine.setPosition(sf::Vector3f(p.x, 0, p.y));
	thrusters.setPosition(sf::Vector3f(p.x, 0, p.y));
	shield.setPosition(sf::Vector3f(p.x, 0, p.y));
}

void SoundManager::Update()
{
	DeleteExpired();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (speed < 70)
		{
			speed += 0.7f;
		}
	}
	else
	{
		if (speed > 0.01f)
		{
			speed -= 1.00f;
		}
		//boosterSprite.setColor(sf::Color(255, 255, 255, 0));
	}
	engine.setVolume(speed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (thrusterSpeed < 100)
		{
			thrusterSpeed += 2.00f;
		}
	}
	else
	{
		if (thrusterSpeed > 0.01f)
		{
			thrusterSpeed -= 2.00f;
		}
		//boosterSprite.setColor(sf::Color(255, 255, 255, 0));
	}

	thrusters.setVolume(thrusterSpeed);

	if (shieldsActive == false)
	{
		if (shield.getVolume() > 0)
		{
			shield.setVolume(shield.getVolume() - 1);
		}
		if (shield.getVolume() <= 0)
		{
			shield.pause();
		}
	}
	else if (shieldsActive == true)
	{
		if (shield.getVolume() < 40)
		{
			shield.setVolume(shield.getVolume() + 1);
		}
	}

	if (laserActive == false)
	{
		if (laser.getVolume() > 0)
		{
			laser.setVolume(laser.getVolume() - 2);
		}
		if (laser.getVolume() <= 5)
		{
			laser.pause();
		}
	}
	else if (laserActive == true)
	{
		if (laser.getVolume() < 20)
		{
			laser.setVolume(laser.getVolume() + 2);
		}
	}
}

void SoundManager::CreateSound(sf::Vector2f position, float type)
{
	if (type == 1)
	{
		sf::Sound* sound = new sf::Sound;
		sound->setBuffer(missileLaunch);
		sound->play();
		sound->setPosition(sf::Vector3f(position.x, 0, position.y));
		sound->setLoop(false);
		sound->setVolume(30);
		float temp = rand() % 2 + 1;
		temp = temp / 10;
		sound->setPitch(1.4 - temp);
		sound->setRelativeToListener(false);
		sound->setAttenuation(20);
		sound->setMinDistance(1000);
		sounds.push_back(sound);
	}
	if (type == 2)
	{
		sf::Sound* sound = new sf::Sound;
		sound->setBuffer(cannonFire);
		sound->play();
		sound->setPosition(sf::Vector3f(position.x, 0, position.y));
		sound->setLoop(false);
		sound->setVolume(6);
		float temp = rand() % 2 + 1;
		temp = temp / 10;
		sound->setPitch(1 - temp);
		sound->setRelativeToListener(false);;
		sound->setAttenuation(20);
		sound->setMinDistance(1000);
		sounds.push_back(sound);
	}
	if (type == 3)
	{
		sf::Sound* sound = new sf::Sound;
		sound->setBuffer(explosion3);
		sound->play();
		sound->setPosition(sf::Vector3f(position.x, 0, position.y));
		sound->setLoop(false);
		sound->setVolume(90);
		float temp = rand() % 2 + 1;
		temp = temp / 10;
		sound->setPitch(1.4 - temp);
		sound->setRelativeToListener(false);
		sound->setAttenuation(20);
		sound->setMinDistance(1000);
		sounds.push_back(sound);
	}
	if (type == 4)
	{
		sf::Sound* sound = new sf::Sound;
		sound->setBuffer(explosion4);
		sound->play();
		sound->setPosition(sf::Vector3f(position.x, 0, position.y));
		sound->setLoop(false);
		sound->setVolume(100);
		float temp = rand() % 2 + 1;
		temp = temp / 10;
		sound->setPitch(1.4);
		sound->setRelativeToListener(false);
		sound->setAttenuation(20);
		sound->setMinDistance(1000);
		sounds.push_back(sound);
	}
	if (type == 5)
	{
		sf::Sound* sound = new sf::Sound;
		sound->setBuffer(wreckExplosion);
		sound->play();
		sound->setPosition(sf::Vector3f(position.x, 0, position.y));
		sound->setLoop(false);
		sound->setVolume(10);
		float temp = rand() % 2 + 1;
		temp = temp / 10;
		sound->setPitch(1 - temp);
		sound->setRelativeToListener(false);
		sound->setAttenuation(20);
		sound->setMinDistance(1000);
		sounds.push_back(sound);
	}
	if (type == 6)
	{
		sf::Sound* sound = new sf::Sound;
		sound->setBuffer(missileExplosion);
		sound->play();
		sound->setPosition(sf::Vector3f(position.x, 0, position.y));
		sound->setLoop(false);
		sound->setVolume(50);
		float temp = rand() % 2 + 1;
		temp = temp / 10;
		sound->setPitch(1.2 - temp);
		sound->setRelativeToListener(false);
		sound->setAttenuation(20);
		sound->setMinDistance(1000);
		sounds.push_back(sound);
	}
	if (type == 7)
	{
		sf::Sound* sound = new sf::Sound;
		sound->setBuffer(explosion1);
		sound->play();
		float temp1 = rand() % 1 + 1;
		sound->setPlayingOffset(sf::seconds(temp1));
		sound->setPosition(sf::Vector3f(position.x, 0, position.y));
		sound->setLoop(false);
		sound->setVolume(80);
		float temp = rand() % 2 + 1;
		temp = temp / 10;
		sound->setPitch(1.4 - temp);
		sound->setRelativeToListener(false);
		sound->setAttenuation(20);
		sound->setMinDistance(1000);
		sounds.push_back(sound);
	}
	if (type == 8)
	{
		sf::Sound* sound = new sf::Sound;
		sound->setBuffer(thrusterSound);
		sound->play();
		float temp1 = rand() % 1 + 1;
		sound->setPlayingOffset(sf::seconds(temp1));
		sound->setPosition(sf::Vector3f(position.x, 0, position.y));
		sound->setLoop(false);
		sound->setVolume(6);
		float temp = rand() % 2 + 1;
		temp = temp / 10;
		sound->setPitch(1.4 - temp);
		sound->setRelativeToListener(false);
		sound->setAttenuation(20);
		sound->setMinDistance(1000);
		sounds.push_back(sound);
	}
	if (type == 9)
	{
		sf::Sound* sound = new sf::Sound;
		sound->setBuffer(cloakOnSound);
		sound->play();
		float temp1 = rand() % 1 + 1;
		sound->setPlayingOffset(sf::seconds(temp1));
		sound->setPosition(sf::Vector3f(position.x, 0, position.y));
		sound->setLoop(false);
		sound->setVolume(100);
		float temp = rand() % 2 + 1;
		temp = temp / 10;
		sound->setPitch(0.8 - temp);
		sound->setRelativeToListener(false);
		sound->setAttenuation(20);
		sound->setMinDistance(1000);
		sounds.push_back(sound);
	}
	if (type == 10)
	{
		sf::Sound* sound = new sf::Sound;
		sound->setBuffer(cloakOffSound);
		sound->play();
		float temp1 = rand() % 1 + 1;
		sound->setPlayingOffset(sf::seconds(temp1));
		sound->setPosition(sf::Vector3f(position.x, 0, position.y));
		sound->setLoop(false);
		sound->setVolume(100);
		float temp = rand() % 2 + 1;
		temp = temp / 10;
		sound->setPitch(0.8 - temp);
		sound->setRelativeToListener(false);
		sound->setAttenuation(20);
		sound->setMinDistance(1000);
		sounds.push_back(sound);
	}
	if (type == 11)
	{
		sf::Sound* sound = new sf::Sound;
		sound->setBuffer(mineSound);
		sound->play();
		float temp1 = rand() % 1 + 1;
		sound->setPlayingOffset(sf::seconds(temp1));
		sound->setPosition(sf::Vector3f(position.x, 0, position.y));
		sound->setLoop(false);
		sound->setVolume(20);
		float temp = rand() % 2 + 1;
		temp = temp / 10;
		sound->setPitch(0.8 - temp);
		sound->setRelativeToListener(false);
		sound->setAttenuation(20);
		sound->setMinDistance(1000);
		sounds.push_back(sound);
	}
}

void SoundManager::ShieldsOn()
{
	shield.play();
	shieldsActive = true;
}

void SoundManager::ShieldsOff()
{
	shieldsActive = false;
}

void SoundManager::LaserOn()
{
	laser.play();
	laserActive = true;
}

void SoundManager::LaserOff()
{
	laserActive = false;
}

void SoundManager::DeleteExpired()
{

	for (int i = 0; i < sounds.size(); i++)
	{
		if (sounds[i]->getStatus() == sf::Sound::Stopped)
		{
			delete sounds.at(i);
			sounds.erase(sounds.begin() + i);
			if (i != 0)
			{
				i--;
			}
		}
	}

	/*vector<sf::Sound*>::iterator iter;
	vector<sf::Sound*>::iterator endIter;

	iter = sounds.begin();
	endIter = sounds.end();

	for (; iter != endIter; ++iter)
	{
		if ((*iter)->getStatus() == sf::Sound::Stopped)
		{
			if (sounds.size() == 1)
			{
				delete sounds.at(0);
				sounds.clear();
				break;
			}
			else
			{
				delete (*iter);
				iter = sounds.erase(iter);
				iter = sounds.begin();
				endIter = sounds.end();
			}
		}
	}*/

	checkDestroyed = false;
}