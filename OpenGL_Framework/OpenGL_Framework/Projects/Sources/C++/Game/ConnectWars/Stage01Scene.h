/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Library/Scene/BaseScene.h"
#include "../../Library/Camera/Camera/Perspective/PerspectiveCamera.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"
#include "../../Library/OpenGL/Buffer/Frame/FrameBuffer.h"
#include "BasePlayer.h"
#include "PlayerGenerator.h"
#include "OptionGenerator.h"
#include "BulletGenerator.h"
#include "EffectGenerator.h"


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
        C_Stage01Scene();                                               // �R���X�g���N�^
        ~C_Stage01Scene() override;                                     // �f�X�g���N�^
        Scene::ecSceneReturn Initialize() override;                     // ����������
        Scene::ecSceneReturn Update() override;                         // �X�V����
        void Draw() override;                                           // �`�揈��
        void Finalize() override;                                       // �I������
    private:
        Task::C_GeneralTaskSystem taskSystem_;                          ///< @brief �^�X�N�V�X�e��
        C_PlayerGenerator playerGenerator_;                             ///< @brief �v���C���[�����@
        C_OptionGenerator optionGenerator_;                             ///< @brief �I�v�V���������@
        C_BulletGenerator bulletGenerator_;                             ///< @brief �e�����@
        C_EffectGenerator effectGenerator_;                             ///< @brief �G�t�F�N�g�����@
        std::shared_ptr<Camera::IC_Camera> spMainCamera_;               ///< @brief ���C���J����
        S_CameraData mainCameraData_;                                   ///< @brief ���C���J�����̏��

        bool RemainLoadProcess();                                       // �c��̃��[�h����
    };
}