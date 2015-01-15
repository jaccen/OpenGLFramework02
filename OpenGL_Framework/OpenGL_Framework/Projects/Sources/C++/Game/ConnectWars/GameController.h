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
    //! @brief �Q�[���R���g���[���[
    //! @brief �Q�[���𐧌䂷�邽�߂̃N���X
    //!
    //-------------------------------------------------------------
    class C_GameController : public GameObject::C_GameObject
    {
    public:
        C_GameController(const std::string& rId, int32_t type);                 // �R���X�g���N�^
        virtual ~C_GameController() override;                                   // �f�X�g���N�^
        bool Update() override;                                                 // �X�V����
        void Draw() override;                                                   // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override;                // ���b�Z�[�W����
        void EnableWait(bool validFlag = true);                                 // �ҋ@��L����
        int32_t GetNowFrame() const;                                            // ���݂̃t���[�������擾
    protected:
        Timer::C_FrameCounter frameCounter_;                                    ///< @brief �t���[���J�E���^�[
        bool waitFlag_ = false;                                                 ///< @brief �ҋ@�t���O
    };
}
