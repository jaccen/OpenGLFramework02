/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectWarsDefine.h"
#include "../../Library/GameObject/GameObject.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief �J�����R���g���[���[
    //! @brief �J�����𐧌䂷�邽�߂̃N���X
    //!
    //-------------------------------------------------------------
    class C_CameraController : public GameObject::C_GameObject
    {
    public:
        C_CameraController(const std::string& rId, int32_t type);               // �R���X�g���N�^
        virtual ~C_CameraController() override;                                 // �f�X�g���N�^
        bool Update() override;                                                 // �X�V����
        void Draw() override;                                                   // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override;                // ���b�Z�[�W����
    protected:
    };
}
