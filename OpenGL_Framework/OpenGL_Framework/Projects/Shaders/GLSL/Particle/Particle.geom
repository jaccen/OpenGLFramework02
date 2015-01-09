#version 400


/* ���o�͂���v���~�e�B�u�̎�� */
layout (points) in;										// �_( ���� )
layout (triangle_strip, max_vertices = 4) out;			// �O�p�`�X�g���b�v( �o�� )


/* ���� */
in float v_angle[];										// �p�x
in float v_width[];										// ��
in float v_height[];									// ����
in vec4 v_color[];										// �F


/* �o�� */
out vec4 g_color;										// �F
out vec2 g_textureCoord;								// �e�N�X�`�����W


/* ���j�t�H�[���ϐ� */
uniform mat4 billboardMatrix;							// �r���{�[�h�s��
uniform mat4 modelMatrix;								// ���f���s��
uniform mat4 viewProjectionMatrix;						// �r���[�v���W�F�N�V�����s��
uniform vec2 textureCoordUpperLeft;						// �e�N�X�`�����W�̍���
uniform vec2 textureCoordLowerRight;					// �e�N�X�`�����W�̉E��



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


/* ���C���֐� */
void main()
{
	// �T�C�Y�̔���
	float halfWidth = 0.5 * v_width[0];
	float halfHeight = 0.5 * v_height[0];

	// ���f���r���[�v���W�F�N�V�����s������߂�
	mat4 modelViewProjectionMatrix = viewProjectionMatrix * modelMatrix;

	// �e���W�����߂�
	vec2 direction = vec2(-halfWidth, halfHeight);
	
	gl_Position = modelViewProjectionMatrix * (gl_in[0].gl_Position + (billboardMatrix * RotationVectorAxisZ(direction, v_angle[0])));
	g_color = v_color[0];
	g_textureCoord = textureCoordUpperLeft;
	EmitVertex();
	
	direction.xy = vec2(-halfWidth, -halfHeight);
	gl_Position = modelViewProjectionMatrix * (gl_in[0].gl_Position + (billboardMatrix * RotationVectorAxisZ(direction, v_angle[0])));
	g_color = v_color[0];
	g_textureCoord = vec2(textureCoordUpperLeft.x, textureCoordLowerRight.y);
	EmitVertex();

	direction.xy = vec2(halfWidth, halfHeight);
	gl_Position = modelViewProjectionMatrix * (gl_in[0].gl_Position + (billboardMatrix * RotationVectorAxisZ(direction, v_angle[0])));
	g_color = v_color[0];
	g_textureCoord = vec2(textureCoordLowerRight.x, textureCoordUpperLeft.y);
	EmitVertex();
	
	direction.xy = vec2(halfWidth, -halfHeight);
	gl_Position = modelViewProjectionMatrix * (gl_in[0].gl_Position + (billboardMatrix * RotationVectorAxisZ(direction, v_angle[0])));
	g_color = v_color[0];
	g_textureCoord = textureCoordLowerRight;
	EmitVertex();
	
	// �����I��
	EndPrimitive();
}
