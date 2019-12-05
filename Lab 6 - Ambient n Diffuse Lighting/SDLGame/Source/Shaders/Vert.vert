#version 430 core

layout(location = 0) in vec3 VertPos;
layout(location = 1) in vec2 UVs;
layout(location = 2) in vec3 normal;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

uniform vec3 light_pos = vec3(10.0, 10.0, 10.0);

out vec2 UV;
out vec3 normalVec;
out vec3 lightVec;

void main(void)                                                   
{                                             
	UV = UVs;	
	
	// new position using the projection and modelview matrices in addition to the position of each vertices
	vec4 P = proj_matrix * mv_matrix * vec4(VertPos.x + ((gl_InstanceID/10)/2.0f) , VertPos.y, VertPos.z -(mod(gl_InstanceID , 10)/2), 1.0f);

	normalVec = mat3(mv_matrix) * normal;		//calculate the normal with current light_pos

	gl_Position = P;
	lightVec = light_pos;
}         