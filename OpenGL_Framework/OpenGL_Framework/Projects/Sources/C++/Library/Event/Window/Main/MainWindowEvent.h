/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../BaseWindowEvent.h"


//-------------------------------------------------------------
//!
//! @brief �C�x���g
//! @brief �C�x���g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Event
{
    //-------------------------------------------------------------
    //!
    //! @brief ���C���E�B���h�E�C�x���g
    //! @brief ���C���E�B���h�E�̃C�x���g�̏������܂Ƃ߂��N���X
    //!
    //-------------------------------------------------------------
    class C_MainWindowEvent : public C_BaseWindowEvent
    {
    public:
        C_MainWindowEvent(uint32_t windowId);               // �R���X�g���N�^
        ~C_MainWindowEvent() override;                      // �f�X�g���N�^
        bool Process(EventData& rEvent) override;           // �C�x���g�̏���
    };
}