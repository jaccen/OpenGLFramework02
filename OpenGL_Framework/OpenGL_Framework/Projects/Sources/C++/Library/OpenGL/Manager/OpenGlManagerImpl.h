/* �w�b�_�t�@�C�� */
#include "OpenGlManager.h"
#include "../../Debug/Helper/DebugHelper.h"
#include "../../JSON/JsonObject.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace OpenGL
{
    /* �ʖ� */
    using Profile = SDL_GLprofile;                                                                      // Profile�^

    //-------------------------------------------------------------
    //!
    //! @brief OpenGL�}�l�[�W���[�C���v�������g
    //! @brief OpenGL�}�l�[�W���[�C���v�������g�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_OpenGlManager::C_OpenGlManagerImpl
    {
    public:
        C_OpenGlManagerImpl(C_OpenGlManager* pOpenGlManager);                                           // �R���X�g���N�^
        ~C_OpenGlManagerImpl();                                                                         // �f�X�g���N�^
        bool Initialize(const Window::C_BaseWindow& rMainWindow);                                       // ����������
        bool InitializeWithJsonFile(const Window::C_BaseWindow& rMainWindow,                            // Json�t�@�C���ŏ���������
                                    const std::string& rFilePath);
        void Finalize();                                                                                // �I������
        bool CreateRenderingContext(const std::string& rId);                                            // �����_�����O�R���e�L�X�g���쐬
        void DestroyRenderingContext(const std::string& rId);                                           // �����_�����O�R���e�L�X�g��j��
        void AllDestroyRenderingContext();                                                              // �S�Ẵ����_�����O�R���e�L�X�g��j��
        bool SetCurrentRenderingContext(const std::string& rId);                                        // �����_�����O�R���e�L�X�g���J�����g�ɐݒ�
        void ResetCurrentRenderingContext();                                                            // �J�����g�̃����_�����O�R���e�L�X�g�����Z�b�g
        void SwapBuffer();                                                                              // �o�b�t�@�̓���ւ�
    private:
        std::unordered_map<std::string, RenderingContextPtr> pRenderingContexts_;                       ///< @brief �����_�����O�R���e�L�X�g
        Window::WindowDataPtr pMainWindowData_;                                                         ///< @brief ���C���E�B���h�E�f�[�^
        C_OpenGlManager* pOpenGlManager_ = nullptr;                                                     ///< @brief OpenGL�}�l�[�W���[

        bool InitializeGlew();                                                                          // glew�̏���������
        void EnableDoubleBuffer(bool validFlag);                                                        // �_�u���o�b�t�@�̗L����
        void EnableSwapInterval(bool validFlag);                                                        // ����������L����
        void EnableShareRenderingContext(bool validFlag = true);                                        // �����_�����O�R���e�L�X�g�̋��L��L����
        void ResetMainWindowData();                                                                     // ���C���E�B���h�E�̏������Z�b�g
        void SetVersion(int32_t major, int32_t minor);                                                  // �o�[�W�����̐ݒ�
        void SetProfire(int32_t profire);                                                               // �v���t�@�C����ݒ�
        void SetColorBuffferSize(int32_t redBufferSize,                                                 // �J���[�o�b�t�@�̃T�C�Y��ݒ�
                                 int32_t greenBufferSize,
                                 int32_t blueBufferSize,
                                 int32_t alphaBufferSize);
        void SetFrameBufferSize(int32_t bufferSize);                                                    // �t���[���o�b�t�@�̃T�C�Y��ݒ�
        void SetDepthBufferSize(int32_t bufferSize);                                                    // �[�x�o�b�t�@�̃T�C�Y��ݒ�
        void SetStencilBufferSize(int32_t bufferSize);                                                  // �X�e���V���o�b�t�@�̃T�C�Y��ݒ�
        void SetMultiSample(int32_t sampleNumber);                                                      // �}���`�T���v���̐ݒ�
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_OpenGlManager::C_OpenGlManagerImpl::C_OpenGlManagerImpl(C_OpenGlManager* pOpenGlManager) :

        // OpenGL�}�l�[�W���[
        pOpenGlManager_(pOpenGlManager)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_OpenGlManager::C_OpenGlManagerImpl::~C_OpenGlManagerImpl()
    {
        if (pMainWindowData_) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  ���C���E�B���h�E
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_OpenGlManager::C_OpenGlManagerImpl::Initialize(const Window::C_BaseWindow& rMainWindow)
    {
        // �o�[�W������ݒ�
        const int32_t MAJOR_VERSION = 4;
        const int32_t MINOR_VERSION = 0;

        SetVersion(MAJOR_VERSION, MINOR_VERSION);

        // �v���t�@�C���̐ݒ�
        SetProfire(Profile::SDL_GL_CONTEXT_PROFILE_CORE);

        // �J���[�o�b�t�@�̐ݒ�
        const int32_t RED_BUFFER_SIZE = 8;
        const int32_t GREEN_BUFFER_SIZE = 8;
        const int32_t BLUE_BUFFER_SIZE = 8;
        const int32_t ALPHA_BUFFER_SIZE = 8;

        SetColorBuffferSize(RED_BUFFER_SIZE,
                            GREEN_BUFFER_SIZE,
                            BLUE_BUFFER_SIZE,
                            ALPHA_BUFFER_SIZE);

        // �o�b�t�@�T�C�Y�̐ݒ�
        const int32_t FRAME_BUFFER_SIZE = 32;

        static_assert(FRAME_BUFFER_SIZE >= (RED_BUFFER_SIZE 
                                          + GREEN_BUFFER_SIZE
                                          + BLUE_BUFFER_SIZE 
                                          + ALPHA_BUFFER_SIZE), "�t���[���o�b�t�@�̃T�C�Y������܂���B");

        SetFrameBufferSize(FRAME_BUFFER_SIZE);

        // �[�x�o�b�t�@�̐ݒ�
        const int32_t DEPTH_BUFFER_SIZE = 32;

        SetDepthBufferSize(DEPTH_BUFFER_SIZE);

        // �}���`�T���v���̐ݒ�
        const int32_t MULTI_SAMPLE_SAMPLE_NUMBER = 4;

        SetMultiSample(MULTI_SAMPLE_SAMPLE_NUMBER);

        // �X�e���V���o�b�t�@�̐ݒ�
        const int32_t STENCIL_BUFFER_SIZE = 8;

        SetStencilBufferSize(STENCIL_BUFFER_SIZE);

        // �_�u���o�b�t�@��L����
        EnableDoubleBuffer(true);

        // ����������L����
        EnableSwapInterval(true);

        // �����_�����O�R���e�L�X�g�̋��L��L����
        EnableShareRenderingContext(true);

        // ���C���E�B���h�E�̏���ݒ�
        pMainWindowData_ = rMainWindow.GetWindowData();

        // �����_�����O�R���e�L�X�g���쐬
        if (CreateRenderingContext(RenderingContextID::s_pMAIN) == false) return false;

        // GLEW�̏���������
        if (InitializeGlew() == false) return false;

        // �r���[�|�[�g�̐ݒ�
        const int32_t VIEW_POSITION_X = 0, VIEW_POSITIOIN_Y = 0;
        const int32_t VIEW_WIDTH = rMainWindow.GetWidth();
        const int32_t VIEW_HEIGHT = rMainWindow.GetHeight();

        pOpenGlManager_->SetViewport(VIEW_POSITION_X, VIEW_POSITIOIN_Y, VIEW_WIDTH, VIEW_HEIGHT);

        // �[�x�e�X�g��L���ɂ���
        pOpenGlManager_->EnableDepthTest(true);

        // �}���`�T���v�����O��L���ɂ���
        pOpenGlManager_->EnableMultiSample(true);

        // �o�b�N�o�b�t�@���N���A
        pOpenGlManager_->ClearBackBuffer();

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  JSON�t�@�C���ŏ������������s��
     *  @param  ���C���E�B���h�E
     *  @param  �t�@�C���p�X
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_OpenGlManager::C_OpenGlManagerImpl::InitializeWithJsonFile(const Window::C_BaseWindow& rMainWindow,
                                                                      const std::string& rFilePath)
    {
        // JSON�I�u�W�F�N�g���쐬
        auto data = JSON::JsonObject::s_CreateFromFile(rFilePath);

        // �o�[�W������ݒ�
        SetVersion(data["OpenGLData"]["Version"]["Major"].GetValue<JSON::Integer>(),
                   data["OpenGLData"]["Version"]["Minor"].GetValue<JSON::Integer>());

        // �v���t�@�C���̐ݒ�
        SetProfire(Profile::SDL_GL_CONTEXT_PROFILE_CORE);

        // �J���[�o�b�t�@�̐ݒ�
        const int32_t RED_BUFFER_SIZE = data["OpenGLData"]["Buffer"]["Color"]["Red"].GetValue<JSON::Integer>();
        const int32_t GREEN_BUFFER_SIZE = data["OpenGLData"]["Buffer"]["Color"]["Green"].GetValue<JSON::Integer>();
        const int32_t BLUE_BUFFER_SIZE = data["OpenGLData"]["Buffer"]["Color"]["Blue"].GetValue<JSON::Integer>();
        const int32_t ALPHA_BUFFER_SIZE = data["OpenGLData"]["Buffer"]["Color"]["Alpha"].GetValue<JSON::Integer>();

        SetColorBuffferSize(RED_BUFFER_SIZE, GREEN_BUFFER_SIZE, BLUE_BUFFER_SIZE, ALPHA_BUFFER_SIZE);

        // �t���[���o�b�t�@�̐ݒ�
        const int32_t FRAME_BUFFER_SIZE = 32;

        assert(FRAME_BUFFER_SIZE >= (RED_BUFFER_SIZE 
                                   + GREEN_BUFFER_SIZE
                                   + BLUE_BUFFER_SIZE
                                   + ALPHA_BUFFER_SIZE));

        SetFrameBufferSize(FRAME_BUFFER_SIZE);

        // �[�x�o�b�t�@�̐ݒ�
        SetDepthBufferSize(data["OpenGLData"]["Buffer"]["Depth"].GetValue<JSON::Integer>());

        // �X�e���V���o�b�t�@�̐ݒ�
        SetStencilBufferSize(data["OpenGLData"]["Buffer"]["Stencil"].GetValue<JSON::Integer>());

        // �}���`�T���v���̐ݒ�
        if (data["OpenGLData"]["MultiSample"]["UseFlag"].GetValue<JSON::Boolean>() == true)
        {
            SetMultiSample(data["OpenGLData"]["MultiSample"]["SampleNumber"].GetValue<JSON::Integer>());
        }

        // �_�u���o�b�t�@��L����
        EnableDoubleBuffer(true);

        // ����������L����
        EnableSwapInterval(data["OpenGLData"]["UseSwapIntervalFlag"].GetValue<JSON::Boolean>());

        // �����_�����O�R���e�L�X�g�̋��L��L����
        EnableShareRenderingContext(data["OpenGLData"]["UseShareRenderingContextFlag"].GetValue<JSON::Boolean>());

        // ���C���E�B���h�E�̏���ݒ�
        pMainWindowData_ = rMainWindow.GetWindowData();

        // �����_�����O�R���e�L�X�g���쐬
        if (CreateRenderingContext(RenderingContextID::s_pMAIN) == false) return false;

        // GLEW�̏���������
        if (InitializeGlew() == false) return false;

        // �r���[�|�[�g�̐ݒ�
        const int32_t VIEW_POSITION_X = 0, VIEW_POSITIOIN_Y = 0;
        const int32_t VIEW_WIDTH = rMainWindow.GetWidth();
        const int32_t VIEW_HEIGHT = rMainWindow.GetHeight();

        pOpenGlManager_->SetViewport(VIEW_POSITION_X, VIEW_POSITIOIN_Y, VIEW_WIDTH, VIEW_HEIGHT);

        // �[�x�e�X�g��L���ɂ���
        pOpenGlManager_->EnableDepthTest(true);

        // �}���`�T���v�����O��L���ɂ���
        pOpenGlManager_->EnableMultiSample(true);

        // �o�b�N�o�b�t�@���N���A
        pOpenGlManager_->ClearBackBuffer();

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  OpenGL�̏I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::Finalize()
    {
        // �J�����g�̃����_�����O�R���e�L�X�g�����Z�b�g���A
        // ���ׂẴ����_�����O�R���e�L�X�g��j��
        ResetCurrentRenderingContext();
        AllDestroyRenderingContext();

        // ���C���E�B���h�E�̏��̏��L����j��
        pMainWindowData_.reset();
    }


    /*************************************************************//**
     *
     *  @brief  �����_�����O�R���e�L�X�g���쐬����
     *  @param  ID
     *  @return ����I���Ftrue �E �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_OpenGlManager::C_OpenGlManagerImpl::CreateRenderingContext(const std::string& rId)
    {
        assert(pMainWindowData_);

        if (pRenderingContexts_.find(rId) != pRenderingContexts_.end())
        {
            PrintLog("[ C_OpenGlManagerImpl::CreateRenderingContext ] : ���Ƀ����_�����O�R���e�L�X�g���쐬����Ă��܂��B\n");
            PrintLog("                                             ID : %s\n", rId.c_str());

            return false;
        }

        // �����_�����O�R���e�L�X�g���쐬
        RenderingContextPtr pRenderingContext(::SDL_GL_CreateContext(pMainWindowData_.get()),
                                              [](RenderingContext* pRenderingContext){ ::SDL_GL_DeleteContext(pRenderingContext); });

        if (!pRenderingContext)
        {
            PrintLog("[ C_OpenGlManagerImpl::CreateRenderingContext ] : �����_�����O�R���e�L�X�g�̍쐬�Ɏ��s���܂����B\n");
            PrintLog("                                     �G���[���e : %s\n", ::SDL_GetError());

            return false;
        }

        pRenderingContexts_.emplace(rId, pRenderingContext);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �����_�����O�R���e�L�X�g��j������
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::DestroyRenderingContext(const std::string& rId)
    {
        if (pRenderingContexts_.find(rId) == pRenderingContexts_.end())
        {
            std::cout << "[ C_OpenGlManagerImpl::DestroyRenderingContext ] : �����_�����O�R���e�L�X�g���ۂ�������Ă��܂���B" << std::endl;
            std::cout << "                                              ID : " << rId << std::endl;

            return;
        }

        pRenderingContexts_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �S�Ẵ����_�����O�R���e�L�X�g��j������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::AllDestroyRenderingContext()
    {
        pRenderingContexts_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �����_�����O�R���e�L�X�g���J�����g�ɐݒ肷��
     *  @param  ID
     *  @return ����I���Ftrue �E �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_OpenGlManager::C_OpenGlManagerImpl::SetCurrentRenderingContext(const std::string& rId)
    {
        assert(pMainWindowData_);

        auto iterator = pRenderingContexts_.find(rId);

        if (iterator == pRenderingContexts_.end())
        {
            PrintLog("[ C_OpenGlManagerImpl::SetCurrentRenderingContext ] : �����_�����O�R���e�L�X�g���쐬����Ă��܂���B\n");
            PrintLog("                         ID : %s\n", rId.c_str());

            return false;
        }

        if (::SDL_GL_MakeCurrent(pMainWindowData_.get(), (*iterator).second.get()) != 0)
        {
            PrintLog("[ C_OpenGlManagerImpl::SetCurrentRenderingContext ] : �����_�����O�R���e�L�X�g���J�����g�ɂ���̂Ɏ��s���܂����B\n");
            PrintLog("                                         �G���[���e : %s\n", ::SDL_GetError());

            return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �J�����g�̃����_�����O�R���e�L�X�g�����Z�b�g����
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::ResetCurrentRenderingContext()
    {
        assert(pMainWindowData_);

        ::SDL_GL_MakeCurrent(pMainWindowData_.get(), nullptr);
    }


    /*************************************************************//**
     *
     *  @brief  �o�b�t�@�̓���ւ����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::SwapBuffer()
    {
        ::SDL_GL_SwapWindow(pMainWindowData_.get());
    }

    /*************************************************************//**
     *
     *  @brief  glew�̏������������s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue �E �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_OpenGlManager::C_OpenGlManagerImpl::InitializeGlew()
    {
        // glewInit���ĂԑO�ɂ����GL_TRUE�ɂ���K�v������( �����̏����̖�� )
        glewExperimental = GL_TRUE;

        // �g���֐������[�h
        GLenum errorResult = ::glewInit();

        if (errorResult != GLEW_OK)
        {
            PrintLog("[ C_OpenGlManagerImpl::Initialize ] : �g���֐��̃��[�h�Ɏ��s���܂����B\n");
            PrintLog("                         �G���[���e : %s\n", ::glewGetErrorString(errorResult));

            return false;
        }

        // GLEW2.0���O���t�B�b�N�J�[�h���T�|�[�g���Ă��Ȃ��ꍇ
        if (!GLEW_VERSION_2_0)
        {
            PrintLog("[ C_OpenGlManagerImpl::Initialize ] : GLEW2.0���O���t�B�b�N�J�[�h���T�|�[�g���Ă��܂���B\n");

            return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �_�u���o�b�t�@��L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::EnableDoubleBuffer(bool validFlag)
    {
        (validFlag == true) ? ::SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) : ::SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
    }


    /*************************************************************//**
     *
     *  @brief  ����������L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::EnableSwapInterval(bool validFlag)
    {
        (validFlag == true) ? ::SDL_GL_SetSwapInterval(1) : ::SDL_GL_SetSwapInterval(0);
    }


    /*************************************************************//**
     *
     *  @brief  �����_�����O�R���e�L�X�g�̋��L��L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::EnableShareRenderingContext(bool validFlag)
    {
        (validFlag == true) ? ::SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1) : ::SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 0);
    }


    /*************************************************************//**
     *
     *  @brief  �o�[�W������ݒ肷��
     *  @param  ���W���[�o�[�W����
     *  @param  �}�C�i�[�o�[�W����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::SetVersion(int32_t major, int32_t minor)
    {
        assert(major >= 1 && minor >= 0);

        ::SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
        ::SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
    }


    /*************************************************************//**
     *
     *  @brief  �v���t�@�C����ݒ肷��
     *  @param  �v���t�@�C��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::SetProfire(int32_t profile)
    {
        ::SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, profile);
    }


    /*************************************************************//**
     *
     *  @brief  �J���[�o�b�t�@�̃T�C�Y��ݒ肷��
     *  @param  ���b�h�o�b�t�@�̃T�C�Y
     *  @param  �O���[���o�b�t�@�̃T�C�Y
     *  @param  �u���[�o�b�t�@�̃T�C�Y
     *  @param  �A���t�@�o�b�t�@�̃T�C�Y
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::SetColorBuffferSize(int32_t redBufferSize,
                                                                   int32_t greenBufferSize,
                                                                   int32_t blueBufferSize,
                                                                   int32_t alphaBufferSize)
    {
        assert(redBufferSize >= 0);
        assert(greenBufferSize >= 0);
        assert(blueBufferSize >= 0);
        assert(alphaBufferSize >= 0);

        ::SDL_GL_SetAttribute(SDL_GL_RED_SIZE, redBufferSize);
        ::SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, greenBufferSize);
        ::SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, blueBufferSize);
        ::SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, alphaBufferSize);
    }


    /*************************************************************//**
     *
     *  @brief  �t���[���o�b�t�@�̃T�C�Y��ݒ肷��
     *  @param  �t���[���o�b�t�@�̃T�C�Y
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::SetFrameBufferSize(int32_t bufferSize)
    {
        ::SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, bufferSize);
    }


    /*************************************************************//**
     *
     *  @brief  �[�x�o�b�t�@�̃T�C�Y��ݒ肷��
     *  @param  �[�x�o�b�t�@�̃T�C�Y
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::SetDepthBufferSize(int32_t bufferSize)
    {
        ::SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, bufferSize);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e���V���o�b�t�@��ݒ肷��
     *  @param  �X�e���V���o�b�t�@�̃T�C�Y
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::SetStencilBufferSize(int32_t bufferSize)
    {
        ::SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, bufferSize);
    }


    /*************************************************************//**
     *
     *  @brief  �}���`�T���v���A���`�G�C���A�X��ݒ肷��
     *  @param  �}���`�T���v���ŗ��p����T���v���̐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::SetMultiSample(int32_t sampleNumber)
    {
        ::SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        ::SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, sampleNumber);
    }
}