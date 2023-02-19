#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texture;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 view;
uniform mat4 projection;

out vec4 ourColor; 

/*
	TODO:
	- Implement Texture Value Estimation
	*/
vec4 Texture_Mapping()
{
	return vec4(0.5, 0.5, 0.5, 1.0);
}

void main()
{
	vec4 value = /*projection */ scale * vec4(aPos, 1.0f);
  
	gl_Position = translation * rotation *  value;
#if 1
	if (texture.x == 0 && texture.y == 0) {
		ourColor = vec4(0.5, 0.5, 0.5, 1.0);
	} else {
		ourColor = Texture_Mapping();
	}

	vec4 light_trayectory = vec4(1.0, 1.0, 1.0, 0.0);

	ourColor = (light_trayectory + vec4(normals, 1.0)) * ourColor;
#else
	ourColor = vec4(1.0, 1.0, 1.0, 1.0);
#endif
}


/* == ABOUT LIGHT ==

	Incident Light = reflected light + scattered light + absorbed light + transmited light

	## Lambert Illumination Model ## 


	
	*/
