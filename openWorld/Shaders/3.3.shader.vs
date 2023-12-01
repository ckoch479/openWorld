#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 FragPos;

void main()
{
    FragPos = vec3(0.5,0.5,0.2);//aColor;
   
    
    gl_Position = vec4(aPos, 1.0);
}	