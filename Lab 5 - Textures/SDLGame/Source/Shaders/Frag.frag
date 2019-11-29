#version 430 core

out vec4 color;                                                   

in vec2 UV;
in float shft;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main(void)                                                   
{    
vec4 pxl0 = texture( texture0, UV );
vec4 pxl1 = texture( texture1, UV );

vec2 U2 = UV;
	 U2.x = UV.x + shft;
	 U2.y = UV.y;

vec4 pxl2 = texture( texture2, U2 );

	vec4 tmp = mix( pxl0, pxl1, 0.5);
    color = mix( tmp, pxl2, 0.5); 
	
}                                                                 