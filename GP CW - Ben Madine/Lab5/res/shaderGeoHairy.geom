//Version 
#version 330 core

//Layout qualifr
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

//Passing in normal data
in VS_OUT {
    vec3 v_norm;
} gs_in[];

//creating a float to shrorten lines
const float MAGNITUDE = 0.4;

void GenerateLine(int index)
{
//Setting position of current vertexs
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
	//Restricitng length of line
    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].v_norm, 0.0) * MAGNITUDE;
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0); // first vertex normal
    GenerateLine(1); // second vertex normal
    GenerateLine(2); // third vertex normal
}  
