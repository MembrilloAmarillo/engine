#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 texture;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 view;
uniform mat4 projection;

out vec4 ourColor; 

void main()
{
	vec4 value = projection * scale * vec4(aPos, 1.0f);
    
	gl_Position = translation * rotation *  value;
    
    ourColor = aColor;
}

