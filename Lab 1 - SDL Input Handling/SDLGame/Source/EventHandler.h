#pragma once
#include "SDL.h"


class EventHandler
{
public:
	EventHandler();
	~EventHandler();

	static bool Update();
	static SDL_Event events;
	
//	static bool wOn;			//flags that a WASD key was pressed
//	static bool sOn;			//abandoned flags that attempted to allow
//	static bool aOn;			//simultaneous key presses (ie diagonal movement)
//	static bool dOn;

private:
};


