/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Library/GameObject/GameObject.h"
#include "ConnectWarsDefine.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /** ����UI�̏�� */
    struct S_ImageUiData
    {
        Vector2 position_;
        Vector2 size_;
        Vector4 color_;
        Vector2 textureUpperLeft_;
        Vector2 textureLowerRight_;
    };

    /** �摜UI�̏�� */
    struct S_WordUiData
    {
        std::string words_;
        Vector2 position_;
        Vector2 size_;
        Vector4 color_;
        float wordOffset_ = 0.0f;
    };


    //-------------------------------------------------------------
    //!
    //! @brief �x�[�XUI
    //! @brief UI�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BaseUi : public GameObject::C_GameObject
    {
    public:
        C_BaseUi(const std::string& rId, int32_t type);                         // �R���X�g���N�^
        virtual ~C_BaseUi() override;                                           // �f�X�g���N�^
        bool Update() override;                                                 // �X�V����
        void Draw() override;                                                   // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override;                // ���b�Z�[�W����
    protected:
        bool updateLockFlag_ = false;                                           ///< @brief �X�V���b�N�t���O

        virtual void DoUpdate() = 0;                                            // ����J�̍X�V����
        virtual void DoDraw() = 0;                                              // ����J�̕`�揈��
        virtual bool DoMessageProcess(const Telegram& rTelegram) = 0;           // ����J�̃��b�Z�[�W����
    };
}