#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D diffuse_texture0;
uniform sampler2D specular_texture0;

void main()
{
    FragColor = mix(texture(diffuse_texture0,TexCoords), texture(specular_texture0,TexCoords),0.5f);
} 