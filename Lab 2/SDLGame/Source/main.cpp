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

// new OpenGL/GLEW headers:
#define GL3_PROTOTYPES 1
#include "glew.h"

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

#define THICKLINE 128.0

// Our opengl context handle
SDL_GLContext GLContext;
SDL_Window *window;

// GameState
bool GameRunning = true;

void DisplaySplashScreen(SDL_Window* mainWindow, SDL_Renderer* mainRenderer);
bool Init(SDL_Window** mainWindow, SDL_Renderer** mainRenderer);

void DoTaskI(float f0, float f1, float f2)
{
	glPointSize(16.0f);

	glBegin(GL_POINTS);																//TASK 1: Draw a point, line, and triangle
	glColor4f(f0, f1, f2, 1.0f);													//draw a large point in the upper left quarter
	glVertex3f(-0.5, 0.5, 0.0f);
	glEnd();

	glLineWidth(THICKLINE);															//drawing lines from min to max of each primary colour 			
	for (float x = -128.0f; x < 128.0f; x++)										//to test banding and colour resolution
	{																				//(need to repeat with thicker lines or full boxes/triangles)
		glBegin(GL_LINES);
		glColor4f(((x + 128.0f) / 256.0f), 0.0f, 0.0f, 1.0f);							//each line segment is 1/256th width of the screen
		glVertex3f (x / 128.0f, 1.0f - 0.04f, 0.0f);						//with 1 / 256th of a colour increment from the previous segment
		glVertex3f((x + 1.0f) / 128.0f, 1.0f - 0.04f, 0.0f);

		glColor4f(0.0f, ((x + 128.0f) / 256.0f), 0.0f, 1.0f);
		glVertex3f(x / 128.0f, (1.0f - 0.12f), 0.0f);
		glVertex3f((x + 1.0f) / 128.0f, (1.0f - 0.12f), 0.0f);

		glColor4f(0.0f, 0.0f, ((x + 128.0f) / 256.0f), 1.0f);
		glVertex3f(x / 128.0f, (1.0f - 0.20), 0.0f);
		glVertex3f((x + 1.0f) / 128.0f, (1.0f - 0.20), 0.0f);

		glEnd();
	}

	glBegin(GL_TRIANGLES);															//a regular triangle using a mashup of our fader
	glColor4f(f0, f1, f2, 1.0f);
	glVertex3f(-0.75f, 0.66f, 0.0f);
	glColor4f(f1, f2, f0, 1.0f);
	glVertex3f(-0.25f, 0.0f, 0.0f);
	glColor4f(f2, f0, f1, 1.0f);
	glVertex3f(-0.75f, 0.0f, 0.0f);
	glEnd();

}


//start here with task 2
const float TASK2TRIANGLE[9] = { -0.75f, -0.10f, 0.0f,
								 -0.75f, -0.76f, 0.0f,
								 -0.25f, -0.10f, 0.0f };

float task2ColourArray[12] = {};
const int task2FadeArray[9] = { 2, 1, 0,					//index's of the faders for the vertex colours of task 2
						        0, 2, 1,					//made of combinations not in task I 
						        1, 0, 2 };					//(figure if I'm going to hard code in the values might as well) 
															//(use a const array instead of just inline code assignments   )
															//(also just 3X3 as I will manually assign the alpha		   )
void DoTaskII(float f[])
{
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			task2ColourArray[x * 4 + y] = f[task2FadeArray[x * 3 + y]];
		}
		task2ColourArray[x * 4 + 3] = 1.0f;											//make sure to keep alpha at 1.0f
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(4, GL_FLOAT, 0, &task2ColourArray[0]);
	glVertexPointer(3, GL_FLOAT, 0, &TASK2TRIANGLE[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

}

//TASK 3 data
const float TASK3VERTICES[21] =	{ 0.25f,  0.50f, 0.0f,
								  0.375f, 0.75f, 0.0f,
								  0.50f,  0.50f, 0.0f,
								  0.625f, 0.75f, 0.0f,
								  0.75f,  0.50f, 0.0f,
								  0.375f, 0.25f, 0.0f,
								  0.625f, 0.25f, 0.0f};

float task3ColourArray[28] = { 1.0f, 0.0f, 0.0f, 1.0f,			//Red triangle
							   1.0f, 0.0f, 0.0f, 1.0f,
							   0.0f, 0.0f, 0.0f, 1.0f,			// <- this is the center point and we will override this colour with the fader
							   0.0f, 1.0f, 0.0f, 1.0f,			//Green triangle
							   0.0f, 1.0f, 0.0f, 1.0f,
							   0.0f, 0.0f, 1.0f, 1.0f,			//Blue triangle
							   0.0f, 0.0f, 1.0f, 1.0f};

#define REDCENTER 8												//defines for quick reference to the center point colour index above
#define GREENCENTER 9
#define BLUECENTER 10

const unsigned int task3VertIndices[9] = { 0, 1, 2,
								  3, 4, 2,
								  5, 6, 2 };

void DoTaskIII(float f[])
{
	task3ColourArray[REDCENTER] = f[0];
	task3ColourArray[GREENCENTER] = f[1];
	task3ColourArray[BLUECENTER] = f[2];

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(4, GL_FLOAT, 0, &task3ColourArray[0]);
	glVertexPointer(3, GL_FLOAT, 0, &TASK3VERTICES[0]);

	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, &task3VertIndices[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

//TASK IV

float task4ColourArray[1000] = {};
float task4Vertices[1000] = {};
unsigned int task4TriangleMap[1000] = {};

#define xOFFSET 0.5f
#define yOFFSET -0.5f
#define xRADIUS (0.5f *0.75f)
#define yRADIUS  0.5f
#define MINTRIS 3					//for our 1000 arrays, we have a max of 250 triangles
#define MAXTRIS 249
#define CIRCLERADIANS (2 * 3.14159265)
#define CIRCLESEGMENTS ((2 * 3.14159265)/3)

int currentNumOfTris = MINTRIS;
int TriCountTick = 0;

void DoTaskIV(float f[])
{
	task4Vertices[0] = xOFFSET;						//the first vertex will be the origin/common to all the triangles
	task4Vertices[1] = yOFFSET;
	task4Vertices[2] = 0.0f;
	task4ColourArray[0] = f[0];						//set to white and full alpha so it's always present
	task4ColourArray[1] = f[1];
	task4ColourArray[2] = f[2];
	task4ColourArray[3] = 1.0f;

	TriCountTick++;
	if (TriCountTick > (MAXTRIS - currentNumOfTris) / 4)
	{
		TriCountTick = 0;
		currentNumOfTris++;
		if (currentNumOfTris > MAXTRIS)
		{
			currentNumOfTris = MINTRIS;
		}
	}

	float angleStep = CIRCLERADIANS / currentNumOfTris;		//pre calculate for efficiency

	for (int a = 1; a < currentNumOfTris + 1; a++)
	{
		task4Vertices[a * 3 + 0] = (xRADIUS * cos(angleStep * a)) + xOFFSET;	//X position of vertex
		task4Vertices[a * 3 + 1] = (yRADIUS * sin(angleStep * a)) + yOFFSET;	//Y position of vertex
		task4Vertices[a * 3 + 2] = 0.0f;									//Z position is always 0 and only here as a placeholder

		task4ColourArray[a * 4 + 0] = 0.0f;					//default everyone as off and then paint the Red, green, or blue
		task4ColourArray[a * 4 + 1] = 0.0f;					//depending on if they are in the first, second, or third segments
		task4ColourArray[a * 4 + 2] = 0.0f;
		task4ColourArray[a * 4 + 3] = 1.0f;

		if (a*angleStep < CIRCLESEGMENTS)
		{
			task4ColourArray[a * 4 + 2] = 1.0f - ((a*angleStep / CIRCLESEGMENTS) - long(a*angleStep / CIRCLESEGMENTS));
			task4ColourArray[a * 4 + 0] =(a*angleStep / CIRCLESEGMENTS) - long (a*angleStep / CIRCLESEGMENTS);
		}
		else if (a*angleStep < (2 * CIRCLESEGMENTS))
		{
			task4ColourArray[a * 4 + 0] = 1.0f - ((a*angleStep / CIRCLESEGMENTS) - long(a*angleStep / CIRCLESEGMENTS));
			task4ColourArray[a * 4 + 1] = (a*angleStep / CIRCLESEGMENTS) - long(a*angleStep / CIRCLESEGMENTS);
		}
		else
		{
			task4ColourArray[a * 4 + 1] = 1.0f - ((a*angleStep / CIRCLESEGMENTS) - long(a*angleStep / CIRCLESEGMENTS));
			task4ColourArray[a * 4 + 2] = (a*angleStep / CIRCLESEGMENTS) - long(a*angleStep / CIRCLESEGMENTS);
		}
	}

	int triMapIdx = 0;
	task4TriangleMap[triMapIdx++] = 0;
	
	for (int a = 1; a < currentNumOfTris; a++)
	{
		task4TriangleMap[triMapIdx++] = a;
		task4TriangleMap[triMapIdx++] = a + 1;
		task4TriangleMap[triMapIdx++] = 0;
	}
	task4TriangleMap[triMapIdx++] = currentNumOfTris;
	task4TriangleMap[triMapIdx++] = 1;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(4, GL_FLOAT, 0, &task4ColourArray[0]);
	glVertexPointer(3, GL_FLOAT, 0, &task4Vertices[0]);

	glDrawElements(GL_TRIANGLES, triMapIdx, GL_UNSIGNED_INT, &task4TriangleMap[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;

	float fader[3] = { 0.0f, 0.0f, 0.0f };
	float fadeIncrement = 0.01f;
	int   fadeColour = 0;
	bool  fadingIn = true;

	if (!Init(&window, &renderer))
	{
		return false;
	}

	srand(time(0));

	// this will run for 1500ms before allowing input
	DisplaySplashScreen(window, renderer);

	// Main game loop
	while (GameRunning) 
	{
		// the order of everything within this loop is very important.
		// handle button events
		GameRunning = EventHandler::Update();

		// pause to control framerate
		SDL_Delay(15);

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//TASK I
		DoTaskI(fader[0], fader[1], fader[2]);

		
		//Task II
		DoTaskII(fader);

	
		//************	Task III	**********************
		DoTaskIII(fader);

		//Task IV Bonus fun :)
		DoTaskIV(fader);

		SDL_GL_SwapWindow(window);

		if (fadingIn)
		{
			fader[fadeColour] += fadeIncrement;
			if (fader[fadeColour] > 1.0)
			{
				fadeColour = rand() % 3;
				fadingIn = !(fader[fadeColour] >= 1.0);					//set fadding to the opposite direction of where the new colour is currently set
			}
		}
		else
		{
			fader[fadeColour] -= fadeIncrement;
			if (fader[fadeColour] < 0.0)
			{
				fadeColour = rand() % 3;
				fadingIn = (fader[fadeColour] <= 0.0);
			}
		}

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