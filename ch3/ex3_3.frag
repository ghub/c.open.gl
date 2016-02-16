#version 150

in float Color;

out vec4 outColor;

void main()
{
    outColor = vec4(vec3(Color), 1.0);
}
