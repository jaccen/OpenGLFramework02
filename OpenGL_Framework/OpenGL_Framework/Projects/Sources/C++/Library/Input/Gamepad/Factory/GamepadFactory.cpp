/* �w�b�_�t�@�C�� */
#include "GamepadFactory.h"
#include "../Gamepad/XInput/XInput.h"
#include "../../../Debug/Helper/DebugHelper.h"


//-------------------------------------------------------------
//!
//! @brief �C���v�b�g
//! @brief ���͊֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Input
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_GamepadFactory::C_GamepadFactory()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_GamepadFactory::~C_GamepadFactory()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �e�Q�[���p�b�h�𐶐�����
     *  @param  ���O
     *  @param  �Q�[���p�b�h�̏��
     *  @param  �e�Q�[���p�b�h
     *
     ****************************************************************/
    C_Gamepad* C_GamepadFactory::Create(const std::string& rName, GamepadData* pGamepadData)
    {
        // XInput�𐶐�
        if (rName == C_XInput::s_pNAME)
        {
            return newEx C_XInput(pGamepadData);
        }

        return nullptr;
    }
}