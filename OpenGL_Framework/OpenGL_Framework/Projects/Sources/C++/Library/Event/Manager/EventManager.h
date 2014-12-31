/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Singleton/Singleton.h"
#include "../Window/BaseWindowEvent.h"


/* �O���錾 */
namespace Window
{
    class C_BaseWindow;
}


//-------------------------------------------------------------
//!
//! @brief �C�x���g
//! @brief �C�x���g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Event
{
    //-------------------------------------------------------------
    //!
    //! @brief �C�x���g�}�l�[�W���[
    //! @brief �C�x���g���Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_EventManager : public Singleton::C_Singleton<C_EventManager>
    {
        friend C_Singleton<C_EventManager>;                                         // �V���O���g�����t�����h��
    public:
        void Initialize(const Window::C_BaseWindow& rMainWindow);                   // ����������
        void Update();                                                              // �X�V����
        void EntryWindowEvent(C_BaseWindowEvent* pWindowEvent);                     // �E�B���h�E�̃C�x���g��o�^
        void EnableTextInput(bool validFlag = true);                                // �e�L�X�g���͂̃C�x���g��L����
        bool IsFinishFlag() const;                                                  // �I���t���O���擾
    private:
        /* �O���錾 */
        class C_EventManagerImpl;

        std::unique_ptr<C_EventManagerImpl> upImpl_;                                /// <@brief �������

        C_EventManager();                                                           // �R���X�g���N�^
        ~C_EventManager() override;                                                 // �f�X�g���N�^
    };
}