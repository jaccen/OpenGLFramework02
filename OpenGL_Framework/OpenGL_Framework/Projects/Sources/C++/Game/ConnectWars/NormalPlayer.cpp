/* �w�b�_�t�@�C�� */
#include "NormalPlayer.h"
#include "RigidBodyInputMoveLogic.h"
#include "NormalGun.h"
#include "PlayerGunFactory.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"
#include "../../Library/OpenGL/Manager/OpenGlManager.h"
#include "../../Library/Shader/GLSL/Uniform/Manager/UniformBufferManager.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"
#include "../../Library/Debug/Helper/DebugHelper.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  ID
     *  @param  ���
     *
     ****************************************************************/
    C_NormalPlayer::C_NormalPlayer(const std::string& rId, int32_t type) : C_BasePlayer(rId, type)
    {
        // �v���C���[�̏����擾
        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pNORMAL_PLAYER));
        auto pPlayerData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pNORMAL_PLAYER).get();

        // ���`��𐫐���
        radius_ = static_cast<float>((*pPlayerData)["CreateData"]["Radius"].GetValue<JSON::Real>());
        ResetMoveLimitBoundingBox();

        // ���̂��쐬���A�����G���W���ɒǉ�
        Physics::Transform transform;
        transform.setIdentity();
        transform.setOrigin(Physics::Vector3(static_cast<float>((*pPlayerData)["CreateData"]["Position"][0].GetValue<JSON::Real>()),
                                             static_cast<float>((*pPlayerData)["CreateData"]["Position"][1].GetValue<JSON::Real>()),
                                             static_cast<float>((*pPlayerData)["CreateData"]["Position"][2].GetValue<JSON::Real>())));

        int32_t collisionMask = C_CollisionObject::FILTER_TYPE_OPTION
                              | C_CollisionObject::FILTER_TYPE_ENEMY 
                              | C_CollisionObject::FILTER_TYPE_ENEMY_BULLET
                              | C_CollisionObject::FILTER_TYPE_OBSTACLE;

		upRigidBody_ = std::make_unique<Physics::C_RigidBody>(newEx Physics::C_SphereShape(radius_), transform, static_cast<float>((*pPlayerData)["CreateData"]["Mass"].GetValue<JSON::Real>()));
        
        // �Փˉ������Ȃ����A��]��S�ăt���[�Y
        upRigidBody_->EnableCollisionResponse(false);
        upRigidBody_->EnableFreezeRotation(true, true, true);
        
        Physics::C_PhysicsEngine::s_GetInstance()->AddRigidBody(upRigidBody_.get(), 
                                                                C_CollisionObject::FILTER_TYPE_PLAYER,
                                                                collisionMask);

        // ���g��ݒ�
        upRigidBody_->SetUserPointer(this);

        // ���f�������擾
        assert(OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pNORMAL_PLAYER));
        pModelData_ = OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pNORMAL_PLAYER).get();

        // GLSL�I�u�W�F�N�g���擾
        assert(Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pHALF_LAMBERT_PHONG));
        pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pHALF_LAMBERT_PHONG).get();

        // ���j�t�H�[���o�b�t�@�ƃC���f�b�N�X���擾
        assert(Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pMAIN_CAMERA));
        pUniformBuffer_ = Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pMAIN_CAMERA).get();
        uniformBlockIndex_ = pUniformBuffer_->GetBlockIndexFromProgramObject(pGlslObject_->GetProgramObjectHandle());

        // �p���[�ƃq�b�g�|�C���g���쐬
        upPower_ = std::make_unique<C_BasePower>((*pPlayerData)["CreateData"]["Power"].GetValue<JSON::Integer>());
        upHitPoint_ = std::make_unique<C_BaseHitPoint>((*pPlayerData)["CreateData"]["HitPoint"].GetValue<JSON::Integer>());

        // �ړ��̃��W�b�N���쐬
        moveSpeedLevel_ = (*pPlayerData)["CreateData"]["MoveSpeedLevel"].GetValue<JSON::Integer>();
        moveSpeedUpInterval_ = static_cast<float>((*pPlayerData)["CreateData"]["MoveSpeedUpInterval"].GetValue<JSON::Real>());
        upMoveLogic_ = std::make_unique<C_RigidBodyInputMoveLogic>(static_cast<float>((*pPlayerData)["CreateData"]["Movement"].GetValue<JSON::Real>()), 1.0f);

        // �e���쐬
        C_PlayerBeamGunFactory playerBeamGunFactory;
        int32_t gunDataCount = (*pPlayerData)["GunDataCount"].GetValue<JSON::Integer>();

        upGuns_.reserve(gunDataCount);

        for (int32_t i = 0; i < gunDataCount; ++i)
        {
            upGuns_.emplace_back(playerBeamGunFactory.Create(this, i));
        }

        // ���̑��̃f�[�^��ݒ�
        remainLife_ = (*pPlayerData)["CreateData"]["RemainLife"].GetValue<JSON::Integer>();
        connectPetrifyFrame_ = (*pPlayerData)["CreateData"]["ConnectPetrifyFrame"].GetValue<JSON::Integer>();
        bombChargeFrame_ = (*pPlayerData)["CreateData"]["BombChargeFrame"].GetValue<JSON::Integer>();
        bombInvincibleFrame_ = (*pPlayerData)["CreateData"]["BombInvincibleFrame"].GetValue<JSON::Integer>();
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_NormalPlayer::~C_NormalPlayer()
    {
        // ���̂𕨗��G���W�����珜��
        Physics::C_PhysicsEngine::s_GetInstance()->RemoveRigidBody(upRigidBody_.get());
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_NormalPlayer::DoDraw()
    {
        pGlslObject_->BeginWithUnifomBuffer(pUniformBuffer_->GetHandle(), uniformBlockIndex_);

        // �}�e���A����ݒ�
        pGlslObject_->SetUniformVector3("material.diffuse", Vector3(0.5f, 1.0f, 0.5f));
        pGlslObject_->SetUniformVector3("material.ambient", Vector3(0.1f, 0.1f, 0.1f));
        pGlslObject_->SetUniformVector3("material.specular", Vector3(0.9f, 0.9f, 0.9f));
        pGlslObject_->SetUniform1f("material.shininess", 100.0f);
        pGlslObject_->SetUniformVector3("light.position", Vector3(0.0f, 100.0f, 0.0f));
        pGlslObject_->SetUniformVector3("light.diffuse", Vector3(0.9f, 0.9f, 0.9f));
        pGlslObject_->SetUniformVector3("light.ambient", Vector3(0.9f, 0.9f, 0.9f));
        pGlslObject_->SetUniformVector3("light.specular", Vector3(0.9f, 0.9f, 0.9f));

        upRigidBody_->GetTransform().getOpenGLMatrix(modelMatrix_.a_);
        pGlslObject_->SetUniformMatrix4x4("modelMatrix", modelMatrix_);

        auto pOpenGlManager = OpenGL::C_OpenGlManager::s_GetInstance();

        pOpenGlManager->DrawPrimitiveWithIndices(OpenGL::Primitive::s_TRIANGLE,
                                                 pModelData_->GetVertexArrayObjectHandle(), 
                                                 pModelData_->GetIndexBufferObjectHandle(),
                                                 OpenGL::DataType::s_UNSIGNED_SHORT,
                                                 static_cast<int32_t>(pModelData_->GetIndexCount()));

        pGlslObject_->End();

        pGlslObject_->End();
    }
}