#pragma once
#include <string>
#include "..\Math.h"
#include "SDL.h"

// new OpenGL/GLEW headers:
#define GL3_PROTOTYPES 1
#include "glew.h"

using namespace std;

class GameObject3D
{
public:
	GameObject3D();
	~GameObject3D();

	// used for any variables and data that needs to be setup on the object before we try to use it.
	void Init();

	// used to render the object to the screen
	void Draw();

	// used to update processing on the object (in case it's moving or has some processing to compute)
	void Update();

	// when the object is destroyed to ensure any memory allocated during it's lifetime is cleaned up.
	void Destroy();
private:

	// pos, rot, scale
	Transform3D transform;

	GLuint bufferHandle;

	// should be defined inside the header file
	float vertex[36] = {
		-0.5f, 0.0f, -2.0f,
		0.5f, 0.0f, -2.0f,
		0.0f, 0.5f, -2.0f,

		-0.5f, 0.0f, -2.0f,
		-0.5f, 0.0f, -50.0f,
		0.0f, 0.5f, -2.0f,

		0.5f, 0.0f, -2.0f,
		-0.5f, 0.0f, -50.0f,
		0.0f, 0.5f, -2.0f,

		0.5f, 0.0f, -2.0f,
		-0.5f, 0.0f, -50.0f,
		0.5f, 0.0f, -2.0f,
	};
};

