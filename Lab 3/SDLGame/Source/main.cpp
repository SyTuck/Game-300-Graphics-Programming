#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// for loading sprites
#include "Utils.h"

// processing events
#include "EventHandler.h"

// creating a basic gameobject
#include "Objects\GameObject2D.h"
#include "Objects\GameObject3D.h"

#include "SDL.h"

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

void DisplaySplashScreen(SDL_Window* mainWindow, SDL_Renderer* mainRenderer);
bool Init(SDL_Window** mainWindow, SDL_Renderer** mainRenderer);

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;

	if (!Init(&window, &renderer))
	{
		return false;
	}

	// this will run for 1500ms before allowing input
	DisplaySplashScreen(window, renderer);

	glPointSize(5.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	float depth = 1.0f;

	GameObject3D myObj;
	myObj.Init();

	// Main game loop
	while (GameRunning) 
	{
		// the order of everything within this loop is very important.
		// handle button events
		GameRunning = EventHandler::Update();

		// pause to control framerate
		SDL_Delay(3);

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// PART 1: Initializing the View port
		// set your matrix mode for dealing with the view
		// load up the identity matrix
		// setup your view
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1000.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// we push the matrix here so that we are dealing with a clear matrix for all our modifications of this object to remain on.
		glPushMatrix();
		myObj.Update();
		myObj.Draw();
		// we are done dealing with the tetrahedron now so we can go ahead and pop off the matrix which contained it's modifications
		glPopMatrix();

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

void DisplaySplashScreen(SDL_Window* mainWindow, SDL_Renderer* mainRenderer)
{
	// this object is defined inside the GameObject2D file.
	GameObject2D SplashScreen;
	SplashScreen.Init("Data\\Art\\SplashScreen.bmp", mainRenderer);

	// Draw a black background
	SDL_SetRenderDrawColor(mainRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(mainRenderer);

	// draw our example game object
	SplashScreen.Draw(mainWindow, mainRenderer);

	// Update the screen!
	SDL_RenderPresent(mainRenderer);

	// pause to control framerate
	SDL_Delay(1500);
}