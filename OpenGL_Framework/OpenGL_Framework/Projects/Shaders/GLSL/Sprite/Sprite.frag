#version 400


/* ���� */
in vec4 g_color;												// �F
in vec2 g_textureCoord;											// �e�N�X�`�����W


/* �o�� */
layout (location = 0) out vec4 f_fragmentColor;					// �t���O�����g�F


/* ���j�t�H�[���ϐ� */
uniform sampler2D Texture;										// �e�N�X�`��


/* ���C���֐� */
void main()
{
	vec4 textureColor = texture(Texture, g_textureCoord);
	f_fragmentColor = textureColor * g_color;
}