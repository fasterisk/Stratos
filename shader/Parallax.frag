#version 400

uniform sampler2D tColorTexture;
uniform sampler2D tSpecularTexture;
uniform sampler2D tShadowMap;
uniform sampler2D tNormalMap;
uniform sampler2D tBumpMap;

in vec2 v2f_v2TexCoords;
in vec4 v2f_v4ShadowTexCoords;
in vec3 v2f_v3LightDirectionTS;
in vec3 v2f_v3EyeDirectionTS;

void main(void)
{
	vec3 v3EyeDirectionTS = normalize(v2f_v3EyeDirectionTS);
	vec3 v3LightDirectionTS = normalize(v2f_v3LightDirectionTS);

	//BUMP
	float fHeight = texture2D(tBumpMap, v2f_v2TexCoords).r;
	fHeight = 0.01f * fHeight - 0.005;

	vec3 v3ViewDirTS = -v3EyeDirectionTS;
	v3ViewDirTS.x = -v3ViewDirTS.x;
	vec2 v2NewTexCoords = v2f_v2TexCoords + (fHeight * v3ViewDirTS.xy);


	vec3 v3NormalTS = normalize(texture2D(tNormalMap, v2NewTexCoords).rgb*2.0 - 1.0);
	
	//DIFFUSE
	vec3 v3DiffuseMaterial = texture(tColorTexture, v2NewTexCoords).rgb;
	float fDiffuseIntensity = max(0.0, dot(v3NormalTS, v3LightDirectionTS));

	vec3 v3DiffuseColor = v3DiffuseMaterial*fDiffuseIntensity;

	//AMBIENT
	vec3 v3AmbientColor = vec3(0.0, 0.0, 0.0);

	//SPECULAR
	vec3 v3SpecularColor = vec3(0.0, 0.0, 0.0);
	if(fDiffuseIntensity != 0)
	{
		vec3 v3SpecularReflection = normalize(reflect(-v3LightDirectionTS, v3NormalTS));
		vec3 v3SpecularIntensity = texture(tSpecularTexture, v2NewTexCoords).rgb;
		float fSpecularComponent = pow(max(0.0, dot(v3EyeDirectionTS, v3SpecularReflection)), 128.0);
		v3SpecularColor = v3SpecularIntensity * fSpecularComponent;
	}

	//SHADOW
	vec3 v3ShadowTexCoords = v2f_v4ShadowTexCoords.xyz/v2f_v4ShadowTexCoords.w;
	v3ShadowTexCoords.z -= 0.0001;
		
	float fInShadow = 1.0;
	if(v3ShadowTexCoords.x < 1.0 && v3ShadowTexCoords.y < 1.0 && v3ShadowTexCoords.x > 0.0 && v3ShadowTexCoords.y > 0.0)
	{
		float fDepth = texture2D(tShadowMap, v3ShadowTexCoords.xy).r;
		fInShadow = (fDepth < v3ShadowTexCoords.z) ? 0.0 : 1.0;
	}

	gl_FragColor = vec4((v3AmbientColor + v3DiffuseColor + v3SpecularColor) * fInShadow, 1.0f);
}