#version 430 core

out vec4 color;                                                   

in vec2 UV;
in vec3 normalVec;
in vec3 lightVec;

uniform sampler2D texture0;
uniform vec3 ambience		= vec3(0.1, 0.1, 0.1);
uniform vec3 diffuse_albedo = vec3(1.0, 1.0, 1.0);		//material properties (using default only)

layout (location = 2) in vec3 normal;

void main(void)                                                   
{             
	vec3 N = normalize(normalVec);
	vec3 L = normalize(lightVec);

	vec3 diffuse = max(dot(N, L), 0.0) * diffuse_albedo;

    color = texture( texture0, UV ) * vec4(diffuse + ambience, 1.0f);  
}                                                                 