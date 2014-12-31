/* �w�b�_�t�@�C�� */
#include "EventManager.h"
#include "../Window/Main/MainWindowEvent.h"
#include "../../Input/Keyboard/KeyboardManager.h"
#include "../../Input/Mouse/MouseManager.h"
#include <forward_list>


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
    //! @brief �C�x���g�}�l�[�W���[�C���v�������g
    //! @brief �C�x���g�}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_EventManager::C_EventManagerImpl
    {
    public:
        C_EventManagerImpl();                                                       // �R���X�g���N�^
        ~C_EventManagerImpl();                                                      // �f�X�g���N�^
        void Update();                                                              // �X�V����
        void EntryWindowEvent(C_BaseWindowEvent* pWindowEvent);                     // �E�B���h�E�̃C�x���g��o�^
        bool IsFinishFlag() const;                                                  // �I���t���O���擾
    private:
        EventData event_;                                                           ///< @brief �C�x���g�̏��
        std::forward_list<std::unique_ptr<C_BaseWindowEvent>> upWindowEvents_;      ///< @brief �E�B���h�E�̃C�x���g

        static bool s_finishFlag;                                                   // �I���𔻒f����t���O   

        void WindowEvent();                                                         // �E�B���h�E�̃C�x���g����
        void QuitEvent();                                                           // �I���̃C�x���g����
    };


#pragma region �ÓI�����o�ϐ��̏�����


    /* �I���𔻒f����t���O */
    bool C_EventManager::C_EventManagerImpl::s_finishFlag = false;


#pragma endregion


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_EventManager::C_EventManagerImpl::C_EventManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_EventManager::C_EventManagerImpl::~C_EventManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EventManager::C_EventManagerImpl::Update()
    {
        // �C�x���g�̍X�V
        while (::SDL_PollEvent(&event_))
        {
            switch (event_.type)
            {
            /* �E�B���h�E�̃C�x���g */
            case SDL_WINDOWEVENT:

                WindowEvent();

                break;
            /* �}�E�X�z�C�[���̃C�x���g */
            case SDL_MOUSEWHEEL:

                // �}�E�X�z�C�[���̐��������̉�]��ݒ�
                Input::C_MouseManager::s_GetInstance()->SetWheelScrollVertical(event_.wheel.y);

                break;
            /* �e�L�X�g���͂̃C�x���g */
            case SDL_TEXTINPUT:

                Input::C_KeyboardManager::s_GetInstance()->SetInputCharacter(event_.text.text);

                break;
            /* �I���̃C�x���g */
            case SDL_QUIT:

                QuitEvent();

                break;
            /* ���̑��̃C�x���g */
            default:
                break;
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  �E�B���h�E�̃C�x���g��o�^����
     *  @param  �E�B���h�E�̃C�x���g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EventManager::C_EventManagerImpl::EntryWindowEvent(C_BaseWindowEvent* pWindowEvent)
    {
        upWindowEvents_.emplace_front(pWindowEvent);
    }


    /*************************************************************//**
     *
     *  @brief  �I���t���O���擾
     *  @param  �Ȃ�
     *  @return �I���t���O
     *
     ****************************************************************/
    bool C_EventManager::C_EventManagerImpl::IsFinishFlag() const
    {
        return s_finishFlag;
    }


    /*************************************************************//**
     *
     *  @brief  �E�B���h�E�̃C�x���g�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EventManager::C_EventManagerImpl::WindowEvent()
    {
        // ���[�v�J�E���^
        int32_t loopCount = 0;

        // �C�e���[�^
        auto iterator = upWindowEvents_.begin();

        // �E�B���h�E�C�x���g������
        while (iterator != upWindowEvents_.end())
        {
            if (event_.window.windowID == (*iterator)->GetWindowId())
            {
                if ((*iterator)->Process(event_) == false)
                {
                    iterator = upWindowEvents_.erase_after(std::next(upWindowEvents_.before_begin(), loopCount));
                    continue;
                }

                ++iterator;
                ++loopCount;
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  �I���̃C�x���g�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EventManager::C_EventManagerImpl::QuitEvent()
    {
        s_finishFlag = true;
    }
}