/* �w�b�_�t�@�C�� */
#include "UniformBuffer.h"
#include "../../../OpenGL/OpenGlDefine.h"


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
    //! @brief GLSL
    //! @brief GLSL�֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace GLSL
    {
        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �]������o�b�t�@
         *  @param  �o�b�t�@�̃T�C�Y
         *  @param  �u���b�N��
         *  @param  �C���̎��
         *
         ****************************************************************/
        C_UniformBuffer::C_UniformBuffer(void* pBuffer,
                                         uint32_t bufferSize,
                                         const std::string& rBlockName,
                                         OpenGL::ModifyEnum modifyType) :

            // �u���b�N��
            blockName_(rBlockName)

        {
            // ���j�t�H�[���o�b�t�@�I�u�W�F�N�g���쐬���A�o�C���h
            const int32_t CREWATE_BUFFER_NUMBER = 1;

            glGenBuffers(CREWATE_BUFFER_NUMBER, &handle_);
            glBindBuffer(OpenGL::Buffer::s_UNIFORM, handle_);

            // �f�[�^��]��
            glBufferData(OpenGL::Buffer::s_UNIFORM, bufferSize, pBuffer, modifyType);

            // ���j�t�H�[���o�b�t�@�I�u�W�F�N�g���A���o�C���h
            glBindBuffer(OpenGL::Buffer::s_UNIFORM, 0);
        }


        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_UniformBuffer::~C_UniformBuffer()
        {
            // ���j�t�H�[���o�b�t�@�[�I�u�W�F�N�g��j��
            const int32_t DELETE_BUFFER_NUMBER = 1;

            glDeleteBuffers(DELETE_BUFFER_NUMBER, &handle_);
        }


        /*************************************************************//**
         *
         *  @brief  �o�b�t�@�̏����������s��
         *  @param  �o�b�t�@
         *  @param  �o�b�t�@�̃T�C�Y
         *  @param  �C���̎��
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_UniformBuffer::Rewrite(void* pBuffer,
                                      uint32_t bufferSize,
                                      OpenGL::ModifyEnum modifyType)
        {
            // ���j�t�H�[���o�b�t�@�I�u�W�F�N�g���o�C���h
            glBindBuffer(OpenGL::Buffer::s_UNIFORM, handle_);

            // �f�[�^��]��
            glBufferData(OpenGL::Buffer::s_UNIFORM, bufferSize, pBuffer, modifyType);

            // ���j�t�H�[���o�b�t�@�I�u�W�F�N�g���A���o�C���h
            glBindBuffer(OpenGL::Buffer::s_UNIFORM, 0);
        }


        /*************************************************************//**
         *
         *  @brief  �v���O�����I�u�W�F�N�g����u���b�N�̃C���f�b�N�X���擾����
         *  @param  �Ȃ�
         *  @return �u���b�N�̃C���f�b�N�X
         *
         ****************************************************************/
        UniformBufferObjectHandle C_UniformBuffer::GetBlockIndexFromProgramObject(ProgramObjectHandle programObjectHandle) const
        {
            return glGetUniformBlockIndex(programObjectHandle, blockName_.c_str());
        }


        /*************************************************************//**
         *
         *  @brief  �n���h�����擾����
         *  @param  �Ȃ�
         *  @return �n���h��
         *
         ****************************************************************/
        UniformBufferObjectHandle C_UniformBuffer::GetHandle() const
        {
            return handle_;
        }


        /*************************************************************//**
         *
         *  @brief  �����������s��
         *  @param  �o�b�t�@�̃T�C�Y
         *  @param  �u���b�N��
         *  @return ���j�t�H�[���o�b�t�@
         *
         ****************************************************************/
        UniformBufferPtr C_UniformBuffer::s_Create(void* pBuffer,
                                                   uint32_t bufferSize,
                                                   const std::string& rBlockName,
                                                   OpenGL::ModifyEnum drawUsage)
        {
            return std::make_shared<C_UniformBuffer>(pBuffer, bufferSize, rBlockName, drawUsage);
        }
    }
}