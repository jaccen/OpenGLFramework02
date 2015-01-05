/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../../../Singleton/Singleton.h"
#include "../UniformBuffer.h"


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
        //-------------------------------------------------------------
        //!
        //! @brief ���j�t�H�[���o�b�t�@�}�l�[�W���[
        //! @brief ���j�t�H�[���o�b�t�@���Ǘ�����N���X
        //!
        //-------------------------------------------------------------
        class C_UniformBufferManager : public Singleton::C_Singleton<C_UniformBufferManager>
        {
            friend C_Singleton<C_UniformBufferManager>;
        public:
            void Entry(const UniformBufferPtr& prUniformBuffer, const std::string& rId);                // �o�^����
            void Remove(const std::string& rId);                                                        // ��������
            void AllRemove();                                                                           // �S�Ẵ��j�t�H�[���o�b�t�@������
            boost::optional<const UniformBufferPtr&> GetUniformBuffer(const std::string& rId) const;    // ���j�t�H�[���o�b�t�@���擾
        private:
            /* �O���錾 */
            class C_UniformBufferManagerImpl;

            std::unique_ptr<C_UniformBufferManagerImpl> upImpl_;                                        ///< @brief �������

            C_UniformBufferManager();                                                                   // �R���X�g���N�^
            ~C_UniformBufferManager() override;                                                         // �f�X�g���N�^
        };
    }
}
