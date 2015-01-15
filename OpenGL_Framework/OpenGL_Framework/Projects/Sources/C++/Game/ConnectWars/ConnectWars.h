/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Library/Framework/Framework.h"
#include "../../Library/Scene/Manager/SceneManager.h"
#include "../../Library/Lua/LuaStateManager.h"
#include "../../Library/GameObject/Manager/GameObjectManager.h"
#include "../../Library/GameObject/Message/Dispatcher/MessageDispatcher.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "../../Library/Particle/System/Manager/ParticleSystemManager.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"


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
    //! @brief �R�l�N�g�E�H�[�Y
    //! @brief �R�l�N�g�E�H�[�Y��\���N���X
    //!
    //-------------------------------------------------------------
    class C_ConnectWars : public Framework::C_Framework
    {
    public:
        C_ConnectWars();                                                                    // �R���X�g���N�^
        virtual ~C_ConnectWars() override;                                                  // �f�X�g���N�^
    private:
        std::unique_ptr<Scene::C_SceneManager> upSceneManager_;                             ///< @brief �V�[���}�l�[�W���[
        std::unique_ptr<Lua::C_LuaStateManager> upLuaStateManager_;                         ///< @brief Lua�X�e�[�g�}�l�[�W���[
        std::unique_ptr<Sprite::C_SpriteCreaterManager> upSpriteCreaterManager_;            ///< @brief �X�v���C�g�N���G�C�^�[�}�l�[�W���[
        std::unique_ptr<Particle::C_ParticleSystemManager> upParticleSystemManager_;        ///< @brief �p�[�e�B�N���V�X�e���}�l�[�W���[
        std::unique_ptr<GameObject::C_GameObjectManager> upGameObjectManager_;              ///< @brief �Q�[���I�u�W�F�N�g�}�l�[�W���[
        std::unique_ptr<GameObject::Message::C_MessageDispatcher> upMessageDispatcher_;     ///< @brief ���b�Z�[�W�f�B�X�p�b�`���[
        std::unique_ptr<Physics::C_PhysicsEngine> upPhysicsEngine_;                         ///< @brief �t�B�W�b�N�X�G���W��

        bool Initialize() override;                                                         // ����������
        bool Update() override;                                                             // �X�V����
        void Draw() override;                                                               // �`�揈��
        void Finalize() override;                                                           // �I������
    };
}