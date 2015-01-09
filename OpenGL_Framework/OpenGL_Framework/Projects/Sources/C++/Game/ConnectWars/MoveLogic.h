/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectWarsDefine.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief ���[�u���W�b�N( �C���^�[�t�F�[�X )
    //! @brief �ړ��̃��W�b�N�̃C���^�[�t�F�[�X�N���X
    //!
    //-------------------------------------------------------------
    template<typename T>
    class IC_MoveLogic
    {
    public:
        IC_MoveLogic() = default;                           //!< @brief �R���X�g���N�^
        virtual ~IC_MoveLogic() = default;                  //!< @brief �f�X�g���N�^
        virtual void Process(T* pSomething) = 0;            //!< @brief ����
    };
}