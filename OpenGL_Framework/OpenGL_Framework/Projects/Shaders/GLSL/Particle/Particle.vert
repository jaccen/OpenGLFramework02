#version 400


/* ���� */
layout (location = 0) in vec3 vertexPosition;			// ���_���W
layout (location = 1) in float angle;					// �p�x
layout (location = 2) in float width;					// ��
layout (location = 3) in float height;					// ����
layout (location = 4) in vec4 color;					// �F


/* �o�� */
out float v_angle;										// �p�x
out float v_width;										// ��
out float v_height;										// ����
out vec4 v_color;										// �F


/* ���C���֐� */
void main()
{
	// ���ׂĂ̒l�����̂܂܃W�I���g���V�F�[�_�[�֑���
	gl_Position = vec4(vertexPosition, 1.0);
	v_angle = angle;
	v_width = width;
	v_height = height;
	v_color = color;
}
