/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "CollisionObject.h"
#include "RigidBodyMoveLogic.h"
#include "../../Library/State/Machine/StateMachine.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* �O���錾 */
    class C_BasePlayer;
    class C_BaseOption;
    class C_BaseEnemy;
    class C_BaseBullet;
    class C_BaseObstacle;
    class C_BaseBomb;
    class C_BaseGun;


    //-------------------------------------------------------------
    //!
    //! @brief �x�[�X�V�[���h
    //! @brief �V�[���h�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BaseShield : public C_CollisionObject
    {
    public:
        C_BaseShield(const std::string& rId,                                                            // �R���X�g���N�^
                     int32_t type,  
                     int32_t shooterType,
                     C_CollisionObject* pTarget);                                             
        virtual ~C_BaseShield() override = 0;                                                           // �f�X�g���N�^
        bool Update() override final;                                                                   // �X�V����
        void Draw() override final;                                                                     // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override final;                                  // ���b�Z�[�W����
        void DispatchCollision(C_CollisionObject* pCollisionObject) override final;                     // �Փ˂𔭑�
        virtual void CollisionProcess(C_BasePlayer* pPlayer) override;                                  // �v���C���[�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseOption* pOption) override;                                  // �I�v�V�����Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) override;                                    // �G�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBullet* pBullet) override;                                  // �e�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) override;                              // ��Q���Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBomb* pBomb) override;                                      // �{���Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseShield* pShield) override;                                  // �V�[���h�Ƃ̏Փˎ�����
        virtual void Move();                                                                            // �ړ�����
        virtual void MoveLimitCheck() {};                                                               // �ړ��������m�F
        const Physics::Vector3& GetPosition() const override;                                           // ���W���擾
        void SetPosition(const Physics::Vector3& rPosition) override;                                   // ���W��ݒ�
    protected:
        std::unique_ptr<Physics::C_RigidBody> upRigidBody_;                                             ///< @brief ����
        std::unique_ptr<C_RigidBodyMoveLogic> upMoveLogic_;                                             ///< @brief �ړ��̃��W�b�N
        int32_t shooterType_ = 0;                                                                       ///< @brief �ˌ��҂̎��

        virtual void DoUpdate();                                                                        // ����J�̍X�V����
        virtual void DoDraw() = 0;                                                                      // ����J�̕`�揈��
        virtual bool DoMessageProcess(const Telegram& rTelegram);                                       // ����J�̃��b�Z�[�W����
    };
}