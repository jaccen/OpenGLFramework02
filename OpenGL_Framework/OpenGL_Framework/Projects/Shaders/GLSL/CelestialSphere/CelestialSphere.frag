#version 400


/* input */
in vec2 f_textureCoord;


/* output */
layout (location = 0) out vec4 fragmentColor;


/* uniform variable */
uniform sampler2D u_texture;


/* ƒƒCƒ“ŠÖ” */
void main()
{
	fragmentColor = texture(u_texture, f_textureCoord);
}