/* �w�b�_�t�@�C�� */
#include "MainWindowEvent.h"
#include "../../../OpenGL/Manager/OpenGlManager.h"
#include "../../../Window/Manager/WindowManager.h"


//-------------------------------------------------------------
//!
//! @brief �C�x���g
//! @brief �C�x���g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Event
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �E�B���h�E��ID
     *
     ****************************************************************/
    C_MainWindowEvent::C_MainWindowEvent(uint32_t windowId) : C_BaseWindowEvent(windowId)
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_MainWindowEvent::~C_MainWindowEvent()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �C�x���g�̏������s��
     *  @param  �C�x���g
     *  @return �C�x���g�ێ��Ftrue
     *  @return �C�x���g�j���Ffalse
     *
     ****************************************************************/
    bool C_MainWindowEvent::Process(EventData& rEvent)
    {
        switch (rEvent.window.event)
        {
        /* �E�B���h�E�����T�C�Y */
        case WindowEventType::SDL_WINDOWEVENT_RESIZED:
        {
            // ���W���擾
            int32_t positionX = 0, positionY = 0;
            ::SDL_GetWindowPosition(::SDL_GetWindowFromID(windowId_), &positionX, &positionY);

            // ���ƍ�����ݒ肵�A�r���[�|�[�g���Đݒ�
            assert(Window::C_WindowManager::s_GetInstance()->GetWindow());

            auto pWindow = Window::C_WindowManager::s_GetInstance()->GetWindow().get();

            pWindow->SetWidth(rEvent.window.data1);
            pWindow->SetHeight(rEvent.window.data2);

            OpenGL::C_OpenGlManager::s_GetInstance()->SetViewport(positionX, positionY, rEvent.window.data1, rEvent.window.data2);
        }
            break;
        /* �E�B���h�E����� */
        case WindowEventType::SDL_WINDOWEVENT_CLOSE:

            // �C�x���g�ɏI��������C�x���g��ݒ肷��
            rEvent.type = SDL_QUIT;
            ::SDL_PushEvent(&rEvent);

            return false;

            break;
        }

        return true;
    }
}