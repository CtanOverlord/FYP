#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include "Box2D\Box2D.h"
#include "Ship.h"
#include "Projectile.h"
#include "Wreck.h"
#include "AnimationManager.h"
#include "CapPoint.h"

class ContactListener : public b2ContactListener {
private:

public:

	ContactListener() : b2ContactListener() {
	}

	void BeginContact(b2Contact* contact)
	{
		void* fixAType = contact->GetFixtureA()->GetUserData();
		void* fixBType = contact->GetFixtureB()->GetUserData();

		if (fixAType == "plasma" && fixBType == "enemy"
			|| fixAType == "enemy" && fixBType == "plasma") {
			if (fixAType == "plasma") {				
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 10);
			}
			else if (fixBType == "plasma") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 10);
			}
		}

		if (fixAType == "plasmaE" && fixBType == "player"
			|| fixAType == "player" && fixBType == "plasmaE") {
			if (fixAType == "plasmaE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 10);
			}
			else if (fixBType == "plasmaE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 10);
			}
		}

		if (fixAType == "plasmaE" && fixBType == "ally"
			|| fixAType == "ally" && fixBType == "plasmaE") {
			if (fixAType == "plasmaE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 10);
			}
			else if (fixBType == "plasmaE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 10);
			}
		}

		if (fixAType == "plasma" && fixBType == "bound"
			|| fixAType == "bound" && fixBType == "plasma") {
			if (fixAType == "plasma") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
			}
			else if (fixBType == "plasma") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
			}
		}

		if (fixAType == "plasmaE" && fixBType == "bound"
			|| fixAType == "bound" && fixBType == "plasmaE") {
			if (fixAType == "plasmaE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
			}
			else if (fixBType == "plasmaE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
			}
		}

		if (fixAType == "slug" && fixBType == "enemy"
			|| fixAType == "enemy" && fixBType == "slug") {
			if (fixAType == "slug") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 10);
				SoundManager::GetInstance()->CreateSound(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 6);
				AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 13, 0);
			}
			else if (fixBType == "slug") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 10);
				SoundManager::GetInstance()->CreateSound(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 6);
				AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 13, 0);
			}
		}

		if (fixAType == "slugE" && fixBType == "player"
			|| fixAType == "player" && fixBType == "slugE") {
			if (fixAType == "slugE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 10);
				SoundManager::GetInstance()->CreateSound(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 6);
				AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 13, 0);
			}
			else if (fixBType == "slugE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 10);
				SoundManager::GetInstance()->CreateSound(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 6);
				AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 13, 0);
			}
		}

		if (fixAType == "slugE" && fixBType == "ally"
			|| fixAType == "ally" && fixBType == "slugE") {
			if (fixAType == "slugE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 10);
				SoundManager::GetInstance()->CreateSound(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 6);
				AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 13, 0);
			}
			else if (fixBType == "slugE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 10);
				SoundManager::GetInstance()->CreateSound(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 6);
				AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 13, 0);
			}
		}

		if (fixAType == "slug" && fixBType == "wreck"
			|| fixAType == "wreck" && fixBType == "slug") {
			if (fixAType == "slug") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 100);
				SoundManager::GetInstance()->CreateSound(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 6);
				AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 13, 0);
			}
			else if (fixBType == "slug") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 100);
				SoundManager::GetInstance()->CreateSound(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 6);
				AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 13, 0);
			}
		}

		if (fixAType == "slugE" && fixBType == "wreck"
			|| fixAType == "wreck" && fixBType == "slugE") {
			if (fixAType == "slugE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 100);
				SoundManager::GetInstance()->CreateSound(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 6);
				AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 13, 0);
			}
			else if (fixBType == "slugE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 100);
				SoundManager::GetInstance()->CreateSound(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 6);
				AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 13, 0);
			}
		}

		if (fixAType == "slug" && fixBType == "bound"
			|| fixAType == "bound" && fixBType == "slug") {
			if (fixAType == "slug") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				//static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 13, 0);
			}
			else if (fixBType == "slug") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				//static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 13, 0);
			}
		}

		if (fixAType == "slugE" && fixBType == "bound"
			|| fixAType == "bound" && fixBType == "slugE") {
			if (fixAType == "slugE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				//static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 13, 0);
			}
			else if (fixBType == "slugE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				//static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 13, 0);
			}
		}

		if (fixAType == "plasma" && fixBType == "wreck"
			|| fixAType == "wreck" && fixBType == "plasma") {
			if (fixAType == "plasma") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 15);
			}
			else if (fixBType == "plasma") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 15);
			}
		}

		if (fixAType == "plasmaE" && fixBType == "wreck"
			|| fixAType == "wreck" && fixBType == "plasmaE") {
			if (fixAType == "plasmaE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 15);
			}
			else if (fixBType == "plasmaE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 15);
			}
		}

		if (fixAType == "missile" && fixBType == "enemy"
			|| fixAType == "enemy" && fixBType == "missile") {
			if (fixAType == "missile") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				//b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 40);
			}
			else if (fixBType == "missile") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				//b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 40);
			}
		}

		if (fixAType == "missileE" && fixBType == "player"
			|| fixAType == "player" && fixBType == "missileE") {
			if (fixAType == "missileE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				//b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 40);
			}
			else if (fixBType == "missileE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				//b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 40);
			}
		}

		if (fixAType == "missileE" && fixBType == "ally"
			|| fixAType == "ally" && fixBType == "missileE") {
			if (fixAType == "missileE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				//b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 40);
			}
			else if (fixBType == "missileE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				//b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 40);
			}
		}

		if (fixAType == "missile" && fixBType == "bound"
			|| fixAType == "bound" && fixBType == "missile") {
			if (fixAType == "missile") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
			}
			else if (fixBType == "missile") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
			}
		}

		if (fixAType == "missileE" && fixBType == "bound"
			|| fixAType == "bound" && fixBType == "missileE") {
			if (fixAType == "missileE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
			}
			else if (fixBType == "missileE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
			}
		}

		if (fixAType == "mine" && fixBType == "enemy"
			|| fixAType == "enemy" && fixBType == "mine") {
			if (fixAType == "mine") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				//b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 40);
			}
			else if (fixBType == "mine") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				//b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 40);
			}
		}


		if (fixAType == "mineE" && fixBType == "player"
			|| fixAType == "player" && fixBType == "mineE") {
			if (fixAType == "mineE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				//b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 40);
			}
			else if (fixBType == "mineE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				//b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 40);
			}
		}

		if (fixAType == "mineE" && fixBType == "ally"
			|| fixAType == "ally" && fixBType == "mineE") {
			if (fixAType == "mineE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				//b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 40);
			}
			else if (fixBType == "mineE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				//b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 40);
			}
		}

		if (fixAType == "mine" && fixBType == "bound"
			|| fixAType == "bound" && fixBType == "mine") {
			if (fixAType == "mine") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
			}
			else if (fixBType == "mine") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
			}
		}

		if (fixAType == "mineE" && fixBType == "bound"
			|| fixAType == "bound" && fixBType == "mineE") {
			if (fixAType == "mineE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
			}
			else if (fixBType == "mineE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
			}
		}

		if (fixAType == "capZone" && fixBType == "player"
			|| fixAType == "player" && fixBType == "capZone") {
			if (fixAType == "capZone") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				//static_cast<CapPoint*>(bodyUserData1)->addOccupant("Blue");
			}
			else if (fixBType == "capZone") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				//static_cast<CapPoint*>(bodyUserData1)->addOccupant("Blue");
			}
		}

		if (fixAType == "capZone" && fixBType == "enemy"
			|| fixAType == "enemy" && fixBType == "capZone") {
			if (fixAType == "capZone") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				//static_cast<CapPoint*>(bodyUserData1)->addOccupant("Red");
			}
			else if (fixBType == "capZone") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				//static_cast<CapPoint*>(bodyUserData1)->addOccupant("Red");
			}
		}

		if (fixAType == "drain" && fixBType == "enemy"
			|| fixAType == "enemy" && fixBType == "drain") {
			if (fixAType == "drain") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				//b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 40);
				static_cast<Ship*>(bodyUserData2)->setFuel(static_cast<Ship*>(bodyUserData2)->getFuel() - 250);
			}
			else if (fixBType == "drain") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				//b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 40);
				static_cast<Ship*>(bodyUserData2)->setFuel(static_cast<Ship*>(bodyUserData2)->getFuel() - 250);
			}
		}
		if (fixAType == "drainE" && fixBType == "player"
			|| fixAType == "player" && fixBType == "drainE") {
			if (fixAType == "drainE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				//b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 40);
				static_cast<Ship*>(bodyUserData2)->setFuel(static_cast<Ship*>(bodyUserData2)->getFuel() - 250);
			}
			else if (fixBType == "drainE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				//b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 40);
				static_cast<Ship*>(bodyUserData2)->setFuel(static_cast<Ship*>(bodyUserData2)->getFuel() - 250);
			}
		}


		if (fixAType == "drain" && fixBType == "bound"
			|| fixAType == "bound" && fixBType == "drain") {
			if (fixAType == "drain") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
			}
			else if (fixBType == "drain") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
			}
		}

		if (fixAType == "drainE" && fixBType == "bound"
			|| fixAType == "bound" && fixBType == "drainE") {
			if (fixAType == "drainE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
			}
			else if (fixBType == "drainE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
			}
		}

		if (fixAType == "missile" && fixBType == "wreck"
			|| fixAType == "wreck" && fixBType == "missile") {
			if (fixAType == "missile") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 100);
			}
			else if (fixBType == "missile") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 100);
			}
		}

		if (fixAType == "missileE" && fixBType == "wreck"
			|| fixAType == "wreck" && fixBType == "missileE") {
			if (fixAType == "missileE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 100);
			}
			else if (fixBType == "missileE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 100);
			}
		}

		if (fixAType == "mine" && fixBType == "wreck"
			|| fixAType == "wreck" && fixBType == "mine") {
			if (fixAType == "mine") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 100);
			}
			else if (fixBType == "mine") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 100);
			}
		}

		if (fixAType == "mineE" && fixBType == "wreck"
			|| fixAType == "wreck" && fixBType == "mineE") {
			if (fixAType == "mineE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 100);
			}
			else if (fixBType == "mineE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 100);
			}
		}

		if (fixAType == "drain" && fixBType == "wreck"
			|| fixAType == "wreck" && fixBType == "drain") {
			if (fixAType == "drain") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 100);
			}
			else if (fixBType == "drain") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 100);
			}
		}

		if (fixAType == "drainE" && fixBType == "wreck"
			|| fixAType == "wreck" && fixBType == "drainE") {
			if (fixAType == "drainE") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 100);
			}
			else if (fixBType == "drainE") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Wreck*>(bodyUserData2)->setTTL(static_cast<Wreck*>(bodyUserData2)->getTTL() - 100);
			}
		}
	}

	void EndContact(b2Contact* contact)
	{
			void* fixAType = contact->GetFixtureA()->GetUserData();
			void* fixBType = contact->GetFixtureB()->GetUserData();

			if (fixAType == "slug" && fixBType == "enemy"
				|| fixAType == "enemy" && fixBType == "slug") {
				if (fixAType == "slug") {
					void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
					void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

					//b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

					//b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();

					static_cast<Projectile*>(bodyUserData1)->setTTL(0);
					static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 340);
					SoundManager::GetInstance()->CreateSound(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 6);
					AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 11, static_cast<Projectile*>(bodyUserData1)->getSprite().getRotation() + 90);
				}
				else if (fixBType == "slug") {
					void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
					void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
					//b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();

					//b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();

					static_cast<Projectile*>(bodyUserData1)->setTTL(0);
					static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 340);
					SoundManager::GetInstance()->CreateSound(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 6);
					AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 11, static_cast<Projectile*>(bodyUserData1)->getSprite().getRotation() + 90);
				}
			}

			if (fixAType == "slugE" && fixBType == "player"
				|| fixAType == "player" && fixBType == "slugE") {
				if (fixAType == "slugE") {
					void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
					void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

					//b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

					//b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();

					static_cast<Projectile*>(bodyUserData1)->setTTL(0);
					static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 340);
					SoundManager::GetInstance()->CreateSound(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 6);
					AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 11, static_cast<Projectile*>(bodyUserData1)->getSprite().getRotation() + 90);
				}
				else if (fixBType == "slugE") {
					void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
					void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
					//b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();

					//b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();

					static_cast<Projectile*>(bodyUserData1)->setTTL(0);
					static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 340);
					SoundManager::GetInstance()->CreateSound(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 6);
					AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 11, static_cast<Projectile*>(bodyUserData1)->getSprite().getRotation() + 90);
				}
			}

			if (fixAType == "slugE" && fixBType == "ally"
				|| fixAType == "ally" && fixBType == "slugE") {
				if (fixAType == "slugE") {
					void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
					void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

					//b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

					//b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();

					static_cast<Projectile*>(bodyUserData1)->setTTL(0);
					static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 340);
					SoundManager::GetInstance()->CreateSound(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 6);
					AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 11, static_cast<Projectile*>(bodyUserData1)->getSprite().getRotation() + 90);
				}
				else if (fixBType == "slugE") {
					void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
					void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
					//b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();

					//b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();

					static_cast<Projectile*>(bodyUserData1)->setTTL(0);
					static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 340);
					SoundManager::GetInstance()->CreateSound(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 6);
					AnimationManager::GetInstance()->CreateAnimation(static_cast<Projectile*>(bodyUserData1)->getSprite().getPosition(), 11, static_cast<Projectile*>(bodyUserData1)->getSprite().getRotation() + 90);
				}
			}

			if (fixAType == "capZone" && fixBType == "player"
				|| fixAType == "player" && fixBType == "capZone") {
				if (fixAType == "capZone") {
					void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
					void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

					//static_cast<CapPoint*>(bodyUserData1)->removeOccupant("Blue");
				}
				else if (fixBType == "capZone") {
					void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
					void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

					//static_cast<CapPoint*>(bodyUserData1)->removeOccupant("Blue");
				}
			}

			if (fixAType == "capZone" && fixBType == "enemy"
				|| fixAType == "enemy" && fixBType == "capZone") {
				if (fixAType == "capZone") {
					void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
					void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

					//static_cast<CapPoint*>(bodyUserData1)->removeOccupant("Red");
				}
				else if (fixBType == "capZone") {
					void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
					void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

					//static_cast<CapPoint*>(bodyUserData1)->removeOccupant("Red");
				}
			}
	}
};
#endif