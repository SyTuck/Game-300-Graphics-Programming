#include "EventHandler.h"

SDL_Event EventHandler::events;

//bool EventHandler::wOn;			//flags that a WASD key was pressed
//bool EventHandler::sOn;			//unused flags from an attempt to have the key presses non-binding
//bool EventHandler::aOn;
//bool EventHandler::dOn;


EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

bool EventHandler::Update()						//returns true to keep the game running, false for a shutdown/close key event
{
	bool success = true;
	bool dwnFlag = false;
	// Check for events
	while (SDL_PollEvent(&events))							//removed the while so the checking for events 			
	{														//becomes non-blocking
		SDL_PollEvent(&events);

		if (EventHandler::events.type == SDL_KEYDOWN)			//key press events handled here
		{
			if (EventHandler::events.key.keysym.sym == SDLK_ESCAPE)
			{
				success = false;
			}
		}

	}

	return success;
}
//		 tried something fancy but had to abandon it :( 

/*		else if (EventHandler::events.type == SDL_KEYUP)
		{
			SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
			EventHandler::events.key.keysym.sym = SDLK_UNKNOWN;
		}

		if ((EventHandler::events.type == SDL_KEYDOWN) || (EventHandler::events.type == SDL_KEYUP))	//key press events handled here
		{
			if (EventHandler::events.key.keysym.sym == SDLK_ESCAPE)									//shutdown when the escape key is pressed
			{
				success = false;
			}

			if (EventHandler::events.type == SDL_KEYDOWN)
			{
				dwnFlag = true;
			}
			else if(EventHandler::events.type == SDL_KEYUP)
			{
				dwnFlag = false;
			}

			if (EventHandler::events.key.keysym.sym == SDLK_w)			//Keep track of our down key presses (also deactivate the opposing keypress)
			{
				EventHandler::wOn = dwnFlag;
				if (dwnFlag)
				{
					EventHandler::sOn = false;
				}
			}
			else if (EventHandler::events.key.keysym.sym == SDLK_s)
			{
				EventHandler::sOn = dwnFlag;
				if (dwnFlag)
				{
					EventHandler::wOn = false;
				}
			}
			else if (EventHandler::events.key.keysym.sym == SDLK_a)
			{
				EventHandler::aOn = dwnFlag;
				if (dwnFlag)
				{
					EventHandler::dOn = false;
				}
			}
			else if (EventHandler::events.key.keysym.sym == SDLK_d)
			{
				EventHandler::dOn = dwnFlag;
				if (dwnFlag)
				{
					EventHandler::aOn = false;
				}				
			}
		}
*/
