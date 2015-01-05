/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../GlslDefine.h"
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
        /* �O���錾 */
        class C_UniformBuffer;


        /* �ʖ� */
        using UniformBufferPtr = std::shared_ptr<C_UniformBuffer>;                      // UniformBufferPtr�^


        //-------------------------------------------------------------
        //!
        //! @brief ���j�t�H�[���o�b�t�@�[
        //! @brief ���j�t�H�[���o�b�t�@�̃��b�p�[�N���X
        //! @brief �� std140���C�A�E�g�O��̍��ɂȂ��Ă��邱�Ƃɒ���
        //!
        //-------------------------------------------------------------
        class C_UniformBuffer
        {
        public:
            C_UniformBuffer(void* pBuffer,                                                                          // �R���X�g���N�^
                            uint32_t bufferSize,
                            const std::string& rBlockName,
                            OpenGL::ModifyEnum modifyType);
            ~C_UniformBuffer();                                                                                     // �f�X�g���N�^
            void Rewrite(void* pBuffer,                                                                             // ������������
                         uint32_t bufferSize,
                         OpenGL::ModifyEnum modifyType);
            UniformBlockIndex GetBlockIndexFromProgramObject(ProgramObjectHandle programObjectHandle) const;        // �v���O�����I�u�W�F�N�g����u���b�N�̃C���f�b�N�X���擾
            UniformBufferObjectHandle GetHandle() const;                                                            // �n���h�����擾
            static UniformBufferPtr s_Create(void* pBuffer,                                                         // ��������
                                             uint32_t bufferSize,
                                             const std::string& rBlockName,
                                             OpenGL::ModifyEnum modifyType);
        private:
            UniformBufferObjectHandle handle_ = 0;                                                                  ///< @brief �n���h��
            std::string blockName_;                                                                                 ///< @brief �u���b�N�� 
        };
    }
}
