#version 400


// ���_�J���[
in vec4 color;


// �ŏI�I�ȃt���O�����g�J���[
layout(location = 0) out vec4 fragColor;


void main()
{
	// ���_�J���[���ŏI�I�ȃt���O�����g�J���[�Ƃ���
	fragColor = color;
}