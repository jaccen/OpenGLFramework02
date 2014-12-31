/* �w�b�_�t�@�C�� */
#include "FrameworkImpl.h"
#include "../SDL/SdlManager.h"
#include "../Window/Manager/WindowManager.h"
#include "../Event/Manager/EventManager.h"
#include "../Timer/TimeManager.h"
#include "../JSON/JsonObject.h"
#include "../OpenGL/Manager/OpenGlManager.h"
#include "../Input/Keyboard/KeyboardManager.h"
#include "../Input/Mouse/MouseManager.h"
#include "../Input/Gamepad/Manager/GamepadManager.h"
#include "../Sound/SoundManager.h"
#include "../Texture/Manager/TextureManager.h"
#include "../Debug/String/DebugString.h"
#include "../Camera/Manager/CameraManager.h"


/* �}�N����` */
#define _CRTDBG_MAP_ALLOC           // <crtdbg.h>���̊֐��̃������̊��蓖�Ă�ǐՂ���悤�ɂ���}�N��


/* VisualStudio�֘A�̃w�b�_�t�@�C�� */
#include <crtdbg.h>


//-------------------------------------------------------------
//!
//! @brief �t���[�����[�N
//! @brief �t���[�����[�N�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Framework
{
    /* �v���g�^�C�v�錾 */
    static bool s_InitializeMainWindowWithJsonFile(Window::C_BaseWindow* pMainWindow,
                                                   const std::string& rFilePath);


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_Framework::C_Framework(C_Framework* pGame) :

        // �������
        upImpl_(std::make_unique<C_FrameworkImpl>(pGame))

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_Framework::~C_Framework()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ���s�������s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_Framework::Run()
    {
        // �ŏ��̏���
        FirstProcess();

        // ����������
        if (upImpl_->GetGame()->Initialize() == false) return false;

        /* ���C�����[�v */
        while (Event::C_EventManager::s_GetInstance()->IsFinishFlag() == false)
        {
            // �X�V����
            if (upImpl_->GetGame()->Update() == false) break;

            // �`��t���O�������Ă���ꍇ�͕`�揈���Ɖ�ʂ̍X�V���s��
            if (Timer::C_TimeManager::s_GetInstance()->IsDrawFlag() == true)
            {
                upImpl_->GetGame()->Draw();
                upImpl_->GetGame()->UpdateScreen();
            }
        }

        // �I������
        upImpl_->GetGame()->Finalize();

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_Framework::Initialize()
    {
        // SDL�}�l�[�W���[�̏��������� 
        if (SDL::C_SdlManager::s_GetInstance()->Initialize() == false) return false;

        // ���C���E�B���h�E�̏���������
        auto pMainWindow = std::make_shared<Window::C_BaseWindow>();
        Window::C_WindowManager::s_GetInstance()->Entry(pMainWindow);

        if (pMainWindow->Initialize() == false) return false;

        // OpenGL�}�l�[�W���[�̏���������
        if (OpenGL::C_OpenGlManager::s_GetInstance()->Initialize(*pMainWindow) == false) return false;

        // �C�x���g�}�l�[�W���[�̏���������
        Event::C_EventManager::s_GetInstance()->Initialize(*pMainWindow);

        // �^�C���l�[�W���[�̏���������
        Timer::C_TimeManager::s_GetInstance()->Initialize();

        // �L�[�{�[�h�}�l�[�W���[�̏���������
        Input::C_KeyboardManager::s_GetInstance()->Initialize();

        // �Q�[���p�b�h�}�l�[�W���[�̏���������
        Input::C_GamepadManager::s_GetInstance()->Initialize();

        // �T�E���h�}�l�[�W���[�̏���������
        if (Sound::C_SoundManager::s_GetInstance()->Initialize() == false) return false;

        // �t�H���g�}�l�[�W���[�̏���������
        if (Font::C_FontManager::s_GetInstance()->Initialize() == false) return false;

        // �f�o�b�O������̏���������
        if (Debug::C_DebugString::s_GetInstance()->Initialize() == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  JSON�t�@�C���ŏ������������s��
     *  @param  ���C���E�B���h�E�f�[�^�̃t�@�C���p�X
     *  @param  OpenGL�f�[�^�̃t�@�C���p�X
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_Framework::InitializeWithJsonFile(const std::string& rMainWindowDataFilePath,
                                             const std::string& rOpenGlDataFilePath)
    {
        // SDL�}�l�[�W���[�̏��������� 
        if (SDL::C_SdlManager::s_GetInstance()->Initialize() == false) return false;

        // ���C���E�B���h�E�̏���������
        auto pMainWindow = std::make_shared<Window::C_BaseWindow>();
        Window::C_WindowManager::s_GetInstance()->Entry(pMainWindow);

        if (s_InitializeMainWindowWithJsonFile(pMainWindow.get(), rMainWindowDataFilePath) == false)
        {
            return false;
        }

        // OpenGL�}�l�[�W���[�̏���������
        if (OpenGL::C_OpenGlManager::s_GetInstance()->InitializeWithJsonFile(*pMainWindow, rOpenGlDataFilePath) == false)
        {
            return false;
        }

        // �C�x���g�}�l�[�W���[�̏���������
        Event::C_EventManager::s_GetInstance()->Initialize(*pMainWindow);

        // �^�C���l�[�W���[�̏���������
        Timer::C_TimeManager::s_GetInstance()->Initialize();

        // �L�[�{�[�h�}�l�[�W���[�̏���������
        Input::C_KeyboardManager::s_GetInstance()->Initialize();

        // �Q�[���p�b�h�}�l�[�W���[�̏���������
        Input::C_GamepadManager::s_GetInstance()->Initialize();

        // �T�E���h�}�l�[�W���[�̏���������
        if (Sound::C_SoundManager::s_GetInstance()->Initialize() == false) return false;
        
        // �t�H���g�}�l�[�W���[�̏���������
        if (Font::C_FontManager::s_GetInstance()->Initialize() == false) return false;

        // �f�o�b�O������̏���������
        if (Debug::C_DebugString::s_GetInstance()->Initialize() == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_Framework::Update()
    {
        // �^�C���}�l�[�W���[�̍X�V����
        Timer::C_TimeManager::s_GetInstance()->Update();

        // �C�x���g�}�l�[�W���[�̍X�V����
        Event::C_EventManager::s_GetInstance()->Update();

        // �L�[�{�[�h�}�l�[�W���[�̍X�V����
        Input::C_KeyboardManager::s_GetInstance()->Update();

        // �}�E�X�}�l�[�W���[�̍X�V����
        Input::C_MouseManager::s_GetInstance()->Update();

        // �Q�[���p�b�h�}�l�[�W���[�̍X�V����
        Input::C_GamepadManager::s_GetInstance()->Update();

        // �J�����}�l�[�W���[�̍X�V����
        Camera::C_CameraManager::s_GetInstance()->Update();

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_Framework::Draw()
    {
        Debug::C_DebugString::s_GetInstance()->Draw("[ FPS : " + std::to_string(Timer::C_TimeManager::s_GetInstance()->GetNowFps()) + " ]", Debug::Vector3(0.0f, 0.0f, 0.0f), 0.7f, 255, 255, 255);
    }


    /*************************************************************//**
     *
     *  @brief  ��ʂ̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_Framework::UpdateScreen()
    {
        OpenGL::C_OpenGlManager::s_GetInstance()->SwapBuffer();
        OpenGL::C_OpenGlManager::s_GetInstance()->ClearBackBuffer();
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_Framework::Finalize()
    {
        // �f�o�b�O������̏I������
        Debug::C_DebugString::s_GetInstance()->Finalize();

        // �e�N�X�`����S�Ĕj��
        Texture::C_TextureManager::s_GetInstance()->AllDestroy();

        // �t�H���g�}�l�[�W���[�̏I������
        Font::C_FontManager::s_GetInstance()->Finalize();

        // �T�E���h�}�l�[�W���[�̏I������
        Sound::C_SoundManager::s_GetInstance()->Finalize();

        // �Q�[���p�b�h�}�l�[�W���[�̏I������
        Input::C_GamepadManager::s_GetInstance()->Finalize();

        // OpenGL�}�l�[�W���[�̏I������
        OpenGL::C_OpenGlManager::s_GetInstance()->Finalize();

        // ���C���E�B���h�E������
        Window::C_WindowManager::s_GetInstance()->Remove();

        // SDL�}�l�[�W���[�̏I������
        SDL::C_SdlManager::s_GetInstance()->Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  ��ԍŏ��ɍs���ׂ��������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_Framework::FirstProcess()
    {
        // �v���O�����I�����Ƀ��������[�N�����_���v����ݒ�
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

        // �o�͐���f�o�b�O�E�B���h�E�ɐݒ�
        _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

        // �������[���[�N�����������ʒu�����m���Ă����֐�( �����Ƀ������[���[�N�����ԍ������� )
        //_CrtSetBreakAlloc(152);
    }


    /*************************************************************//**
     *
     *  @brief  JSON�t�@�C���Ń��C���E�B���h�E�̏������������s��
     *  @param  ���C���E�B���h�E
     *  @param  �t�@�C���p�X
     *  @return ����I���Ftrue
     *  @return �ȏ�I���Ffalse
     *
     ****************************************************************/
    bool s_InitializeMainWindowWithJsonFile(Window::C_BaseWindow* pMainWindow,
                                            const std::string& rFilePath)
    {
        // JSON�I�u�W�F�N�g�𐶐�
        auto data = JSON::JsonObject::s_CreateFromFile(rFilePath);

        // ���C���E�B���h�E�̃^�C�g���E�T�C�Y�E�����t���O���擾
        std::string title = data["MainWindowData"]["Title"].GetValue<JSON::String>();
        int32_t width = data["MainWindowData"]["Size"]["Width"].GetValue<JSON::Integer>();
        int32_t height = data["MainWindowData"]["Size"]["Height"].GetValue<JSON::Integer>();
        int32_t createFlags = Window::CreateFlag::SDL_WINDOW_OPENGL;

        if (data["MainWindowData"]["CreateFlag"]["Resizeable"].GetValue<JSON::Boolean>() == true)
        {
            createFlags |= Window::CreateFlag::SDL_WINDOW_RESIZABLE;
        }

        if (data["MainWindowData"]["CreateFlag"]["FullScreen"].GetValue<JSON::Boolean>() == true)
        {
            createFlags |= Window::CreateFlag::SDL_WINDOW_FULLSCREEN;
        }

        // ���C���E�B���h�E�̏���������
        if (pMainWindow->Initialize(title, width, height, createFlags) == false) return false;

        // �^�C���l�[�W���[�̏���������
        Timer::C_TimeManager::s_GetInstance()->Initialize();

        return true;
    }
}