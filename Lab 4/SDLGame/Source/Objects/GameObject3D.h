#pragma once
#include <string>
#include "..\Math.h"
#include "SDL.h"

// new OpenGL/GLEW headers:
#define GL3_PROTOTYPES 1
#include "glew.h"

using namespace std;

enum COLLISIONAXIS			//collision enums are set as bit values so multiple simultaneous collisions can be detected
{							//(to prevent possible "bouncing" at the boundry edge, not sure this is an actual issue) 
	NOCOLLISION = false,
	XCOLLISION = 1,
	YCOLLISION = 2,
	ZCOLLISION = 4
};

class GameObject3D
{
public:
	GameObject3D();
	~GameObject3D();

	// used for any variables and data that needs to be setup on the object before we try to use it.
	virtual void Init() {};

	// used to render the object to the screen
	virtual void Draw() {};

	// used to update processing on the object (in case it's moving or has some processing to compute)
	virtual void Update();

	// when the object is destroyed to ensure any memory allocated during it's lifetime is cleaned up.
	virtual void Destroy() {};

	// when the object is destroyed to ensure any memory allocated during it's lifetime is cleaned up.
	int CheckCollision(GameObject3D otherObj);		//Modified to return an Axis enum for the collision detection
													//(no collision = NOCOLLISION = 0 = false so boolean checks will still work)

	void ReflectXVelocity();						//These methods are use to reverse the velocity of a specific access
	void ReflectYVelocity();
	void ReflectZVelocity();

protected:

	// pos, rot, scale
	Transform3D transform;	

	// movement speed in direction
	Vec3 velocity;

	// width, height, depth/length
	Vec3 dimensions;

	GLuint bufferHandle;

	int iframes = 0;

private:

};

