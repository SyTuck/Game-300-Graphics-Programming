#include "EventHandler.h"
#include <stdio.h>
#include <string.h>
#include "CameraManager.h"

bool EventHandler::events[];

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

bool EventHandler::Update()
{
	bool success = true;

	SDL_Event currEvents;
	// Check for events
	int x, y;
	SDL_GetMouseState(&x, &y);
	CameraManager::GetInstance()->Rotate(x, y);

	while (SDL_PollEvent(&currEvents))
	{
		switch (currEvents.key.keysym.sym)
		{
		case SDLK_w:
		{
			SetButton(ControlsEvents::W_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_a:
		{
			SetButton(ControlsEvents::A_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_s:
		{
			SetButton(ControlsEvents::S_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_d:
		{
			SetButton(ControlsEvents::D_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_q:
		{
			SetButton(ControlsEvents::Q_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_z:
		{
			SetButton(ControlsEvents::Z_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_x:
		{
			SetButton(ControlsEvents::X_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_e:
		{
			SetButton(ControlsEvents::E_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_UP:
		{
			SetButton(ControlsEvents::UP_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_DOWN:
		{
			SetButton(ControlsEvents::DOWN_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_RIGHT:
		{
			SetButton(ControlsEvents::RIGHT_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_LEFT:
		{
			SetButton(ControlsEvents::LEFT_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_PAGEUP:
		{
			SetButton(ControlsEvents::PGUP_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_PAGEDOWN:
		{
			SetButton(ControlsEvents::PGDOWN_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_r:
		{
			SetButton(ControlsEvents::R_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_g:
		{
			SetButton(ControlsEvents::G_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_b:
		{
			SetButton(ControlsEvents::B_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_DELETE:
		{
			SetButton(ControlsEvents::DEL_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_HOME:
		{
			SetButton(ControlsEvents::HOME_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_END:
		{
			SetButton(ControlsEvents::END_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_ESCAPE:
		{
			success = false;
			break;
		}
		}
	}	
	return success;
}

void EventHandler::SetButton(ControlsEvents eventNum, bool pressed)
{
	events[eventNum] = pressed;
}
