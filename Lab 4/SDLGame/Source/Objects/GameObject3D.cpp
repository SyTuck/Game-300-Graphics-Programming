#include "GameObject3D.h"
#include "..\EventHandler.h"

GameObject3D::GameObject3D()
{
}


GameObject3D::~GameObject3D()
{
}

void GameObject3D::Update()
{
	if (iframes > 0)
	{
		iframes--;
	}
}

int GameObject3D::CheckCollision(GameObject3D otherObj)
{
	Vec3 LocalPos = transform.position;
	Vec3 OtherPos = otherObj.transform.position;

	int retAxis = NOCOLLISION;

	// perform a check for collision based on the other objects position and dimensions in addition to the local position and dimensions.
	// you can assume our objects positions are central to the object

	if ((LocalPos.x - (dimensions.x*1.5) + velocity.x < OtherPos.x - otherObj.dimensions.x) ||		//reversed the +/- on LocalPos so Left Most edge of this object
		(LocalPos.x + (dimensions.x*1.5) + velocity.x > OtherPos.x + otherObj.dimensions.x))			//is checked agains the Right Most of the other object
	{																							//also adding in the velocity step checks the collision one frame ahead
		retAxis |= XCOLLISION;																	//so we don't clip through the wall by a full velocity step (at least)
	}
	if ((LocalPos.y - dimensions.y + velocity.y < OtherPos.y - otherObj.dimensions.y) ||
		(LocalPos.y + dimensions.y + velocity.y > OtherPos.y + otherObj.dimensions.y))
	{
		retAxis |= YCOLLISION;
	}
	if ((LocalPos.z - dimensions.z + velocity.z < OtherPos.z - otherObj.dimensions.z) ||
		(LocalPos.z + dimensions.z + velocity.z > OtherPos.z + otherObj.dimensions.z))
	{
		retAxis |= ZCOLLISION;
	}

	return retAxis;
}

/**************************************************************************
	Reflext[XYZ]Velocity

	These methods are used to reverse the velocity of the specefied
	Axis. Used by other objects when a collision is detected

****************************************************************************/
void GameObject3D::ReflectXVelocity()
{
	velocity.x *= -1.0f;
	velocity.y += (velocity.y * 0.1f * (1 - rand() % 3));									//adding in a small reflection error (to make it more dynamic)
	velocity.z += (velocity.z * 0.1f * (1 - rand() % 3));

}
void GameObject3D::ReflectYVelocity()
{
	velocity.y *= -1.0f;
	velocity.z += (velocity.z * 0.1f * (1 - rand() % 3));									
	velocity.z += (velocity.z * 0.1f * (1 - rand() % 3));
}
void GameObject3D::ReflectZVelocity()
{
	velocity.z *= -1.0f;
	velocity.y += (velocity.y * 0.1f * (1 - rand() % 3));									
	velocity.x += (velocity.x * 0.1f * (1 - rand() % 3));
}
