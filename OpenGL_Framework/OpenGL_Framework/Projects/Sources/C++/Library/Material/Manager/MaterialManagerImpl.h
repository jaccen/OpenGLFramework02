/* �w�b�_�t�@�C�� */
#include "MaterialManager.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief �}�e���A��
//! @brief �}�e���A���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Material
{
    //-------------------------------------------------------------
    //!
    //! @brief �}�e���A���}�l�[�W���[�C���v�������g
    //! @brief �}�e���A���}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_MaterialManager::C_MaterialManagerImpl
    {
    public:
        C_MaterialManagerImpl();                                                            // �R���X�g���N�^
        ~C_MaterialManagerImpl();                                                           // �f�X�g���N�^
        void Entry(const MaterialPtr& prMaterial, const std::string& rId);                  // �o�^����
        void Remove(const std::string& rId);                                                // ��������
        void AllRemove();                                                                   // �S�Ẵ}�e���A��������
        boost::optional<const MaterialPtr&> GetMaterial(const std::string& rId) const;      // �}�e���A�����擾
    private:
        std::unordered_map<std::string, MaterialPtr> pMaterials_;                           ///< @brief �}�e���A��
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_MaterialManager::C_MaterialManagerImpl::C_MaterialManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_MaterialManager::C_MaterialManagerImpl::~C_MaterialManagerImpl()
    {
        if (pMaterials_.empty() == false) AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  �}�e���A���̓o�^���s��
     *  @param  �}�e���A��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_MaterialManager::C_MaterialManagerImpl::Entry(const MaterialPtr& prMaterial, const std::string& rId)
    {
        // �}�e���A�������ɓo�^����Ă���ꍇ
        if (pMaterials_.find(rId) != pMaterials_.end())
        {
            std::cout << "[ C_MaterialManagerImpl::Entry ] : �}�e���A�������ɓo�^����Ă��܂��B" << std::endl;
            std::cout << "                              ID : " << rId << std::endl;

            return;
        }

        pMaterials_.emplace(rId, prMaterial);
    }


    /*************************************************************//**
     *
     *  @brief  �}�e���A���̏������s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_MaterialManager::C_MaterialManagerImpl::Remove(const std::string& rId)
    {
        // �}�e���A�����o�^����Ă��Ȃ��ꍇ
        if (pMaterials_.find(rId) == pMaterials_.end())
        {
            std::cout << "[ C_MaterialManagerImpl::Remove ] : �}�e���A����o�^���Ă��܂���B" << std::endl;
            std::cout << "                               ID : " << rId << std::endl;

            return;
        }

        pMaterials_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �S�Ẵ}�e���A���̏������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_MaterialManager::C_MaterialManagerImpl::AllRemove()
    {
        pMaterials_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �}�e���A�����擾����
     *  @param  ID
     *  @return �o�^����Ă����ꍇ    �F�}�e���A��
     *  @return �o�^����ĂȂ������ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const MaterialPtr&> C_MaterialManager::C_MaterialManagerImpl::GetMaterial(const std::string& rId) const
    {
        auto iterator = pMaterials_.find(rId);
        if (iterator == pMaterials_.end()) return boost::none;

        return (*iterator).second;
    }
}