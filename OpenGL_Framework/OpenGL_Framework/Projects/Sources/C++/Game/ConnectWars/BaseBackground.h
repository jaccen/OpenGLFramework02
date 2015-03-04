/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Library/GameObject/GameObject.h"
#include "../../Library/Shader/GLSL/Object/Manager/GlslObjectManager.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"
#include "ConnectWarsDefine.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* �O���錾 */
    class C_BackgroundMoveLogic;


    //-------------------------------------------------------------
    //!
    //! @brief �X�y�[�X
    //! @brief �F���̃X�J�C�X�t�B�A��`�悷��N���X
    //!
    //-------------------------------------------------------------
    class C_BaseBackground : public GameObject::C_GameObject
    {
    public:
        C_BaseBackground(const std::string& rId, int32_t type);                         // �R���X�g���N�^
        virtual ~C_BaseBackground();                                                    // �f�X�g���N�^
        bool Update() override;                                                         // �X�V����
        void Draw() override;                                                           // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override;                        // ���b�Z�[�W����
        const Vector3& GetPosition() const;                                             // ���W���擾
        const Vector3& GetRotation() const;                                             // ��]�ʂ��擾
        C_BackgroundMoveLogic* GetMoveLogic() const;                                    // �ړ����W�b�N���擾
        void SetPosition(const Vector3& rPosition);                                     // ���W��ݒ�
        void SetRotation(const Vector3& rRotation);                                     // ��]�ʂ�ݒ�
        virtual void SetScale(const Vector3& rScale);                                   // �g�嗦��ݒ�
        void SetLifeFrame(int32_t lifeFrame);                                           // �����t���[������ݒ�
    protected:
        Shader::GLSL::GlslObjectPtr pGlslObject_;                                       ///< @brief GLSL�I�u�W�F�N�g
        Shader::GLSL::UniformBufferPtr pUniformBuffer_;                                 ///< @brief ���j�t�H�[���o�b�t�@
        Shader::GLSL::UniformBlockIndex uniformBlockIndex_ = 0;                         ///< @brief ���j�t�H�[���u���b�N�̃C���f�b�N�X
        int32_t lifeFrame_ = 0;                                                         ///< @brief �����t���[����
        Timer::C_FrameCounter frameCounter_;                                            ///< @brief �t���[���J�E���^�[
        Vector3 position_;                                                              ///< @brief ���W
        Vector3 rotation_;                                                              ///< @brief ��]��
        Vector3 scale_ = Vector3::s_ONE;                                                ///< @brief �g�嗦
        std::unique_ptr<C_BackgroundMoveLogic> upMoveLogic_;                            ///< @brief �ړ����W�b�N

        virtual void DoUpdate() = 0;                                                    // ����J�̍X�V����
        virtual void DoDraw() = 0;                                                      // ����J�̕`�揈��
        virtual bool DoMessageProcess(const Telegram& rTelegram) = 0;                   // ����J�̃��b�Z�[�W����
    };
}