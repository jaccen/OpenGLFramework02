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
    class C_Shooter;
    class C_BasePlayer;
    class C_BaseOption;
    class C_BaseEnemy;
    class C_BaseObstacle;
    class C_BaseBomb;


    //-------------------------------------------------------------
    //!
    //! @brief �x�[�X�o���b�g
    //! @brief �o���b�g�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BaseBullet : public C_CollisionObject
    {
    public:
        C_BaseBullet(const std::string& rId, int32_t type);                                 // �R���X�g���N�^
        virtual ~C_BaseBullet() override = 0;                                               // �f�X�g���N�^
        bool Update() override final;                                                       // �X�V����
        void Draw() override final;                                                         // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override final;                      // ���b�Z�[�W����
        void DispatchCollision(C_CollisionObject* pCollisionObject) override;               // �Փˌ��m�𔭑�
        void CollisionProcess(C_BasePlayer* pPlayer) override;                              // �v���C���[�Ƃ̏Փˎ�����
        void CollisionProcess(C_BaseOption* pOption) override;                              // �I�v�V�����Ƃ̏Փˎ�����
        void CollisionProcess(C_BaseEnemy* pEnemy) override;                                // �G�Ƃ̏Փˎ�����
        void CollisionProcess(C_BaseBullet* pBullet) override;                              // �e�Ƃ̏Փˎ�����
        void CollisionProcess(C_BaseObstacle* pObstacle) override;                          // ��Q���Ƃ̏Փˎ�����
        void CollisionProcess(C_BaseBomb* pBomb) override;                                  // ��Q���Ƃ̏Փˎ�����
        virtual void Move();                                                                // �ړ�����
        State::C_StateMachine<C_BaseBullet>* GetStateMachine() const;                       // �X�e�[�g�}�V�[�����擾
    protected:
        std::unique_ptr<Physics::C_CollisionShape> upCollisionShape_;                       ///< @brief �Փˌ`��
        std::unique_ptr<Physics::C_RigidBody> upRigidBody_;                                 ///< @brief ����
        std::unique_ptr<C_RigidBodyMoveLogic> upMoveLogic_;                                 ///< @brief �ړ��̃��W�b�N
        std::unique_ptr<State::C_StateMachine<C_BaseBullet>> upStateMachine_;               ///< @brief �X�e�[�g�}�V�[��

        virtual void DoUpdate();                                                            // ����J�̍X�V����
        virtual void DoDraw();                                                              // ����J�̕`�揈��
        virtual bool DoMessageProcess(const Telegram& rTelegram);                           // ����J�̃��b�Z�[�W����
    };
}