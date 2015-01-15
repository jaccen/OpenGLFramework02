/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../../Singleton/Assert/AssertSingleton.h"
#include "../../../Texture/TextureDefine.h"
#include "../SpriteCreater.h"


//-------------------------------------------------------------
//!
//! @brief �X�v���C�g
//! @brief �X�v���C�g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Sprite
{
    //-------------------------------------------------------------
    //!
    //! @brief �X�v���C�g�N���G�C�^�[�}�l�[�W���[
    //! @brief �X�v���C�g�N���G�C�^�[���Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_SpriteCreaterManager : public Singleton::C_AssertSingleton<C_SpriteCreaterManager>
    {
    public:
        C_SpriteCreaterManager();                                                                                   // �R���X�g���N�^
        ~C_SpriteCreaterManager() override;                                                                         // �f�X�g���N�^
        void Draw();                                                                                                // �`�揈��
        void Sort();                                                                                                // �\�[�g����
        bool Create(const std::string& rId,                                                                         // �X�v���C�g�N���G�C�^�[���쐬
                    const Camera::CameraPtr& prCamera,
                    const Texture::TextureDataPtr pTextureData,
                    uint32_t maxSpriteCount = 100,
                    float priority = 0.0f);
        void Destroy(const std::string& rId);                                                                       // �X�v���C�g�N���G�C�^�[��j��
        void AllDestroy();                                                                                          // �X�v���C�g�N���G�C�^�[��S�Ĕj��
        boost::optional<SpriteCreaterWeakPtr> GetSpriteCreater(const std::string& rId);                             // �X�v���C�g�N���G�C�^�[���擾
    private:
        /* �O���錾 */
        class C_SpriteCreaterManagerImpl;

        std::unique_ptr<C_SpriteCreaterManagerImpl> upImpl_;                                                        ///< @brief �������
    };
}