#version 400

layout( location = 0 ) out vec4 fragcolor;
 
in vec3 v_norm;
uniform mat4 v_pos; 
 
void main() {

	vec4 color;
	color = vec4(0.2,0.1,0.1,1.0);

  fragcolor.a = 0.6;
  fragcolor.rgb = vec3(smoothstep(0.4, 0.8, vdn)) + vec3(color.x,color.y,color.z);
}