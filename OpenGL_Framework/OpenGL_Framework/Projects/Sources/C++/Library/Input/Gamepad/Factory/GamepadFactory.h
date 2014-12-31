/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Gamepad/Gamepad.h"


//-------------------------------------------------------------
//!
//! @brief �C���v�b�g
//! @brief ���͊֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Input
{
    //-------------------------------------------------------------
    //!
    //! @brief �Q�[���p�b�h�t�@�N�g��( �C���^�[�t�F�[�X )
    //! @brief �Q�[���p�b�h�t�@�N�g���̃C���^�[�t�F�[�X
    //!
    //-------------------------------------------------------------
    class IC_GamepadFactory
    {
    public:
        IC_GamepadFactory(){};                                                  //!< @brief �R���X�g���N�^
        virtual ~IC_GamepadFactory(){};                                         //!< @brief �f�X�g���N�^
        virtual C_Gamepad* Create(const std::string& rName,                     //!< @brief ��������
                                  GamepadData* pGamepadData) = 0;
    };


    //-------------------------------------------------------------
    //!
    //! @brief �Q�[���p�b�h�t�@�N�g��
    //! @brief �e�Q�[���p�b�h�𐶐�����N���X
    //!
    //-------------------------------------------------------------
    class C_GamepadFactory : public IC_GamepadFactory
    {
    public:
        C_GamepadFactory();                                                     // �R���X�g���N�^
        virtual ~C_GamepadFactory() override;                                   // �f�X�g���N�^
        virtual C_Gamepad* Create(const std::string& rName,                     // ��������
                                  GamepadData* pGamepadData) override;
    };
}