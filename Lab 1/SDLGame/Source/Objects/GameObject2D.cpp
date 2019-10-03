#include "GameObject2D.h"
#include "..\Utils.h"

// processing events
#include "..\EventHandler.h"

GameObject2D::GameObject2D()
{

}

GameObject2D::~GameObject2D()
{

}


void GameObject2D::Init(string TextureFile, SDL_Renderer* renderer)
{
	// if a texture is supplied load it up and apply it to the object.
	if(TextureFile != "")
	{
		Utils::LoadSprite(TextureFile.c_str(), renderer, &Dimensions, &sprite);
	}
}

void GameObject2D::Draw( SDL_Window* window, SDL_Renderer* renderer)
{
	if (sprite != NULL)
	{
		// create a bounding box based on the dimensions and position.
		SDL_Rect Bounds;
		Bounds.x = transform.position.x;
		Bounds.y = transform.position.y;
		Bounds.w = Dimensions.x;
		Bounds.h = Dimensions.y;

		// adds the sprite to the render queue to be processed and displayed on the screen later.
		SDL_RenderCopy(renderer, sprite, NULL, &Bounds);
	}

}

void GameObject2D::Update()
{
	int keytracker = 0;


	if (EventHandler::events.key.keysym.sym == SDLK_w)			//WASD movement control support
	{
		transform.position.y -= 1;
	}
	else if (EventHandler::events.key.keysym.sym == SDLK_s)			//move this up into the key check code above
	{
		transform.position.y += 1;
	}
	else if (EventHandler::events.key.keysym.sym == SDLK_a)
	{
		transform.position.x -= 1;
	}
	else if (EventHandler::events.key.keysym.sym == SDLK_d)
	{
		transform.position.x += 1;
	}

}

// more parts of the abandoned fancy stuff
	/*

	if (EventHandler::wOn)			//WASD movement control support
	{
		transform.position.y -= 1;
		keytracker++;
	}
	if (EventHandler::sOn)
	{
		transform.position.y += 1;
		keytracker++;
	}
	if (EventHandler::aOn)
	{
		transform.position.x -= 1;
		keytracker++;
	}
	if (EventHandler::dOn)
	{
		transform.position.x += 1;
		keytracker++;
	}
//	if (!keytracker)
//	{
//		transform.position.y = 0;
//		transform.position.x = 0;
//	}
*/

void GameObject2D::Destroy()
{

}