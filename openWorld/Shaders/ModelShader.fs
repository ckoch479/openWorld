#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D diffuse_texture0;
void main()
{
    FragColor = texture(diffuse_texture0,TexCoords);
} 