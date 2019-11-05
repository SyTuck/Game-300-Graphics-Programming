#include "GamePlayManager.h"
#include <iostream>

GamePlayManager* GamePlayManager::instance = nullptr;


GamePlayManager::GamePlayManager()
{
}


GamePlayManager::~GamePlayManager()
{
}

void GamePlayManager::DisplaySplashScreen(SDL_Window* mainWindow, SDL_Renderer* mainRenderer)
{
	// this object is defined inside the GameObject2D file.
	GameObject2D SplashScreen;
	SplashScreen.Init("Data\\Art\\SplashScreen.bmp", mainRenderer);
	GameObject2D SplashScreen2;
	SplashScreen2.Init("Data\\Art\\SplashScreen2.bmp", mainRenderer);

	// Draw a black background
	SDL_SetRenderDrawColor(mainRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(mainRenderer);

	SwapSplash(mainWindow, mainRenderer, 500, SplashScreen);
	SwapSplash(mainWindow, mainRenderer, 5, SplashScreen2);
	SwapSplash(mainWindow, mainRenderer, 300, SplashScreen);
	SwapSplash(mainWindow, mainRenderer, 10, SplashScreen2);
	SwapSplash(mainWindow, mainRenderer, 250, SplashScreen);
	SwapSplash(mainWindow, mainRenderer, 15, SplashScreen2);
	SwapSplash(mainWindow, mainRenderer, 500, SplashScreen);
	SwapSplash(mainWindow, mainRenderer, 15, SplashScreen2);
	SwapSplash(mainWindow, mainRenderer, 100, SplashScreen);
	SwapSplash(mainWindow, mainRenderer, 300, SplashScreen2);

}

void GamePlayManager::SwapSplash(SDL_Window* mainWindow, SDL_Renderer* mainRenderer, Uint32 delay, GameObject2D screen)
{
	SDL_RenderClear(mainRenderer);
	screen.Draw(mainWindow, mainRenderer);

	// Update the screen!
	SDL_RenderPresent(mainRenderer);
	SDL_Delay(delay);
}


void GamePlayManager::InitGameplay()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	LightManager::GetInstance()->SetupSimpleLighting();

	pumpkin.Init("Data\\Art\\single_pumpkin.obj");
	//eyeBall.Init("Data\\Art\\2.obj");
	walls.Init(20.0f);
}


void GamePlayManager::Update()
{
	glLoadIdentity();
	LightManager::GetInstance()->ApplyLighting();

	glPushMatrix();
	pumpkin.Update();
	pumpkin.Draw();
	glPopMatrix();

	//glPushMatrix();
	//eyeBall.Update();
	//eyeBall.Draw();
	//glPopMatrix();

	glLoadIdentity();
	glPushMatrix();
	walls.Update();
	walls.Draw();
	glPopMatrix();



	int collResult = pumpkin.CheckCollision(walls);		//changed nature of collision. Now it detects if the bounding box is WITHIN the other object
	if (collResult)										
	{
		cout << "pumpkin tried escaping the level" << endl;
		// Once you trigger this print out upon the pumpkin exiting the level, reflect the velocity on the axis it made contact with.
			// this may require you to modify the CheckCollision function to return a value more representative of how the contact was made ( like a Vec3, enum or integer representing the axis)		
			// Once reflected add to the collision detection function so that it also checks for all other dimensions and not just the x.
			// your pumpkin should continuously bounce within the levels box
		
		if (collResult & XCOLLISION)			//mask off for each possible collision in case of simultaneous collisions (corner cases)
		{
			pumpkin.ReflectXVelocity();
		}
		if (collResult & YCOLLISION)
		{
			pumpkin.ReflectYVelocity();
		}
		if (collResult & ZCOLLISION)
		{
			pumpkin.ReflectZVelocity();
		}
	}
}