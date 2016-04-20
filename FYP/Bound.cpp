#include "Bound.h"

static const float SCALE = 30.f;

Bound::Bound(b2World& World, sf::Vector2f position, float rotation, int t)
{
	type = t;

	if (type == 1)
	{
		if (!boundTexture.loadFromFile("Bounds.png"))
		{

		}

		boundTexture.setSmooth(true);

		boundSprite.setTexture(boundTexture);

		boundSprite.setScale(sf::Vector2f(1.0f, 1.0f));

		boundSprite.setPosition((position));

		boundSprite.setOrigin(sf::Vector2f(500, 20));

		angle = rotation;

		boundSprite.setRotation(angle);
	}
	else if (type == 2)
	{
		if (!boundTexture.loadFromFile("BoundShort.png"))
		{

		}

		boundTexture.setSmooth(true);

		boundSprite.setTexture(boundTexture);

		boundSprite.setScale(sf::Vector2f(1.0f, 1.0f));

		boundSprite.setPosition((position));

		boundSprite.setOrigin(sf::Vector2f(250, 20));

		angle = rotation;

		boundSprite.setRotation(angle);
	}

	world = &World;

	CreateBody();

	boundBody->SetTransform(b2Vec2(boundSprite.getPosition().x / SCALE, boundSprite.getPosition().y / SCALE), b2_pi * angle / 180.0);

	//boundSprite.setPosition(boundBody->GetPosition().x * SCALE, boundBody->GetPosition().y * SCALE);
	//boundSprite.setRotation(boundBody->GetAngle());
}

void Bound::Update()
{
	//boundSprite.setPosition(boundBody->GetPosition().x * SCALE, boundBody->GetPosition().y * SCALE);
	//boundSprite.setRotation(boundBody->GetAngle());

	//boundBody->SetTransform(b2Vec2(boundSprite.getPosition().x / SCALE, boundSprite.getPosition().y / SCALE), angle);
}

void Bound::Draw(sf::RenderWindow & window)
{
	window.draw(boundSprite);
}

sf::Sprite Bound::getSprite()
{
	return boundSprite;
}

b2Body* Bound::getBody()
{
	return boundBody;
}

void Bound::CreateBody()
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(boundSprite.getPosition().x / SCALE, boundSprite.getPosition().y / SCALE);
	BodyDef.type = b2_staticBody;
	BodyDef.userData = this;
	b2Body* Body = world->CreateBody(&BodyDef);
	Body->SetFixedRotation(false);
	Body->SetSleepingAllowed(false);

	b2PolygonShape Shape;
	Shape.SetAsBox(((boundSprite.getTextureRect().width * boundSprite.getScale().x) / 2) / SCALE, ((boundSprite.getTextureRect().height * boundSprite.getScale().x) / 2) / SCALE);
	//b2CircleShape Shape;
	//Shape.m_radius = (boundSprite.getLocalBounds().width / 4) / SCALE;
	//Shape.SetAsBox((5.5 / 2) / SCALE, (22 / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.0f;
	FixtureDef.friction = 0.0f;
	FixtureDef.shape = &Shape;
	FixtureDef.filter.categoryBits = 0x0010;
	FixtureDef.filter.maskBits = 0x0010 | 0x0002 | 0x0001 | 0x0004 | 0x0008;
	FixtureDef.userData = "bound";
	//FixtureDef.isSensor = true;
	Body->CreateFixture(&FixtureDef);

	boundBody = Body;
}