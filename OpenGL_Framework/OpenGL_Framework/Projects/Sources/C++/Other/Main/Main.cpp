/* �w�b�_�t�@�C�� */
#include "../StaticLibrary/StaticLibrary.h"
#include "../../Game/ConnectWars/ConnectWars.h"


/* �����[�X�� */
#ifndef _DEBUG


// �T�u�V�X�e����Windows�ɕύX���A�G���g���[�|�C���g��main�֐��Ƃ���
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


#endif


/*************************************************************//**
 *
 *  @brief  ���C���֐�
 *  @param  �R�}���h���C������n���ꂽ�����̐�
 *  @param  �R�}���h���C���̈����Ƃ��ēn���ꂽ������
 *  @return ����I���F0
 *  @return �ُ�I���F-1
 *
 ****************************************************************/
int main(int argc, char* argv[])
{
    // �Q�[���𐶐����A���s
    auto pGame = std::make_unique<ConnectWars::C_ConnectWars>();
    if (pGame->Run() == false) return -1;

    return 0;
}
