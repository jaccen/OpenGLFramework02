#version 400


/* ���́E�o�͂���}�`�v�f */
layout (points) in;									// �v���~�e�B�u�̎��
layout (triangle_strip, max_vertices = 4) out;		// �v���~�e�B�u�̎�ނƒ��_�̐�


/* �o�� */
out vec2 gTexCoord;									// �e�N�X�`�����W


/* ���͒萔 */
uniform float Width;								// ���̔���
uniform float Height;								// �����̔���
uniform mat4 OrthographicProjectionMatrix ;			// �v���W�F�N�V�����s��


/* ������ */
void Left()
{
    gl_Position = OrthographicProjectionMatrix  * (vec4(0.0, Height, 0.0, 0.0) + gl_in[0].gl_Position);
	gTexCoord = vec2(0.0, 1.0);
	EmitVertex();
	
	gl_Position = OrthographicProjectionMatrix  * (vec4(Width, Height, 0.0, 0.0) + gl_in[0].gl_Position);
	gTexCoord = vec2(1.0, 1.0);
	EmitVertex();
	
	gl_Position = OrthographicProjectionMatrix  * (vec4(0.0, 0.0, 0.0, 0.0) + gl_in[0].gl_Position);
	gTexCoord = vec2(0.0, 0.0);
	EmitVertex();
	
	gl_Position = OrthographicProjectionMatrix  * (vec4(Width, 0.0, 0.0, 0.0) + gl_in[0].gl_Position);
	gTexCoord = vec2(1.0, 0.0);
	EmitVertex();
}



/* ���C���֐� */
void main()
{
    // �������ŏ������s��
    Left();
	
	EndPrimitive();
}


