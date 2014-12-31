/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include <SDL_video.h>


//-------------------------------------------------------------
//!
//! @brief �E�B���h�E
//! @brief �E�B���h�E�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Window
{
    /* �ʖ� */
    using WindowData = SDL_Window;                                                          // WindowData�^
    using WindowDataPtr = std::shared_ptr<WindowData>;                                      // WindowDataPtr�^
    using CreateFlag = SDL_WindowFlags;                                                     // CreateFlag�^


    namespace
    {
        /* �f�t�H���g */
        namespace Default
        {
            const int32_t s_WIDTH = 640;                                                    ///< @brief ��
            const int32_t s_HEIGHT = 480;                                                   ///< @brief ����
        }

        /* �����ʒu */
        namespace CreatePosition
        {
            const int32_t s_CENTER = SDL_WINDOWPOS_CENTERED;                                ///< @brief �^��
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief �x�[�X�E�B���h�E
    //! @brief �E�B���h�E�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BaseWindow
    {
    public:
        C_BaseWindow();                                                                     // �R���X�g���N�^
        virtual ~C_BaseWindow();                                                            // �f�X�g���N�^
        virtual bool Initialize(const ::std::string& rTitle = "OpenGL_Framework",           // ����������
                                int32_t width = Default::s_WIDTH,
                                int32_t height = Default::s_HEIGHT,
                                int32_t createFlags = CreateFlag::SDL_WINDOW_OPENGL,
                                int32_t createPositionX = CreatePosition::s_CENTER,
                                int32_t createPositionY = CreatePosition::s_CENTER);
        virtual void Finalize();                                                            // �I������
        const WindowDataPtr& GetWindowData() const;                                         // �E�B���h�E�̏����擾
        uint32_t GetId() const;                                                             // ID���擾
        int32_t GetWidth() const;                                                           // �����擾
        int32_t GetHeight() const;                                                          // �������擾
        void SetWidth(int32_t width);                                                       // ����ݒ�
        void SetHeight(int32_t height);                                                     // ������ݒ�

        template<typename T = float>
        T GetAspectRatio();                                                                 // �A�X�y�N�g����擾
    protected:
        WindowDataPtr pWindowData_;                                                         ///< @brief �E�B���h�E���
        uint32_t id_ = 0;                                                                   ///< @brief ID
        int32_t width_ = 0;                                                                 ///< @brief ��
        int32_t height_ = 0;                                                                ///< @brief ����
    };
}