#version 400

layout(location=0) in vec3 in_v3Vertex;
layout(location=1) in vec2 in_v2TexCoords;
layout(location=2) in vec3 in_v3Normal;

uniform mat4 m4ModelViewProjectionMatrix;

smooth out vec2 v2f_v2TexCoords;


void main(void)
{
	v2f_v2TexCoords = in_v2TexCoords;
	gl_Position = m4ModelViewProjectionMatrix * vec4(in_v3Vertex, 1.0f);
}