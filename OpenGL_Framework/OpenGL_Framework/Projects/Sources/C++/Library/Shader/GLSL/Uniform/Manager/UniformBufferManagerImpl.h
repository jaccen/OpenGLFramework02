/* �w�b�_�t�@�C�� */
#include "UniformBufferManager.h"
#include <unordered_map>


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
        //! @brief ���j�t�H�[���o�b�t�@�C���v�������g
        //! @brief ���j�t�H�[���o�b�t�@�̃v���C�x�[�g���̎���
        //!
        //-------------------------------------------------------------
        class C_UniformBufferManager::C_UniformBufferManagerImpl
        {
        public:
            C_UniformBufferManagerImpl();                                                                   // �R���X�g���N�^
            ~C_UniformBufferManagerImpl();                                                                  // �f�X�g���N�^
            void Entry(const UniformBufferPtr& prUniformBuffer, const std::string& rId);                    // �o�^����
            void Remove(const std::string& rId);                                                            // ��������
            void AllRemove();                                                                               // �S�Ẵ��j�t�H�[���o�b�t�@������
            boost::optional<const UniformBufferPtr&> GetUniformBuffer(const std::string& rId) const;        // ���j�t�H�[���o�b�t�@���擾
        private:
            std::unordered_map<std::string, UniformBufferPtr> pUniformBuffers_;                             ///< @brief ���j�t�H�[���o�b�t�@
        };


        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_UniformBufferManager::C_UniformBufferManagerImpl::C_UniformBufferManagerImpl()
        {
        }


        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_UniformBufferManager::C_UniformBufferManagerImpl::~C_UniformBufferManagerImpl()
        {
            if (pUniformBuffers_.empty() == false) AllRemove();
        }


        /*************************************************************//**
         *
         *  @brief  ���j�t�H�[���o�b�t�@�̓o�^���s��
         *  @param  ���j�t�H�[���o�b�t�@
         *  @param  ID
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_UniformBufferManager::C_UniformBufferManagerImpl::Entry(const UniformBufferPtr& prUniformBuffer, const std::string& rId)
        {
            // ���j�t�H�[���o�b�t�@�����ɓo�^����Ă���ꍇ
            if (pUniformBuffers_.find(rId) != pUniformBuffers_.end())
            {
                std::cout << "[ C_UniformBufferManagerImpl::Entry ] : ���j�t�H�[���o�b�t�@�����ɓo�^����Ă��܂��B" << std::endl;
                std::cout << "                                   ID : " << rId << std::endl;

                return;
            }

            pUniformBuffers_.emplace(rId, prUniformBuffer);
        }


        /*************************************************************//**
         *
         *  @brief  ���j�t�H�[���o�b�t�@�̏������s��
         *  @param  ID
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_UniformBufferManager::C_UniformBufferManagerImpl::Remove(const std::string& rId)
        {
            // ���j�t�H�[���o�b�t�@���o�^����Ă��Ȃ��ꍇ
            if (pUniformBuffers_.find(rId) == pUniformBuffers_.end())
            {
                std::cout << "[ C_UniformBufferManagerImpl::Remove ] : ���j�t�H�[���o�b�t�@��o�^���Ă��܂���B" << std::endl;
                std::cout << "                                    ID : " << rId << std::endl;

                return;
            }

            pUniformBuffers_.erase(rId);
        }


        /*************************************************************//**
         *
         *  @brief  �S�Ẵ��j�t�H�[���o�b�t�@�̏������s��
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_UniformBufferManager::C_UniformBufferManagerImpl::AllRemove()
        {
            pUniformBuffers_.clear();
        }


        /*************************************************************//**
         *
         *  @brief  ���j�t�H�[���o�b�t�@���擾����
         *  @param  ID
         *  @return �o�^����Ă����ꍇ    �F���j�t�H�[���o�b�t�@
         *  @return �o�^����ĂȂ������ꍇ�Fnone
         *
         ****************************************************************/
        boost::optional<const UniformBufferPtr&> C_UniformBufferManager::C_UniformBufferManagerImpl::GetUniformBuffer(const std::string& rId) const
        {
            auto iterator = pUniformBuffers_.find(rId);
            if (iterator == pUniformBuffers_.end()) return boost::none;

            return (*iterator).second;
        }
    }
}