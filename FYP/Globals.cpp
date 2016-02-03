#include "Globals.h"

static bool instanceFlag = false;
static Globals* instance = NULL;

Globals::Globals()
{
	enum entityCats{
	   SHIP = 0x0001,
	   FRIENDLY_SHIP = 0x0002,
	   PLASMA = 0x0004,
	   MISSILE = 0x0008,
	   WRECK = 0x0010,
	};
}

Globals * Globals::GetInstance()
{
	if (!instanceFlag) {
		instance = new Globals();
		instanceFlag = true;
	}
	return instance;
}