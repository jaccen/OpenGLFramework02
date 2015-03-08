/* �w�b�_�t�@�C�� */
#include "EventManagerImpl.h"
#include "../../Window/Window/BaseWindow.h"
#include "../../Debug/Helper/DebugHelper.h"
#include <SDL.h>


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
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_EventManager::C_EventManager() :

        // �������
        upImpl_(std::make_unique<C_EventManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_EventManager::~C_EventManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  ���C���E�B���h�E��ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EventManager::Initialize(const Window::C_BaseWindow& rMainWindow)
    {
        // ����������Ă��Ȃ��ꍇ�A����������
        if (::SDL_WasInit(SDL_INIT_EVENTS) == 0) ::SDL_InitSubSystem(SDL_INIT_EVENTS);

        // ���C���E�B���h�E�̃C�x���g��o�^
        upImpl_->EntryWindowEvent(newEx C_MainWindowEvent(rMainWindow.GetId()));

        // �e�L�X�g���͂̃C�x���g�𖳌���
        EnableTextInput(false);
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EventManager::Update()
    {
        upImpl_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  �E�B���h�E�̃C�x���g��o�^����
     *  @param  �E�B���h�E�̃C�x���g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EventManager::EntryWindowEvent(C_BaseWindowEvent* pWindowEvent)
    {
        upImpl_->EntryWindowEvent(pWindowEvent);
    }


    /*************************************************************//**
     *
     *  @brief  �e�L�X�g���͂̃C�x���g��L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EventManager::EnableTextInput(bool validFlag)
    {
        (validFlag == true) ? ::SDL_StartTextInput() : ::SDL_StopTextInput();
    }


    /*************************************************************//**
     *
     *  @brief  �I���̃C�x���g�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EventManager::QuitEvent()
    {
        upImpl_->QuitEvent();
    }


    /*************************************************************//**
     *
     *  @brief  �I���t���O���擾����
     *  @param  �Ȃ�
     *  @return �I���t���O
     *
     ****************************************************************/
    bool C_EventManager::IsFinishFlag() const
    {
        return upImpl_->IsFinishFlag();
    }
}