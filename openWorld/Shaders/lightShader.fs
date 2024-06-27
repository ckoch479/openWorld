#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

in mat3 TBN;
uniform bool hasNormalTextures;

struct material
{
    sampler2D diffuse_texture0;
    sampler2D specular_texture0;
    sampler2D normal_texture0;
    float shininess;
};

struct DirLight
{
vec3 direction;
vec3 ambient;
vec3 diffuse;
vec3 specular;
};

uniform material Material;
uniform sampler2D shadowMap;

uniform vec3 viewPos;
uniform float far_plane;

uniform DirLight dirLight;

vec3 CalcDirLight(DirLight light,vec3 normal, vec3 viewDir, float shadowMod);

float shadowCalculation(vec4 fragPosLightSpace);

vec3 calculateNormal();

void main()
{
    float gamma = 2.2; //this will eventually be changed to a uniform for renderer settings

   vec3 norm = calculateNormal(); 
   vec3 viewDir = normalize(viewPos - fs_in.FragPos);

   float shadow = shadowCalculation(fs_in.FragPosLightSpace);
   
    vec3 result = CalcDirLight(dirLight,norm,viewDir,shadow);
   

    vec4 fragColor = vec4(result,1.0);
    FragColor.rgb = pow(fragColor.rgb,vec3(1.0/gamma));
} 
//this calculates a normal map for objects that have one
vec3 calculateNormal()
{
    vec3 normal;
    
    if(hasNormalTextures)
    {
        normal = texture(Material.normal_texture0, fs_in.TexCoords).rgb;
        normal = normal * 2.0 - 1.0;
        normal = normalize(TBN * -normal); //had to invert normal due to textures being inverted when loaded but not all of them for some reason
    }
    else
    {
    normal = normalize(fs_in.Normal);
    }
    return normal;
}

float shadowCalculation(vec4 fragPosLightSpace)
{
      vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
  
    projCoords = projCoords * 0.5 + 0.5;

    float closestDepth = texture(shadowMap, projCoords.xy).r; 

    float currentDepth = projCoords.z;

  //  vec3 lightPos = dirLight.direction * -20;
   // vec3 normal = normalize(fs_in.Normal);
  //  vec3 lightDir = normalize(lightPos - fs_in.FragPos);
   // float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

   float bias = 0.005;
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

vec3 CalcDirLight(DirLight light,vec3 normal, vec3 viewDir, float shadowMod)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(viewDir, halfwayDir), 0.0), Material.shininess);

    // combine results
    vec3 ambient = light.ambient * vec3(texture(Material.diffuse_texture0, fs_in.TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(Material.diffuse_texture0, fs_in.TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(Material.specular_texture0, fs_in.TexCoords));
    return (ambient + (1.0 - shadowMod) * (diffuse + specular));
}

