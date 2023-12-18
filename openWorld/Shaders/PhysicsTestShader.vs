#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 texCoords;

out vec3 ourColor;

uniform mat4 modelMatrix;
uniform mat4 view;
uniform mat4 projection;
//uniform vec3 aColor;

void main()
{
    ourColor = aColor;

    gl_Position = projection * view * modelMatrix * vec4(aPos, 1.0);
}	