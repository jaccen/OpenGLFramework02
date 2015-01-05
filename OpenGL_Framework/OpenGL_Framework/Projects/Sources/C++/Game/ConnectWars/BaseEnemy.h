/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "Shooter.h"


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
    class C_BaseBullet;
    class C_BaseObstacle;
    class C_BaseBomb;


    //-------------------------------------------------------------
    //!
    //! @brief �x�[�X�G�l�~�[
    //! @brief �G�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BaseEnemy : public C_Shooter
    {
    public:
        C_BaseEnemy(const std::string& rId, int32_t type);                                  // �R���X�g���N�^
        virtual ~C_BaseEnemy() override;                                                    // �f�X�g���N�^
        bool Update() override final;                                                       // �X�V����
        void Draw() override final;                                                         // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override final;                      // ���b�Z�[�W����
        void DispatchCollision(C_CollisionObject* pCollisionObject) override final;         // �Փˌ��m�𔭑�
        virtual void CollisionProcess(C_BasePlayer* pPlayer) override;                      // �v���C���[�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseOption* pOption) override;                      // �I�v�V�����Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) override;                        // �G�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBullet* pBullet) override;                      // �e�Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) override;                  // ��Q���Ƃ̏Փˎ�����
        virtual void CollisionProcess(C_BaseBomb* pBomb) override;                          // �{���Ƃ̏Փˎ�����
        virtual void Move();                                                                // �ړ�����
        virtual void Shot();                                                                // �ˌ�����
    protected:
        virtual void DoUpdate() = 0;                                                        // ����J�̍X�V����
        virtual void DoDraw() = 0;                                                          // ����J�̕`�揈��
        virtual bool DoMessageProcess(const Telegram& rTelegram) = 0;                       // ����J�̃��b�Z�[�W����
    };
}