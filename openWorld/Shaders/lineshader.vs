#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in int  triangleIndex;

out vec3 ourcolor;

uniform mat4 modelMatrix[3]; //model matrix is used to transform 3 vertices of this triangle to match its collider box
uniform mat4 view;
uniform mat4 projection;

void main()
{
    ourcolor = aColor;
   
    vec4 worldTranformed = modelMatrix[triangleIndex] * vec4(aPos,1.0);
    gl_Position = projection * view * worldTranformed;//modelMatrix[triangleIndex] * vec4(aPos, 1.0);

    //gl_Position = vec4(aPos,1.0f);
}	