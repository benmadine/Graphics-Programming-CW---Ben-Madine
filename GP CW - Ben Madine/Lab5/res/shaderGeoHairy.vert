//Version Number
#version 330 core

//The layout qualifers
layout (location = 0) in vec3 VertexPosition;
layout (location = 2) in vec3 VertexNormal;

//Uniform variable
uniform mat4 transform;

//Setting interface block and passing out normal data
out VS_OUT {
	vec3 v_norm;
} vs_out;

//Passing out position data
out vec4 v_pos; 

void main()
{
	//Sets the position of the current vertex and assigns the position data
	gl_Position = transform * vec4(VertexPosition, 1.0);
	v_pos = vec4(VertexPosition, 1.0);

	//Creates normal Matrix (inverses the matrix) and assigns normal data
	mat3 normalMatrix = mat3(transpose(inverse(transform)));
	vs_out.v_norm = normalize(vec3(transform * vec4(normalMatrix * VertexNormal, 0.0)));
}