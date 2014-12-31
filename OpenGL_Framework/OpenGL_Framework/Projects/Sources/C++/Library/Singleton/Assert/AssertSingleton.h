/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
//!
//! @brief �V���O���g��
//! @brief �V���O���g���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Singleton
{
    //-------------------------------------------------------------
    //!
    //! @brief �A�T�[�g�V���O���g��
    //! @brief �A�T�[�g�ɂ��C���X�^���X��1�ɕۏႷ��N���X
    //!
    //-------------------------------------------------------------
    template<class T>
    class C_AssertSingleton
    {
    public:
        C_AssertSingleton();                                                            // �R���X�g���N�^
        virtual ~C_AssertSingleton();                                                   // �f�X�g���N�^
        static T* s_GetInstance();                                                      // �C���X�^���X���擾
    private:
        static T* s_pInstance;                                                          ///< @brief �B��̃C���X�^���X

        C_AssertSingleton(const C_AssertSingleton& rOther) = delete;                    //!< @brief �R�s�[�R���X�g���N�^
        C_AssertSingleton& operator=(const C_AssertSingleton& rOther) = delete;         //!< @brief ������Z�q�̃I�[�o�[���[�h
    };
}


/* ���� */
#include "AssertSingletonImpl.h"
