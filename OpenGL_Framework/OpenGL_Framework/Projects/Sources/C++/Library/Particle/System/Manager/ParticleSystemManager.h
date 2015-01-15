/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../../Singleton/Assert/AssertSingleton.h"
#include "../../../Texture/TextureDefine.h"
#include "../ParticleSystem.h"


//-------------------------------------------------------------
//!
//! @brief �p�[�e�B�N��
//! @brief �p�[�e�B�N���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Particle
{
    //-------------------------------------------------------------
    //!
    //! @brief �p�[�e�B�N���V�X�e���}�l�[�W���[
    //! @brief �p�[�e�B�N���V�X�e�����Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_ParticleSystemManager : public Singleton::C_AssertSingleton<C_ParticleSystemManager>
    {
    public:
        C_ParticleSystemManager();                                                                              // �R���X�g���N�^
        ~C_ParticleSystemManager() override;                                                                    // �f�X�g���N�^
        void Update();                                                                                          // �X�V����
        void Draw();                                                                                            // �`�揈��
        bool Create(const std::string& rId,                                                                     // �p�[�e�B�N�X�V�X�e�����쐬
                    const Camera::CameraPtr& prCamera,
                    Texture::TextureHandle textureHandle,
                    uint32_t maxParticleCount = 10000);
        void Destroy(const std::string& rId);                                                                   // �p�[�e�B�N���V�X�e����j��
        void AllDestroy();                                                                                      // �p�[�e�B�N���V�X�e����S�Ĕj��
        boost::optional<ParticleSystemWeakPtr> GetParticleSystem(const std::string& rId);                       // �p�[�e�B�N���V�X�e�����擾
    private:
        /* �O���錾 */
        class C_ParticleSystemManagerImpl;

        std::unique_ptr<C_ParticleSystemManagerImpl> upImpl_;                                                   ///< @brief �������
    };
}
