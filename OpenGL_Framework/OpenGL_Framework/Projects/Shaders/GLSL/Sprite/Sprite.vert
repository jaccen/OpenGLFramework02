#version 400


/* ���� */
layout (location = 0) in vec3 position;					// ���_���W
layout (location = 1) in vec2 size;						// �T�C�Y
layout (location = 2) in float angle;					// �p�x
layout (location = 3) in vec4 color;					// �F
layout (location = 4) in vec2 textureUpperLeft;			// �e�N�X�`���̍�����W
layout (location = 5) in vec2 textureLowerRight;		// �e�N�X�`���̉E�����W
layout (location = 6) in vec2 textureSize;				// �e�N�X�`���̃T�C�Y


/* �o�� */
out vec2 v_size;										// �T�C�Y
out float v_angle;										// �p�x
out vec4 v_color;										// �F
out vec2 v_textureUpperLeft;							// �e�N�X�`���̍�����W
out vec2 v_textureLowerRight;							// �e�N�X�`���̉E�����W
out vec2 v_textureSize;									// �e�N�X�`���̃T�C�Y


/* ���C���֐� */
void main()
{
	gl_Position = vec4(position, 1.0);
	v_size = size;
	v_angle = angle;
	v_color = color;
	v_textureUpperLeft = textureUpperLeft;
	v_textureLowerRight = textureLowerRight;
	v_textureSize = textureSize;
}
