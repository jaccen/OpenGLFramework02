/* �w�b�_�t�@�C�� */
#include "FrameCounter.h"


//-------------------------------------------------------------
//!
//! @brief �^�C�}�[
//! @brief �^�C�}�[�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Timer
{
    /* �v���g�^�C�v�錾 */
    static void s_JudgeReset(int32_t* pCount, int32_t resetCount, bool resetFlag);


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �X�^�[�g�J�E���g��
     *
     ****************************************************************/
    C_FrameCounter::C_FrameCounter(int32_t startCount) :

        // �J�E���g��
        count_(startCount)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_FrameCounter::~C_FrameCounter()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�E���g�A�b�v���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FrameCounter::CountUp()
    {
        ++count_;
        s_JudgeReset(&count_, autoResetCount_, autoResetFlag_);
    }


    /*************************************************************//**
     *
     *  @brief  �J�E���g�_�E�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FrameCounter::CountDown()
    {
        --count_;
        s_JudgeReset(&count_, autoResetCount_, autoResetFlag_);
    }


    /*************************************************************//**
     *
     *  @brief  �J�E���g���̃��Z�b�g���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FrameCounter::Reset()
    {
        count_ = 0;
    }


    /*************************************************************//**
     *
     *  @brief  �������Z�b�g��L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FrameCounter::EnableAutoReset(bool validFlag)
    {
        autoResetFlag_ = validFlag;
    }


    /*************************************************************//**
     *
     *  @brief  �J�E���g�����擾����
     *  @param  �Ȃ�
     *  @return �J�E���g��
     *
     ****************************************************************/
    int32_t C_FrameCounter::GetCount() const
    {
        return count_;
    }


    /*************************************************************//**
     *
     *  @brief  �������Z�b�g�J�E���g�����擾����
     *  @param  �Ȃ�
     *  @return �������Z�b�g�J�E���g��
     *
     ****************************************************************/
    int32_t C_FrameCounter::GetAutoResetCount() const
    {
        return autoResetCount_;
    }


    /*************************************************************//**
     *
     *  @brief  �J�E���g����ݒ肷��
     *  @param  �J�E���g��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FrameCounter::SetCount(int32_t count)
    {
        count_ = count;
    }


    /*************************************************************//**
     *
     *  @brief  �������Z�b�g�J�E���g����ݒ肷��
     *  @param  �������Z�b�g�J�E���g��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FrameCounter::SetAutoResetCount(int32_t autoResetCount)
    {
        autoResetCount_ = autoResetCount;
    }


    /*************************************************************//**
     *
     *  @brief  ���Z�b�g�̔��f���s��
     *  @param  �J�E���g��
     *  @param  ���Z�b�g�J�E���g��
     *  @param  ���Z�b�g���邩���f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void s_JudgeReset(int32_t* pCount, int32_t resetCount, bool resetFlag)
    {
        if (resetFlag == true)
        {
            if (*pCount == resetCount)
            {
                *pCount = 0;
            }
        }
    }
}