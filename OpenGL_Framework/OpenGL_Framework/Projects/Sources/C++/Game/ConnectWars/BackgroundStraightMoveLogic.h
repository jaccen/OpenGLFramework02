/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "BackgroundMoveLogic.h"


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
    //! @brief �o�b�N�O���E���h���[�u���W�b�N
    //! @brief �w�i�̈ړ��̃��W�b�N�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BackgroundStraightMoveLogic : public C_BackgroundMoveLogic
    {
    public:
        C_BackgroundStraightMoveLogic();                            // �R���X�g���N�^
        ~C_BackgroundStraightMoveLogic() override;                  // �f�X�g���N�^
    private:
        void DoProcess(Background* pBackground) override;           ///< @brief ����J�̏���
    };
}