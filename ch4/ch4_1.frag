#version 150

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texCheckerboard;

void main()
{
    outColor = texture(texCheckerboard, Texcoord);
}
