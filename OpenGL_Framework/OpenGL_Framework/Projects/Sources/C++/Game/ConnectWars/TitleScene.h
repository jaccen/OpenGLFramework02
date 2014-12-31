/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Library/Scene/BaseScene.h"
#include "../../Library/Camera/Camera/Perspective/PerspectiveCamera.h"


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
    //! @brief �^�C�g���V�[��
    //! @brief �^�C�g����\���N���X
    //!
    //-------------------------------------------------------------
    class C_TitleScene : public Scene::C_BaseScene
    {
    public:
        C_TitleScene();                                                 // �R���X�g���N�^
        ~C_TitleScene() override;                                       // �f�X�g���N�^
        Scene::ecSceneReturn Initialize() override;                     // ����������
        Scene::ecSceneReturn Update() override;                         // �X�V����
        void Draw() override;                                           // �`�揈��
        void Finalize() override;                                       // �I������
    private:
        std::shared_ptr<Camera::C_PerspectiveCamera> spCamera_;         // �J����
    };
}