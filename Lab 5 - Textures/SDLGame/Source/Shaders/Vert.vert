#version 430 core

layout(location = 0) in vec3 VertPos;
layout(location = 1) in vec2 UVs;
layout(location = 2) in float shift; 

out vec2 UV;
out float shft;

void main(void)                                                   
{                                             
	UV = UVs;
	shft = shift;
	gl_Position.xyz =  VertPos;
	gl_Position.w = 1.0;
}         