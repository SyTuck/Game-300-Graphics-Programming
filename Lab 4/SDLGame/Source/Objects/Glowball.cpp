#include "Glowball.h"
#include <stdlib.h>


Glowball::Glowball()
{
}


Glowball::~Glowball()
{
}

void Glowball::Init(string modelFile)
{
	ObjModel::Init(modelFile);
	velocity.x = 0.0f;// 0.3;
	velocity.y = 0.0f; // 0.05f;
	velocity.z = 0.0f; // -0.2f;
	transform.position.z = -10.0f;
	transform.scale.x = 0.01f;
	transform.scale.y = 0.01f;
	transform.scale.z = 0.01f;

	dimensions.x = 0.1f;	// width
	dimensions.y = 0.1f;	// height
	dimensions.z = 0.1f;	// length
}

/*
void Glowball::Draw()
{

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

	DoTaskIV(fader);

}
*/
#define xOFFSET 0.0f
#define yOFFSET 0.0f
#define zOFFSET 0.0f

#define xRADIUS (0.1f *0.75f)
#define yRADIUS  0.1f
#define zRadius  0.1f
//#define MINTRIS 3					//for our 1000 arrays, we have a max of 250 triangles
//#define MAXTRIS 249
#define CIRCLERADIANS (2 * 3.14159265)
#define CIRCLESEGMENTS ((2 * 3.14159265)/3)

int currentNumOfTris = 10;
//int TriCountTick = 0;
/*****************************************************
	DoTaskIV

	Just an extra bit for drawing a cirlce and using
	the faders programmatically.

	The number of vertex increases just to show things
	are being calculated on the fly

******************************************************/
void Glowball::DoTaskIV(float f[])
{
	task4Vertices[0] = xOFFSET;								//the first vertex will be the origin/common to all the triangles
	task4Vertices[1] = yOFFSET;
	task4Vertices[2] = 0.0f;
	task4ColourArray[0] = f[0];								//the center point of the cirlce (common point of each trianble)
	task4ColourArray[1] = f[1];								//will use the fader colour
	task4ColourArray[2] = f[2];
	task4ColourArray[3] = 1.0f;

//	TriCountTick++;
//	if (TriCountTick > (MAXTRIS - currentNumOfTris) / 4)	//speed up the change of the number of triangles slowly over time
//	{														//because once we reach 50 or so triangles, it looks like not 
//		TriCountTick = 0;									//much is happening anyways
//		currentNumOfTris++;
//		if (currentNumOfTris > MAXTRIS)
//		{
//			currentNumOfTris = MINTRIS;
//		}
//	}

	float angleStep = CIRCLERADIANS / currentNumOfTris;		//pre calculate for efficiency

	for (int a = 1; a < currentNumOfTris + 1; a++)
	{
		task4Vertices[a * 3 + 0] = (xRADIUS * cos(angleStep * a)) + xOFFSET;	//X position of vertex
		task4Vertices[a * 3 + 1] = (yRADIUS * sin(angleStep * a)) + yOFFSET;	//Y position of vertex
		task4Vertices[a * 3 + 2] = 0.0f;										//Z position is always 0 and only here as a placeholder

		task4ColourArray[a * 4 + 0] = 0.0f;					//default everyone as off and then paint the Red, green, or blue
		task4ColourArray[a * 4 + 1] = 0.0f;					//depending on if they are in the first, second, or third segments
		task4ColourArray[a * 4 + 2] = 0.0f;
		task4ColourArray[a * 4 + 3] = 1.0f;

		if (a*angleStep < CIRCLESEGMENTS)					//circle is divided into three segments that fades from one primary colour to the next
		{
			task4ColourArray[a * 4 + 2] = 1.0f - ((a*angleStep / CIRCLESEGMENTS) - long(a*angleStep / CIRCLESEGMENTS));
			task4ColourArray[a * 4 + 0] = (a*angleStep / CIRCLESEGMENTS) - long(a*angleStep / CIRCLESEGMENTS);
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

	for (int a = 1; a < currentNumOfTris; a++)											//creating the element array
	{
		task4TriangleMap[triMapIdx++] = a;
		task4TriangleMap[triMapIdx++] = a + 1;
		task4TriangleMap[triMapIdx++] = 0;
	}
	task4TriangleMap[triMapIdx++] = currentNumOfTris;
	task4TriangleMap[triMapIdx++] = 1;

	glEnableClientState(GL_VERTEX_ARRAY);												//and finally draw it all up
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(4, GL_FLOAT, 0, &task4ColourArray[0]);
	glVertexPointer(3, GL_FLOAT, 0, &task4Vertices[0]);

	glDrawElements(GL_TRIANGLES, triMapIdx, GL_UNSIGNED_INT, &task4TriangleMap[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}