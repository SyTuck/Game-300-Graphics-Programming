#include "GameObject3D.h"
#include "..\EventHandler.h"

GameObject3D::GameObject3D()
{
}


GameObject3D::~GameObject3D()
{
}

// used for any variables and data that needs to be setup on the object before we try to use it.
void GameObject3D::Init()
{
	// generate a handle or name
	glGenBuffers(1, &bufferHandle); 

	// bind the buffer as the active buffer for OpenGL to modify
	glBindBuffer(GL_ARRAY_BUFFER, bufferHandle); 

	// insert the data from the data array into the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), &vertex[0], GL_STATIC_DRAW);
}

// used to render the object to the screen
void GameObject3D::Draw()
{	
	glBindBuffer(GL_ARRAY_BUFFER, bufferHandle);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, nullptr);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertex) / 3);
	glDisableClientState(GL_VERTEX_ARRAY);
}

// used to update processing on the object (in case it's moving or has some processing to compute)
void GameObject3D::Update()
{
	// Part 2: object update code in here:
	// a) Complete all directions to display the tetrahedron in all translation movements (XYZ)
	// hint: this will require modifying the eventhandler to allow for more input
	// b) scale the tetrahedron in all directions equally down by half using a button press of your choosing
	// c) rotate the tetrahedron along the Y axis with a button press of your choice.

	if (EventHandler::events[ControlsEvents::DOWN_PRESSED])
	{
		glTranslatef(0.0f, -1.0f, 0.0f);
	}

	if (EventHandler::events[ControlsEvents::UP_PRESSED])
	{
		glTranslatef(0.0f, 1.0f, 0.0f);
	}
}

// when the object is destroyed to ensure any memory allocated during it's lifetime is cleaned up.
void GameObject3D::Destroy()
{
}