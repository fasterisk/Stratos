#version 400

layout(location=0) in vec3 in_v3Vertex;
layout(location=1) in vec2 in_v2TexCoords;
layout(location=2) in vec3 in_v3Normal;

uniform mat4 m4ModelViewProjectionMatrix;
uniform mat4 m4ModelViewMatrix;
uniform mat4 m4ShadowMatrix;

uniform mat3 m3NormalMatrix;

uniform vec3 v3LightPosition;
uniform vec3 v3CameraPosition;

smooth out vec2 v2f_v2TexCoords;
smooth out vec3 v2f_v3Normal;
smooth out vec3 v2f_v3LightDirection;
smooth out vec3 v2f_v3ViewDirection;
smooth out vec4 v2f_v4ShadowTexCoords;


void main(void)
{
	v2f_v2TexCoords = in_v2TexCoords;
	v2f_v3Normal = m3NormalMatrix * in_v3Normal;

	vec4 v4Position = m4ModelViewMatrix * vec4(in_v3Vertex, 1.0f);
	vec3 v3Position = v4Position.xyz / v4Position.w;
	
	v2f_v3LightDirection = normalize(v3LightPosition - v3Position);
	v2f_v3ViewDirection = normalize(v3CameraPosition - v3Position);

	v2f_v4ShadowTexCoords = m4ShadowMatrix * vec4(in_v3Vertex, 1.0f);

	gl_Position = m4ModelViewProjectionMatrix * vec4(in_v3Vertex, 1.0f);
}