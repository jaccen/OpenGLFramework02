/* �w�b�_�t�@�C�� */
#include "PlayerGenerator.h"
#include "NormalPlayer.h"
#include "../../Library/GameObject/Manager/GameObjectManager.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"
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
    C_PlayerGenerator::C_PlayerGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PlayerGenerator::~C_PlayerGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �����������s��
     *  @param  ��Q����ID
     *  @param  ���W
     *  @return �v���C���[
     *
     ****************************************************************/
    PlayerPtr C_PlayerGenerator::Create(const std::string& rId)
    {
        // �e�v���C���[�𐶐�
        PlayerPtr pPlayer;

        if (rId == ID::Generator::Player::s_pNORMAL)
        {
            pPlayer = std::make_shared<C_NormalPlayer>(ID::GameObject::s_pPLAYER, TYPE_PLAYER);
        }
        else
        {
            StrongAssert(false);
        }

        // �^�X�N�V�X�e���ɓo�^
        pTaskSystem_->Entry(pPlayer, Priority::Task::Update::s_player, Priority::Task::Draw::s_player);

        // �Q�[���I�u�W�F�N�g�}�l�[�W���[�ɓo�^
        GameObject::C_GameObjectManager::s_GetInstance()->Entry(pPlayer);

        return pPlayer;
    }


    /*************************************************************//**
     *
     *  @brief  �^�X�N�V�X�e����ݒ肷��
     *  @param  �^�X�N�V�X�e��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }
}