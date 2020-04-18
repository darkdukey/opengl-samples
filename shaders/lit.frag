#version 330 core
in vec2 TexCoord;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 ambientColor;
uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_normal0;
uniform sampler2D texture_height0;

void main()
{
    FragColor = texture(texture_diffuse0, TexCoord) * vec4(ambientColor, 1.0);
}
