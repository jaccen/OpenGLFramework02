/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Library/Scene/BaseScene.h"
#include "../../Library/Camera/Camera/Perspective/PerspectiveCamera.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"
#include "../../Library/OpenGL/Buffer/Frame/FrameBuffer.h"
#include "BasePlayer.h"


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
    //! @brief �X�e�[�W01�V�[��
    //! @brief �X�e�[�W01��\���N���X
    //!
    //-------------------------------------------------------------
    class C_Stage01Scene : public Scene::C_BaseScene
    {
    public:
        C_Stage01Scene();                                                           // �R���X�g���N�^
        ~C_Stage01Scene() override;                                                 // �f�X�g���N�^
        Scene::ecSceneReturn Initialize() override;                                 // ����������
        Scene::ecSceneReturn Update() override;                                     // �X�V����
        void Draw() override;                                                       // �`�揈��
        void Finalize() override;                                                   // �I������
    private:
        std::unique_ptr<Task::C_GeneralTaskSystem> upTaskSystem_;                   ///< @brief �^�X�N�V�X�e��

        std::shared_ptr<Camera::C_PerspectiveCamera> spCamera_;                     // �J����
        OpenGL::FrameBufferPtr pFrameBuffer_;                                       // �t���[���o�b�t�@
        std::unique_ptr<C_BasePlayer> upPlayer_;
    };
}