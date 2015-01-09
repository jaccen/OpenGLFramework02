/* �w�b�_�t�@�C�� */
#include "EvenIntervalShotLogic.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{


#pragma region �ÓI�����o�ϐ��̏�����


    /* ������̎ˌ��� */
    const int32_t C_EvenIntervalShotLogic::s_INFINITE_SHOT_COUNT = -1;


#pragma endregion


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �ˌ��̊Ԋu
     *
     ****************************************************************/
    C_EvenIntervalShotLogic::C_EvenIntervalShotLogic(int32_t shotInterval,
                                                     int32_t shotStartDelay,
                                                     int32_t maxShotCount) : C_ShotLogic(shotInterval),

        // �ˌ��J�n�̒x���t���[����
        shotStartDelay_(shotStartDelay),

        // �ő�ˌ���
        maxShotCount_(maxShotCount)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_EvenIntervalShotLogic::~C_EvenIntervalShotLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̏������s��
     *  @param  �Ȃ�
     *  @return �ˌ����������Ftrue
     *  @return �ˌ�������  �Ffalse
     *
     ****************************************************************/
    bool C_EvenIntervalShotLogic::DoProcess()
    {
        bool shotReadyFlag = false;

        if ((frameCounter_.GetCount() >= shotStartDelay_)
         && (maxShotCount_ == s_INFINITE_SHOT_COUNT || shotCount_ < maxShotCount_))
        {
            if (frameCounter_.GetCount() % shotInterval_ == 0)
            {
                ++shotCount_;
                shotReadyFlag = true;
            }
        }

        // �J�E���g�A�b�v
        frameCounter_.CountUp();

        return shotReadyFlag;
    }
}