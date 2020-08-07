#version 330 core

in vec2 ourTexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float factor;

void main()
{
	FragColor = mix(texture(texture1, ourTexCoord), texture(texture2, ourTexCoord), factor);
}