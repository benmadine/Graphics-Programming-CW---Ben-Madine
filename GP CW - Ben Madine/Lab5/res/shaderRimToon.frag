//Version number
#version 400

//Unfrom variable
uniform mat4 u_pm;
uniform mat4 u_vm;
uniform mat4 v_pos; 
uniform vec3 lightDir;
 
//Layout Qualifer
layout( location = 0 ) out vec4 fragcolor;
 
//Passing in normal data
in vec3 v_norm;

void main() 
{
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
		color = vec4(1.0,0.5,0.5,1.0);
	else if (intensity > 0.5)
		color = vec4(0.6,0.3,0.3,1.0);
	else if (intensity > 0.25)
		color = vec4(0.4,0.2,0.2,1.0);
	else
		color = vec4(0.2,0.1,0.1,1.0);

//Setting the final colour values
  fragcolor.a = 0.6;
  fragcolor.rgb = vec3(smoothstep(0.4, 0.8, vdn)) + vec3(color.x,color.y,color.z);
}