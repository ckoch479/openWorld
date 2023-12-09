#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoords;

uniform mat4 modelMatrix;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoord;
   
    
    gl_Position = projection * view  * modelMatrix *  vec4(aPos, 1.0);
}	