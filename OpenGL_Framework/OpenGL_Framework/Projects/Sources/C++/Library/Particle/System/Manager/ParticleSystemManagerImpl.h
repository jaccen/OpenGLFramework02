/* �w�b�_�t�@�C�� */
#include "ParticleSystemManager.h"
#include "../../../Debug/Helper/DebugHelper.h"
#include <deque>


//-------------------------------------------------------------
//!
//! @brief �p�[�e�B�N��
//! @brief �p�[�e�B�N���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Particle
{
    /* �ʖ� */
    using ParticleSystemPtr = std::shared_ptr<C_ParticleSystem>;                                                    // ParticleSystemPtr�^


    //-------------------------------------------------------------
    //!
    //! @brief �p�[�e�B�N���}�l�[�W���[�C���v�������g
    //! @brief �p�[�e�B�N���V�X�e���̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_ParticleSystemManager::C_ParticleSystemManagerImpl
    {
    public:
        C_ParticleSystemManagerImpl();                                                                              // �R���X�g���N�^
        ~C_ParticleSystemManagerImpl();                                                                             // �f�X�g���N�^
        void Update();                                                                                              // �X�V����
        void Draw();                                                                                                // �`�揈��
        bool Create(const std::string& rId,                                                                         // �p�[�e�B�N���V�X�e�����쐬
                    const Camera::CameraPtr& prCamera,
                    Texture::TextureHandle textureHandle,
                    uint32_t maxParticleCount);
        void Destroy(const std::string& rId);                                                                       // �p�[�e�B�N���V�X�e����j��
        void AllDestroy();                                                                                          // �p�[�e�B�N���V�X�e����S�Ĕj��
        boost::optional<ParticleSystemWeakPtr> GetParticleSystem(const std::string& rId);                           // �p�[�e�B�N���V�X�e�����擾
    private:
        std::deque<std::pair<std::string, ParticleSystemPtr>> pParticleSystems_;                                    ///< @brief �p�[�e�B�N���V�X�e��
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_ParticleSystemManager::C_ParticleSystemManagerImpl::C_ParticleSystemManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_ParticleSystemManager::C_ParticleSystemManagerImpl::~C_ParticleSystemManagerImpl()
    {
        if (pParticleSystems_.empty() == false) AllDestroy();
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystemManager::C_ParticleSystemManagerImpl::Update()
    {
        for (auto& rParticleSystem : pParticleSystems_)
        {
            if (rParticleSystem.second->GetEnableFlag() == true) rParticleSystem.second->Update();
        }
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystemManager::C_ParticleSystemManagerImpl::Draw()
    {
        for (auto &rParticleSystem : pParticleSystems_)
        {
            if (rParticleSystem.second->GetEnableFlag() == true) rParticleSystem.second->Draw();
        }
    }


    /*************************************************************//**
     *
     *  @brief  �p�[�e�B�N���V�X�e���̍쐬����
     *  @param  ID
     *  @param  �J����
     *  @parama �e�N�X�`���n���h��
     *  @param  �p�[�e�B�N���̍ő吔
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_ParticleSystemManager::C_ParticleSystemManagerImpl::Create(const std::string& rId,
                                                                      const Camera::CameraPtr& prCamera,
                                                                      Texture::TextureHandle textureHandle,
                                                                      uint32_t maxParticleCount)
    {
        // ���ɍ쐬���Ă���ꍇ
        auto iterator = std::find_if(pParticleSystems_.begin(),
                                     pParticleSystems_.end(),
                                     [&](const std::pair<std::string, ParticleSystemPtr>& rpPatricleSystem){ return rpPatricleSystem.first == rId; });


        if (iterator != pParticleSystems_.end())
        {
            std::cout << "[ C_ParticleSystemManagerImpl::Create ] : ���ɓ������p�[�e�B�N���V�X�e�����쐬���Ă��܂��B" << std::endl;
            std::cout << "                               ID : " << rId << std::endl;

            return true;
        }

        // �p�[�e�B�N���V�X�e���𐶐����A������
        auto pParticleSystem = std::make_shared<C_ParticleSystem>();

        if (pParticleSystem->Initialize(prCamera, textureHandle, maxParticleCount) == false)
        {
            PrintLog("[ C_ParticleSystemManagerImpl::Initialize ] : �p�[�e�B�N���V�X�e���̏����������Ɏ��s���܂����B");

            return false;
        }

        // �p�[�e�B�N���V�X�e����ێ�����
        pParticleSystems_.emplace_back(rId, pParticleSystem);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �p�[�e�B�N���V�X�e����j������
     *  @parama ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystemManager::C_ParticleSystemManagerImpl::Destroy(const std::string& rId)
    {
        // �p�[�e�B�N���V�X�e�����쐬����Ă��Ȃ��ꍇ
        auto iterator = std::find_if(pParticleSystems_.begin(),
                                     pParticleSystems_.end(),
                                     [&](const std::pair<std::string, ParticleSystemPtr>& rpPatricleSystem){ return rpPatricleSystem.first == rId; });


        if (iterator == pParticleSystems_.end())
        {
            std::cout << "[ C_ParticleSystemManagerImpl::Destroy ] : �p�[�e�B�N���V�X�e�����쐬����Ă��܂���B" << std::endl;

            return;
        }

        (*iterator).second->Finalize();
        pParticleSystems_.erase(iterator);
    }


    /*************************************************************//**
     *
     *  @brief  �p�[�e�B�N���V�X�e����S�Ĕj������
     *  @parama �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystemManager::C_ParticleSystemManagerImpl::AllDestroy()
    {
        for (auto& rParticleSystem : pParticleSystems_) rParticleSystem.second->Finalize();
        pParticleSystems_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �p�[�e�B�N���V�X�e�����擾����
     *  @parama ID
     *  @return �쐬����Ă���ꍇ  �F�p�[�e�B�N���V�X�e��
     *  @return �쐬����Ă��Ȃ��ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<ParticleSystemWeakPtr> C_ParticleSystemManager::C_ParticleSystemManagerImpl::GetParticleSystem(const std::string& rId)
    {
        auto iterator = std::find_if(pParticleSystems_.begin(),
                                     pParticleSystems_.end(),
                                     [&](const std::pair<std::string, ParticleSystemPtr>& rpPatricleSystem){ return rpPatricleSystem.first == rId; });
        
        if (iterator == pParticleSystems_.end()) return boost::none;
        return (*iterator).second;
    }
}