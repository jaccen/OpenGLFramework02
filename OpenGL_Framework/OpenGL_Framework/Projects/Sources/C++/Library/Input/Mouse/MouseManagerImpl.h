/* �w�b�_�t�@�C�� */
#include "MouseManager.h"
#include <SDL_mouse.h>
#include <array>


//-------------------------------------------------------------
//!
//! @brief �C���v�b�g
//! @brief ���͊֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Input
{
    //-------------------------------------------------------------
    //!
    //! @brief �}�E�X�}�l�[�W���[�C���v�������g
    //! @brief �}�E�X�}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_MouseManager::C_MouseManagerImpl
    {
    public:
        C_MouseManagerImpl();                                                       // �R���X�g���N�^
        ~C_MouseManagerImpl();                                                      // �f�X�g���N�^

        void CursorAndButtonUpdate();                                               // �J�[�\���ƃ{�^���̍X�V����
        void WheelUpdate();                                                         // �z�C�[���̍X�V����
        int32_t GetCursorPositionX() const;                                         // �J�[�\����X���W���擾
        int32_t GetCursorPositionY() const;                                         // �J�[�\����Y���W���擾
        int32_t GetButtonPressingCount(eButton button) const;                       // �{�^���������Ă���t���[�������擾
        int32_t GetButtonReleasingCount(eButton button) const;                      // �{�^���𗣂��Ă���t���[�������擾
        int32_t GetWheelScrollingCount(eWheelScroll wheelScroll) const;             // �z�C�[������]���Ă���t�[���������擾
        int32_t GetWheelReleasingCount(eWheelScroll wheelScroll) const;             // �z�C�[������]���Ă��Ȃ��t���[�������擾
        void SetWheelScrollVertical(int32_t wheelScrollVertical);                   // �z�C�[���̐��������̉�]��ݒ�
    private:
        int32_t cursorPositionX_ = 0;                                               ///< @brief �J�[�\����X���W
        int32_t cursorPositionY_ = 0;                                               ///< @brief �J�[�\����Y���W
        std::array<int32_t, BUTTON_TOTAL_NUMBER> buttonPressingCounts_;             ///< @brief �{�^���̉����Ă���t���[�����̃J�E���^
        std::array<int32_t, BUTTON_TOTAL_NUMBER> buttonReleasingCounts_;            ///< @brief �{�^���̗����Ă���t���[�����̃J�E���^
        std::array<int32_t, WHEEL_SCROLL_TOTAL_NUMBER> wheelScrollingCounts_;       ///< @brief �z�C�[���̉�]���Ă���t���[�����̃J�E���^
        std::array<int32_t, WHEEL_SCROLL_TOTAL_NUMBER> wheelReleasingCounts_;       ///< @brief �z�C�[���̉�]���Ă��Ȃ��t���[�����̃J�E���^
        int32_t wheelScrollVertical_ = 0;                                           ///< @brief �z�C�[���̐��������̉�]

        void WheelResetReleasingAndUpScrolling(eWheelScroll wheelScroll);           /* �z�C�[������]���Ă��Ȃ��t���[�����̃��Z�b�g��
                                                                                       ��]���Ă���t���[�����̑���*/
        void WheelResetScrollingAndUpReleasing(eWheelScroll wheelScroll);           /* �z�C�[������]���Ă���t���[�����̃��Z�b�g��
                                                                                       ��]���Ă��Ȃ��t���[�����̑���*/
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_MouseManager::C_MouseManagerImpl::C_MouseManagerImpl()
    {
        // �{�^���̃t���[�����̃J�E���^��������
        buttonPressingCounts_.fill(0);
        buttonReleasingCounts_.fill(0);

        // �z�C�[���̉�]�̃t���[�����̃J�E���^��������
        wheelScrollingCounts_.fill(0);
        wheelReleasingCounts_.fill(0);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_MouseManager::C_MouseManagerImpl::~C_MouseManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�[�\���ƃ{�^���̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_MouseManager::C_MouseManagerImpl::CursorAndButtonUpdate()
    {
        // �J�[�\���̍��W�ƃ{�^���̏�Ԃ��擾
        Uint32 buttonState = ::SDL_GetMouseState(&cursorPositionX_, &cursorPositionY_);

        for (unsigned int i = 0; i < BUTTON_TOTAL_NUMBER; ++i)
        {
            // �{�^�������͂���Ă���ꍇ
            if (buttonState & SDL_BUTTON((i + 1)))
            {
                // �{�^���𗣂��Ă���t���[���������Z�b�g���A
                // �{�^���������Ă���t���[������1����
                if (buttonReleasingCounts_[i] > 0) buttonReleasingCounts_[i] = 0;

                ++buttonPressingCounts_[i];
            }
            else
            {
                // �{�^���������Ă���t���[���������Z�b�g���A
                // �{�^���𗣂��Ă���t���[������1����
                if (buttonPressingCounts_[i] > 0) buttonPressingCounts_[i] = 0;

                ++buttonReleasingCounts_[i];
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  �z�C�[���̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_MouseManager::C_MouseManagerImpl::WheelUpdate()
    {
        // �z�C�[�������]���Ă���ꍇ
        if (wheelScrollVertical_ > 0)
        {
            // ���]�����Ă���t���[�������グ��
            WheelResetReleasingAndUpScrolling(WHEEL_SCROLL_UP);
            WheelResetScrollingAndUpReleasing(WHEEL_SCROLL_DOWN);
        }
        // �z�C�[��������]���Ă���ꍇ
        else if (wheelScrollVertical_ < 0)
        {
            // ����]�����Ă���t���[�������グ��
            WheelResetReleasingAndUpScrolling(WHEEL_SCROLL_DOWN);
            WheelResetScrollingAndUpReleasing(WHEEL_SCROLL_UP);
        }
        else
        {
            // �㉺�̗����Ă���t���[�������グ��
            WheelResetScrollingAndUpReleasing(WHEEL_SCROLL_UP);
            WheelResetScrollingAndUpReleasing(WHEEL_SCROLL_DOWN);
        }

        // �z�C�[���̐��������̉�]�����Z�b�g
        wheelScrollVertical_ = 0;
    }


    /*************************************************************//**
     *
     *  @brief  �J�[�\����X���W���擾����
     *  @param  �Ȃ�
     *  @return �J�[�\����X���W
     *
     ****************************************************************/
    int32_t C_MouseManager::C_MouseManagerImpl::GetCursorPositionX() const
    {
        return cursorPositionX_;
    }


    /*************************************************************//**
     *
     *  @brief  �J�[�\����Y���W���擾����
     *  @param  �Ȃ�
     *  @return �J�[�\����Y���W
     *
     ****************************************************************/
    int32_t C_MouseManager::C_MouseManagerImpl::GetCursorPositionY() const
    {
        return cursorPositionY_;
    }


    /*************************************************************//**
     *
     *  @brief  �{�^���������Ă���t���[�������擾����
     *  @param  �{�^��
     *  @return �{�^���������Ă���t���[����
     *
     ****************************************************************/
    int32_t C_MouseManager::C_MouseManagerImpl::GetButtonPressingCount(eButton button) const
    {
        return buttonPressingCounts_.at(button);
    }


    /*************************************************************//**
     *
     *  @brief  �{�^���𗣂��Ă���t���[�������擾����
     *  @param  �{�^��
     *  @return �{�^���𗣂��Ă���t���[����
     *
     ****************************************************************/
    int32_t C_MouseManager::C_MouseManagerImpl::GetButtonReleasingCount(eButton button) const
    {
        return buttonReleasingCounts_.at(button);
    }


    /*************************************************************//**
     *
     *  @brief  �z�C�[������]���Ă���t���[�������擾����
     *  @param  �z�C�[���̉�]����
     *  @return �z�C�[������]���Ă���t���[����
     *
     ****************************************************************/
    int32_t C_MouseManager::C_MouseManagerImpl::GetWheelScrollingCount(eWheelScroll wheelScroll) const
    {
        return wheelScrollingCounts_.at(wheelScroll);
    }


    /*************************************************************//**
     *
     *  @brief  �z�C�[������]���Ă��Ȃ��t���[�������擾����
     *  @param  �z�C�[���̉�]����
     *  @return �z�C�[������]���Ă��Ȃ��t���[����
     *
     ****************************************************************/
    int C_MouseManager::C_MouseManagerImpl::GetWheelReleasingCount(eWheelScroll wheelScroll) const
    {
        return wheelReleasingCounts_.at(wheelScroll);
    }


    /*************************************************************//**
     *
     *  @brief  �z�C�[���𐂒������̉�]��ݒ肷��
     *  @param  �z�C�[���̐��������̉�]
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_MouseManager::C_MouseManagerImpl::SetWheelScrollVertical(int32_t wheelScrollVertical)
    {
        wheelScrollVertical_ = wheelScrollVertical;
    }


    /*************************************************************//**
     *
     *  @brief  �z�C�[���̉�]���Ă��Ȃ��t���[�����̃��Z�b�g��
     *  @brief  ��]���Ă���t���[�����̑������s��
     *  @param  �z�C�[���̉�]����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_MouseManager::C_MouseManagerImpl::WheelResetReleasingAndUpScrolling(eWheelScroll wheelScroll)
    {
        if (wheelReleasingCounts_[wheelScroll] > 0)
        {
            wheelReleasingCounts_[wheelScroll] = 0;
        }

        ++wheelScrollingCounts_[wheelScroll];
    }


    /*************************************************************//**
     *
     *  @brief  �z�C�[���̉�]���Ă���t���[�����̃��Z�b�g��
     *  @brief  ��]���Ă��Ȃ��t���[�����̑������s��
     *  @param  �z�C�[���̉�]����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_MouseManager::C_MouseManagerImpl::WheelResetScrollingAndUpReleasing(eWheelScroll wheelScroll)
    {
        if (wheelScrollingCounts_[wheelScroll] > 0)
        {
            wheelScrollingCounts_[wheelScroll] = 0;
        }

        ++wheelReleasingCounts_[wheelScroll];
    }
}