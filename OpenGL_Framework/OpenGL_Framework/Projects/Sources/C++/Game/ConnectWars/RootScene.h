/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Library/Scene/BaseScene.h"
#include "../../Library/Camera/Camera/Perspective/PerspectiveCamera.h"
#include "UiFont.h"


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
    //! @brief ���[�g�V�[��
    //! @brief �ŏ�ʂɂ���V�[����\���N���X
    //!
    //-------------------------------------------------------------
    class C_RootScene : public Scene::C_BaseScene
    {
    public:
        C_RootScene();                                                  // �R���X�g���N�^
        ~C_RootScene() override;                                        // �f�X�g���N�^
        Scene::ecSceneReturn Initialize() override;                     // ����������
        Scene::ecSceneReturn Update() override;                         // �X�V����
        void Draw() override;                                           // �`�揈��
        void Finalize() override;                                       // �I������
    private:
        std::unique_ptr<C_UiFont> upUiFont_;                            ///< @brief UI�t�H���g

        void SetPhysicsEngine();                                        // �����G���W���̐ݒ�
        bool BindToLua();                                               // Lua�ւ̃o�C���h����
        void SetTaskPriority();                                         // �^�X�N�̗D��x��ݒ�
        void CreateCameras();                                           // �J�����̍쐬
        bool LoadTexturesAndCreateSpriteCreater();                      // �e�N�X�`���̃��[�h�����ƃX�v���C�g�N���G�C�^�[�̍쐬
        void PushNextScene();                                           // ���̃V�[����ǉ�
    };
}