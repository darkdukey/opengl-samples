#version 330 core
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

struct Material {
    vec3 ambientValue;
    vec3 diffuseValue;
    vec3 specularValue;
    float shininess;
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
// uniform sampler2D texture_diffuse0;
// uniform sampler2D texture_specular0;
// uniform sampler2D texture_normal0;
// uniform sampler2D texture_height0;

//Diffuse Color
vec3 calcDiffuse(vec3 lightDir, vec3 lightColor, vec3 norm) {
    lightDir = normalize(lightDir);
    float diff = max(dot(norm, lightDir), 0.0);
    return (lightColor * diff);
}

//Specular Color
vec3 calcSpecular(vec3 viewDir, vec3 lightDir, vec3 lightColor, vec3 norm, float shininess){
    viewDir = normalize(viewDir);
    lightDir = normalize(lightDir);

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    return (lightColor * spec); 
}

vec3 calcMaterial(vec3 viewDir, vec3 lightDir, vec3 lightColor, vec3 norm, Material m){
    vec3 ambient = lightColor * m.ambientValue;
    vec3 diffuse = calcDiffuse(lightDir, lightColor, norm) * m.diffuseValue;
    vec3 specular = calcSpecular(viewDir, lightDir, lightColor, norm, m.shininess) * m.specularValue;
    return (ambient + diffuse + specular);
}

void main()
{
    vec3 norm = normalize(Normal);

    //Calculate diffuse color for each direct light
    vec3 lightDir;
    vec3 lightColor = vec3(0);
    vec3 viewDir = viewPos - FragPos;
    
    // Directional light
    for(int i=0;i<directLightCount;i++){
        lightColor += calcMaterial(viewDir, -directLightDir[i], directLightColor[i], norm, material);
    }

    // Point light
    for(int i=0;i<pointLightCount;i++){
        vec3 lightDir = pointLightPos[i] - FragPos;
        lightColor += calcMaterial(viewDir, lightDir, pointLightColor[i], norm, material);
    }

    FragColor = vec4(lightColor, 1.0);
}
