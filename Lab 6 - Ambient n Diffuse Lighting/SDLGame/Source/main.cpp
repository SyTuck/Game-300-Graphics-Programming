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

// Our opengl context handle
SDL_GLContext GLContext;
SDL_Window *window;

// GameState
bool GameRunning = true;

bool Init(SDL_Window** mainWindow, SDL_Renderer** mainRenderer);
void Shutdown(SDL_Window* mainWindow);

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

	int r = 0;
	int b = 0;
	int g = 0;

	int x = 0;
	int y = 0;
	int z = 0;


	// Main game loop
	while (GameRunning) 
	{
		// the order of everything within this loop is very important.
		// handle button events
		GameRunning = EventHandler::Update();
		// pause to control framerate
		SDL_Delay(3);
																						//ambient light colour control
			 if (EventHandler::events[R_PRESSED])		r++;							//Red					
		else if (EventHandler::events[G_PRESSED])		g++;							//Green
		else if (EventHandler::events[B_PRESSED])		b++;							//Blue
		else if (EventHandler::events[PGUP_PRESSED])  {	r++;	 g++;     b++;		}	//Fade up
		else if (EventHandler::events[PGDOWN_PRESSED]){ r--;	 g--;     b--;		}	//Fade down
		else if (EventHandler::events[DEL_PRESSED])   { r = 0;	 g = 0;	  b = 0;	}	//Full bright
		else if (EventHandler::events[HOME_PRESSED])  { r = 255; g = 255; b = 255;	}	//Full dark

			 if (r < 0)		r = 0;														//overflow protection
		else if (r > 255)	r = 255;
			 if (g < 0)		g = 0;
		else if (g > 255)	g = 255;
			 if (b < 0)		b = 0;
		else if (b > 255)	b = 255;

			 if (EventHandler::events[X_PRESSED])	  z--;								//light position control
		else if (EventHandler::events[Z_PRESSED])     z++;
		else if (EventHandler::events[DOWN_PRESSED])  y--;
		else if (EventHandler::events[UP_PRESSED])    y++;
		else if (EventHandler::events[LEFT_PRESSED])  x--;
		else if (EventHandler::events[RIGHT_PRESSED]) x++;

		ShaderManager::GetInstance()->SetLightLevels((float) r / 255, (float) g / 255, (float) b / 255);
		ShaderManager::GetInstance()->SetLightPosition((float) x, (float) y, (float) z);

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