#include "Pumpkin.h"

Pumpkin::Pumpkin()
{
}

Pumpkin::~Pumpkin()
{
}

void Pumpkin::Init(string modelFile)
{
	ObjModel::Init(modelFile);
	velocity.x = 0.3;
	velocity.y = 0.05f;
	velocity.z = -0.2f;
	transform.position.z = -10.0f;

	dimensions.x = 4.0;	// width
	dimensions.y = 4.0;	// height
	dimensions.z = 4.0;	// length
}

// this is used to process individual vertices for your model
void Pumpkin::ProcessVertice(int shapeId, float vx, float vy, float vz, float r, float g, float b)
{
	ObjModel::ProcessVertice(shapeId, vx, vy, vz, r, g, b);

	if (shapeId == CORE)
	{
		glMaterialfv(GL_FRONT, GL_DIFFUSE, pumpkinColor);
		glColor3f(0.8f, 0.5f, 0.3f);
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_DIFFUSE, stemColor);
		glColor3f(0.3f, 0.9f, 0.7f);
	}
}

void Pumpkin::Update()
{
	transform.position.y += velocity.y;
	transform.position.x += velocity.x;
	transform.position.z += velocity.z;
	ObjModel::Update();
}
