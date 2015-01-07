/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Pool/General/GeneralMemoryPool.h"


//-------------------------------------------------------------
//!
//! @brief ������
//! @brief �������֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Memory
{
    /* �O���錾 */
    class C_MemoryListInitializer;


    //-------------------------------------------------------------
    //!
    //! @brief �������[���X�g
    //! @brief �����������X�g��ɊǗ�����N���X
    //!
    //-------------------------------------------------------------
    struct S_MemoryList
    {
        friend C_MemoryListInitializer;                         // ���������X�g�C�j�V�����C�U�N���X���t�����h��
    public:
        size_t size_ = 0;                                       ///< @brief �������T�C�Y
        const char* pFileName_ = nullptr;                       ///< @brief �t�@�C����
        int32_t lineNumber_ = 0;                                ///< @brief �s��
        bool usePoolFlag_ = false;                              ///< @brief �v�[�����g�p���Ă��邩���f����t���O
        S_MemoryList* pNext_ = nullptr;                         ///< @brief ���̃��X�g

/* �ėp�������v�[���g�p�� */
#ifdef USE_GENERAL_MEMORY_POOL

        static C_GeneralMemoryPool* s_pGeneralMemoryPool;       ///< @brief �ėp�������v�[��

#endif

        static S_MemoryList* s_pLast;                           ///< @brief �Ō�̃��X�g�̃|�C���^
    };



    /* �ėp�������v�[���g�p�� */
#ifdef USE_GENERAL_MEMORY_POOL


    //-------------------------------------------------------------
    //!
    //! @brief �������[���X�g�C�j�V�����C�U
    //! @brief ���������X�g�̐ÓI�ϐ��̎�����ۏ؂��邽�߂̃N���X
    //!
    //-------------------------------------------------------------
    class C_MemoryListInitializer
    {
    public:
        C_MemoryListInitializer();                              // �R���X�g���N�^
        ~C_MemoryListInitializer();                             // �f�X�g���N�^
    };


    /* �������[���X�g�C�j�V�����C�U�̃C���X�^���X */
    static C_MemoryListInitializer s_memoryListInitializer;


#endif

}