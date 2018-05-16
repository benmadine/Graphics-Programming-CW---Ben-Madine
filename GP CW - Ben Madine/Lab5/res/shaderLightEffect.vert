//Version Number
#version 330 core

//The layout qualifers
layout (location = 0) in vec3 VertexPosition;
layout (location = 2) in vec3 VertexNormal;

//Passing out the normal and position data
out vec3 v_norm;
out vec4 v_pos; 

//Uniform variable
uniform mat4 transform;

void main()
{
	//Assigning the normal and position data
	v_norm = VertexNormal;
	v_pos = vec4(VertexPosition, 1.0);
	
	// Sets the position of the current vertex
	gl_Position = transform * vec4(VertexPosition, 1.0);
}