#version 400


/* ���� */
layout (location = 0) in vec3 VertexPosition;		// ���_���W( ���_��O�� )


/* �萔 */
uniform vec3 Position;                              // ���W


/* ���C���֐� */
void main()
{
	// ���_���W��ݒ�
	gl_Position = vec4((VertexPosition + Position), 1.0);
}
