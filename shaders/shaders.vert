#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 translation;
uniform mat4 rotation;
out vec4 ourColor; 

void main()
{
    vec4 value = translation * vec4(aPos, 1.0);

    gl_Position = rotation * value;

    ourColor = aColor;
}

