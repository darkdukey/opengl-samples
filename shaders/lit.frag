#version 330 core
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

struct Material {
    sampler2D diffuseMap;
    sampler2D specularMap;
    float     shininess;
}; 

uniform Material material;

// Camera Position
uniform vec3 viewPos;

uniform vec3 ambientColor;
uniform vec3 directLightDir[2];
uniform vec3 directLightColor[2];
uniform int directLightCount;
uniform vec3 pointLightPos[6];
uniform vec3 pointLightColor[6];
uniform int pointLightCount;
uniform vec3 spotLightPos[6];
uniform vec3 spotLightColor[6];
uniform int spotLightCount;
uniform bool no_texture;

//Diffuse Color
vec3 calcDiffuse(vec3 lightDir, vec3 lightColor, vec3 norm, Material m, vec2 TexCoord) {
    lightDir = normalize(lightDir);
    float diff = max(dot(norm, lightDir), 0.0);
    return (lightColor * diff) * vec3(texture(m.diffuseMap, TexCoord));
}

//Specular Color
vec3 calcSpecular(vec3 viewDir, vec3 lightDir, vec3 lightColor, vec3 norm, Material m, vec2 TexCoord){
    viewDir = normalize(viewDir);
    lightDir = normalize(lightDir);

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), m.shininess);
    return (lightColor * spec * vec3(texture(m.specularMap, TexCoord))); 
}

vec3 calcMaterial(vec3 viewDir, vec3 lightDir, vec3 lightColor, vec3 norm, Material m, vec2 TexCoord){
    vec3 diffuse = calcDiffuse(lightDir, lightColor, norm, m, TexCoord);
    vec3 specular = calcSpecular(viewDir, lightDir, lightColor, norm, m, TexCoord);
    return (diffuse + specular);
}

void main()
{
    vec3 norm = normalize(Normal);
    vec3 finalColor = vec3(0);
    vec3 viewDir = viewPos - FragPos;
    
    // Directional light
    for(int i=0;i<directLightCount;i++){
        finalColor += calcMaterial(viewDir, -directLightDir[i], directLightColor[i], norm, material, TexCoord);
    }

    // Point light
    for(int i=0;i<pointLightCount;i++){
        vec3 lightDir = pointLightPos[i] - FragPos;
        finalColor += calcMaterial(viewDir, lightDir, pointLightColor[i], norm, material, TexCoord);
    }
    
    FragColor = vec4(finalColor, 1.0);
}
