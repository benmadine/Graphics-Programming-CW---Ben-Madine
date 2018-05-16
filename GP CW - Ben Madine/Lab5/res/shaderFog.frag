//Version number
#version 400

//Uniform Variables
uniform mat4 u_pm;
uniform mat4 u_vm;
uniform vec3 lightDir;
uniform float minDist;
uniform float maxDist;
uniform vec3 fogColor;
uniform float zpos;

//Layout Qualifer
layout( location = 0 ) out vec4 fragcolor;
 
//Passing in the normal and position data
in vec3 v_norm;
in vec4 v_pos; 
 
vec3 toonRim() {
//Calculating the rim contribution
	vec3 n = normalize(mat3(u_vm) * v_norm);      // convert normal to view space
	vec3 p = vec3((u_pm) * v_pos);                // position in clip space
	vec3 v = normalize(p);                        // normalised eye vector
	float vdn = 0.6 - max(dot(v, n), 0.0);        // the rim contribution
//Ending Rim 

//Start Toon
//Calculating intensity usng dot product, and creating colour varaible
	float intensity;
	vec4 color;
	intensity = dot(lightDir,v_norm);

//Chaning colour depending on intensity value
	if (intensity > 0.95)
		color = vec4(4.0,0.5,0.7,1.0);
	else if (intensity > 0.5)
		color = vec4(0.2,0.6,0.3,1.0);
	else if (intensity > 0.25)
		color = vec4(0.1,0.2,0.8,1.0);
	else
		color = vec4(0.2,0.7,0.1,1.0);

//Returning the colour
  fragcolor.a = 0.6;
  return vec3(smoothstep(0.4, 0.8, vdn)) + vec3(color.x,color.y,color.z);
}

void main() 
{
//Setting the fog variables and calculating attributes for it, calling the toonRim and
//getting final colour
	float dist = abs( zpos );
	float fogFactor = (maxDist - dist) / (maxDist - minDist);
	fogFactor = clamp( fogFactor, 0.0, 1.0 );
	vec3 toonRim = toonRim();

	vec3 color = mix( fogColor, toonRim, fogFactor);
	fragcolor = vec4(color, 1.0);
}
