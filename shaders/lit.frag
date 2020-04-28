#version 330 core
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

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
uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_normal0;
uniform sampler2D texture_height0;

//Diffuse Color
vec3 calcDiffuse(vec3 lightDir, vec3 lightColor, vec3 norm) {
    lightDir = normalize(lightDir);
    float diff = max(dot(norm, lightDir), 0.0);
    return (lightColor * diff);
}

//Specular Color
vec3 calcSpecular(vec3 viewDir, vec3 lightDir, vec3 lightColor, vec3 norm, float strength, float shininess){
    viewDir = normalize(viewDir);
    lightDir = normalize(lightDir);

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    return (lightColor * (spec * strength)); 
}

vec3 calcMaterial(vec3 viewDir, vec3 lightDir, vec3 lightColor, vec3 norm, vec3 ambient, float strength, float shininess){
    vec3 diffuse = calcDiffuse(lightDir, lightColor, norm);
    vec3 specular = calcSpecular(viewDir, lightDir, lightColor, norm, strength, shininess);
    return (ambient + diffuse + specular);
}

void main()
{
    vec3 norm = normalize(Normal);

    //Calculate diffuse color for each direct light
    vec3 diffuseColor = vec3(0);
    vec3 specularColor = vec3(0);
    vec4 baseColor = texture(texture_diffuse0, TexCoord);
    if(no_texture)
        baseColor = vec4(1);
    vec3 finalColor = vec3(0);

    //TODO: define this base on material file
    float specularStrength = 0.5;
    int shininess = 32;
    
    vec3 viewDir = viewPos - FragPos;
    
    // Directional light
    for(int i=0;i<directLightCount;i++){
        finalColor += calcMaterial(viewDir, -directLightDir[i], directLightColor[i], norm, ambientColor, specularStrength, shininess);
    }

    // Point light
    for(int i=0;i<pointLightCount;i++){
        vec3 lightDir = pointLightPos[i] - FragPos;
        finalColor += calcMaterial(viewDir, lightDir, pointLightColor[i], norm, ambientColor, specularStrength, shininess);
    }
    
    FragColor = vec4(finalColor * baseColor.xyz, 1.0);
}
