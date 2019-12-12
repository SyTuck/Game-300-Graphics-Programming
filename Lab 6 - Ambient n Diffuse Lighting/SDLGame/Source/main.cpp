#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// for loading sprites
#include "Utils.h"

#define TINYOBJLOADER_IMPLEMENTATION

#include "SDL.h"

#include "GamePlayManager.h"
#include "ShaderManager.h"

// new OpenGL/GLEW headers:
//#define GL3_PROTOTYPES 1
#include "glew.h"

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

#define R 0
#define G 1
#define B 2

#define X 0
#define Y 1
#define Z 2

// Our opengl context handle
SDL_GLContext GLContext;
SDL_Window *window;

// GameState
bool GameRunning = true;

bool Init(SDL_Window** mainWindow, SDL_Renderer** mainRenderer);
void Shutdown(SDL_Window* mainWindow);

/**********************************************************************
	AmbientControl
	
	check supported key presses to changed the light colors, intensity
	and its position. Parameters are interger arrays of the RGB values
	and the XYZ position of the light source (passed by reference)
	
	If's structured in block style to compress and highlight similar
	but trivial code
	
***********************************************************************/
void AmbientControl(int color[], int position[])
{
	//ambient light colour control
		 if (EventHandler::events[R_PRESSED])		color[R]++;									//Red					
	else if (EventHandler::events[G_PRESSED])		color[G]++;									//Green
	else if (EventHandler::events[B_PRESSED])		color[B]++;									//Blue

	else if (EventHandler::events[PGUP_PRESSED])  { color[R]++;	  color[G]++;   color[B]++; }	//Fade up
	else if (EventHandler::events[PGDOWN_PRESSED]){ color[R]--;	  color[G]--;   color[B]--; }	//Fade down
	else if (EventHandler::events[HOME_PRESSED])  { color[R]=255; color[G]=255; color[B]=255; }	//Full bright
	else if (EventHandler::events[DEL_PRESSED])   { color[R]= 0;  color[G]= 0;  color[B]= 0; }	//Full dark

	//overflow protection
	if		(color[R] < 0)	 color[R] = 0;														
	else if (color[R] > 255) color[R] = 255;
	if		(color[G] < 0)	 color[G] = 0;
	else if (color[G] > 255) color[G] = 255;
	if		(color[B] < 0)	 color[B] = 0;
	else if (color[B] > 255) color[B] = 255;

	//light position control
		 if (EventHandler::events[X_PRESSED])	  position[Z]--;								
	else if (EventHandler::events[Z_PRESSED])     position[Z]++;
	else if (EventHandler::events[DOWN_PRESSED])  position[Y]--;
	else if (EventHandler::events[UP_PRESSED])    position[Y]++;
	else if (EventHandler::events[LEFT_PRESSED])  position[X]--;
	else if (EventHandler::events[RIGHT_PRESSED]) position[X]++;

	else if (EventHandler::events[END_PRESSED]) { position[X] = 0; position[Y] = 0; position[Z] = 0; }
}

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;


	if (!Init(&window, &renderer))
	{
		return false;
	}

	// this will run for 1500ms before allowing input
	GamePlayManager::GetInstance()->DisplaySplashScreen(window, renderer);

	ShaderManager::GetInstance()->LoadShaders();
	GamePlayManager::GetInstance()->InitGameplay();

	int rgb[3] = { 0, 0, 0 };
	int xyz[3] = { 0, 0, 0 };

	// Main game loop
	while (GameRunning) 
	{
		// the order of everything within this loop is very important.
		// handle button events
		GameRunning = EventHandler::Update();
		// pause to control framerate
		SDL_Delay(3);

		AmbientControl(rgb, xyz);
	
		ShaderManager::GetInstance()->SetLightLevels((float) rgb[R] / 255, (float) rgb[G] / 255, (float) rgb[B] / 255);
		ShaderManager::GetInstance()->SetLightPosition((float) xyz[X], (float) xyz[Y], (float) xyz[Z]);

		//glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		  
		static const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);
		glUseProgram(0);


		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1000.0f);

		glMatrixMode(GL_MODELVIEW);
		
		GamePlayManager::GetInstance()->Update();
		SDL_GL_SwapWindow(window);
	}

	Shutdown(window);

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


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glewExperimental = GL_TRUE;
	//ShaderManager::GetInstance()->Init();

	glewInit();
	glEnable(GL_TEXTURE_2D);

	ShaderManager::GetInstance()->Startup();

	// Initialize the sprite positions
	srand(time(NULL));
	return true;
}

void Shutdown(SDL_Window* mainWindow)
{
	ShaderManager::GetInstance()->Shutdown();
	SDL_GL_DeleteContext(GLContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}