/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "MoveLogic.h"
#include "BaseBackground.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* �ʖ� */
    using Background = C_BaseBackground;                                                    // Background�^


    //-------------------------------------------------------------
    //!
    //! @brief �o�b�N�O���E���h���[�u���W�b�N
    //! @brief �w�i�̈ړ��̃��W�b�N�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BackgroundMoveLogic : public IC_MoveLogic<Background>
    {
    public:
        C_BackgroundMoveLogic() = default;                                                  // �R���X�g���N�^
        virtual ~C_BackgroundMoveLogic() override = default;                                // �f�X�g���N�^
        virtual void Process(Background* pBackground) override final;                       // ����
        virtual void SetVelocity(const Vector3& rVelocity);                                 // ���x��ݒ�
        virtual void SetAccelaration(const Vector3& rAccelaration);                         // �����x��ݒ�
        virtual void SetRotationVelocity(const Vector3& rRotationVelocity);                 // ��]���x��ݒ�
        virtual void SetRotationAccelaration(const Vector3& rRotationAccelaration);         // ��]�����x��ݒ�
    protected:
        virtual void DoProcess(Background* pBackground) = 0;                                ///< @brief ����J�̏���

        Vector3 velocity_;                                                                  ///< @brief ���x
        Vector3 accelaration_;                                                              ///< @brief �����x
        Vector3 rotationVelocity_;                                                          ///< @brief ��]���x
        Vector3 rotationAccelaration_;                                                      ///< @brief ��]�����x
    };
}