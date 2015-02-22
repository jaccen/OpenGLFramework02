/* �w�b�_�t�@�C�� */
#include "SpriteCreaterManager.h"
#include "../../../Debug/Helper/DebugHelper.h"
#include <deque>


//-------------------------------------------------------------
//!
//! @brief �X�v���C�g
//! @brief �X�v���C�g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Sprite
{
    /* �O���錾 */
    struct S_ManagementData;


    /* �ʖ� */
    using SpriteCreaterPtr = std::shared_ptr<C_SpriteCreater>;                                                      // SpriteCreaterPtr�^
    using ManagementPair = std::pair<std::string, S_ManagementData>;                                                // ManagementPair�^


    /** �Ǘ���� */
    struct S_ManagementData
    {
        float priority_ = 0.0f;                                                                                     ///< @brief �v���C�I���e�B
        SpriteCreaterPtr pSpriteCreater_;                                                                           ///< @brief �X�v���C�g�N���G�C�^�[
    };

    //-------------------------------------------------------------
    //!
    //! @brief �X�v���C�g�N���G�C�^�[�}�l�[�W���[�C���v�������g
    //! @brief �X�v���C�g�N���G�C�^�[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_SpriteCreaterManager::C_SpriteCreaterManagerImpl
    {
    public:
        C_SpriteCreaterManagerImpl();                                                                               // �R���X�g���N�^
        ~C_SpriteCreaterManagerImpl();                                                                              // �f�X�g���N�^
        void Draw();                                                                                                // �`�揈��
        void Sort();                                                                                                // �\�[�g����
        bool Create(const std::string& rId,                                                                         // �X�v���C�g�N���G�C�^�[���쐬
                    const Camera::CameraPtr& prCamera,
                    const Texture::TextureDataPtr pTextureData,
                    uint32_t maxParticleCount,
                    float priority);
        void Destroy(const std::string& rId);                                                                       // �X�v���C�g�N���G�C�^�[��j��
        void AllDestroy();                                                                                          // �X�v���C�g�N���G�C�^�[��S�Ĕj��
        boost::optional<SpriteCreaterWeakPtr> GetSpriteCreater(const std::string& rId);                             // �X�v���C�g�N���G�C�^�[���擾
    private:
        std::deque<ManagementPair> managementDatas_;                                                                ///< @brief �Ǘ����
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::C_SpriteCreaterManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::~C_SpriteCreaterManagerImpl()
    {
        if (managementDatas_.empty() == false) AllDestroy();
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::Draw()
    {
        for (auto& rManagementData : managementDatas_) rManagementData.second.pSpriteCreater_->Draw();
    }


    /*************************************************************//**
     *
     *  @brief  �\�[�g�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::Sort()
    {

        std::sort(managementDatas_.begin(),
                  managementDatas_.end(),
                  [](const ManagementPair& rManagementData, const ManagementPair& rAnotherManagementData){ return rManagementData.second.priority_ > rAnotherManagementData.second.priority_; });
    }

    /*************************************************************//**
     *
     *  @brief  �X�v���C�g�N���G�C�^�[�̍쐬����
     *  @param  ID
     *  @param  �J����
     *  @parama �e�N�X�`�����
     *  @param  �X�v���C�g�̍ő吔
     *  @param  �D��x
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::Create(const std::string& rId,
                                                                    const Camera::CameraPtr& prCamera,
                                                                    const Texture::TextureDataPtr pTextureData,
                                                                    uint32_t maxSpriteCount,
                                                                    float priority)
    {
        // ���ɍ쐬���Ă���ꍇ
        auto iterator = std::find_if(managementDatas_.begin(),
                                     managementDatas_.end(),
                                     [&](const ManagementPair& rpPatricleSystem){ return rpPatricleSystem.first == rId; });


        if (iterator != managementDatas_.end())
        {
            std::cout << "[ C_SpriteCreaterManagerImpl::Create ] : ���ɓ������X�v���C�g�N���G�C�^�[���쐬���Ă��܂��B" << std::endl;
            std::cout << "                                    ID : " << rId << std::endl;

            return true;
        }

        // �X�v���C�g�N���G�C�^�[�𐶐����A������
        auto pSpriteCreater = std::make_shared<C_SpriteCreater>();

        if (pSpriteCreater->Initialize(prCamera, pTextureData, maxSpriteCount) == false)
        {
            PrintLog("[ C_SpriteCreaterManagerImpl::Initialize ] : �X�v���C�g�N���G�C�^�[�̏����������Ɏ��s���܂����B");

            return false;
        }

        // �Ǘ�����ݒ肵�A�ێ�
        S_ManagementData managementData;
        managementData.pSpriteCreater_ = pSpriteCreater;
        managementData.priority_ = priority;

        managementDatas_.emplace_back(rId, managementData);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �X�v���C�g�N���G�C�^�[��j������
     *  @parama ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::Destroy(const std::string& rId)
    {
        // �X�v���C�g�N���G�C�^�[���쐬����Ă��Ȃ��ꍇ
        auto iterator = std::find_if(managementDatas_.begin(),
                                     managementDatas_.end(),
                                     [&](const ManagementPair& rManagementData){ return rManagementData.first == rId; });


        if (iterator == managementDatas_.end())
        {
            std::cout << "[ C_SpriteCreaterManagerImpl::Destroy ] : �X�v���C�g�N���G�C�^�[���쐬����Ă��܂���B" << std::endl;

            return;
        }

        (*iterator).second.pSpriteCreater_->Finalize();
        managementDatas_.erase(iterator);
    }


    /*************************************************************//**
     *
     *  @brief  �X�v���C�g�N���G�C�^�[��S�Ĕj������
     *  @parama �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::AllDestroy()
    {
        for (auto& rManagementData : managementDatas_) rManagementData.second.pSpriteCreater_->Finalize();
        managementDatas_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �X�v���C�g�N���G�C�^�[���擾����
     *  @parama ID
     *  @return �쐬����Ă���ꍇ  �F�X�v���C�g�N���G�C�^�[
     *  @return �쐬����Ă��Ȃ��ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<SpriteCreaterWeakPtr> C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::GetSpriteCreater(const std::string& rId)
    {
        auto iterator = std::find_if(managementDatas_.begin(),
                                     managementDatas_.end(),
                                     [&](const ManagementPair rpPatricleSystem){ return rpPatricleSystem.first == rId; });
        
        if (iterator == managementDatas_.end()) return boost::none;
        return (*iterator).second.pSpriteCreater_;
    }
}