/* �w�b�_�t�@�C�� */
#include "BaseWindow.h"
#include "../../Debug/Helper/DebugHelper.h"


//-------------------------------------------------------------
//!
//! @brief �E�B���h�E
//! @brief �E�B���h�E�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Window
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BaseWindow::C_BaseWindow()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BaseWindow::~C_BaseWindow()
    {
        if (!pWindowData_) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  �E�B���h�E�̏������������s��
     *  @param  �^�C�g��
     *  @param  ��
     *  @param  ����
     *  @param  �������ɗ��p����t���O
     *  @param  ��������Ƃ���X���W
     *  @param  ��������Ƃ���Y���W
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_BaseWindow::Initialize(const std::string& rTitle,
                                  int32_t width,
                                  int32_t height,
                                  int32_t createFlags,
                                  int32_t createPositionX,
                                  int32_t createPositionY)
    {
        assert(createFlags & CreateFlag::SDL_WINDOW_OPENGL);
        
#ifndef _DEBUG

        /*
        // �E�B���h�E���[�h�ƃt���X�N���[���̐؂�ւ����s�����b�Z�[�W�{�b�N�X��\��
        if (MessageBox(nullptr, "�t���X�N���[�����[�h�ŕ\�����܂����H", "�X�N���[�����[�h�ݒ�", MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
        // �ʏ�̃t���X�N���[����( ���Ń\�t�g�𓮂����Ă�Ƃ��܂������Ȃ����Ƃ�����̂Œ��� )
        createFlags |= CreateFlag::SDL_WINDOW_FULLSCREEN;

        // createFlags |= CreateFlag::SDL_WINDOW_FULLSCREEN_DESKTOP;
        }*/

#endif

        // �E�B���h�E�̐���
        pWindowData_.reset(::SDL_CreateWindow(rTitle.c_str(),
                           createPositionX,
                           createPositionY,
                           width,
                           height,
                           createFlags),
                           [](WindowData* pWindowData){ ::SDL_DestroyWindow(pWindowData); });

        // �E�B���h�E�̐����Ɏ��s�����ꍇ
        if (!pWindowData_)
        {
            PrintLog("[ C_BaseWindow::Initialize ] : �E�B���h�E�̐����Ɏ��s���܂����B\n");
            PrintLog("                  �G���[���e : %s\n", ::SDL_GetError());

            return false;
        }

        // ID�̎擾
        id_ = ::SDL_GetWindowID(pWindowData_.get());

        // �T�C�Y�̐ݒ�
        width_ = width;
        height_ = height;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �E�B���h�E�̏I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseWindow::Finalize()
    {
        // �E�B���h�E�f�[�^�̏��L����j�����AID�����Z�b�g
        pWindowData_.reset();
        id_ = 0;
    }


    /*************************************************************//**
     *
     *  @brief  �E�B���h�E�̏����擾����
     *  @param  �Ȃ�
     *  @return �E�B���h�E
     *
     ****************************************************************/
    const WindowDataPtr& C_BaseWindow::GetWindowData() const
    {
        return pWindowData_;
    }


    /*************************************************************//**
     *
     *  @brief  ID���擾����
     *  @param  �Ȃ�
     *  @return ID
     *
     ****************************************************************/
    uint32_t C_BaseWindow::GetId() const
    {
        return id_;
    }


    /*************************************************************//**
     *
     *  @brief  �����擾����
     *  @param  �Ȃ�
     *  @return ��
     *
     ****************************************************************/
    int32_t C_BaseWindow::GetWidth() const
    {
        return width_;
    }


    /*************************************************************//**
     *
     *  @brief  �������擾����
     *  @param  �Ȃ�
     *  @return ����
     *
     ****************************************************************/
    int32_t C_BaseWindow::GetHeight() const
    {
        return height_;
    }


    /*************************************************************//**
     *
     *  @brief  ����ݒ肷��
     *  @param  ��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseWindow::SetWidth(int32_t width)
    {
        width_ = width;
    }


    /*************************************************************//**
     *
     *  @brief  ������ݒ肷��
     *  @param  ����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseWindow::SetHeight(int32_t height)
    {
        height_ = height;
    }


    /*************************************************************//**
     *
     *  @brief  �A�X�y�N�g����擾����
     *  @param  �Ȃ�
     *  @return �A�X�y�N�g��
     *
     ****************************************************************/
    template<typename T>
    T C_BaseWindow::GetAspectRatio()
    {
        return static_cast<T>(width_) / static_cast<T>(height_);
    }


#pragma region �����I�C���X�^���X��


    /* �A�X�y�N�g����擾 */
    template float C_BaseWindow::GetAspectRatio();
    template double C_BaseWindow::GetAspectRatio();


#pragma endregion

}