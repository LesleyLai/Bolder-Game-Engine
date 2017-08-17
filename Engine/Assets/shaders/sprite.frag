#version 330 core
out vec4 FragColor;

uniform float gv;

void main()
{
   FragColor = vec4(1.0f, gv, 0.0f, 1.0f);
}
