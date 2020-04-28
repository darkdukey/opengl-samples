#version 330 core
in vec4 vertColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 colorTint;

void main()
{
    FragColor = vec4(colorTint, 1.0);
}
