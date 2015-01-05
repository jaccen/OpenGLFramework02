/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include <vector>
#include "../../OpenGlDefine.h"
#include "../../../Texture/TextureDefine.h"


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace OpenGL
{
    /* �O���錾 */
    class C_FrameBuffer;


    /* �ʖ� */
    using FrameBufferObjectHandle = GLuint;                                                                 // FrameBufferObjectHandle�^
    using RenderBufferObjectHandle = GLuint;                                                                // RenderBufferObjectHandle�^
    using FrameBufferPtr = std::shared_ptr<C_FrameBuffer>;                                                  // FrameBufferPtr�^
    using AttachmentType = GLenum;                                                                          // AttachmentType�^


    //-------------------------------------------------------------
    //!
    //! @brief �t���[���o�b�t�@
    //! @brief �t���[���o�b�t�@�̃��b�p�[�N���X
    //!
    //-------------------------------------------------------------
    class C_FrameBuffer
    {
    public:
        C_FrameBuffer();                                                                                    // �R���X�g���N�^
        ~C_FrameBuffer();                                                                                   // �f�X�g���N�^
        void Initialize(int32_t windowWidth,                                                                // ����������
                        int32_t windowHeight,
                        Texture::TextureHandle textureHandles[],
                        uint32_t textureHandleCount,
                        OpenGL::FormatType depthInternalFormat = OpenGL::Format::Internal::s_DEPTH_24);
        void Finalize();                                                                                    // �I������
        void Bind();                                                                                        // �t���[���o�b�t�@���o�C���h
        void Unbind();                                                                                      // �t���[���o�b�t�@���A���o�C���h

        static FrameBufferPtr s_Create();                                                                   // ��������
    private:
        FrameBufferObjectHandle frameBufferObjectHandle_ = 0;                                               ///< @brief �t���[���o�b�t�@�I�u�W�F�N�g�n���h��
        RenderBufferObjectHandle renderBufferObjectHandle_ = 0;                                             ///< @brief �����_�[�o�b�t�@�I�u�W�F�N�g�n���h��
        std::vector<AttachmentType> attachmentTypes_;                                                       ///< @brief �֘A�t���̎��
    };
}
