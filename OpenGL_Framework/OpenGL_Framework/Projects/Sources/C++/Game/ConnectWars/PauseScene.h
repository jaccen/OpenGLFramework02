/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Library/Scene/BaseScene.h"
#include "../../Library/Camera/Manager/CameraManager.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"


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
    //! @brief �|�[�Y�V�[��
    //! @brief �|�[�Y��\���N���X
    //!
    //-------------------------------------------------------------
    class C_PauseScene : public Scene::C_BaseScene
    {
    public:
        C_PauseScene();                                                 // �R���X�g���N�^
        ~C_PauseScene() override;                                       // �f�X�g���N�^
        Scene::ecSceneReturn Initialize() override;                     // ����������
        Scene::ecSceneReturn Update() override;                         // �X�V����
        void Draw() override;                                           // �`�揈��
        void Finalize() override;                                       // �I������
    private:
        Task::C_GeneralTaskSystem taskSystem_;                          ///< @brief �^�X�N�V�X�e��
        Camera::CameraPtr pUiCamera_;                                   ///< @brief UI�p�J����

        bool RemainLoadProcess();                                       // �c��̃��[�h����
    };
}