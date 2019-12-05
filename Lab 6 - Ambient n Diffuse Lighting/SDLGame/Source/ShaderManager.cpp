#include "ShaderManager.h"
#include <cstdio>
#include <iostream>
#include "Utils.h"
#include "vmath.h"
#include "CameraManager.h"

using namespace std;

ShaderManager* ShaderManager::instance = nullptr;

#define LOG_COMPILE_SHADERS 1

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

void ShaderManager::Init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glewExperimental = GL_TRUE;
}

// function to call post Init
void ShaderManager::Startup()
{
	programObj = glCreateProgram();
}

void ShaderManager::LoadVertices(static const GLfloat CubeVB[], int numVerts)
{
	glBindBuffer(GL_ARRAY_BUFFER, verticesHandle);
	glBufferData(GL_ARRAY_BUFFER, numVerts, CubeVB, GL_STATIC_DRAW);
}

void ShaderManager::LoadUVs(static const GLfloat uvVB[], int numUVs)
{
	glBindBuffer(GL_ARRAY_BUFFER, UVHandle);
	glBufferData(GL_ARRAY_BUFFER, numUVs, uvVB, GL_STATIC_DRAW);
}

void ShaderManager::LoadNormals(static const GLfloat norms[], int numnorms)
{
	glBindBuffer(GL_ARRAY_BUFFER, normalHandle);
	glBufferData(GL_ARRAY_BUFFER, numnorms, norms, GL_STATIC_DRAW);
}

void ShaderManager::FindUniformHandles()
{
	TextureUniformHandle = glGetUniformLocation(programObj, "texture0");// Get the initial matrices references from the program.

	AmbienceUniformHandle = glGetUniformLocation(programObj, "ambience");

	LightPositionUniformHandle = glGetUniformLocation(programObj, "light_pos");

	ModelViewUniformHandle = glGetUniformLocation(programObj, "mv_matrix");

	ProjectionUniformHandle = glGetUniformLocation(programObj, "proj_matrix");
}

void ShaderManager::LoadShaderFromFile(const char * shaderfile, GLenum type)
{
	GLuint shaderObj = 0;
	FILE * filePtr;
	
#ifdef LOG_COMPILE_SHADERS
	string newStr = "Source\\Shaders\\glslangValidator.exe ";
	newStr.append(shaderfile);
	cout << newStr.c_str();
	system(newStr.c_str());
#endif

	if (fopen_s(&filePtr, shaderfile, "rb"))
	{
		cout << "error opening shader file: " << shaderfile << endl;
		return;
	}

	fseek(filePtr, 0, SEEK_END);
	int size = ftell(filePtr);
	fseek(filePtr, 0, SEEK_SET);

	char *data = new char[size + 1];

	if (!data)
	{
		cout << "No Data inside shader file: " << shaderfile << endl;
		return;
	}

	fread(data, 1, size, filePtr);
	data[size] = 0;
	fclose(filePtr);

	ProcessShaderFile(shaderObj, data, type);

	delete[] data;
}

void ShaderManager::ProcessShaderFile(GLuint shader, char *shaderData, GLenum type)
{

	shader = glCreateShader(type);

	if (!shader)
	{
		cout << "error creating shader: " << shader << endl;
		return;
	}

	glShaderSource(shader, 1, &shaderData, NULL);
	glCompileShader(shader);
	glAttachShader(programObj, shader);
	glDeleteShader(shader);
}

void ShaderManager::LoadShaders()
{
	LoadShaderFromFile("Source\\Shaders\\Vert.vert" , GL_VERTEX_SHADER);
	LoadShaderFromFile("Source\\Shaders\\Frag.frag" , GL_FRAGMENT_SHADER);

	glLinkProgram(programObj);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &verticesHandle);
	glGenBuffers(1, &UVHandle);
	glGenBuffers(1, &normalHandle);
	FindUniformHandles();
}

void ShaderManager::Render(GLuint texture, Vec3 position)
{
	glUseProgram(programObj);

	//pass in the vertices for our cube
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, verticesHandle);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, UVHandle);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalHandle);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// pass our data to openGL to store for the shaders use.
	glUniform1i(TextureUniformHandle, texture);

	glUniform3fv(AmbienceUniformHandle, 1, &AmbientLightLevels[0]);
	glUniform3fv(LightPositionUniformHandle, 1, &lightPosition[0]);

	vmath::mat4 proj_matrix = CameraManager::GetInstance()->getModifiedProjectionMatrix();
	glUniformMatrix4fv(ProjectionUniformHandle, 1, GL_FALSE, proj_matrix);

	vmath::mat4 mv_matrix = vmath::translate(position.x, position.y, position.z);
	glUniformMatrix4fv(ModelViewUniformHandle, 1, GL_FALSE, mv_matrix);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 12 * 3, 10*10);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void ShaderManager::Shutdown()
{
	glDeleteProgram(programObj);
	glDeleteVertexArrays(1, &vao);
}