/* �w�b�_�t�@�C�� */
#include "CollisionProcess.h"
#include "ConnectWarsDefine.h"
#include "BasePlayer.h"
#include "BaseOption.h"
#include "BaseEnemy.h"
#include "BaseBullet.h"
#include "BaseObstacle.h"
#include "BaseBomb.h"
#include "../../Library/Debug/Helper/DebugHelper.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* �v���g�^�C�v�錾 */
    static void s_DamageToTarget(C_CollisionObject* pAttacker, C_CollisionObject* pTarget);


    /*************************************************************//**
     *
     *  @brief  �v���C���[���m�̏Փˎ��������s��
     *  @param  �v���C���[
     *  @param  ������̃v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_PlayerAndPlayer(C_BasePlayer* pPlayer, C_BasePlayer* pAnotherPlayer)
    {
        StrongAssert(false && "[ C_CollisionProcess::s_PlayerAndPlayer ] �v���C���[��2�̈ȏ�ɂȂ邱�Ƃ͂��肦�܂���B\n");
    }


    /*************************************************************//**
     *
     *  @brief  �v���C���[�ƃI�v�V�����̏Փˎ��������s��
     *  @param  �v���C���[
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_PlayerAndOption(C_BasePlayer* pPlayer, C_BaseOption* pOption)
    {
        if (pOption->IsOnceConnectFlag() == false)
        {
            // ��x�A�����������f����t���O��ݒ�
            pOption->SetOnceConnectFlag(true);

            // �v���C���[����̃I�t�Z�b�g�����߂�
            auto playerPosition = pPlayer->GetRigidBody()->GetTransform().getOrigin();
            auto optionTransform = pOption->GetRigidBody()->GetTransform();

            Physics::Vector3 offsetFromPlayer = optionTransform.getOrigin() - playerPosition;
            offsetFromPlayer = offsetFromPlayer.normalize();

            offsetFromPlayer = offsetFromPlayer * pPlayer->GetRadius()
                             + offsetFromPlayer * pOption->GetRadius();
            offsetFromPlayer *= Connect::s_OffsetFactor;
            pOption->SetOffsetFromPlayer(offsetFromPlayer);

            // �I�v�V�����̍��W��ݒ�
            optionTransform.setOrigin(playerPosition + offsetFromPlayer);
            pOption->GetRigidBody()->SetTransform(optionTransform);

            // �V�K�A������
            pPlayer->NewConnect();
            pOption->NewConnect();

            // �A���̌��ʂ�����
            pOption->ConnectEffect();

            // �I�v�V��������1����
            pPlayer->AddOptionCount(1);
        }
    }


    /*************************************************************//**
     *
     *  @brief  �v���C���[�ƓG�̏Փˎ��������s��
     *  @param  �v���C���[
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_PlayerAndEnemy(C_BasePlayer* pPlayer, C_BaseEnemy* pEnemy)
    {
        s_DamageToTarget(pPlayer, pEnemy);
        s_DamageToTarget(pEnemy, pPlayer);
    }


    /*************************************************************//**
     *
     *  @brief  �v���C���[�ƒe�̏Փˎ��������s��
     *  @param  �v���C���[
     *  @param  �e
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_PlayerAndBullet(C_BasePlayer* pPlayer, C_BaseBullet* pBullet)
    {
        assert(pBullet->GetShooterType() == TYPE_ENEMY);
        
        s_DamageToTarget(pPlayer, pBullet);
        s_DamageToTarget(pBullet, pPlayer);
    }


    /*************************************************************//**
     *
     *  @brief  �v���C���[�Ə�Q���̏Փˎ��������s��
     *  @param  �v���C���[
     *  @param  ��Q��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_PlayerAndObstacle(C_BasePlayer* pPlayer, C_BaseObstacle* pObstacle)
    {
        s_DamageToTarget(pPlayer, pObstacle);
        s_DamageToTarget(pObstacle, pPlayer);
    }


    /*************************************************************//**
     *
     *  @brief  �v���C���[�ƃ{���̏Փˎ��������s��
     *  @param  �v���C���[
     *  @param  �{��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_PlayerAndBomb(C_BasePlayer* pPlayer, C_BaseBomb* pBomb)
    {
        StrongAssert(false && "[ C_CollisionProcess::s_PlayerAndBomb ] �v���C���[�ƃ{�����Փ˂��邱�Ƃ͂��肦�܂���B\n");
    }


    /*************************************************************//**
     *
     *  @brief  �I�v�V�������m�̏Փˎ��������s��
     *  @param  �I�v�V����
     *  @param  ������̃I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_OptionAndOption(C_BaseOption* pOption, C_BaseOption* pAnotherOption)
    {
        // �ǂ������x���A�����Ă��Ȃ��ꍇ�͉������Ȃ�
        if (pOption->IsOnceConnectFlag() == false && pAnotherOption->IsOnceConnectFlag() == false) return;

        // �e�I�v�V������ǉ�
        pOption->AddConnectOption(pAnotherOption);
        pAnotherOption->AddConnectOption(pOption);
    }


    /*************************************************************//**
     *
     *  @brief  �I�v�V�����ƓG�̏Փˎ��������s��
     *  @param  �I�v�V����
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_OptionAndEnemy(C_BaseOption* pOption, C_BaseEnemy* pEnemy)
    {
        s_DamageToTarget(pOption, pEnemy);
        s_DamageToTarget(pEnemy, pOption);
    }


    /*************************************************************//**
     *
     *  @brief  �I�v�V�����ƒe�̏Փˎ��������s��
     *  @param  �I�v�V����
     *  @param  �e
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_OptionAndBullet(C_BaseOption* pOption, C_BaseBullet* pBullet)
    {
        assert(pBullet->GetShooterType() == TYPE_ENEMY);

        s_DamageToTarget(pOption, pBullet);
        s_DamageToTarget(pBullet, pOption);
    }


    /*************************************************************//**
     *
     *  @brief  �I�v�V�����Ə�Q���̏Փˎ��������s��
     *  @param  �I�v�V����
     *  @param  ��Q��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_OptionAndObstacle(C_BaseOption* pOption, C_BaseObstacle* pObstacle)
    {
        s_DamageToTarget(pOption, pObstacle);
        s_DamageToTarget(pObstacle, pOption);
    }


    /*************************************************************//**
     *
     *  @brief  �I�v�V�����ƃ{���̏Փˎ��������s��
     *  @param  �I�v�V����
     *  @param  �{��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_OptionAndBomb(C_BaseOption* pOption, C_BaseBomb* pBomb)
    {
        StrongAssert(false && "[ C_CollisionProcess::s_OptionAndBomb ] �I�v�V�����ƃ{�����Փ˂��邱�Ƃ͂��肦�܂���B\n");
    }


    /*************************************************************//**
     *
     *  @brief  �G���m�̏Փˎ��������s��
     *  @param  �G
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_EnemyAndEnemy(C_BaseEnemy* pEnemy, C_BaseEnemy* pAnotherEnemy)
    {
        StrongAssert(false && "[ C_CollisionProcess::s_EnemyAndEnemy ] �G���m���Փ˂��邱�Ƃ͂��肦�܂���B\n");
    }


    /*************************************************************//**
     *
     *  @brief  �G�ƒe�̏Փˎ��������s��
     *  @param  �G
     *  @param  �e
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_EnemyAndBullet(C_BaseEnemy* pEnemy, C_BaseBullet* pBullet)
    {
        assert(pBullet->GetShooterType() == TYPE_PLAYER || pBullet->GetShooterType() == TYPE_OPTION);

        s_DamageToTarget(pEnemy, pBullet);
        s_DamageToTarget(pBullet, pEnemy);
    }


    /*************************************************************//**
     *
     *  @brief  �G�Ə�Q���̏Փˎ��������s��
     *  @param  �G
     *  @param  ��Q��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_EnemyAndObstacle(C_BaseEnemy* pEnemy, C_BaseObstacle* pObstacle)
    {
        s_DamageToTarget(pEnemy, pObstacle);
        s_DamageToTarget(pObstacle, pEnemy);
    }


    /*************************************************************//**
     *
     *  @brief  �G�ƃ{���̏Փˎ��������s��
     *  @param  �G
     *  @param  �{��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_EnemyAndBomb(C_BaseEnemy* pEnemy, C_BaseBomb* pBomb)
    {
        // s_DamageToTarget(pEnemy, pBomb);
        s_DamageToTarget(pBomb, pEnemy);
    }


    /*************************************************************//**
     *
     *  @brief  �e���m�̏Փˎ��������s��
     *  @param  �e
     *  @param  ������̒e
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_BulletAndBullet(C_BaseBullet* pBullet, C_BaseBullet* pAnotherBullet)
    {
        StrongAssert(false && "[ C_CollisionProcess::s_BulletAndBullet ] �e���m���Փ˂��邱�Ƃ͂��肦�܂���B\n");
    }


    /*************************************************************//**
     *
     *  @brief  �e�Ə�Q���̏Փˎ��������s��
     *  @param  �e
     *  @param  ��Q��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_BulletAndObstale(C_BaseBullet* pBullet, C_BaseObstacle* pObstacle)
    {
        s_DamageToTarget(pBullet, pObstacle);
        s_DamageToTarget(pObstacle, pBullet);
    }


    /*************************************************************//**
     *
     *  @brief  �e�ƃ{���̏Փˎ��������s��
     *  @param  �e
     *  @param  �{��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_BulletAndBomb(C_BaseBullet* pBullet, C_BaseBomb* pBomb)
    {
        assert(pBullet->GetShooterType() == TYPE_ENEMY);

        // s_DamageToTarget(pBullet, pBomb);
        s_DamageToTarget(pBomb, pBullet);
    }


    /*************************************************************//**
     *
     *  @brief  ��Q�����m�̏Փˎ��������s��
     *  @param  ��Q��
     *  @param  ������̏�Q��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_ObstacleAndObstacle(C_BaseObstacle* pObstacle, C_BaseObstacle* pAnotherObstacle)
    {
        s_DamageToTarget(pObstacle, pAnotherObstacle);
        s_DamageToTarget(pAnotherObstacle, pObstacle);
    }


    /*************************************************************//**
     *
     *  @brief  ��Q���ƃ{���̏Փˎ��������s��
     *  @param  ��Q��
     *  @param  �{��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_ObstacleAndBomb(C_BaseObstacle* pObstacle, C_BaseBomb* pBomb)
    {
        // s_DamageToTarget(pObstacle, pBomb);
        s_DamageToTarget(pBomb, pObstacle);
    }


    /*************************************************************//**
     *
     *  @brief  �{�����m�̏Փˎ��������s��
     *  @param  �{��
     *  @param  ������̃{��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionProcess::s_BombAndBomb(C_BaseBomb* pBomb, C_BaseBomb* pAnotherBomb)
    {
    }


    /*************************************************************//**
     *
     *  @brief  �Ώێ҂փ_���[�W��^����
     *  @param  �U����
     *  @param  �Ώێ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void s_DamageToTarget(C_CollisionObject* pAttacker, C_CollisionObject* pTarget)
    {
        if (pTarget->IsInvincibleFlag() == false)
        {
            pTarget->GetHitPoint()->Subtract(pAttacker->GetPower()->GetValue());
        }
    }
}