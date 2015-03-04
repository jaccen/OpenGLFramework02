/* �w�b�_�t�@�C�� */
#include "PlayerAdventMoveLogic.h"
#include "../../Library/Math/Define/MathDefine.h"
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
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PlayerAdventMoveLogic::C_PlayerAdventMoveLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PlayerAdventMoveLogic::~C_PlayerAdventMoveLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �ړ��ʂ�ݒ肷��
     *  @param  �ړ���
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerAdventMoveLogic::SetMovement(float movement)
    {
        movement_ = movement;
    }


    /*************************************************************//**
     *
     *  @brief  �f�B�[�v�R�s�[���s��
     *  @param  �Ȃ�
     *  @return ���g�̃R�s�[
     *
     ****************************************************************/
    C_RigidBodyMoveLogic* C_PlayerAdventMoveLogic::DeepCopy()
    {
        return newEx C_PlayerAdventMoveLogic();
    }


    /*************************************************************//**
     *
     *  @brief  �ړ��I�����m�F����
     *  @param  �Ȃ�
     *  @return �ړ��I���̏ꍇ    �Ftrue
     *  @return �ړ��I���łȂ��ꍇ�Ffalse
     *
     ****************************************************************/
    bool C_PlayerAdventMoveLogic::IsMoveFinish() const
    {
        return (finishCount == frameCounter_.GetCount()) ? true : false;
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̏������s��
     *  @param  ����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerAdventMoveLogic::DoProcess(RigidBody* pRigidBody)
    {
        if (finishCount == frameCounter_.GetCount()) return;
        
        // ��������W�ƈړ���
        Physics::Vector3 addPosition = Physics::Vector3(0.0f, 0.0f, 0.0f);

        if (frameCounter_.GetCount() < 10)
        {
            addPosition = Physics::Vector3(0.05f, 0.8f, 1.5f);
        }
        else if (frameCounter_.GetCount() < 20)
        {
            addPosition = Physics::Vector3(0.05f, 0.7f, 0.8f);
        }
        else if (frameCounter_.GetCount() < 30)
        {
            addPosition = Physics::Vector3(0.05f, 0.5f, 0.7f);
        }
        else
        {
            addPosition = Physics::Vector3(0.05f, 0.4f, 0.5f);
        }

        // ���W��������
        pRigidBody->AddPosition(addPosition);
    
        frameCounter_.CountUp();
    }
}