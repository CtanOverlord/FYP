#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include <SFML/Graphics.hpp>

class Globals {
private:

public:
	Globals();
	static Globals* GetInstance();
	enum entityCats;
};

#endif 
