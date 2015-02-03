/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Library/GameObject/GameObject.h"
#include "../../Library/Shader/GLSL/Object/Manager/GlslObjectManager.h"
#include "ConnectWarsDefine.h"


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
    //! @brief �X�y�[�X
    //! @brief �F���̃X�J�C�X�t�B�A��`�悷��N���X
    //!
    //-------------------------------------------------------------
    class C_BaseBackground : public GameObject::C_GameObject
    {
    public:
        C_BaseBackground(const std::string& rId, int32_t type);                 // �R���X�g���N�^
        virtual ~C_BaseBackground();                                            // �f�X�g���N�^
        bool Update() override;                                                 // �X�V����
        void Draw() override;                                                   // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override;                // ���b�Z�[�W����
    protected:
        Shader::GLSL::GlslObjectPtr pGlslObject_;                               ///< @brief GLSL�I�u�W�F�N�g
        Shader::GLSL::UniformBufferPtr pUniformBuffer_;                         ///< @brief ���j�t�H�[���o�b�t�@
        Shader::GLSL::UniformBlockIndex uniformBlockIndex_ = 0;                 ///< @brief ���j�t�H�[���u���b�N�̃C���f�b�N�X

        virtual void DoUpdate() = 0;                                            // ����J�̍X�V����
        virtual void DoDraw() = 0;                                              // ����J�̕`�揈��
        virtual bool DoMessageProcess(const Telegram& rTelegram) = 0;           // ����J�̃��b�Z�[�W����
    };
}