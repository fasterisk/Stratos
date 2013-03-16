#version 400

uniform sampler2D tLensFlareTexture;
uniform sampler2D tDepthTexture;

uniform vec4 v4SunPosition;
uniform vec2 v2Aspect;
uniform vec2 v2LensFlarePosition;
uniform vec4 v4LensFlareColor;
uniform float fLensFlareScale;

in vec4 v2f_v4Position;
in vec2 v2f_v2TexCoords;

void main(void)
{
	vec2 v2LensFlareTexCoords = (v2LensFlarePosition.xy - v2f_v4Position.xy) * v2Aspect / fLensFlareScale + vec2(0.5, 0.5);
	if(v2LensFlareTexCoords.x > 1 || v2LensFlareTexCoords.y > 1 || v2LensFlareTexCoords.x < 0 || v2LensFlareTexCoords.y < 0 || v4SunPosition.z > texture(tDepthTexture, (vec2(v4SunPosition.xy) + 1.0) / 2.0).r)
		discard;
	else
		gl_FragColor = texture(tLensFlareTexture, v2LensFlareTexCoords) * v4LensFlareColor;
}