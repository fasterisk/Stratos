#version 400

layout(location=0) in vec3 in_v3Vertex;
layout(location=1) in vec2 in_v2TexCoords;
layout(location=2) in vec3 in_v3Normal;
layout(location=3) in vec3 in_v3Tangent;
layout(location=4) in vec3 in_v3Bitangent;

uniform mat4 m4ModelViewProjectionMatrix;
uniform mat4 m4ModelViewMatrix;
uniform mat4 m4ViewMatrix;
uniform mat4 m4ShadowMatrix;

uniform mat3 m3NormalMatrix;

uniform vec3 v3LightPosition;
uniform vec3 v3CameraPosition;

out vec2 v2f_v2TexCoords;
out vec4 v2f_v4ShadowTexCoords;
out vec3 v2f_v3LightDirectionTS;
out vec3 v2f_v3EyeDirectionTS;
out vec3 v2f_v3EyeDirectionCS;

void main(void)
{
	vec4 v4PositionCS = m4ModelViewMatrix * vec4(in_v3Vertex, 1.0f);
	vec3 v3PositionCS = v4PositionCS.xyz / v4PositionCS.w;
	
	vec3 v3EyeDirectionCS = vec3(0,0,0) - v3PositionCS;

	vec3 v3LightPositionCS = (m4ViewMatrix * vec4(v3LightPosition, 1.0f)).xyz;
	vec3 v3LightDirectionCS = v3LightPositionCS - v3PositionCS;

	vec3 v3TangentCS = m3NormalMatrix * in_v3Tangent;
	vec3 v3BitangentCS = m3NormalMatrix * in_v3Bitangent;
	vec3 v3NormalCS = m3NormalMatrix * in_v3Normal;

	mat3 m3TBN = transpose(mat3(
		v3TangentCS,
		v3BitangentCS,
		v3NormalCS
	));

	v2f_v3LightDirectionTS = m3TBN * v3LightDirectionCS;
	v2f_v3EyeDirectionTS = m3TBN * v3EyeDirectionCS;

	v2f_v4ShadowTexCoords = m4ShadowMatrix * vec4(in_v3Vertex, 1.0f);
	v2f_v2TexCoords = in_v2TexCoords;


	gl_Position = m4ModelViewProjectionMatrix * vec4(in_v3Vertex, 1.0f);
}