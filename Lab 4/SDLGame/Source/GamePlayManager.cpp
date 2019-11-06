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
//	glEnable(GL_CULL_FACE);

	LightManager::GetInstance()->SetupSimpleLighting();

	Pumpkin pumpkin;
	pumpkin.Init("Data\\Art\\single_pumpkin.obj");
	for (int x = 0; x < TOTPUMPKINS; x++)
	{
		pumpkins[x] = pumpkin;

	}

//	eyeBall.Init("Data\\Art\\2.obj");
	walls.Init(20.0f);
}


void GamePlayManager::Update()
{



	for (int x = 0; x < TOTPUMPKINS; x++)
	{

		glLoadIdentity();
		LightManager::GetInstance()->ApplyLighting();

		glPushMatrix();
		pumpkins[x].Update();
		pumpkins[x].Draw();
		glPopMatrix();
	}

//	glLoadIdentity();
//	glPushMatrix();
	//eyeBall.Update();
//	eyeBall.Draw();
//	glPopMatrix();

	glLoadIdentity();
	glPushMatrix();
	walls.Update();
	walls.Draw();
	glPopMatrix();


	for (int x = 0; x < TOTPUMPKINS; x++)
	{
		int YcollResult = NOCOLLISION;
		int collResult = pumpkins[x].CheckWithin(walls);		//changed nature of collision. Now it detects if the bounding box is WITHIN the other object

		if ((freeForAll) && (collResult == NOCOLLISION))
		{
			for (int y = x+1; y < TOTPUMPKINS; y++)
			{
				YcollResult = pumpkins[x].CheckCollision(pumpkins[y]);
				if (YcollResult)
				{
					if (pumpkins[x].freeFromAll)
					{
						ReflectPumpkin(&pumpkins[y], YcollResult);
						collResult = YcollResult;
						cout << "pumpkin " << y << " collided with pumkin " << x << endl;
						break;
					}
				}
				else
				{
					pumpkins[x].freeFromAll = true;
				}
			}
		}
		if (collResult)
		{
			freeForAll = true;									//once we have our first wall collision, "blow out" all the pumpkins
			if (!YcollResult)
			{
				cout << "pumpkin " << x << " tried escaping the level" << endl;
			}
			// Once you trigger this print out upon the pumpkin exiting the level, reflect the velocity on the axis it made contact with.
				// this may require you to modify the CheckCollision function to return a value more representative of how the contact was made ( like a Vec3, enum or integer representing the axis)		
				// Once reflected add to the collision detection function so that it also checks for all other dimensions and not just the x.
				// your pumpkin should continuously bounce within the levels box

			ReflectPumpkin(&pumpkins[x], collResult);
		}
	}
}

void GamePlayManager::ReflectPumpkin(Pumpkin *pkn, int axs)
{
	if (axs & XCOLLISION)			//mask off for each possible collision in case of simultaneous collisions (corner cases)
	{
		pkn->ReflectXVelocity();
	}
	if (axs & YCOLLISION)
	{
		pkn->ReflectYVelocity();
	}
	if (axs & ZCOLLISION)
	{
		pkn->ReflectZVelocity();
	}
}