#version 400

uniform sampler2D tColorTexture1;
uniform sampler2D tColorTexture2;

in vec2 v2f_v2TexCoords;

void main(void)
{
	gl_FragColor = texture(tColorTexture1, v2f_v2TexCoords) + texture(tColorTexture2, v2f_v2TexCoords);
}