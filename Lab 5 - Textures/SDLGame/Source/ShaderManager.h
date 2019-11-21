#pragma once
#include "SDL.h"

// new OpenGL/GLEW headers:
#define GL3_PROTOTYPES 1
#include "glew.h"

class ShaderManager
{
public:
	static ShaderManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new ShaderManager();
		}
		return instance;
	}

	void Init();

	void Startup();

	void LoadShaders();

	void Render();

	void Shutdown();

	void LoadShaderFromFile(const char * shaderfile, GLenum type);

private:

	ShaderManager();
	~ShaderManager();

	void ProcessShaderFile(GLuint shader, char *shaderData, GLenum type);
	void LoadVertices();
	void LoadTextures();
	void LoadUVs();

	GLuint programObj;
	GLuint vao;

	GLuint verticesHandle;
	GLuint Texture0[2];
	GLuint UVHandle;
	GLint  TextureUniformHandle0;
	GLint  TextureUniformHandle1;

	static ShaderManager* instance;
};

