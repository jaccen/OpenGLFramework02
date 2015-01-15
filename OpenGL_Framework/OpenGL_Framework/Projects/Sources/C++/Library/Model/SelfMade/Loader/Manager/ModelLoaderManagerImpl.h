/* �w�b�_�t�@�C�� */
#include "ModelLoaderManager.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief ���f��
//! @brief ���f���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Model
{
    //-------------------------------------------------------------
    //!
    //! @brief SelfMade
    //! @brief ����֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace SelfMade
    {
        //-------------------------------------------------------------
        //!
        //! @brief ���f�����[�_�[�}�l�[�W���[�C���v�������g
        //! @brief ���f�����[�_�[�}�l�[�W���[�̃v���C�x�[�g���̎���
        //!
        //-------------------------------------------------------------
        class C_ModelLoaderManager::C_ModelLoaderManagerImpl
        {
        public:
            C_ModelLoaderManagerImpl();                                                                 // �R���X�g���N�^
            ~C_ModelLoaderManagerImpl();                                                                // �f�X�g���N�^
            void Entry(const ModelLoaderPtr& prModelLoader, const std::string& rId);                    // �o�^����
            void Remove(const std::string& rId);                                                        // ��������
            void AllRemove();                                                                           // �S�Ẵ��f�����[�_�[������
            boost::optional<const ModelLoaderPtr&> GetModelLoader(const std::string& rId) const;        // ���f�����[�_�[���擾
        private:
            std::unordered_map<std::string, ModelLoaderPtr> pModelLoaders_;                             ///< @brief ���f�����[�_�[
        };


        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_ModelLoaderManager::C_ModelLoaderManagerImpl::C_ModelLoaderManagerImpl()
        {
        }


        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_ModelLoaderManager::C_ModelLoaderManagerImpl::~C_ModelLoaderManagerImpl()
        {
            if (pModelLoaders_.empty() == false) AllRemove();
        }


        /*************************************************************//**
         *
         *  @brief  ���f�����[�_�[�̓o�^���s��
         *  @param  ���f�����[�_�[
         *  @param  ID
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ModelLoaderManager::C_ModelLoaderManagerImpl::Entry(const ModelLoaderPtr& prModelLoader, const std::string& rId)
        {
            // ���f�����[�_�[�����ɓo�^����Ă���ꍇ
            if (pModelLoaders_.find(rId) != pModelLoaders_.end())
            {
                std::cout << "[ C_ModelLoaderManagerImpl::Entry ] : ���f�����[�_�[�����ɓo�^����Ă��܂��B" << std::endl;
                std::cout << "                                 ID : " << rId << std::endl;

                return;
            }

            pModelLoaders_.emplace(rId, prModelLoader);
        }


        /*************************************************************//**
         *
         *  @brief  ���f�����[�_�[�̏������s��
         *  @param  ID
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ModelLoaderManager::C_ModelLoaderManagerImpl::Remove(const std::string& rId)
        {
            // ���f�����[�_�[���o�^����Ă��Ȃ��ꍇ
            if (pModelLoaders_.find(rId) == pModelLoaders_.end())
            {
                std::cout << "[ C_ModelLoaderManagerImpl::Remove ] : ���f�����[�_�[��o�^���Ă��܂���B" << std::endl;
                std::cout << "                                  ID : " << rId << std::endl;

                return;
            }

            pModelLoaders_.erase(rId);
        }


        /*************************************************************//**
         *
         *  @brief  �S�Ẵ��f�����[�_�[�̏������s��
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ModelLoaderManager::C_ModelLoaderManagerImpl::AllRemove()
        {
            pModelLoaders_.clear();
        }


        /*************************************************************//**
         *
         *  @brief  ���f�����[�_�[���擾����
         *  @param  ID
         *  @return �o�^����Ă����ꍇ    �F���f�����[�_�[
         *  @return �o�^����ĂȂ������ꍇ�Fnone
         *
         ****************************************************************/
        boost::optional<const ModelLoaderPtr&> C_ModelLoaderManager::C_ModelLoaderManagerImpl::GetModelLoader(const std::string& rId) const
        {
            auto iterator = pModelLoaders_.find(rId);
            if (iterator == pModelLoaders_.end()) return boost::none;

            return (*iterator).second;
        }
    }
}