#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// for loading sprites
#include "Utils.h"

#define TINYOBJLOADER_IMPLEMENTATION

#include "SDL.h"

#include "GamePlayManager.h"

// new OpenGL/GLEW headers:
#define GL3_PROTOTYPES 1
#include "glew.h"

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

// Our opengl context handle
SDL_GLContext GLContext;
SDL_Window *window;

// GameState
bool GameRunning = true;

bool Init(SDL_Window** mainWindow, SDL_Renderer** mainRenderer);

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;

	if (!Init(&window, &renderer))
	{
		return false;
	}

	srand(time(0));

	// this will run for 1500ms before allowing input
	GamePlayManager::GetInstance()->DisplaySplashScreen(window, renderer);

	GamePlayManager::GetInstance()->InitGameplay();

	// Main game loop
	while (GameRunning) 
	{
		// the order of everything within this loop is very important.
		// handle button events
		GameRunning = EventHandler::Update();
		// pause to control framerate
		//SDL_Delay(1);						//upping the speed for smoother movement (velocities divided by half)

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1000.0f);

		glMatrixMode(GL_MODELVIEW);
		
		GamePlayManager::GetInstance()->Update();

		SDL_GL_SwapWindow(window);
	}

	SDL_Quit();

	return true;
}

bool Init(SDL_Window** mainWindow, SDL_Renderer** mainRenderer)
{
	// create our basic SDL window, this is why we have both a console window and a window for our graphical game.
	// we will use this for both 2D and 3D rendering.
	*mainWindow = SDL_CreateWindow("Basic SDL Project",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL);

	if (!*mainWindow)
	{
		return false;
	}

	// Creates the 2D renderer used to display SDL sprites.
	// We will use this for 2D rendering in front of the screen.
	// OpenGL however will use it's own rendered but share the same window as SDL.
	*mainRenderer = SDL_CreateRenderer(*mainWindow, -1, 0);
	if (!*mainRenderer)
	{
		return false;
	}

	// initialize our context using our window as the source
	GLContext = SDL_GL_CreateContext(*mainWindow);
	glewInit();

	// Initialize the sprite positions
	srand(time(NULL));
	return true;
}
