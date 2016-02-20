#version 150

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texKitten;

void main()
{
    float y = 0.5 - abs(Texcoord.y - 0.5);
    vec4 colKitten = texture(texKitten, vec2(Texcoord.x, y));
    outColor = colKitten;
}
