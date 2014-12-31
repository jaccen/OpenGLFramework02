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
uniform int Alignment;								// ��������


/* �萔 */
const int LEFT = 0;
const int RIGHT = 1;


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


/* �E���� */
void Right()
{
    gl_Position = OrthographicProjectionMatrix  * (vec4(-Width, Height, 0.0, 0.0) + gl_in[0].gl_Position);
	gTexCoord = vec2(0.0, 1.0);
	EmitVertex();
	
	gl_Position = OrthographicProjectionMatrix  * (vec4(0.0, Height, 0.0, 0.0) + gl_in[0].gl_Position);
	gTexCoord = vec2(1.0, 1.0);
	EmitVertex();
	
	gl_Position = OrthographicProjectionMatrix  * (vec4(-Width, 0.0, 0.0, 0.0) + gl_in[0].gl_Position);
	gTexCoord = vec2(0.0, 0.0);
	EmitVertex();
	
	gl_Position = OrthographicProjectionMatrix  * (vec4(0.0, 0.0, 0.0, 0.0) + gl_in[0].gl_Position);
	gTexCoord = vec2(1.0, 0.0);
	EmitVertex();
}


/* �������� */
void Center()
{
    // ���ƍ����̔���
    float HalfWidth = Width / 2.0;
    float HalfHeight = Height /2.0;

    gl_Position = OrthographicProjectionMatrix  * (vec4(-HalfWidth, Height, 0.0, 0.0) + gl_in[0].gl_Position);
	gTexCoord = vec2(0.0, 1.0);
	EmitVertex();
	
	gl_Position = OrthographicProjectionMatrix  * (vec4(HalfWidth, Height, 0.0, 0.0) + gl_in[0].gl_Position);
	gTexCoord = vec2(1.0, 1.0);
	EmitVertex();
	
	gl_Position = OrthographicProjectionMatrix  * (vec4(-HalfWidth, 0.0, 0.0, 0.0) + gl_in[0].gl_Position);
	gTexCoord = vec2(0.0, 0.0);
	EmitVertex();
	
	gl_Position = OrthographicProjectionMatrix  * (vec4(HalfWidth, 0.0, 0.0, 0.0) + gl_in[0].gl_Position);
	gTexCoord = vec2(1.0, 0.0);
	EmitVertex();
}


/* ���C���֐� */
void main()
{
    // ���������ɉ������������s��
    if (Alignment == LEFT)
    {
	    Left();
    }
    else if (Alignment == RIGHT)
    {
        Right();
    }
    else
    {
        Center();
    }
	
	EndPrimitive();
}


