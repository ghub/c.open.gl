#version 150

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texKitten;

void main()
{
    vec4 colKitten = texture(texKitten, Texcoord);
    outColor = colKitten * vec4(Color, 1.0);
}
