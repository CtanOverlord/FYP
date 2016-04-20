#include "Wreck.h"

static const float SCALE = 30.f;

Wreck::Wreck(b2World& World, sf::Vector2f position, float a, int type)
{
	if (type == 0)
	{
		if (!wreckTexture.loadFromFile("shipWreck1.png"))
		{

		}
	}
	if (type == 1)
	{
		if (!wreckTexture.loadFromFile("shipWreck3.png"))
		{

		}
	}
	if (type == 2)
	{
		if (!wreckTexture.loadFromFile("shipWreck2.png"))
		{

		}
	}
	if (type == 3)
	{
		if (!wreckTexture.loadFromFile("shipWreck4.png"))
		{

		}
	}
	if (type == 4)
	{
		if (!wreckTexture.loadFromFile("FrigateWreck1.png"))
		{

		}
	}
	if (type == 5)
	{
		if (!wreckTexture.loadFromFile("FrigateWreck2.png"))
		{

		}
	}
	if (type == 6)
	{
		if (!wreckTexture.loadFromFile("SniperWreck1.png"))
		{

		}
	}
	if (type == 7)
	{
		if (!wreckTexture.loadFromFile("SniperWreck2.png"))
		{

		}
	}
	if (type == 8)
	{
		if (!wreckTexture.loadFromFile("SniperWreck3.png"))
		{

		}
	}

	angle = a;
	
	wreckTexture.setSmooth(true);
	
	wreckSprite.setTexture(wreckTexture);

	wreckSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	wreckSprite.setPosition((position));

	if (type == 0)
	{
		wreckSprite.setOrigin(sf::Vector2f(103, 126));
	}
	if (type == 1)
	{
		wreckSprite.setOrigin(sf::Vector2f(103, 185));
	}
	if (type == 2)
	{
		wreckSprite.setOrigin(sf::Vector2f(111, 141));
	}
	if (type == 3)
	{
		wreckSprite.setOrigin(sf::Vector2f(108, 153));
	}
	if (type == 4)
	{
		wreckSprite.setOrigin(sf::Vector2f(61, 101.5));
	}
	if (type == 5)
	{
		wreckSprite.setOrigin(sf::Vector2f(67.5, 76.5));
	}
	if (type == 6)
	{
		wreckSprite.setOrigin(sf::Vector2f(100, 103.5));
	}
	if (type == 7)
	{
		wreckSprite.setOrigin(sf::Vector2f(28, 170));
	}
	if (type == 8)
	{
		wreckSprite.setOrigin(sf::Vector2f(27.5, 182.5));
	}

	wreckSprite.setRotation(angle);

	world = &World;

	CreateBody();

	wreckBody->SetTransform(wreckBody->GetPosition(), angle / (180.0f / b2_pi));

	float temp = rand() % 2 + 1;

	float temp2 = rand() % 20 + 1;

	sf::Vector2f direction(rand() % 50 + 1, rand() % 50 + 1);
	const float velocity = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (type == 0)
	{
		wreckBody->ApplyLinearImpulse(b2Vec2(-direction.x / 5, -direction.y / 5), wreckBody->GetWorldCenter(), false);
		if (temp == 1)
		{
			wreckBody->ApplyAngularImpulse(temp2, false);
		}
		else
		{
			wreckBody->ApplyAngularImpulse(-temp2, false);
		}
	}
	if (type == 1)
	{
		wreckBody->ApplyLinearImpulse(b2Vec2(-direction.x / 5, direction.y / 5), wreckBody->GetWorldCenter(), false);
		if (temp == 1)
		{
			wreckBody->ApplyAngularImpulse(temp2, false);
		}
		else
		{
			wreckBody->ApplyAngularImpulse(-temp2, false);
		}
	}
	if (type == 2)
	{
		wreckBody->ApplyLinearImpulse(b2Vec2(direction.x / 5, -direction.y / 5), wreckBody->GetWorldCenter(), false);
		if (temp == 1)
		{
			wreckBody->ApplyAngularImpulse(temp2, false);
		}
		else
		{
			wreckBody->ApplyAngularImpulse(-temp2, false);
		}
	}
	if (type == 3)
	{
		wreckBody->ApplyLinearImpulse(b2Vec2(direction.x / 5, direction.y / 5), wreckBody->GetWorldCenter(), false);
		if (temp == 1)
		{
			wreckBody->ApplyAngularImpulse(temp2, false);
		}
		else
		{
			wreckBody->ApplyAngularImpulse(-temp2, false);
		}
	}
	if (type == 4)
	{
		wreckBody->ApplyLinearImpulse(b2Vec2(-direction.x / 14,- direction.y / 14), wreckBody->GetWorldCenter(), false);
		if (temp == 1)
		{
			wreckBody->ApplyAngularImpulse(temp2 / 2, false);
		}
		else
		{
			wreckBody->ApplyAngularImpulse(-temp2 / 2, false);
		}
	}
	if (type == 5)
	{
		wreckBody->ApplyLinearImpulse(b2Vec2(direction.x / 14, direction.y / 14), wreckBody->GetWorldCenter(), false);
		if (temp == 1)
		{
			wreckBody->ApplyAngularImpulse(temp2 / 2, false);
		}
		else
		{
			wreckBody->ApplyAngularImpulse(-temp2 / 2, false);
		}
	}
	if (type == 6)
	{
		wreckBody->ApplyLinearImpulse(b2Vec2(direction.x / 14, direction.y / 14), wreckBody->GetWorldCenter(), false);
		if (temp == 1)
		{
			wreckBody->ApplyAngularImpulse(temp2 / 2, false);
		}
		else
		{
			wreckBody->ApplyAngularImpulse(-temp2 / 2, false);
		}
	}
	if (type == 7)
	{
		wreckBody->ApplyLinearImpulse(b2Vec2(-direction.x / 14, -direction.y / 14), wreckBody->GetWorldCenter(), false);
		if (temp == 1)
		{
			wreckBody->ApplyAngularImpulse(temp2 / 2, false);
		}
		else
		{
			wreckBody->ApplyAngularImpulse(-temp2 / 2, false);
		}
	}
	if (type == 8)
	{
		wreckBody->ApplyLinearImpulse(b2Vec2(direction.x / 14, -direction.y / 14), wreckBody->GetWorldCenter(), false);
		if (temp == 1)
		{
			wreckBody->ApplyAngularImpulse(temp2 / 2, false);
		}
		else
		{
			wreckBody->ApplyAngularImpulse(-temp2 / 2, false);
		}
	}

	//transform.rotate(angle, pos2);

	float scale1 = (rand() % 50 + 1) + 520;

	ttl = scale1;
}

void Wreck::Update()
{
	//velocity.x = cos((angle + 90) * 0.0174532925);
	//velocity.y = sin((angle + 90) * 0.0174532925);

	wreckSprite.setPosition(wreckBody->GetPosition().x * SCALE, wreckBody->GetPosition().y * SCALE);
	wreckSprite.setRotation(wreckBody->GetAngle() * (180.0f / b2_pi));
	//wreckBody->SetTransform(b2Vec2(wreckSprite.getPosition().x / SCALE, wreckSprite.getPosition().y / SCALE), angle);
	
	//AnimationManager::GetInstance()->CreateAnimation(wreckSprite.getPosition(), 5, 0);

	ttl--;
}

void Wreck::Draw(sf::RenderWindow & window)
{
	window.draw(wreckSprite);
}

sf::Sprite Wreck::getSprite()
{
	return wreckSprite;
}

float Wreck::getTTL()
{
	return ttl;
}

void Wreck::setTTL(float t)
{
	ttl = t;
}

b2Body* Wreck::getBody()
{
	return wreckBody;
}

void Wreck::CreateBody()
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(wreckSprite.getPosition().x / SCALE, wreckSprite.getPosition().y / SCALE);
	BodyDef.type = b2_dynamicBody;
	BodyDef.userData = this;
	b2Body* Body = world->CreateBody(&BodyDef);
	Body->SetFixedRotation(false);
	Body->SetSleepingAllowed(false);

	b2PolygonShape Shape;
	Shape.SetAsBox(((wreckSprite.getTextureRect().width * wreckSprite.getScale().x) / 2) / SCALE, ((wreckSprite.getTextureRect().height * wreckSprite.getScale().x) / 2) / SCALE);
	//Shape.SetAsBox((5.5 / 2) / SCALE, (22 / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.0f;
	FixtureDef.friction = 0.0f;
	FixtureDef.shape = &Shape;
	FixtureDef.filter.categoryBits = 0x0010;
	FixtureDef.filter.maskBits = 0x0010 | 0x0002 | 0x0001 | 0x0004 | 0x0008;
	FixtureDef.userData = "wreck";
	//FixtureDef.isSensor = true;
	Body->CreateFixture(&FixtureDef);

	wreckBody = Body;
}