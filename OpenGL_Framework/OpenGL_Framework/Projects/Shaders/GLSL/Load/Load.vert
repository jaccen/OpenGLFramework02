#version 400


/* ���� */
layout (location = 0) in vec3 VertexPosition;		// ���_���W


/* ���C���֐� */
void main()
{
	// ���_���W��ݒ�
	gl_Position = vec4(VertexPosition, 1.0);
}
