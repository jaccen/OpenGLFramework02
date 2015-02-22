/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectWarsDefine.h"
#include "Fade.h"
#include "../../Library/GameObject/GameObject.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"
#include "../../Library/Scene/Manager/SceneManager.h"


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
    //! @brief �V�[���R���g���[���[
    //! @brief �V�[���𐧌䂷�邽�߂̃N���X
    //!
    //-------------------------------------------------------------
    class C_SceneController : public GameObject::C_GameObject
    {
    public:
        C_SceneController(const std::string& rId, int32_t type);                // �R���X�g���N�^
        virtual ~C_SceneController() override;                                  // �f�X�g���N�^
        bool Update() override;                                                 // �X�V����
        void Draw() override;                                                   // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override;                // ���b�Z�[�W����
        void EnableWait(bool validFlag = true);                                 // �ҋ@��L����
        int32_t GetNowFrame() const;                                            // ���݂̃t���[�������擾
        void SetSceneChanger(Scene::IC_SceneChanger* pSceneChanger);            // �V�[���`�F���W���[��ݒ�
    protected:
        Timer::C_FrameCounter frameCounter_;                                    ///< @brief �t���[���J�E���^�[
        bool waitFlag_ = false;                                                 ///< @brief �ҋ@�t���O
        Scene::IC_SceneChanger* pSceneChanger_ = nullptr;                       ///< @brief �V�[���`�F���W���[
        std::unique_ptr<C_Fade> upFade_;                                        ///< @brief �t�F�[�h

        virtual void DoUpdate() = 0;                                            // ����J�̍X�V����
        virtual void DoDraw() = 0;                                              // ����J�̕`�揈��
        virtual bool DoMessageProcess(const Telegram& rTelegram) = 0;           // ����J�̃��b�Z�[�W����
    };
}
