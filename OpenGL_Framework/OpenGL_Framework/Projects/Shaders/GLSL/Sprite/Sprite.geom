#version 400


// �T�u���[�`�����`
subroutine void RenderPassType();
subroutine uniform RenderPassType RenderPass;


/* ���o�͂���v���~�e�B�u�̎�� */
layout (points) in;										// �_( ���� )
layout (triangle_strip, max_vertices = 4) out;			// �O�p�`�X�g���b�v( �o�� )


/* ���� */
in vec2 v_size[];										// �T�C�Y
in float v_angle[];										// �p�x
in vec4 v_color[];										// �F
in vec2 v_textureSize[];								// �e�N�X�`���̃T�C�Y
in vec2 v_textureUpperLeft[];							// �e�N�X�`���̍�����W
in vec2 v_textureLowerRight[];							// �e�N�X�`���̉E�����W


/* �o�� */
out vec4 g_color;										// �F
out vec2 g_textureCoord;								// �e�N�X�`�����W


/* ���j�t�H�[���ϐ� */
uniform mat4 billboardMatrix;							// �r���{�[�h�s��
uniform mat4 viewProjectionMatrix;						// �r���[�v���W�F�N�V�����s��


/* �x�N�g����( ���_���� )Z����]������ */
vec4 RotationVectorAxisZ(vec2 vector, float radian)
{
	vec4 resultVector;

	resultVector.x = vector.x * cos(radian) - vector.y * sin(radian);
	resultVector.y = vector.x * sin(radian) + vector.y * cos(radian);
	resultVector.z = 0.0;
	resultVector.w = 0.0;

	return resultVector;
}


/* �������e���̏��� */
subroutine (RenderPassType)
void PerspectiveProcess()
{
	// �T�C�Y�̔��������߂�
	float halfWidth = 0.5 * v_size[0].x;
	float halfHeight = 0.5 * v_size[0].y;
	
	// �e�N�X�`�����W�����߂�
	vec2 textureCoordUpperLeft = v_textureUpperLeft[0] / v_textureSize[0];
	vec2 textureCoordLowerRight = v_textureLowerRight[0] / v_textureSize[0];

	// �e���W�����߂�
	vec2 direction = vec2(-halfWidth, halfHeight);
	gl_Position = viewProjectionMatrix * (gl_in[0].gl_Position + (billboardMatrix * RotationVectorAxisZ(direction, v_angle[0])));
	g_color = v_color[0];
	g_textureCoord = vec2(textureCoordUpperLeft.x, textureCoordUpperLeft.y);
	EmitVertex();
	
	direction = vec2(halfWidth, halfHeight);
	gl_Position = viewProjectionMatrix * (gl_in[0].gl_Position + (billboardMatrix * RotationVectorAxisZ(direction, v_angle[0])));
	g_color = v_color[0];
	g_textureCoord = vec2(textureCoordLowerRight.x, textureCoordUpperLeft.y);
	EmitVertex();

	direction = vec2(-halfWidth, -halfHeight);
	gl_Position = viewProjectionMatrix * (gl_in[0].gl_Position + (billboardMatrix * RotationVectorAxisZ(direction, v_angle[0])));
	g_color = v_color[0];
	g_textureCoord = vec2(textureCoordUpperLeft.x, textureCoordLowerRight.y);
	EmitVertex();
	
	direction = vec2(halfWidth, -halfHeight);
	gl_Position = viewProjectionMatrix * (gl_in[0].gl_Position + (billboardMatrix * RotationVectorAxisZ(direction, v_angle[0])));
	g_color = v_color[0];
	g_textureCoord = vec2(textureCoordLowerRight.x, textureCoordLowerRight.y);
	EmitVertex();
}


/* �����e���̏��� */
subroutine (RenderPassType)
void OrthographicProcess()
{
	// �T�C�Y�̔��������߂�
	float halfWidth = 0.5 * v_size[0].x;
	float halfHeight = 0.5 * v_size[0].y;

	// �e�N�X�`�����W�����߂�
	vec2 textureCoordUpperLeft = v_textureUpperLeft[0] / v_textureSize[0];
	vec2 textureCoordLowerRight = v_textureLowerRight[0] / v_textureSize[0];

	vec2 direction = vec2(-halfWidth, halfHeight);
	gl_Position = viewProjectionMatrix * (gl_in[0].gl_Position + RotationVectorAxisZ(direction, v_angle[0]));
	g_textureCoord = vec2(textureCoordUpperLeft.x, textureCoordLowerRight.y);
	g_color = v_color[0];
	EmitVertex();
	
	direction = vec2(-halfWidth, -halfHeight);
	gl_Position = viewProjectionMatrix * (gl_in[0].gl_Position + RotationVectorAxisZ(direction, v_angle[0]));
	g_textureCoord = textureCoordUpperLeft;
	g_color = v_color[0];
	EmitVertex();
	
	direction = vec2(halfWidth, halfHeight);
	gl_Position = viewProjectionMatrix * (gl_in[0].gl_Position + RotationVectorAxisZ(direction, v_angle[0]));
	g_textureCoord = textureCoordLowerRight;
	g_color = v_color[0];
	EmitVertex();
	
	direction = vec2(halfWidth, -halfHeight);
	gl_Position = viewProjectionMatrix * (gl_in[0].gl_Position + RotationVectorAxisZ(direction, v_angle[0]));
	g_textureCoord = vec2(textureCoordLowerRight.x, textureCoordUpperLeft.y);
	g_color = v_color[0];
	EmitVertex();
}


/* ���C���֐� */
void main()
{
	// �J�����ɍ��킹���������s��
	RenderPass();
	
	// �����I��
	EndPrimitive();
}
