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
    //! @brief �V���O���g��
    //! @brief �C���X�^���X��1�ɕۏႷ��N���X
    //!
    //-------------------------------------------------------------
    template<typename T>
    class C_Singleton
    {
    public:
        static T* s_GetInstance();                                      // �B��̃C���X�^���X���擾
    protected:
        C_Singleton();                                                  // �R���X�g���N�^
        virtual ~C_Singleton(); 		                                // �f�X�g���N�^
    private:
        C_Singleton(const C_Singleton& rOther) = delete;                //!< @brief �R�s�[�R���X�g���N�^
        C_Singleton& operator=(const C_Singleton& rOther) = delete;     //!< @brief ������Z�q�̃I�[�o�[���[�h
    };
}


/* ���� */
#include "SingletonImpl.h"
