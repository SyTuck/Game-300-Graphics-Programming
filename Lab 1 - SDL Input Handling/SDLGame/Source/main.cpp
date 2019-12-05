#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// for loading sprites
#include "Utils.h"

// processing events
#include "EventHandler.h"

// creating a basic gameobject
#include "Objects\GameObject2D.h"

#include "SDL.h"

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

// GameState
bool GameRunning = true;

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;

	// create our basic SDL window, this is why we have both a console window and a window for our graphical game.
	// we will use this for both 2D and 3D rendering.
	window = SDL_CreateWindow("Basic SDL Project",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);						//there's a window_full_screen value for this (SDL_WINDOW_SHOWN)

	if (!window) 
	{
		return false;
	}

	// Creates the 2D renderer used to display SDL sprites.
	// We will use this for 2D rendering in front of the screen.
	// OpenGL however will use it's own rendered but share the same window as SDL.
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) 
	{
		return false;
	}

	int r = 0x00;							//RGB colour codes for changing the background
	int g = 0x00;							//(defaulting as black)
	int b = 0x00;

	// Initialize the sprite positions
	srand(time(NULL));

	// this object is defined inside the GameObject2D file.
	// See Game 300 - Lecture 2 slides for more information on GameObjects
	GameObject2D SplashScreen;
	SplashScreen.Init("Data\\Art\\SplashScreen.bmp", renderer);

	// Main game loop
	while (GameRunning) 
	{
		// The order of everything within this loop is very important.

		// Draw a black background

		// handle button events
		GameRunning = EventHandler::Update();


		if (EventHandler::events.key.keysym.sym == SDLK_k)			//user control of the background colour 
		{															//Red, Green, and Blue can be controlled independently to allow mixing
			r = 0x00;												//Black ('k') is used to turn all colours off
			g = 0x00;
			b = 0x00;
		}
		else if (EventHandler::events.key.keysym.sym == SDLK_r)
		{
			r = 0xFF;
		}
		else if (EventHandler::events.key.keysym.sym == SDLK_g)
		{
			g = 0xFF;
		}
		else if (EventHandler::events.key.keysym.sym == SDLK_b)
		{
			b = 0xFF;
		}
		SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
		SDL_RenderClear(renderer);

		// update our Object with present time
		SplashScreen.Update();

		// draw our example game object
		SplashScreen.Draw(window, renderer);

		// Update the screen!
		SDL_RenderPresent(renderer);

		// pause to control framerate
		SDL_Delay(3);
	}

	SDL_Quit();

	return true;
}
