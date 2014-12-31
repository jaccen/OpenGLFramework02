/* �w�b�_�t�@�C�� */
#include "FrameBuffer.h"


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
        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �o�b�t�@�̃T�C�Y
         *  @param  �o�b�t�@�̎��
         *  @param  �s�N�Z���f�[�^�̎��
         *  @param  �o�b�t�@�������ɗp����֐�
         *  @param  �o�b�t�@�̐�
         *
         ****************************************************************/
        C_FrameBuffer::C_FrameBuffer(S_BufferSize bufferSizes[],
                                     ecBufferType bufferTypes[],
                                     ecPixelDataType pixelDataTypes[],
                                     CreateBufferFunction pCreateBufferFunctions[],
                                     uint32_t bufferCount)
        {
            // �����_�[�o�b�t�@�f�[�^�����������m��
            renderBufferDatas_.resize(bufferCount);

            for (size_t i = 0; i < bufferCount; ++i)
            {
                // �f�[�^���R�s�[
                renderBufferDatas_[i].size_ = bufferSizes[i];
                renderBufferDatas_[i].type_ = bufferTypes[i];
                renderBufferDatas_[i].pixelDataType_ = pixelDataTypes[i];

                // �e�o�b�t�@�𐶐�
                pCreateBufferFunctions[i](&renderBufferDatas_[i].handle_, &renderBufferDatas_[i].size_);
            }

            // �J���[�o�b�t�@�̃��X�g�ƃJ���[���A�^�b�`������
            std::vector<GLenum> colorBufferList(bufferCount);
            uint32_t colorAttachmentCount = -1;

            // �A�^�b�`�����ނ𔻕ʂ���֐�
            static auto s_DistinctionAttachmentType = [&](ecPixelDataType pixelDataType)
            {
                if (pixelDataType == ecPixelDataType::COLOR)
                {
                    ++colorAttachmentCount;
                    return GL_COLOR_ATTACHMENT0 + colorAttachmentCount;
                }
                else if (pixelDataType == ecPixelDataType::DEPTH)
                {
                    return static_cast<uint32_t>(GL_DEPTH_ATTACHMENT);
                }
                else
                {
                    return static_cast<uint32_t>(GL_STENCIL_ATTACHMENT);
                }
            };

            // �t���[���o�b�t�@�I�u�W�F�N�g�𐶐����A�o�C���h
            glGenFramebuffers(1, &frameBufferObjectHandle_);
            glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObjectHandle_);

            for (size_t i = 0; i < bufferCount; ++i)
            {
                // �A�^�b�`�����ނ��擾
                uint32_t attachmentType = s_DistinctionAttachmentType(renderBufferDatas_[i].pixelDataType_);

                if (renderBufferDatas_[i].type_ == ecBufferType::RENDER)
                {
                    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                              attachmentType,
                                              GL_RENDERBUFFER,
                                              renderBufferDatas_[i].handle_);
                }
                else
                {
                    glFramebufferTexture2D(GL_FRAMEBUFFER,
                                           attachmentType,
                                           GL_TEXTURE_2D,
                                           renderBufferDatas_[i].handle_,
                                           0);
                }

                if (attachmentType == (GL_COLOR_ATTACHMENT0 + colorAttachmentCount))
                {
                    colorBufferList.push_back(attachmentType);
                }
                else
                {
                    colorBufferList.push_back(GL_NONE);
                }
            }

            // �J���[�o�b�t�@�̃��X�g��ݒ�
            glDrawBuffers(colorBufferList.size(), colorBufferList.data());

            // �t���[���o�b�t�@���A���o�C���h
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }


        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_FrameBuffer::~C_FrameBuffer()
        {
            // �����_�[�o�b�t�@��j��
            for (size_t i = 0, bufferSize = renderBufferDatas_.size(); i < bufferSize; ++i)
            {
                if (renderBufferDatas_[i].type_ == ecBufferType::RENDER)
                {
                    glDeleteRenderbuffers(1, &renderBufferDatas_[i].handle_);
                }
                else
                {
                    glDeleteTextures(1, &renderBufferDatas_[i].handle_);
                }
            }

            // �t���[���o�b�t�@�I�u�W�F�N�g��j��
            glDeleteFramebuffers(1, &frameBufferObjectHandle_);
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
            glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObjectHandle_);
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
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }


        /*************************************************************//**
         *
         *  @brief  �����_�[�o�b�t�@�f�[�^���擾����
         *  @param  �C���f�b�N�X
         *  @return �����_�[�o�b�t�@�f�[�^
         *
         ****************************************************************/
        const S_RenderBufferData& C_FrameBuffer::GetRenderBufferData(uint32_t index) const
        {
            assert(index < renderBufferDatas_.size());

            return renderBufferDatas_[index];
        }
    }
}