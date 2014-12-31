/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include <vector>


//-------------------------------------------------------------
//!
//! @brief �V�F�[�_�[
//! @brief �V�F�[�_�[�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Shader
{
    //-------------------------------------------------------------
    //!
    //! @brief �R����
    //! @brief ���ʊ֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace Common
    {
        /* �O���錾 */
        struct S_BufferSize;


        /* �ʖ� */
        using FrameBufferObjectHandle = GLuint;                                                 // FrameBufferObjectHandle�^
        using RenderBufferHandle = GLuint;                                                      // RenderBufferHandle�^
        using InternalFormat = GLenum;                                                          // InternalFormat�^
        using CreateBufferFunction = void(*)(RenderBufferHandle*, S_BufferSize*);               // CreateBufferFunction�^


        /* �o�b�t�@�̎�� */
        enum class ecBufferType
        {
            RENDER,                                                                             ///< @brief �����_�[�o�b�t�@
            TEXTURE,                                                                            ///< @brief ( 2D )�e�N�X�`��
        };

        /** �s�N�Z���f�[�^ */
        enum class ecPixelDataType
        {
            COLOR,                                                                              ///< @brief �F
            DEPTH,                                                                              ///< @brief �[�x
            STENCIL,                                                                            ///< @brief �X�e���V��
        };

         /** �o�b�t�@�̃T�C�Y */
        struct S_BufferSize
        {
            uint32_t width_ = 0;                                                                ///< @brief ��
            uint32_t height_ = 0;                                                               ///< @brief ����
        };

        /** �����_�[�o�b�t�@�f�[�^*/
        struct S_RenderBufferData
        {
            RenderBufferHandle handle_ = 0;                                                     ///< @brief �n���h��
            S_BufferSize size_;                                                                 ///< @brief �T�C�Y
            ecBufferType type_ = ecBufferType::RENDER;                                          ///< @brief ���
            ecPixelDataType pixelDataType_ = ecPixelDataType::COLOR;                            ///< @brief �s�N�Z���f�[�^�̎��
        };


        //-------------------------------------------------------------
        //!
        //! @brief �t���[���o�b�t�@
        //! @brief �t���[���o�b�t�@�̃��b�p�[�N���X
        //!
        //-------------------------------------------------------------
        class C_FrameBuffer
        {
        public:
            C_FrameBuffer(S_BufferSize bufferSizes[],                                           // �R���X�g���N�^
                          ecBufferType bufferTypes[],
                          ecPixelDataType pixelDataTypes[],
                          CreateBufferFunction pCreateBufferFunctions[],
                          uint32_t bufferCount);
            ~C_FrameBuffer();                                                                   // �f�X�g���N�^
            void Bind();                                                                        // �t���[���o�b�t�@���o�C���h
            void Unbind();                                                                      // �t���[���o�b�t�@���A���o�C���h
            const S_RenderBufferData& GetRenderBufferData(uint32_t index) const;                // �����_�[�o�b�t�@�f�[�^���擾
        private:
            FrameBufferObjectHandle frameBufferObjectHandle_ = 0;                               ///< @brief �t���[���o�b�t�@�I�u�W�F�N�g�n���h��
            std::vector<S_RenderBufferData> renderBufferDatas_;                                 ///< @brief �����_�[�o�b�t�@�f�[�^
        };
    }
}