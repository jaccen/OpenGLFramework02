/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "CollisionObject.h"
#include "BasePower.h"
#include "../../Library/State/Machine/StateMachine.h"
#include "../../Library/Physics/Body/Rigid/Rigidbody.h"


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


    //-------------------------------------------------------------
    //!
    //! @brief �x�[�X�{��
    //! @brief �{���̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BaseBomb : public C_CollisionObject
    {
    public:
        C_BaseBomb(const std::string& rId, int32_t type);                                           // �R���X�g���N�^
        ~C_BaseBomb() override;                                                                     // �f�X�g���N�^
        bool Update() override final;                                                               // �X�V����
        void Draw() override final;                                                                 // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override final;                              // ���b�Z�[�W����
        virtual void DispatchCollision(C_CollisionObject* pCollisionObject) override final;         // �Փˌ��m�𔭑�
        virtual void CollisionProcess(C_BasePlayer* pPlayer) override;                              // �v���C���[�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseOption* pOption) override;                              // �I�v�V�����Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) override;                                // �G�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBullet* pBullet) override;                              // �e�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) override;                          // ��Q���Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBomb* pBomb) override;                                  // �{���Ƃ̏Փˎ�����
    protected:
        std::unique_ptr<State::C_StateMachine<C_BaseBomb>> upStateMachine_;                         ///< @brief �X�e�[�g�}�V�[��
        std::unique_ptr<Physics::C_RigidBody> upRigidBody_;                                         ///< @brief ����
        int32_t level_ = 0;                                                                         ///< @brief ���x��

        virtual void DoUpdate() = 0;                                                                // ����J�̍X�V����
        virtual void DoDraw();                                                                      // ����J�̕`�揈��
        virtual bool DoMessageProcess(const Telegram& rTelegram);                                   // ����J�̃��b�Z�[�W����
    };
}