#version 400


// ���_���W�ƒ��_�J���[
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec4 vertexColor;


// �t���O�����g�V�F�[�_�[�ɑ���F
out vec4 color;


// �T�u���[�`��
subroutine void PrimitiveTypeFunction();
subroutine uniform PrimitiveTypeFunction PrimitiveProcess;


uniform mat4 viewProjectionMatrix;		// �r���[�v���W�F�N�V�����s��
uniform float pointSize;				// �_�̃T�C�Y



// �_���L�̏���
subroutine (PrimitiveTypeFunction)
void PointProcess()
{
	gl_PointSize = pointSize;
}


// �����L�̏���
subroutine (PrimitiveTypeFunction)
void LineProcess()
{
}


/* ���C���֐� */
void main()
{
	// �_�̃T�C�Y��ݒ�
	gl_PointSize = pointSize;

	// �r���[�v���W�F�N�V�����s��ƒ��_���W���������l���ŏI�I�Ȓ��_���W�Ƃ���
	gl_Position = viewProjectionMatrix * vec4(vertexPosition, 1.0);
	
	// ���_�J���[�����̂܂܃R�s�[
    color = vertexColor;

	// �e�v���~�e�B�u���L�̏���
	PrimitiveProcess();
}
