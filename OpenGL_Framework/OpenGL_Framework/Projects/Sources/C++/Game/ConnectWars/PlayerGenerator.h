/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectWarsDefine.h"
#include "BasePlayer.h"
#include "../../Library/Singleton/Assert/AssertSingleton.h"
#include <deque>


/* �O���錾 */
namespace Task
{
    class C_GeneralTaskSystem;
}


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* �ʖ� */
    using PlayerPtr = std::shared_ptr<C_BasePlayer>;                            // PlayerPtr�^


    //-------------------------------------------------------------
    //!
    //! @brief �v���C���[�W�F�l���[�^�[
    //! @brief �v���C���[�̐������s���N���X
    //!
    //-------------------------------------------------------------
    class C_PlayerGenerator : public Singleton::C_AssertSingleton<C_PlayerGenerator>
    {
    public:
        C_PlayerGenerator();                                                    // �R���X�g���N�^
        ~C_PlayerGenerator() override;                                          // �f�X�g���N�^
        PlayerPtr Create(const std::string& rId);                               // ��������
        void SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem);             // �^�X�N�V�X�e����ݒ�
    private:
        Task::C_GeneralTaskSystem* pTaskSystem_ = nullptr;                      ///< @brief �^�X�N�V�X�e��
    };
}