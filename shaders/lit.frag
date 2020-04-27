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
uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_normal0;
uniform sampler2D texture_height0;

void main()
{
    vec3 norm = normalize(Normal);

    //Calculate diffuse color for each direct light
    vec3 lightDir;
    vec3 viewDir;
    vec3 diffuseColor = vec3(0);
    vec3 specularColor = vec3(0);
    vec4 baseColor = texture(texture_diffuse0, TexCoord);
    //TODO: define this base on material file
    float specularStrength = 0.5;
    int shininess = 32;
    
    // Directional light
    for(int i=0;i<directLightCount;i++){
        lightDir = normalize(directLightDir[i]);
        float diff = max(dot(norm, -lightDir), 0.0);
        diffuseColor += diff * directLightColor[i];
    }

    // Point light
    for(int i=0;i<pointLightCount;i++){
        //Diffuse color
        lightDir = normalize(pointLightPos[i] - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        diffuseColor += diff * pointLightColor[i];
        //Specular color
        viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        specularColor += specularStrength * spec * pointLightColor[i]; 
    }

    vec3 result = (ambientColor + diffuseColor + specularColor) * baseColor.xyz;
    FragColor = vec4(result, 1.0);
}
