/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Singleton/Singleton.h"
#include <SDL_keyboard.h>


//-------------------------------------------------------------
//!
//! @brief �C���v�b�g
//! @brief ���͊֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Input
{
    /* �ʖ� */
    using KeyCode = SDL_Scancode;                                   // KeyCode�^


    //-------------------------------------------------------------
    //!
    //! @brief �L�[�{�[�h�}�l�[�W���[
    //! @brief �L�[���͂̊Ǘ�������N���X
    //!
    //-------------------------------------------------------------
    class C_KeyboardManager : public Singleton::C_Singleton<C_KeyboardManager>
    {

        friend C_Singleton<C_KeyboardManager>;                              // �V���O���g���N���X���t�����h��
    public:
        void Initialize();                                                  // ����������
        void Update();                                                      // �X�V����
        int32_t GetPressingCount(KeyCode keycode) const;                    // �����Ă���t���[�������擾
        int32_t GetReleasingCount(KeyCode keycode) const;                   // �����Ă���t���[�������擾
        const std::string& GetInputCharacter() const;                       // ���͂����������擾
        void SetInputCharacter(const std::string& rInputCharacter);         // ���͂���������ݒ�
    private:
        /* �O���錾 */
        class C_KeyboardManagerImpl;

        std::unique_ptr<C_KeyboardManagerImpl> upImpl_;                     ///< @brief �������

        C_KeyboardManager();                                                // �R���X�g���N�^
        ~C_KeyboardManager() override;                                      // �f�X�g���N�^
    };
}
