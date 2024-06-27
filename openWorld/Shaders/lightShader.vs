#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out VS_OUT {
vec3 FragPos;
vec3 Normal;
vec2 TexCoords;
vec4 FragPosLightSpace;
}
 vs_out;

 out mat3 TBN;

uniform mat4 modelMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{
    vec3 ourPos = vec3(vec4(aPos,1.0) * modelMatrix);
    vs_out.FragPos = ourPos; //this may be incorrect, may need to have fragment position multiplied by the model matrix first not entirely sure
    vs_out.Normal = transpose(inverse((mat3(modelMatrix)))) * aNormal;
    vs_out.TexCoords = aTexCoord;
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos,1.0);

    vec3 T = normalize(vec3(modelMatrix * vec4(aTangent,0.0)));
    vec3 B = normalize(vec3(modelMatrix * vec4(aBitangent,0.0))); //vec3 B = cross(T,N); if i want to dynamically calculate it 
    vec3 N = normalize(vec3(modelMatrix * vec4(aNormal,0.0)));
    TBN = mat3(T,B,N);
  
    gl_Position = projection * view  * modelMatrix *  vec4(aPos,1.0);
}	