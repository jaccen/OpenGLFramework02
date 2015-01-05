/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
//!
//! @brief �^�C�}�[
//! @brief �^�C�}�[�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Timer
{
    //-------------------------------------------------------------
    //!
    //! @brief �t���[���J�E���^�[
    //! @brief �t���[�������J�E���g����N���X
    //!
    //-------------------------------------------------------------
    class C_FrameCounter
    {
    public:
        explicit C_FrameCounter(int32_t startCount = 0) ;           // �R���X�g���N�^
        ~C_FrameCounter();                                          // �f�X�g���N�^
        void CountUp();                                             // �J�E���g�A�b�v
        void CountDown();                                           // �J�E���g�_�E��
        void Reset();                                               // ���Z�b�g
        void EnableAutoReset(bool validFlag = true);                // �������Z�b�g��L����
        int32_t GetCount() const;                                   // �J�E���g�����擾
        int32_t GetAutoResetCount() const;                          // �������Z�b�g�J�E���g�����擾
        void SetCount(int32_t count);                               // �J�E���g����ݒ�
        void SetAutoResetCount(int32_t autoResetCount);             // �������Z�b�g�J�E���g����ݒ�
    private:
        int32_t count_ = 0;                                         ///< @brief �J�E���g��
        int32_t autoResetCount_ = 0;                                ///< @brief �������Z�b�g�J�E���g��
        bool autoResetFlag_ = false;                                ///< @brief �������Z�b�g�𔻒f����t���O
    };
}
