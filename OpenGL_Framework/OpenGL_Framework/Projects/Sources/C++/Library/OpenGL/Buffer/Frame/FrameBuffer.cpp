/* �w�b�_�t�@�C�� */
#include "FrameBuffer.h"


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace OpenGL
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_FrameBuffer::C_FrameBuffer()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_FrameBuffer::~C_FrameBuffer()
    {
        if (frameBufferObjectHandle_ != 0) Finalize();
    }



    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �e�N�X�`���̕�
     *  @param  �e�N�X�`���̍���
     *  @param  �e�N�X�`���n���h��
     *  @param  �e�N�X�`���n���h���̐�
     *  @param  �[�x�̓����t�H�[�}�b�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FrameBuffer::Initialize(int32_t textureWidth,
                                   int32_t textureHeight,
                                   Texture::TextureHandle textureHandles[],
                                   uint32_t textureHandleCount,
                                   OpenGL::FormatType depthInternalFormat)
    {
        // �����_�[�o�b�t�@�I�u�W�F�N�g���쐬
        glGenRenderbuffers(1, &renderBufferObjectHandle_);
        glBindRenderbuffer(OpenGL::Buffer::s_RENDER, renderBufferObjectHandle_);
        glRenderbufferStorage(OpenGL::Buffer::s_RENDER, depthInternalFormat, textureWidth, textureHeight);
        glBindRenderbuffer(OpenGL::Buffer::s_RENDER, 0);
        
        // �t���[���o�b�t�@�I�u�W�F�N�g���쐬���A�o�C���h
        glGenFramebuffers(1, &frameBufferObjectHandle_);
        Bind();

        for (size_t i = 0; i < textureHandleCount; ++i)
        {
            // �e�N�X�`�����֘A�t��
            glFramebufferTexture2D(OpenGL::Buffer::s_FRAME, GL_COLOR_ATTACHMENT0 + i, Texture::Type::s_2D, textureHandles[i], 0);
        }
        
        // �����_�[�o�b�t�@���֘A�t�� 
        glFramebufferRenderbuffer(OpenGL::Buffer::s_FRAME, GL_DEPTH_ATTACHMENT, OpenGL::Buffer::s_RENDER, renderBufferObjectHandle_);

        // �֘A�t���̎�ނ�ݒ�
        for (size_t i = 0; i < textureHandleCount; ++i)
        {
            attachmentTypes_.push_back(GL_COLOR_ATTACHMENT0 + i);
        }

        glDrawBuffers(textureHandleCount, attachmentTypes_.data());


        // �t���[���o�b�t�@���A���o�C���h
        Unbind();
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FrameBuffer::Finalize()
    {
        // �e�I�u�W�F�N�g��j��
        glDeleteRenderbuffers(1, &renderBufferObjectHandle_);
        glDeleteFramebuffers(1, &frameBufferObjectHandle_);

        renderBufferObjectHandle_ = 0;
        frameBufferObjectHandle_ = 0;
        
        // �A�^�b�`�����g�̎�ނ��N���A
        attachmentTypes_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �t���[���o�b�t�@���o�C���h����
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FrameBuffer::Bind()
    {
        glBindFramebuffer(OpenGL::Buffer::s_FRAME, frameBufferObjectHandle_);
    }


    /*************************************************************//**
     *
     *  @brief  �t���[���o�b�t�@���A���o�C���h����
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FrameBuffer::Unbind()
    {
        glBindFramebuffer(OpenGL::Buffer::s_FRAME, 0);
    }


    /*************************************************************//**
     *
     *  @brief  �����������s��
     *  @param  �Ȃ�
     *  @return �t���[���o�b�t�@
     *
     ****************************************************************/
    FrameBufferPtr C_FrameBuffer::s_Create()
    {
        return std::make_shared<C_FrameBuffer>();
    }
}