/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ShotLogic.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"


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
    //! @brief �C�[�u���C���^�[�o���V���b�g���W�b�N
    //! @brief ���Ԋu�̎ˌ��̃��W�b�N
    //!
    //-------------------------------------------------------------
    class C_EvenIntervalShotLogic : public C_ShotLogic
    {
    public:
        /* �萔 */
        static const int32_t s_INFINITE_SHOT_COUNT;             ///< @brief ������̎ˌ���

        C_EvenIntervalShotLogic(int32_t shotInterval,           // �R���X�g���N�^
                                int32_t shotStartDelay,
                                int32_t maxShotCount);
        ~C_EvenIntervalShotLogic() override;                    // �f�X�g���N�^
    private:
        int32_t shotStartDelay_ = 0;                            ///< @brief �ˌ��J�n�̒x���t���[����
        int32_t shotCount_ = 0;                                 ///< @brief �ˌ���
        int32_t maxShotCount_ = 1;                              ///< @brief �ő�ˌ���
        Timer::C_FrameCounter frameCounter_;                    ///< @brief �t���[���J�E���^�[

        bool DoProcess() override;                              // ����J�̏���
    };
}