#version 400

uniform sampler2D tColorTexture;

in vec2 v2f_v2TexCoords;

void main(void)
{
	gl_FragColor = texture(tColorTexture, v2f_v2TexCoords.st);
}