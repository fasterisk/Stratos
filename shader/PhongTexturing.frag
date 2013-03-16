#version 400

uniform sampler2D tColorTexture;
uniform sampler2D tSpecularTexture;
uniform sampler2D tShadowMap;


in vec2 v2f_v2TexCoords;
in vec3 v2f_v3Normal;
in vec3 v2f_v3LightDirection;
in vec3 v2f_v3ViewDirection;
in vec4 v2f_v4ShadowTexCoords;

void main(void)
{
	vec3 v3ViewDir = normalize(v2f_v3ViewDirection);
	vec3 v3EyeRay = -v3ViewDir;
	vec3 v3LightDir = normalize(v2f_v3LightDirection);
	vec3 v3Normal = normalize(v2f_v3Normal);

	vec3 v3DiffuseMaterial = texture(tColorTexture, v2f_v2TexCoords.st).rgb;
	float fDiffuseIntensity = max(0.0, dot(v3Normal, v3LightDir));

	//diffuse
	vec3 v3DiffuseColor = v3DiffuseMaterial*fDiffuseIntensity;

	//ambient
	vec3 v3AmbientColor = vec3(0.0, 0.0, 0.0);

	//specular
	vec3 v3SpecularColor = vec3(0.0, 0.0, 0.0);
	if(fDiffuseIntensity != 0)
	{
		vec3 v3SpecularReflection = normalize(reflect(-v3LightDir, v3Normal));
		vec3 v3SpecularIntensity = texture(tSpecularTexture, v2f_v2TexCoords.st).rgb;
		float fSpecularComponent = pow(max(0.0, dot(v3ViewDir, v3SpecularReflection)), 128.0);
		v3SpecularColor = v3SpecularIntensity * fSpecularComponent;
	}

	//shadow
	vec3 v3ShadowTexCoords = v2f_v4ShadowTexCoords.xyz/v2f_v4ShadowTexCoords.w;
	v3ShadowTexCoords.z -= 0.000002f;
	float fDepth = texture(tShadowMap, v3ShadowTexCoords.xy).r;
	float fInShadow = (fDepth < v3ShadowTexCoords.z) ? 0.2 : 1.0;

	gl_FragColor = vec4((v3AmbientColor + v3DiffuseColor + v3SpecularColor) * fInShadow, 1.0f);
}