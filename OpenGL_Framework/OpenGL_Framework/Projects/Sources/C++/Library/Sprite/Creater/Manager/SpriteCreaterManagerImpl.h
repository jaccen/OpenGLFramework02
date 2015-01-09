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
    /* �ʖ� */
    using SpriteCreaterPtr = std::shared_ptr<C_SpriteCreater>;                                                      // SpriteCreaterPtr�^


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
        void Update();                                                                                              // �X�V����
        void Draw();                                                                                                // �`�揈��
        bool Create(const std::string& rId,                                                                         // �X�v���C�g�N���G�C�^�[���쐬
                    const Camera::CameraPtr& prCamera,
                    const Texture::TextureDataPtr pTextureData,
                    uint32_t maxParticleCount);
        void Destroy(const std::string& rId);                                                                       // �X�v���C�g�N���G�C�^�[��j��
        void AllDestroy();                                                                                          // �X�v���C�g�N���G�C�^�[��S�Ĕj��
        boost::optional<SpriteCreaterWeakPtr> GetSpriteCreater(const std::string& rId);                             // �X�v���C�g�N���G�C�^�[���擾
    private:
        std::deque<std::pair<std::string, SpriteCreaterPtr>> pSpriteCreaters_;                                      ///< @brief �X�v���C�g�N���G�C�^�[
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
        if (pSpriteCreaters_.empty() == false) AllDestroy();
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
        for (auto &rPatricleSystem : pSpriteCreaters_) rPatricleSystem.second->Draw();
    }


    /*************************************************************//**
     *
     *  @brief  �X�v���C�g�N���G�C�^�[�̍쐬����
     *  @param  ID
     *  @param  �J����
     *  @parama �e�N�X�`�����
     *  @param  �X�v���C�g�̍ő吔
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::Create(const std::string& rId,
                                                                    const Camera::CameraPtr& prCamera,
                                                                    const Texture::TextureDataPtr pTextureData,
                                                                    uint32_t maxParticleCount)
    {
        // ���ɍ쐬���Ă���ꍇ
        auto iterator = std::find_if(pSpriteCreaters_.begin(),
                                     pSpriteCreaters_.end(),
                                     [&](const std::pair<std::string, SpriteCreaterPtr>& rpPatricleSystem){ return rpPatricleSystem.first == rId; });


        if (iterator != pSpriteCreaters_.end())
        {
            std::cout << "[ C_SpriteCreaterManagerImpl::Create ] : ���ɓ������X�v���C�g�N���G�C�^�[���쐬���Ă��܂��B" << std::endl;
            std::cout << "                                    ID : " << rId << std::endl;

            return true;
        }

        // �X�v���C�g�N���G�C�^�[�𐶐����A������
        auto pParticleSystem = std::make_shared<C_SpriteCreater>();

        if (pParticleSystem->Initialize(prCamera, pTextureData, maxParticleCount) == false)
        {
            PrintLog("[ C_SpriteCreaterManagerImpl::Initialize ] : �X�v���C�g�N���G�C�^�[�̏����������Ɏ��s���܂����B");

            return false;
        }

        // �X�v���C�g�N���G�C�^�[��ێ�����
        pSpriteCreaters_.emplace_back(rId, pParticleSystem);

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
        auto iterator = std::find_if(pSpriteCreaters_.begin(),
                                     pSpriteCreaters_.end(),
                                     [&](const std::pair<std::string, SpriteCreaterPtr>& rpPatricleSystem){ return rpPatricleSystem.first == rId; });


        if (iterator == pSpriteCreaters_.end())
        {
            std::cout << "[ C_SpriteCreaterManagerImpl::Destroy ] : �X�v���C�g�N���G�C�^�[���쐬����Ă��܂���B" << std::endl;

            return;
        }

        (*iterator).second->Finalize();
        pSpriteCreaters_.erase(iterator);
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
        for (auto& rParticleSystem : pSpriteCreaters_) rParticleSystem.second->Finalize();
        pSpriteCreaters_.clear();
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
        auto iterator = std::find_if(pSpriteCreaters_.begin(),
                                     pSpriteCreaters_.end(),
                                     [&](const std::pair<std::string, SpriteCreaterPtr>& rpPatricleSystem){ return rpPatricleSystem.first == rId; });
        
        if (iterator == pSpriteCreaters_.end()) return boost::none;
        return (*iterator).second;
    }
}