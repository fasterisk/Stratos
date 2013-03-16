#version 400

uniform vec3 v3Color;

void main(void)
{
	gl_FragColor = vec4(v3Color, 1.0f);
}