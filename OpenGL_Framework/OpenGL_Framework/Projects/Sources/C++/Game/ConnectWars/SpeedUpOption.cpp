/* �w�b�_�t�@�C�� */
#include "SpeedUpOption.h"
#include "BasePlayer.h"
#include "RigidBodyStraightMoveLogic.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"
#include "../../Library/OpenGL/Manager/OpenGlManager.h"
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
     *  @param  ���W
     *
     ****************************************************************/
    C_SpeedUpOption::C_SpeedUpOption(const std::string& rId, int32_t type) : C_BaseOption(rId, type)
    {
        // �I�v�V�����̏����擾
        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSPEED_UP_OPTION));
        auto pOptionData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSPEED_UP_OPTION).get();

        // ���`��𐫐���
        radius_ = static_cast<float>((*pOptionData)["CreateData"]["Radius"].GetValue<JSON::Real>());

        // ���̂��쐬���A�����G���W���ɒǉ�
        Physics::Transform transform;
        transform.setIdentity();

        int32_t collisionMask = C_CollisionObject::FILTER_TYPE_PLAYER
                              | C_CollisionObject::FILTER_TYPE_OPTION
                              | C_CollisionObject::FILTER_TYPE_ENEMY 
                              | C_CollisionObject::FILTER_TYPE_ENEMY_BULLET
                              | C_CollisionObject::FILTER_TYPE_OBSTACLE;

		upRigidBody_ = std::make_unique<Physics::C_RigidBody>(newEx Physics::C_SphereShape(radius_), transform, static_cast<float>((*pOptionData)["CreateData"]["Mass"].GetValue<JSON::Real>()));
        Physics::C_PhysicsEngine::s_GetInstance()->AddRigidBody(upRigidBody_.get(), 
                                                                C_CollisionObject::FILTER_TYPE_OPTION,
                                                                collisionMask);

        upRigidBody_->EnableCollisionResponse(false);
        upRigidBody_->EnableFreezeRotation(true, true, true);

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
        upPower_ = std::make_unique<C_BasePower>((*pOptionData)["CreateData"]["Power"].GetValue<JSON::Integer>());
        upHitPoint_ = std::make_unique<C_BaseHitPoint>((*pOptionData)["CreateData"]["HitPoint"].GetValue<JSON::Integer>());

        // �ړ��̃��W�b�N���쐬
        upMoveLogic_ = std::make_unique<C_RigidBodyStraightMoveLogic>(Physics::Vector3(0.0f, -1.0f, 0.0f) * static_cast<float>((*pOptionData)["CreateData"]["Movement"].GetValue<JSON::Real>()));
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SpeedUpOption::~C_SpeedUpOption()
    {
        // ���̂𕨗��G���W�����珜��
        Physics::C_PhysicsEngine::s_GetInstance()->RemoveRigidBody(upRigidBody_.get());
    }


    /*************************************************************//**
     *
     *  @brief  �A�����̌��ʂ���������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpeedUpOption::ConnectEffect()
    {
        assert(pPlayer_);

        pPlayer_->AddMoveSpeedLevel(1);
    }


    /*************************************************************//**
     *
     *  @brief  ���ʂ����Z�b�g����
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpeedUpOption::ResetEffect()
    {
        assert(pPlayer_);

        pPlayer_->AddMoveSpeedLevel(-1);
    }

    
    /*************************************************************//**
     *
     *  @brief  ����J�̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpeedUpOption::DoDraw()
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
        modelMatrix_ = modelMatrix_ * Matrix4x4::s_CreateScaling(Vector3(radius_));
        pGlslObject_->SetUniformMatrix4x4("modelMatrix", modelMatrix_);

        auto pOpenGlManager = OpenGL::C_OpenGlManager::s_GetInstance();

        pOpenGlManager->DrawPrimitiveWithIndices(OpenGL::Primitive::s_TRIANGLE,
                                                 pModelData_->GetVertexArrayObjectHandle(), 
                                                 pModelData_->GetIndexBufferObjectHandle(),
                                                 OpenGL::DataType::s_UNSIGNED_SHORT,
                                                 static_cast<int32_t>(pModelData_->GetIndexCount()));

        pGlslObject_->End();
    }
}