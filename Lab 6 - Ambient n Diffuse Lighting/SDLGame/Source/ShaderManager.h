#pragma once
#include "SDL.h"

// new OpenGL/GLEW headers:
#define GL3_PROTOTYPES 1
#include "glew.h"
#include "Math.h"


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

	void Render(GLuint texture, Vec3 position);

	void Shutdown();

	void LoadShaderFromFile(const char * shaderfile, GLenum type);
	void LoadVertices(static const GLfloat CubeVB[], int numVerts);
	void LoadUVs(static const GLfloat CubeVB[], int numUVs);
	void LoadNormals(static const GLfloat norms[], int numnorms);
	void SetLightLevels(float r, float g, float b) { AmbientLightLevels[0] = r; AmbientLightLevels[1] = g; AmbientLightLevels[2] = b; }
	void SetLightPosition(float x, float y, float z) { lightPosition[0] = x; lightPosition[1] = y; lightPosition[2] = z; }

private:

	ShaderManager();
	~ShaderManager();

	void ProcessShaderFile(GLuint shader, char *shaderData, GLenum type);
	void FindUniformHandles();

	GLuint programObj;
	GLuint vao;

	GLint TextureUniformHandle;
	GLint AmbienceUniformHandle;
	GLint LightPositionUniformHandle;
	GLint ProjectionUniformHandle;
	GLint ModelViewUniformHandle;

	GLuint verticesHandle;
	GLuint UVHandle;
	GLuint normalHandle;

	float AmbientLightLevels[3];
	float lightPosition[3];
	
	static ShaderManager* instance;
};

