/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "CollisionObject.h"
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "../../Library/Material/Manager/MaterialManager.h"
#include "../../Library/Light/Manager/LightManager.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* �O���錾 */
    class C_BaseOption;
    class C_BaseEnemy;
    class C_BaseBullet;
    class C_BaseObstacle;
    class C_BaseBomb;


    //-------------------------------------------------------------
    //!
    //! @brief �V���[�^�[
    //! @brief �e�����I�u�W�F�N�g
    //!
    //-------------------------------------------------------------
    class C_Shooter : public C_CollisionObject
    {
    public:
        C_Shooter(const std::string& rId, int32_t type);                                        // �R���X�g���N�^
        virtual~C_Shooter() override;                                                           // �f�X�g���N�^
        virtual bool Update() override = 0;                                                     // �X�V����
        virtual void Draw() override = 0;                                                       // �`�揈��
        virtual bool MessageProcess(const Telegram& rTelegram) override = 0;                    // ���b�Z�[�W����
        virtual void DispatchCollision(C_CollisionObject* pCollisionObject) override = 0;       // �Փ˂𔭑�
        virtual void Move() = 0;                                                                // �ړ�����
        virtual void Shot() = 0;                                                                // �ˌ�����
        virtual void CollisionProcess(C_BasePlayer* pPlayer) = 0;                               // �v���C���[�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseOption* pOption) = 0;                               // �I�v�V�����Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) = 0;                                 // �G�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBullet* pBullet) = 0;                               // �e�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) = 0;                           // ��Q���Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBomb* pBomb) = 0;                                   // �{���Ƃ̏Փˎ�����
        virtual void MoveLimitCheck() override = 0;                                             // �ړ��������m�F
        virtual const Physics::Vector3& GetPosition() const override = 0;                       // ���W���擾  
        virtual void SetPosition(const Physics::Vector3& rPosition) override = 0;               // ���W��ݒ�
        virtual const Physics::Matrix3x3& GetRotation() const = 0;                              // ��]�ʂ��擾
        virtual void SetMaterial(const Material::MaterialPtr& prMaterial) = 0;                  // �}�e���A����ݒ�
        virtual void SetLight(const Light::LightPtr& prLight) = 0;                              // ���C�g��ݒ�
    protected:
        OpenGL::PrimitiveBufferPtr pModelData_;                                                 ///< @brief ���f�����
        Texture::TextureDataPtr pModelTextureData_;                                             ///< @brief ���f���̃e�N�X�`�����
        Material::MaterialPtr pBasicMaterial_;                                                  ///< @brief ��{�̃}�e���A��
        Material::MaterialPtr pDamageMaterial_;                                                 ///< @brief �_���[�W�}�e���A��
        Material::MaterialPtr pNowMaterial_;                                                    ///< @brief ���݂̃}�e���A��
        Light::LightPtr pMainLight_;                                                            ///< @brief ���C�����C�g
    };
}