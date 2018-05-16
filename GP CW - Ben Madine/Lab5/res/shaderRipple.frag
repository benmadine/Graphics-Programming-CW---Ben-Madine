//Version number
#version 400

//Layout Qualifer
layout( location = 0 ) out vec4 fragcolor;
 
//Uniform Variables
uniform float time;
uniform sampler2D tex;
uniform sampler2D tex2;

//Setting the radius of ripple
float radius = .5;

//passing in texture cooridnates
in VS_OUT {
    vec2 texCoords;
} gs_in[];

//passing out texture coordinates
out vec2 TexCoords; 

void main()
{
//Creating float variable made equal to the time which is clamped.
	float t = clamp(time / 6., 0., 1.);

//Texture coordinates being assigned and direction variable being specified
	TexCoords = gs_in[0].texCoords;
	vec2 dir = TexCoords - vec2(.5);
	
	//Calcualting distance varaible and offset
	float dist = distance(TexCoords, vec2(.5));
	vec2 offset = dir * (sin(dist * 80. - time*15.) + .5) / 30.;

	//Texture coordinates being assigned for other vertex and applying offset
	TexCoords = gs_in[1].texCoords + offset;
	vec4 diffuse = texture2D(tex, TexCoords);

	//Taking the the texture coordiantes and texttures
	vec4 mixin = texture2D(tex2, TexCoords);

	//Final colour being assigned
 	fragcolor = mixin * t  + diffuse * (1. - t);
}