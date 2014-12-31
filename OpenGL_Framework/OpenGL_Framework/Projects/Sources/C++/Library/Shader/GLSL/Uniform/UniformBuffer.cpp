/* �w�b�_�t�@�C�� */
#include "UniformBuffer.h"


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
         *  @param  �T�C�Y
         *  @param  �u���b�N��
         *  @param  �C���̎��
         *
         ****************************************************************/
        C_UniformBuffer::C_UniformBuffer(void* pBuffer,
                                         uint32_t size,
                                         const std::string& rBlockName,
                                         ModifyEnum modifyType) :

            // �u���b�N��
            blockName_(rBlockName)

        {
            // ���j�t�H�[���o�b�t�@�I�u�W�F�N�g���쐬���A�o�C���h
            const int32_t CREWATE_BUFFER_NUMBER = 1;

            glGenBuffers(CREWATE_BUFFER_NUMBER, &handle_);
            glBindBuffer(BufferType::s_UNIFORM, handle_);

            // �f�[�^��]��
            glBufferData(BufferType::s_UNIFORM, size, pBuffer, modifyType);

            // ���j�t�H�[���o�b�t�@�I�u�W�F�N�g���A���o�C���h
            glBindBuffer(BufferType::s_UNIFORM, 0);
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
         *  @param  �T�C�Y
         *  @param  �C���̎��
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_UniformBuffer::Rewrite(void* pBuffer,
                                      uint32_t size,
                                      ModifyEnum modifyType)
        {
            // ���j�t�H�[���o�b�t�@�I�u�W�F�N�g���o�C���h
            glBindBuffer(BufferType::s_UNIFORM, handle_);

            // �f�[�^��]��
            glBufferData(BufferType::s_UNIFORM, size, pBuffer, modifyType);

            // ���j�t�H�[���o�b�t�@�I�u�W�F�N�g���A���o�C���h
            glBindBuffer(BufferType::s_UNIFORM, 0);
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
         *  @param  �T�C�Y
         *  @param  �u���b�N��
         *  @return ���j�t�H�[���o�b�t�@
         *
         ****************************************************************/
        UniformBufferPtr C_UniformBuffer::s_Create(void* pBuffer,
                                                   uint32_t size,
                                                   const std::string& rBlockName,
                                                   ModifyEnum drawUsage)
        {
            return std::make_shared<C_UniformBuffer>(pBuffer, size, rBlockName, drawUsage);
        }
    }
}