/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "CollisionObject.h"
/*
#include "MoveLogic.h"
#include "RotateLogic.h"
#include "BaseHitPoint.h"
#include "BaseGun.h"
#include "BasePower.h"
*/


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

        /* �Q�b�^�[ */
        //C_BaseHitPoint* GetHitPoint() const;                                                  // �q�b�g�|�C���g���擾
        //C_BasePower* GetPower() const;                                                        // �U���͂��擾
        //bool IsInvincibleFlag() const;                                                        // ���G�t���O���擾

        /* �Z�b�^�[ */
        //void SetInvincibleFlag(bool invincibleFlag);                                          // ���G�t���O��ݒ�
    protected:
        //std::unique_ptr<C_MoveLogic> upMoveLogic_;                                            ///< @brief �ړ��̃��W�b�N
        //std::unique_ptr<C_RotateLogic> upRotateLogic_;                                        ///< @brief ��]�̃��W�b�N
        //std::unique_ptr<C_BaseHitPoint> upHitPoint_;                                          ///< @brief �q�b�g�|�C���g
        //std::unique_ptr<C_BasePower> upPower_;                                                ///< @brief �U����
        //bool invincibleFlag_ = false;                                                         ///< @brief ���G�t���O
    };
}