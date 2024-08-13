#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 5) in ivec4 boneIds;
layout (location = 6) in vec4 weights;

uniform mat4 lightSpaceMatrix;
uniform mat4 modelMatrix;

uniform mat4 finalBoneMatrices[100];

void main()
{
    vec4 totalPosition = vec4(0.0f);
    for(int i = 0 ; i < 4 ; i++)
    {
        if(boneIds[i] == -1) 
            continue;
        if(boneIds[i] >=100) 
        {
            totalPosition = vec4(aPos,1.0f);
            break;
        }
        vec4 localPosition = finalBoneMatrices[boneIds[i]] * vec4(aPos,1.0f);
        totalPosition += localPosition * weights[i];
   }
   
    
    //gl_Position = lightSpaceMatrix * modelMatrix * vec4(aPos, 1.0);
    gl_Position = lightSpaceMatrix * modelMatrix * totalPosition;
}	