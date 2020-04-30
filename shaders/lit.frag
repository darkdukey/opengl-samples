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

struct Light {
    vec3 pos;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Camera Position
uniform vec3 viewPos;

uniform Light directLight[2];
uniform int directLightCount;
uniform Light pointLight[6];
uniform int pointLightCount;
uniform Light spotLight[6];
uniform int spotLightCount;
uniform bool no_texture;

vec3 calcDirLight(Light light, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(-light.pos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuseMap, TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuseMap, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specularMap, TexCoord));
    return (ambient + diffuse + specular);
}

vec3 calcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.pos - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.pos - fragPos);
    // float attenuation = 1.0 / (light.constant + light.linear * distance + 
  	// 		     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuseMap, TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuseMap, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specularMap, TexCoord));
    // ambient  *= attenuation;
    // diffuse  *= attenuation;
    // specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main()
{
    vec3 norm = normalize(Normal);
    vec3 finalColor = vec3(0);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // Directional light
    for(int i=0;i<directLightCount;i++){
        finalColor += calcDirLight(directLight[i], norm, viewDir);
    }
    // Point light
    for(int i=0;i<pointLightCount;i++){
        finalColor += calcPointLight(pointLight[i], norm, FragPos, viewDir);
    }
    
    FragColor = vec4(finalColor, 1.0);
}
