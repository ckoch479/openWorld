#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

layout (location = 3) in ivec4 boneIds;
layout (location = 4) in vec4 weights;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 modelMatrix;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   vec4 totalPosition = vec4(0.0f);

	for(int i = 0; i < MAX_BONE_INFLUENCE; i++)
	{
		if(boneIds[i] == -1)
			continue;

			if(boneIds[i] >= MAX_BONES)
			{
				totalPosition = vec4(aPos,1.0f);
				break;
			}

			vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(aPos,1.0f);
			totalPosition += localPosition * weights[i];
			vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * aNormal;
	}
	FragPos = vec3(modelMatrix * vec4(totalPosition));
	mat4 viewModel = view * modelMatrix;

	 Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;

	gl_Position = projection *  totalPosition * viewModel;
	TexCoords = aTexCoord;
}	