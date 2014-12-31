/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Singleton/Singleton.h"


//-------------------------------------------------------------
//!
//! @brief �C���v�b�g
//! @brief ���͊֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Input
{
    /** �}�E�X�{�^�� */
    enum eButton
    {
        BUTTON_LEFT,                                                            ///< @brief �}�E�X�̍��{�^��
        BUTTON_MIDDLE,                                                          ///< @brief �}�E�X�̃z�C�[���{�^��
        BUTTON_RIGHT,                                                           ///< @brief �}�E�X�̉E�{�^��
        BUTTON_EXTRA1,                                                          ///< @brief �}�E�X�̗]���ȃ{�^��1
        BUTTON_EXTRA2,                                                          ///< @brief �}�E�X�̗]���ȃ{�^��2

        BUTTON_TOTAL_NUMBER,                                                    ///< @brief �}�E�X�{�^���̑���
    };

    /** �}�E�X�z�C�[���̉�]���� */
    enum eWheelScroll
    {
        WHEEL_SCROLL_UP,                                                        ///< @brief �}�E�X�z�C�[���̏��]
        WHEEL_SCROLL_DOWN,                                                      ///< @brief �}�E�X�z�C�[���̉���]

        WHEEL_SCROLL_TOTAL_NUMBER,                                              ///< @brief �}�E�X�z�C�[���̉�]�����̑���
    };

    //-------------------------------------------------------------
    //!
    //! @brief �}�E�X�}�l�[�W���[
    //! @brief �}�E�X���͂��Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_MouseManager : public Singleton::C_Singleton<C_MouseManager>
    {
        friend C_Singleton<C_MouseManager>;                                     // �V���O���g�����t�����h��
    public:
        void Update();                                                          // �X�V����
        int32_t GetCursorPositionX() const;                                     // �J�[�\����X���W���擾
        int32_t GetCursorPositionY() const;                                     // �J�[�\����Y���W���擾
        int32_t GetButtonPressingCount(eButton button) const;                   // �{�^���������Ă���t���[�������擾
        int32_t GetButtonReleasingCount(eButton button) const;                  // �{�^���𗣂��Ă���t���[�������擾
        int32_t GetWheelScrollingCount(eWheelScroll wheelScroll) const;         // �z�C�[������]���Ă���t�[���������擾
        int32_t GetWheelReleasingCount(eWheelScroll wheelScroll) const;         // �z�C�[������]���Ă��Ȃ��t���[�������擾
        void SetWheelScrollVertical(int32_t wheelScrollVertical);               // �z�C�[���̐��������̉�]��ݒ�
    private:
        /* �O���錾 */
        class C_MouseManagerImpl;

        std::unique_ptr<C_MouseManagerImpl> upImpl_;                            ///< @brief �������

        C_MouseManager();                                                       // �R���X�g���N�^
        ~C_MouseManager() override;                                             // �f�X�g���N�^
    };
}