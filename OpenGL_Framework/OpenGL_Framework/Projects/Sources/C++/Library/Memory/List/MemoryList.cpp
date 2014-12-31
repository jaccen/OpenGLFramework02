/* �w�b�_�t�@�C�� */
#include "MemoryList.h"


//-------------------------------------------------------------
//!
//! @brief ������
//! @brief �������֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Memory
{

#pragma region �ÓI�����o�ϐ��̏�����


/* �ėp�������v�[���g�p�� */
#ifdef USE_GENERAL_MEMORY_POOL


    /* �ėp�������v�[�� */
    C_GeneralMemoryPool* S_MemoryList::s_pGeneralMemoryPool = nullptr;


#endif


    /* �Ō�̃��X�g�̃|�C���^ */
    S_MemoryList* S_MemoryList::s_pLast = nullptr;


#pragma endregion


/* �ėp�������v�[���g�p�� */
#ifdef USE_GENERAL_MEMORY_POOL


    /* ���������X�g�C�j�V�����C�U�̎Q�ƃJ�E���^ */
    static uint32_t s_niftyCount = 0;


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_MemoryListInitializer::C_MemoryListInitializer()
    {
        if (s_niftyCount == 0)
        {
            S_MemoryList::s_pGeneralMemoryPool = new C_GeneralMemoryPool;
        }

        ++s_niftyCount;
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_MemoryListInitializer::~C_MemoryListInitializer()
    {
        --s_niftyCount;

        if (s_niftyCount == 0)
        {
            if (S_MemoryList::s_pGeneralMemoryPool)
            {
                delete S_MemoryList::s_pGeneralMemoryPool;
                S_MemoryList::s_pGeneralMemoryPool = nullptr;
            }
        }
    }


#endif

}