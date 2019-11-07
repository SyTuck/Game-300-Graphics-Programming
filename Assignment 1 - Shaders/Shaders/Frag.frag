#version 430 core

in VS_OUT  
{
	vec4 color;
} fs_in;  

out vec4 color;                                                   

void main()                     //main must be void                                              
{                                                                 
    color = fs_in.color;         //  fs_in misspelled            
}                                                                 