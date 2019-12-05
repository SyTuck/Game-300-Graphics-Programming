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
/*********************************************************************
	CheckWithin
	
	This method checks to see if this object is with
	the bounds of the gameobject passed
	
	it also reports back an indication of which axes 
	and direction the collision occured
	
*********************************************************************/
int GameObject3D::CheckWithin(GameObject3D otherObj)
{
	Vec3 LocalPos = transform.position;
	Vec3 OtherPos = otherObj.transform.position;

	int retAxis = NOCOLLISION;

	// perform a check for collision based on the other objects position and dimensions in addition to the local position and dimensions.
	// you can assume our objects positions are central to the object

	if ((LocalPos.x - dimensions.x + velocity.x < OtherPos.x - otherObj.dimensions.x) ||	//reversed the +/- on LocalPos so Left Most edge of this object
		(LocalPos.x + dimensions.x + velocity.x > OtherPos.x + otherObj.dimensions.x))		//is checked agains the Right Most of the other object
	{																						//also adding in the velocity step checks the collision one frame ahead
		retAxis |= XCOLLISION;																//so we don't clip through the wall by a full velocity step (at least)
	}
	if ((LocalPos.y - dimensions.y + velocity.y < OtherPos.y - otherObj.dimensions.y) ||	//modifying the bounding box of the pumpkin because I don't think it's sized right
		(LocalPos.y + dimensions.y + velocity.y > OtherPos.y + otherObj.dimensions.y))		//(and it's very apparent now that I'm doing a "Is within" check)
	{
		retAxis |= YCOLLISION;
	}
	if ((LocalPos.z - dimensions.z + velocity.z < OtherPos.z - otherObj.dimensions.z) ||	//(note that the Velocity is only ever added because the sign is already included in it's value)
		(LocalPos.z + dimensions.z + velocity.z > OtherPos.z + otherObj.dimensions.z))
	{
		retAxis |= ZCOLLISION;
	}

	return retAxis;
}
/***********************************************************************
	CheckCollision
	
	This method is the standard "if edge outside edge then not collide"
	collision detection.

	The method also then does a quick check to find the axes and direction
	of the collision. The assumption is that the closest edge is the one
	that collided, however this isn't always true
	
	*******************************************************************/
int GameObject3D::CheckCollision(GameObject3D otherObj)
{
	Vec3 LocalPos = transform.position;
	Vec3 OtherPos = otherObj.transform.position;

	int retAxis = NOCOLLISION;

	if ((LocalPos.x - dimensions.x > OtherPos.x + otherObj.dimensions.x) ||		//Standard bounding box collision check
		(LocalPos.x + dimensions.x < OtherPos.x - otherObj.dimensions.x) ||		//
		(LocalPos.y - dimensions.y > OtherPos.y + otherObj.dimensions.y) ||		
		(LocalPos.y + dimensions.y < OtherPos.y - otherObj.dimensions.y) ||		
		(LocalPos.z - dimensions.z > OtherPos.z + otherObj.dimensions.z) ||		
		(LocalPos.z + dimensions.z < OtherPos.z - otherObj.dimensions.z))
	{
		retAxis = NOCOLLISION;
	}
	else
	{
		float xdis = fabs(LocalPos.x - OtherPos.x);								//here we find how far apart each axis is
		float ydis = fabs(LocalPos.y - OtherPos.y);								//and make the assumption that the closes axes is the one that collided
		float zdis = fabs(LocalPos.z - OtherPos.z);

		float *lPos = nullptr;
		float *oPos = nullptr;
		float *lVel = nullptr;
		float *oVel = nullptr;

		if ((xdis < ydis) && (xdis < zdis))										//once the closest axis is found
		{																		//record the axis velocity and position
			retAxis = XCOLLISION;												//for check what type of collision we had
			lPos = &LocalPos.x;
			oPos = &OtherPos.x;
			lVel = &velocity.x;
			oVel = &otherObj.velocity.x;
		}
		else if ((ydis < xdis) && (ydis < zdis))
		{
			retAxis = YCOLLISION;
			lPos = &LocalPos.y;
			oPos = &OtherPos.y;
			lVel = &velocity.y;
			oVel = &otherObj.velocity.y;
		}
		else if ((zdis < ydis) && (zdis < xdis))
		{
			retAxis = ZCOLLISION;
			lPos = &LocalPos.z;
			oPos = &OtherPos.z;
			lVel = &velocity.y;
			oVel = &otherObj.velocity.y;
		}
		else
		{
			retAxis = NOCOLLISION;
		}

		if (retAxis != NOCOLLISION)
		{
			if ((*lPos - *oPos) < 0)			//negative collisions are were each object is going in the opposite direction	
			{									// - * + = - (objects were going in the opposite direction)
				retAxis |= NEGATIVECOLLIDE;
			}
			if ((*lVel * *oVel) > 0.0f)			// - * - = + * + = + (objects are going in the same direction
			{									
				retAxis |= OVERTAKECOLLIDE;

				if (fabs(*oVel) > fabs(*lVel))	//report who hit who
				{
					retAxis |= OTHERHIT;
				}
			}
		}
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
	velocity.y += (0.1f * (1 - rand() % 3));									//adding in a small reflection error (to make it more dynamic)
	velocity.z += (0.1f * (1 - rand() % 3));

}
void GameObject3D::ReflectYVelocity()
{
	velocity.y *= -1.0f;
	velocity.z += (0.1f * (1 - rand() % 3));									
	velocity.z += (0.1f * (1 - rand() % 3));
}
void GameObject3D::ReflectZVelocity()
{
	velocity.z *= -1.0f;
	velocity.y += (0.1f * (1 - rand() % 3));									
	velocity.x += (0.1f * (1 - rand() % 3));
}
