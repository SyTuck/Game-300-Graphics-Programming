#pragma once
#include "ObjModel.h"

class Glowball :public ObjModel
{
public:
	Glowball();
	~Glowball();

	void Init(string modelFile);
//	void Draw();

private:
	float task4ColourArray[1000] = {};
	float task4Vertices[1000] = {};
	unsigned int task4TriangleMap[1000] = {};

	void DoTaskIV(float f[]);
	
	float fader[3] = { 0.0f, 0.0f, 0.0f };
	float fadeIncrement = 0.01f;
	int   fadeColour = 0;
	bool  fadingIn = true;

};

