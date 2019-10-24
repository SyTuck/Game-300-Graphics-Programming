#include "GameObject3D.h"
#include "..\EventHandler.h"

GameObject3D::GameObject3D()
{
	transform.position.x = 0.0f;
	transform.position.y = 0.0f;
	transform.position.z = 0.0f;

	transform.rotation.x = 0.0f;
	transform.rotation.y = 0.0f;
	transform.rotation.z = 0.0f;

	transform.scale.x = 1.0f;
	transform.scale.y = 1.0f;
	transform.scale.z = 1.0f;
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
	glFinish();

	glGenBuffers(1, &colrBuffHandle);

	// bind the buffer as the active buffer for OpenGL to modify
	glBindBuffer(GL_ARRAY_BUFFER, colrBuffHandle);

	// insert the data from the data array into the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(colours), &colours[0], GL_STATIC_DRAW);
	glFinish();
}

// used to render the object to the screen
void GameObject3D::Draw()
{	
	glBindBuffer(GL_ARRAY_BUFFER, bufferHandle);			//set up vertex handle and states
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, colrBuffHandle);			//Add colour to the faces
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, nullptr);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertex) / 3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

// used to update processing on the object (in case it's moving or has some processing to compute)
void GameObject3D::Update()
{
	// Part 2: object update code in here:
	// a) Complete all directions to display the tetrahedron in all translation movements (XYZ)
	// hint: this will require modifying the eventhandler to allow for more input
	// b) scale the tetrahedron in all directions equally down by half using a button press of your choosing
	// c) rotate the tetrahedron along the Y axis with a button press of your choice.

	//here, the arrow keys are used for X and Y axis, W and S control the z axis
	//holding the shift key, slides the object along the axis key pressed
	//holding the CTRL key, scales the object along the axis
	//regular key press performs the rotations
	if (EventHandler::events[ControlsEvents::DOWN_PRESSED])
	{
		if (EventHandler::events[ControlsEvents::SHIFT_PRESSED])
		{
			transform.rotation.y -= 0.01f;
		}
		else if (EventHandler::events[ControlsEvents::CTRL_PRESSED])
		{
			transform.scale.y -= 0.001f;
		}
		else
		{
			transform.position.y -= 0.001f;
		}
	}
	else if (EventHandler::events[ControlsEvents::UP_PRESSED])
	{
		if (EventHandler::events[ControlsEvents::SHIFT_PRESSED])
		{
			transform.rotation.y += 0.01f;
		}
		else if (EventHandler::events[ControlsEvents::CTRL_PRESSED])
		{
			transform.scale.y += 0.001f;
		}
		else
		{
			transform.position.y += 0.001f;
		}
	}

	if (EventHandler::events[ControlsEvents::LEFT_PRESSED])
	{
		if (EventHandler::events[ControlsEvents::SHIFT_PRESSED])
		{
			transform.rotation.x -= 0.01f;
		}
		else if (EventHandler::events[ControlsEvents::CTRL_PRESSED])
		{
			transform.scale.x -= 0.001f;
		}
		else
		{
			transform.position.x -= 0.001f;
		}
	}
	else if (EventHandler::events[ControlsEvents::RIGHT_PRESSED])
	{
		if (EventHandler::events[ControlsEvents::SHIFT_PRESSED])
		{
			transform.rotation.x += 0.01f;
		}
		else if (EventHandler::events[ControlsEvents::CTRL_PRESSED])
		{
			transform.scale.x += 0.001f;
		}
		else
		{
			transform.position.x += 0.001f;
		}
	}

	if (EventHandler::events[ControlsEvents::W_PRESSED])
	{
		if (EventHandler::events[ControlsEvents::SHIFT_PRESSED])
		{
			transform.rotation.z -= 0.01f;
		}
		else if (EventHandler::events[ControlsEvents::CTRL_PRESSED])
		{
			transform.scale.z -= 0.001f;
		}
		else
		{
			transform.position.z -= 0.001f;
		}
	}
	else if (EventHandler::events[ControlsEvents::S_PRESSED])
	{
		if (EventHandler::events[ControlsEvents::SHIFT_PRESSED])
		{
			transform.rotation.z += 0.01f;
		}
		else if (EventHandler::events[ControlsEvents::CTRL_PRESSED])
		{
			transform.scale.z += 0.001f;
		}
		else
		{
			transform.position.z += 0.001f;
		}
	} 

	if (EventHandler::events[ControlsEvents::Q_PRESSED])
	{
		transform.scale.z = 2.0f;
		transform.scale.y = 2.0f;
		transform.scale.x = 2.0f;
	}
	else if (EventHandler::events[ControlsEvents::A_PRESSED])
	{
		transform.scale.z = 0.5f;
		transform.scale.y = 0.5f;
		transform.scale.x = 0.5f;
	}
	glRotatef(transform.rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(transform.rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(transform.rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
	glTranslatef(transform.position.x, transform.position.y, transform.position.z);
}

// when the object is destroyed to ensure any memory allocated during it's lifetime is cleaned up.
void GameObject3D::Destroy()
{
}