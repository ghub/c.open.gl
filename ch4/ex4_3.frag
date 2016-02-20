#version 150

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texKitten;
uniform float time;

void main()
{
    float x = Texcoord.x;
    float y = Texcoord.y;
    vec4 colKitten;

    if (y < 0.5)
    {
        colKitten = texture(texKitten, vec2(x, y));
    }
    else
    {
        x = Texcoord.x + 0.03 * sin(60 * y + 6 * time);
        y = 1 - y;
        colKitten = texture(texKitten, vec2(x, y));
        colKitten.rgb *= 0.6;
    }

    outColor = colKitten;
}
