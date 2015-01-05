/* �w�b�_�t�@�C�� */
#include "LightManager.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief ���C�g
//! @brief ���C�g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Light
{
    //-------------------------------------------------------------
    //!
    //! @brief ���C�g�}�l�[�W���[�C���v�������g
    //! @brief ���C�g�}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_LightManager::C_LightManagerImpl
    {
    public:
        C_LightManagerImpl();                                                           // �R���X�g���N�^
        ~C_LightManagerImpl();                                                          // �f�X�g���N�^
        void Entry(const LightPtr& prLight, const std::string& rId);                    // �o�^����
        void Remove(const std::string& rId);                                            // ��������
        void AllRemove();                                                               // �S�Ẵ��C�g������
        boost::optional<const LightPtr&> GetLight(const std::string& rId) const;        // ���C�g���擾
    private:
        std::unordered_map<std::string, LightPtr> pLights_;                             ///< @brief ���C�g
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_LightManager::C_LightManagerImpl::C_LightManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_LightManager::C_LightManagerImpl::~C_LightManagerImpl()
    {
        if (pLights_.empty() == false) AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  ���C�g�̓o�^���s��
     *  @param  ���C�g
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LightManager::C_LightManagerImpl::Entry(const LightPtr& prLight, const std::string& rId)
    {
        // ���C�g�����ɓo�^����Ă���ꍇ
        if (pLights_.find(rId) != pLights_.end())
        {
            std::cout << "[ C_LightManagerImpl::Entry ] : ���C�g�����ɓo�^����Ă��܂��B" << std::endl;
            std::cout << "                           ID : " << rId << std::endl;

            return;
        }

        pLights_.emplace(rId, prLight);
    }


    /*************************************************************//**
     *
     *  @brief  ���C�g�̏������s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LightManager::C_LightManagerImpl::Remove(const std::string& rId)
    {
        // ���C�g���o�^����Ă��Ȃ��ꍇ
        if (pLights_.find(rId) == pLights_.end())
        {
            std::cout << "[ C_LightManagerImpl::Remove ] : ���C�g��o�^���Ă��܂���B" << std::endl;
            std::cout << "                               ID : " << rId << std::endl;

            return;
        }

        pLights_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �S�Ẵ��C�g�̏������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LightManager::C_LightManagerImpl::AllRemove()
    {
        pLights_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  ���C�g���擾����
     *  @param  ID
     *  @return �o�^����Ă����ꍇ    �F���C�g
     *  @return �o�^����ĂȂ������ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const LightPtr&> C_LightManager::C_LightManagerImpl::GetLight(const std::string& rId) const
    {
        auto iterator = pLights_.find(rId);
        if (iterator == pLights_.end()) return boost::none;

        return (*iterator).second;
    }
}