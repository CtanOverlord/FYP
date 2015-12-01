#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include "Box2D\Box2D.h"
#include "Ship.h"
#include "Projectile.h"

class ContactListener : public b2ContactListener {
private:

public:

	ContactListener() : b2ContactListener() {
	}

	void BeginContact(b2Contact* contact)
	{
		void* fixAType = contact->GetFixtureA()->GetUserData();
		void* fixBType = contact->GetFixtureB()->GetUserData();

		if (fixAType == "projectile" && fixBType == "enemy"
			|| fixAType == "enemy" && fixBType == "projectile") {
			if (fixAType == "projectile") {				
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

				//b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 10);
			}
			else if (fixBType == "projectile") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				//b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();

				//b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();

				static_cast<Projectile*>(bodyUserData1)->setTTL(0);
				static_cast<Ship*>(bodyUserData2)->setHealth(static_cast<Ship*>(bodyUserData2)->getHealth() - 10);
			}
		}


		//		static_cast<Player*>(bodyUserData1)->Respawn();
		//		//static_cast<Enemy*>(bodyUserData2)->Die();
		//	}
		//}
		//	if (fixAType == "Player" && fixBType == "Ground"
		//		|| fixAType == "Ground" && fixBType == "Player") {
		//		if (fixAType == "Player") {
		//			void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
		//			void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

		//			static_cast<Player*>(bodyUserData1)->Ground();
		//		}
		//		else if (fixBType == "Player") {
		//			void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
		//			void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
		//			static_cast<Player*>(bodyUserData1)->Ground();
		//		}
		//	}

		//	if (fixAType == "Player" && fixBType == "Flower"
		//		|| fixAType == "Flower" && fixBType == "Player") {
		//		if (fixAType == "Player") {
		//			void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
		//			void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

		//			static_cast<Player*>(bodyUserData1)->OnLadder();
		//			static_cast<Player*>(bodyUserData1)->NotGrounded();
		//		}
		//		else if (fixBType == "Player") {
		//			void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
		//			void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

		//			static_cast<Player*>(bodyUserData1)->OnLadder();
		//			static_cast<Player*>(bodyUserData1)->NotGrounded();
		//			//static_cast<Platform*>(bodyUserData2)->ToggleMove();
		//		}
		//	}
		//}


		//void EndContact(b2Contact* contact) {
		//	void* fixAType = contact->GetFixtureA()->GetUserData();
		//	void* fixBType = contact->GetFixtureB()->GetUserData();

		//	if (fixAType == "Player" && fixBType == "Platform"
		//		|| fixAType == "Platform" && fixBType == "Player") {
		//		if (fixAType == "Player") {
		//			void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		//			//player reset method being called
		//			b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();
		//			b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();
		//			if (posPlat.y - (10 / 60.0f) > posPlayer.y + 16 / 30.0f)
		//				static_cast<Player*>(bodyUserData)->NotGrounded();
		//		}
		//		else if (fixBType == "Player") {
		//			void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		//			//player reset method being called
		//			b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();
		//			b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();
		//			if (posPlat.y - (10 / 60.0f) > posPlayer.y + 16 / 30.0f)
		//				static_cast<Player*>(bodyUserData)->NotGrounded();
		//		}
		//	}

		//	if (fixAType == "Player" && fixBType == "Flower"
		//		|| fixAType == "Flower" && fixBType == "Player") {
		//		if (fixAType == "Player") {
		//			void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
		//			void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();

		//			static_cast<Player*>(bodyUserData1)->OffLadder();
		//			static_cast<Player*>(bodyUserData1)->Ground();
		//		}
		//		else if (fixBType == "Player") {
		//			void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
		//			void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();

		//			static_cast<Player*>(bodyUserData1)->OffLadder();
		//			static_cast<Player*>(bodyUserData1)->Ground();
		//		}
		//	}
	}
};
#endif