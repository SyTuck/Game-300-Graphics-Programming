#pragma once
#include "ObjModel.h"

class Glowball :public ObjModel
{
public:
	Glowball();
	~Glowball();

	void Init(string modelFile);
	void Draw();

private:

	#define NUMOFTRIS 30

	float task4ColourArray[40] = {};
	float task4TriangleMap[50] = {};
	float task4Vertices[30] = {};

	void DoTaskIV(float f[]);
	
	float fader[3] = { 0.0f, 0.0f, 0.0f };
	float fadeIncrement = 0.01f;
	int   fadeColour = 0;
	bool  fadingIn = true;

};

