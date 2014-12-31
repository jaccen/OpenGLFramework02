/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include <SDL_events.h>


//-------------------------------------------------------------
//!
//! @brief �C�x���g
//! @brief �C�x���g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Event
{
    /* �ʖ� */
    using EventData = SDL_Event;                                        // EventData�^
    using WindowEventType = SDL_WindowEventID;                          // WindowEventType�^

    //-------------------------------------------------------------
    //!
    //! @brief �x�[�X�E�B���h�E�C�x���g
    //! @brief �E�B���h�E�C�x���g�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BaseWindowEvent
    {
    public:
        C_BaseWindowEvent(Uint32 windowId);                             // �R���X�g���N�^
        virtual ~C_BaseWindowEvent() = 0;                               // �f�X�g���N�^
        virtual bool Process(EventData& rEvent) = 0;                    // �C�x���g�̏���

        /* �Q�b�^�[ */
        uint32_t GetWindowId() const;                                   // �E�B���h�E��ID���擾
    protected:
        uint32_t windowId_ = 0;                                         ///< @brief �E�B���h�E��ID
    };
}
