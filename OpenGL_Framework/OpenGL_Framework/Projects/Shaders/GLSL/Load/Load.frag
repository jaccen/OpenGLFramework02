#version 400


/* ���� */
in vec2 gTexCoord;								// �e�N�X�`�����W


/* �o�� */
layout (location = 0) out vec4 FragColor;		// �t���O�����g�J���[


/* �萔 */
uniform sampler2D Texture;			            // �e�N�X�`��


/* ���C���֐� */
void main()
{
	// �t���O�����g�J���[��ݒ�
	FragColor = texture(Texture, gTexCoord);
}