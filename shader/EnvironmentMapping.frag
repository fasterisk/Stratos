#version 400

uniform samplerCube tCubeMap;

in vec3 v2f_v3Normal;
in vec3 v2f_v3LightDirection;
in vec3 v2f_v3ViewDirection;


void main(void)
{
	vec3 v3ViewDir = normalize(v2f_v3ViewDirection);
	vec3 v3LightDir = normalize(v2f_v3LightDirection);
	vec3 v3EyeRay = -v3ViewDir;
	vec3 v3Normal = normalize(v2f_v3Normal);

	vec3 v3Reflection = texture(tCubeMap, reflect(v3EyeRay, v3Normal)).rgb;

	float fDiffuseIntensity = max(0.0, dot(v3Normal, v3LightDir));
	float fSpecularIntensity = 0.0f;
	
	if(fDiffuseIntensity != 0)
	{
		vec3 v3SpecularReflection = normalize(reflect(-v3LightDir, v3Normal));
		fSpecularIntensity = pow(max(0.0, dot(v3ViewDir, v3SpecularReflection)), 50.0);
	}

	vec3 v3DiffuseColor = vec3(0.3, 0.3, 0.3) * fDiffuseIntensity;
	vec3 v3SpecularColor = vec3(0.8, 0.6, 0.2) * fSpecularIntensity;

	gl_FragColor = vec4(v3Reflection + v3DiffuseColor + v3SpecularColor, 1.0f);
}