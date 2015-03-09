/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "Shooter.h"
#include "RigidBodyMoveLogic.h"
#include "../../Library/Physics/Body/Rigid/Rigidbody.h"
#include "../../Library/Physics/CollisionShape/Convex/Sphere/SphereShape.h"


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
    class C_BaseShield;


    //-------------------------------------------------------------
    //!
    //! @brief �R�l�N�g�}�V�[��
    //! @brief �A���@�B��\���N���X
    //!
    //-------------------------------------------------------------
    class C_ConnectMachine : public C_Shooter
    {
    public:
        /* �萔 */
        static const int32_t s_MAX_MOVE_SPEED_LEVEL = 4;                                        ///< @brief �ړ��X�s�[�h�̍ő僌�x�� 
        
        C_ConnectMachine(const std::string& rId, int32_t type);                                 // �R���X�g���N�^
        virtual ~C_ConnectMachine() override;                                                   // �f�X�g���N�^
        virtual bool Update() override = 0;                                                     // �X�V����
        virtual void Draw() override = 0;                                                       // �`�揈��
        virtual bool MessageProcess(const Telegram& rTelegram) override = 0;                    // ���b�Z�[�W����
        virtual void DispatchCollision(C_CollisionObject* pCollisionObject) override = 0;       // �Փ˂𔭑�
        virtual void CollisionProcess(C_BasePlayer* pPlayer) = 0;                               // �v���C���[�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseOption* pOption) = 0;                               // �I�v�V�����Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) = 0;                                 // �G�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBullet* pBullet) = 0;                               // �e�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) = 0;                           // ��Q���Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBomb* pBomb) = 0;                                   // �{���Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseShield* pShield) = 0;                               // �V�[���h�Ƃ̏Փˎ�����
        virtual void Move() override = 0;                                                       // �ړ�����
        virtual void Shot() override = 0;                                                       // �ˌ�����
        virtual void AddConnectOption(C_BaseOption* pOption) = 0;                               // �A�����Ă���I�v�V������ǉ�
        virtual void ResetConnect() = 0;                                                        // �A�������Z�b�g
        virtual void NewConnect() = 0;                                                          // �V�K�A��
        std::vector<C_BaseOption*>* GetConnectOptionList();                                     // �A�����Ă���I�v�V�����̃��X�g���擾
        Physics::C_RigidBody* GetRigidBody() const;                                             // ���̂��擾
        float GetRadius() const;                                                                // ���a���擾
        virtual const Physics::Vector3& GetPosition() const override;                           // ���W���擾
        virtual void SetPosition(const Physics::Vector3& rPosition) override;                   // ���W��ݒ�
        virtual const Physics::Matrix3x3& GetRotation() const override;                         // ��]�ʂ��擾
        void SetMaterial(const Material::MaterialPtr& prMaterial) override;                     // �}�e���A����ݒ�
        void SetLight(const Light::LightPtr& prLight) override;                                 // ���C�g��ݒ�
        bool IsEnableConnectFlag() const;                                                       // �A���\�t���O���擾
        void SetEnableConnectFlag(bool enableConnectFlag);                                      // �A���\�t���O��ݒ�

        static void s_SetOwnCrashDerayFrameInterval(uint32_t ownCrashDerayFrameInterval);       // �����x���t���[�����̊Ԋu��ݒ�
    protected:
        std::vector<C_BaseOption*> pConnectOptionList_;                                         ///< @brief �A�����Ă���I�v�V�����̃��X�g
        float radius_ = 0.0f;                                                                   ///< @brief ���a
        std::unique_ptr<Physics::C_RigidBody> upRigidBody_;                                     ///< @brief ����
        std::unique_ptr<C_RigidBodyMoveLogic> upMoveLogic_;                                     ///< @brief �ړ����W�b�N
        bool enableConnectFlag_ = true;                                                         ///< @brief �A���\�t���O

        static uint32_t s_ownCrashDerayFrameInterval;                                           ///< @brief �����x���t���[�����̊Ԋu
    };
}