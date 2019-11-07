#version 430 core

out VS_OUT  
{
	vec4 color; 
} vs_out; 

void main(void)                                                   
{                                             
	const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.0, 1.0),
                                   vec4(-0.25, -0.25, 0.0, 1.0),
                                   vec4( 0.25,  0.25, 0.0, 1.0)); 

    vs_out.color = vec4( 0.25, 0.8, 1.0, 1.0);      //vs_out misspelled, needed an alpha component                  
	gl_Position = vertices[gl_VertexID];            //gl_VertexID misspelled
}         