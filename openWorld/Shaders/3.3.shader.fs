#version 330 core
out vec4 FragColor;

in vec4 ourColor;

void main()
{
    vec4 alphaColor = ourColor;
    
    if(alphaColor.a < 0.1)
        discard;

    FragColor = alphaColor;
} 