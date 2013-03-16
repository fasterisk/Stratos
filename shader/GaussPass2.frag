#version 400

uniform sampler2D tColorTexture;
uniform float fPixelOffset;

in vec2 v2f_v2TexCoords;

void main(void)
{
	vec4 v4Color = vec4(0.0);
	
	v4Color += texture2D(tColorTexture, vec2(v2f_v2TexCoords.x, v2f_v2TexCoords.y - 4.0*fPixelOffset)) * 0.05;
	v4Color += texture2D(tColorTexture, vec2(v2f_v2TexCoords.x, v2f_v2TexCoords.y - 3.0*fPixelOffset)) * 0.09;
	v4Color += texture2D(tColorTexture, vec2(v2f_v2TexCoords.x, v2f_v2TexCoords.y - 2.0*fPixelOffset)) * 0.12;
	v4Color += texture2D(tColorTexture, vec2(v2f_v2TexCoords.x, v2f_v2TexCoords.y - 1.0*fPixelOffset)) * 0.15;
	v4Color += texture2D(tColorTexture, vec2(v2f_v2TexCoords.x, v2f_v2TexCoords.y - 0.0*fPixelOffset)) * 0.16;
	v4Color += texture2D(tColorTexture, vec2(v2f_v2TexCoords.x, v2f_v2TexCoords.y + 1.0*fPixelOffset)) * 0.15;
	v4Color += texture2D(tColorTexture, vec2(v2f_v2TexCoords.x, v2f_v2TexCoords.y + 2.0*fPixelOffset)) * 0.12;
	v4Color += texture2D(tColorTexture, vec2(v2f_v2TexCoords.x, v2f_v2TexCoords.y + 3.0*fPixelOffset)) * 0.09;
	v4Color += texture2D(tColorTexture, vec2(v2f_v2TexCoords.x, v2f_v2TexCoords.y + 4.0*fPixelOffset)) * 0.05;
	
	gl_FragColor = v4Color;
}