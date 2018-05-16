//Version number
#version 330 core

//Layout Qualifer
layout( location = 0 ) out vec4 fragcolor;

//Passing in normal data and frag position
in vec3 v_norm; 
in vec3 FragPos;  
  
//Uniform variables
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(v_norm);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
	//Final Colour
    vec3 result = (ambient + diffuse + specular) * objectColor;
    fragcolor = vec4(result, 1.0);
} 