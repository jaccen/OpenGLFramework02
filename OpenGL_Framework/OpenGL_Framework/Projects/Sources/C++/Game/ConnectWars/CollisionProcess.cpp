/* �w�b�_�t�@�C�� */
#include "CollisionProcess.h"
#include "BasePlayer.h"
#include "BaseOption.h"
#include "../../Library/Debug/Helper/DebugHelper.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
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
        StrongAssert(false && "[ C_CollisionProcess::s_PlayerAndPlayer ] �Q�[�����Ńv���C���[��2�̈ȏ�ɂȂ邱�Ƃ͂��肦�܂���B\n");
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
}