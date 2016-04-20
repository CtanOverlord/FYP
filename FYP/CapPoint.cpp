#include "CapPoint.h"

static const float SCALE = 30.f;

CapPoint::CapPoint(b2World& World, sf::Vector2f position)
{
	if (!capTexture1.loadFromFile("CapturePointOff.png"))
	{

	}
	if (!capTexture2.loadFromFile("CapturePointBlue.png"))
	{

	}
	if (!capTexture3.loadFromFile("CapturePointRed.png"))
	{

	}
	if (!capZoneTexture.loadFromFile("CapZone.png"))
	{

	}
	if (!capZoneTexture2.loadFromFile("CapZone2.png"))
	{

	}
	if (!capZoneTexture3.loadFromFile("CapZone3.png"))
	{

	}
	if (!capAreaTexture.loadFromFile("CapArea.png"))
	{

	}
	if (!capAreaTexture2.loadFromFile("CapArea2.png"))
	{

	}
	if (!capAreaTexture3.loadFromFile("CapArea3.png"))
	{

	}

	capTexture1.setSmooth(true);

	capSprite.setTexture(capTexture1);

	capSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	capSprite.setPosition((position));

	capSprite.setOrigin(sf::Vector2f(134, 132));


	capTexture2.setSmooth(true);

	capSprite2.setTexture(capTexture2);

	capSprite2.setScale(sf::Vector2f(0.5f, 0.5f));

	capSprite2.setPosition((position));

	capSprite2.setOrigin(sf::Vector2f(134, 132));


	capTexture3.setSmooth(true);

	capSprite3.setTexture(capTexture3);

	capSprite3.setScale(sf::Vector2f(0.5f, 0.5f));

	capSprite3.setPosition((position));

	capSprite3.setOrigin(sf::Vector2f(134, 132));


	capZoneTexture.setSmooth(true);

	capZoneSprite.setTexture(capZoneTexture);

	capZoneSprite.setScale(sf::Vector2f(1.0f, 1.0f));

	capZoneSprite.setPosition((position));

	capZoneSprite.setOrigin(sf::Vector2f(375, 375));


	capZoneTexture2.setSmooth(true);

	capZoneSprite2.setTexture(capZoneTexture2);

	capZoneSprite2.setScale(sf::Vector2f(1.0f, 1.0f));

	capZoneSprite2.setPosition((position));

	capZoneSprite2.setOrigin(sf::Vector2f(375, 375));


	capZoneTexture3.setSmooth(true);

	capZoneSprite3.setTexture(capZoneTexture3);

	capZoneSprite3.setScale(sf::Vector2f(1.0f, 1.0f));

	capZoneSprite3.setPosition((position));

	capZoneSprite3.setOrigin(sf::Vector2f(375, 375));


	capAreaTexture.setSmooth(true);

	capAreaSprite.setTexture(capAreaTexture);

	capAreaSprite.setScale(sf::Vector2f(1.0f, 1.0f));

	capAreaSprite.setPosition((position));

	capAreaSprite.setOrigin(sf::Vector2f(375, 375));


	capAreaTexture2.setSmooth(true);

	capAreaSprite2.setTexture(capAreaTexture2);

	capAreaSprite2.setScale(sf::Vector2f(1.0f, 1.0f));

	capAreaSprite2.setPosition((position));

	capAreaSprite2.setOrigin(sf::Vector2f(375, 375));


	capAreaTexture3.setSmooth(true);

	capAreaSprite3.setTexture(capAreaTexture3);

	capAreaSprite3.setScale(sf::Vector2f(1.0f, 1.0f));

	capAreaSprite3.setPosition((position));

	capAreaSprite3.setOrigin(sf::Vector2f(375, 375));

	world = &World;

	CreateBody();

	nuetralCount = 1000;
	blueCount = 0;
	redCount = 0;

	rotSpeed = 1;

	rotSpeed2 = 0.5f;

	contested = false;

	owner = "Nuetral";
}

void CapPoint::Update()
{
	capSprite.setPosition(capBody->GetPosition().x * SCALE, capBody->GetPosition().y * SCALE);
	capSprite2.setPosition(capBody->GetPosition().x * SCALE, capBody->GetPosition().y * SCALE);
	capSprite3.setPosition(capBody->GetPosition().x * SCALE, capBody->GetPosition().y * SCALE);
	//capSprite.setRotation(capBody->GetAngle() * (180.0f / b2_pi));

	capZoneSprite.setPosition(capZoneBody->GetPosition().x * SCALE, capZoneBody->GetPosition().y * SCALE);
	capZoneSprite.setRotation(capZoneSprite.getRotation() + rotSpeed2);

	capZoneSprite2.setPosition(capZoneBody->GetPosition().x * SCALE, capZoneBody->GetPosition().y * SCALE);
	capZoneSprite2.setRotation(capZoneSprite2.getRotation() - rotSpeed2);

	capZoneSprite3.setPosition(capZoneBody->GetPosition().x * SCALE, capZoneBody->GetPosition().y * SCALE);
	capZoneSprite3.setRotation(capZoneSprite3.getRotation() + rotSpeed2);

	capAreaSprite.setPosition(capZoneBody->GetPosition().x * SCALE, capZoneBody->GetPosition().y * SCALE);

	capAreaSprite.setScale(sf::Vector2f(1.0f * (nuetralCount / 1000), 1.0f * (nuetralCount / 1000)));

	capAreaSprite2.setPosition(capZoneBody->GetPosition().x * SCALE, capZoneBody->GetPosition().y * SCALE);

	capAreaSprite2.setScale(sf::Vector2f(1.0f * (blueCount / 1000), 1.0f * (blueCount / 1000)));

	capAreaSprite3.setPosition(capZoneBody->GetPosition().x * SCALE, capZoneBody->GetPosition().y * SCALE);

	capAreaSprite3.setScale(sf::Vector2f(1.0f * (redCount / 1000), 1.0f * (redCount / 1000)));

	contested = false;

	occupants.clear();

	for (int i = 0; i < ShipManager::GetInstance()->ships.size(); i++)
	{
		sf::Vector2f tempPoint = ShipManager::GetInstance()->ships.at(i)->shipSprite.getPosition();

		if (distance(tempPoint, capAreaSprite.getPosition()) < 375)
		{
			if (ShipManager::GetInstance()->ships.at(i)->type == "enemy")
			{
				occupants.push_back("Red");
			}
			else if (ShipManager::GetInstance()->ships.at(i)->type == "player" || ShipManager::GetInstance()->ships.at(i)->type == "ally")
			{
				occupants.push_back("Blue");
			}
		}
	}

	reds = 0;

	blues = 0;

	string tempOccupanant;

	if (occupants.size() > 0)
	{
		tempOccupanant = occupants.at(0);
	}

	if (occupants.size() == 0)
	{
		if (owner != "Red" && redCount > 0)
		{
			redCount -= 2;
		}
		else if (owner != "Blue" && blueCount > 0)
		{
			blueCount -= 2;
		}
		else if (owner == "Nuetral" && nuetralCount < 1000)
		{
			nuetralCount += 4;
		}
		if (owner != "Blue" && blueCount > 0)
		{
			blueCount -= 2;
		}
		else if (owner == "Red" && redCount < 1000)
		{
			redCount += 4;
		}
		if (owner != "Red" && redCount > 0)
		{
			redCount -= 2;
		}
		else if (owner == "Blue" && blueCount < 1000)
		{
			blueCount += 4;
		}
	}

	for (int i = 0; i < occupants.size(); i++)
	{
		if (tempOccupanant != occupants.at(i))
		{
			contested = true;
		}
	}

	if (contested == false)
	{
		for (int i = 0; i < occupants.size(); i++)
		{
			if (owner == "Nuetral")
			{
				if (nuetralCount > 0)
				{
					nuetralCount -= 2;
				}
				if (nuetralCount <= 0)
				{
					if (occupants.at(i) == "Red")
					{
						redCount += 2;
					}
					else if (occupants.at(i) == "Blue")
					{
						blueCount += 2;
					}
				}
				if (redCount >= 1000)
				{
					owner = "Red";
				}
				else if (blueCount >= 1000)
				{
					owner = "Blue";
				}
			}
			else if (owner == "Red" && occupants.at(i) != "Red")
			{
				if (redCount > 0)
				{
					redCount -= 2;
				}
				if (redCount <= 0)
				{
					blueCount += 2;
				}
				if (blueCount >= 1000)
				{
					owner = "Blue";
				}
			}
			else if (owner == "Blue" && occupants.at(i) != "Blue")
			{
				if (blueCount > 0)
				{
					blueCount -= 2;
				}
				if (blueCount <= 0)
				{
					redCount += 2;
				}
				if (redCount >= 1000)
				{
					owner = "Red";
				}
			}
		}
	}

	if (owner == "Nuetral")
	{

	}
	if (owner == "Blue")
	{
		Globals::GetInstance()->blueScore += 0.1;
		capSprite2.setRotation(capSprite2.getRotation() + rotSpeed);
		capSprite3.setRotation(capSprite3.getRotation() + rotSpeed);
	}
	if (owner == "Red")
	{
		Globals::GetInstance()->redScore += 0.1;
		capSprite3.setRotation(capSprite3.getRotation() - rotSpeed);
		capSprite2.setRotation(capSprite2.getRotation() - rotSpeed);
	}
}

float CapPoint::distance(sf::Vector2f d1, sf::Vector2f d2)
{
	float d = sqrt(((d1.x - d2.x) * (d1.x - d2.x)) + ((d1.y - d2.y) * (d1.y - d2.y)));

	return d;
}

void CapPoint::addOccupant(string o)
{
	occupants.push_back(o);
}

void CapPoint::removeOccupant(string o)
{
	vector<string>::iterator iter;
	vector<string>::iterator endIter;

	iter = occupants.begin();
	endIter = occupants.end();

	for (; iter != endIter; ++iter)
	{
		if ((*iter) == o)
		{
			if (occupants.size() == 1)
			{
				occupants.clear();
				break;
			}
			else
			{
				iter = occupants.erase(iter);
				iter = occupants.begin();
				endIter = occupants.end();
			}
		}
	}
}

void CapPoint::Capture(string ali)
{
	if (ali != owner)
	{
		if (owner == "Nuetral")
		{
			if (nuetralCount >= 0)
			{
				nuetralCount -= 2;
			}
			if (ali == "Blue" && nuetralCount <= 0 && redCount <= 0)
			{
				if (blueCount < 1000)
				{
					blueCount += 2;
				}
				if (blueCount >= 1000)
				{
					owner = ali;
					blueCount == 1000;
				}
			}
			if (ali == "Red" && nuetralCount <= 0 && blueCount <= 0)
			{
				if (redCount < 1000)
				{
					redCount += 2;
				}
				if (redCount >= 1000)
				{
					owner = ali;
					redCount == 1000;
				}
			}
		}
		else if (owner == "Blue")
		{
			if (blueCount >= 0)
			{
				blueCount -= 2;
			}
			if (ali == "Red" && blueCount <= 0 && redCount <= 0)
			{
				if (redCount < 1000)
				{
					redCount += 2;
				}
				if (redCount >= 1000)
				{
					owner = ali;
					redCount == 1000;
				}
			}
		}
		else if (owner == "Red")
		{
			if (redCount >= 0)
			{
				redCount -= 2;
			}
			if (ali == "Blue" && redCount <= 0 && blueCount <= 0)
			{
				if (blueCount < 1000)
				{
					blueCount += 2;
				}
				if (blueCount >= 1000)
				{
					owner = ali;
					blueCount == 1000;
				}
			}
		}
	}
}

void CapPoint::Draw(sf::RenderWindow & window)
{
	if (owner == "Nuetral")
	{
		window.draw(capAreaSprite);
		window.draw(capAreaSprite2);
		window.draw(capAreaSprite3);
		window.draw(capSprite);
		window.draw(capZoneSprite);
	}
	else if (owner == "Blue")
	{
		window.draw(capAreaSprite);
		window.draw(capAreaSprite2);
		window.draw(capAreaSprite3);
		window.draw(capSprite2);
		window.draw(capZoneSprite2);
	}
	else if (owner == "Red")
	{
		window.draw(capAreaSprite);
		window.draw(capAreaSprite2);
		window.draw(capAreaSprite3);
		window.draw(capSprite3);
		window.draw(capZoneSprite3);
	}
}

sf::Sprite CapPoint::getSprite()
{
	return capSprite;
}

b2Body* CapPoint::getBody()
{
	return capBody;
}

void CapPoint::CreateBody()
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(capSprite.getPosition().x / SCALE, capSprite.getPosition().y / SCALE);
	BodyDef.type = b2_staticBody;
	BodyDef.userData = this;
	b2Body* Body = world->CreateBody(&BodyDef);
	Body->SetFixedRotation(false);
	Body->SetSleepingAllowed(false);

	//b2PolygonShape Shape;
	//Shape.SetAsBox(((capSprite.getTextureRect().width *capSprite.getScale().x) / 2) / SCALE, ((capSprite.getTextureRect().height * capSprite.getScale().x) / 2) / SCALE);
	b2CircleShape Shape;
	Shape.m_radius = (capSprite.getLocalBounds().width / 4) / SCALE;
	//Shape.SetAsBox((5.5 / 2) / SCALE, (22 / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.0f;
	FixtureDef.friction = 0.0f;
	FixtureDef.shape = &Shape;
	FixtureDef.filter.categoryBits = 0x0010;
	FixtureDef.filter.maskBits = 0x0010 | 0x0002 | 0x0001 | 0x0004 | 0x0008;
	FixtureDef.userData = "cap";
	FixtureDef.isSensor = true;
	Body->CreateFixture(&FixtureDef);

	capBody = Body;

	b2BodyDef BodyDef2;
	BodyDef2.position = b2Vec2(capSprite.getPosition().x / SCALE, capSprite.getPosition().y / SCALE);
	BodyDef2.type = b2_staticBody;
	BodyDef2.userData = this;
	b2Body* Body2 = world->CreateBody(&BodyDef2);
	Body2->SetFixedRotation(false);
	Body2->SetSleepingAllowed(false);

	//b2PolygonShape Shape2;
	b2CircleShape Shape2;
	Shape2.m_radius = (capZoneSprite.getLocalBounds().width / 2) / SCALE;
	//Shape2.SetAsBox(((capSprite.getTextureRect().width *capSprite.getScale().x) / 2) / SCALE, ((capSprite.getTextureRect().height * capSprite.getScale().x) / 2) / SCALE);
	//Shape.SetAsBox((5.5 / 2) / SCALE, (22 / 2) / SCALE);
	b2FixtureDef FixtureDef2;
	FixtureDef2.density = 1.0f;
	FixtureDef2.friction = 0.0f;
	FixtureDef2.shape = &Shape2;
	FixtureDef2.filter.categoryBits = 0x0010;
	FixtureDef2.filter.maskBits = 0x0010 | 0x0002 | 0x0001 | 0x0004 | 0x0008;
	FixtureDef2.userData = "capZone";
	FixtureDef2.isSensor = true;
	Body2->CreateFixture(&FixtureDef2);

	capZoneBody = Body2;
}