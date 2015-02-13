/* �w�b�_�t�@�C�� */
#include "SmallBeamOption.h"
#include "OptionDropState.h"
#include "RigidBodyStraightMoveLogic.h"
#include "OptionGunFactory.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"
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
    C_SmallBeamOption::C_SmallBeamOption(const std::string& rId, int32_t type) : C_BaseOption(rId, type)
    {
        // �I�v�V�����̏����擾
        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSMALL_BEAM_OPTION));
        auto pOptionData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSMALL_BEAM_OPTION).get();

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
        
        upRigidBody_->EnableCollisionResponse(false);
        upRigidBody_->EnableFreezeRotation(true, true, true);
        
        Physics::C_PhysicsEngine::s_GetInstance()->AddRigidBody(upRigidBody_.get(), 
                                                                C_CollisionObject::FILTER_TYPE_OPTION,
                                                                collisionMask);

        // ���g��ݒ�
        upRigidBody_->SetUserPointer(this);

        // ���f�������擾
        assert(OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pSMALL_BEAM_OPTION));
        pModelData_ = OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pSMALL_BEAM_OPTION).get();

        // �e�N�X�`�������擾
        assert(Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pSMALL_BEAM_OPTION));
        pModelTextureData_ = Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pSMALL_BEAM_OPTION).get();

        // GLSL�I�u�W�F�N�g���擾
        assert(Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pPHONG_TEXTURE));
        pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pPHONG_TEXTURE).get();

        // ���j�t�H�[���o�b�t�@�ƃC���f�b�N�X���擾
        assert(Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pMAIN_CAMERA));
        pUniformBuffer_ = Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pMAIN_CAMERA).get();
        uniformBlockIndex_ = pUniformBuffer_->GetBlockIndexFromProgramObject(pGlslObject_->GetProgramObjectHandle());

        // �p���[�ƃq�b�g�|�C���g���쐬
        upPower_ = std::make_unique<C_BasePower>((*pOptionData)["CreateData"]["Power"].GetValue<JSON::Integer>());
        upHitPoint_ = std::make_unique<C_BaseHitPoint>((*pOptionData)["CreateData"]["HitPoint"].GetValue<JSON::Integer>());

        // �ړ��̃��W�b�N���쐬
        upMoveLogic_ = std::make_unique<C_RigidBodyStraightMoveLogic>();
        upMoveLogic_->SetDirection(Physics::Vector3(0.0f, -1.0f, 0.0f));
        upMoveLogic_->SetMovement(static_cast<float>((*pOptionData)["CreateData"]["Movement"].GetValue<JSON::Real>()));

        // �e�̏��̐����擾
        gunDataCount_ = (*pOptionData)["GunDataCount"].GetValue<JSON::Integer>();

        // ���j�t�H�[���ϐ���ݒ�
        pGlslObject_->Begin();

        SetMaterial(pBasicMaterial_);
        pGlslObject_->SetUniform1i("u_texture", 0);
        pGlslObject_->SetUniform1f("u_gamma", 2.2f);

        pGlslObject_->End();
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SmallBeamOption::~C_SmallBeamOption()
    {
        Physics::C_PhysicsEngine::s_GetInstance()->RemoveRigidBody(upRigidBody_.get());
    }


    /*************************************************************//**
     *
     *  @brief  �A�����̌��ʂ���������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SmallBeamOption::ConnectEffect()
    {
        assert(pPlayer_);

        // �e���쐬
        C_OptionSmallBeamGunFactory optionSmallBeamGunFactory;
        upGuns_.reserve(gunDataCount_);

        for (int32_t i = 0; i < gunDataCount_; ++i)
        {
            upGuns_.emplace_back(optionSmallBeamGunFactory.Create(this, i));
        }
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SmallBeamOption::DoDraw()
    {
        pGlslObject_->BeginWithUnifomBuffer(pUniformBuffer_->GetHandle(), uniformBlockIndex_);

        upRigidBody_->GetTransform().getOpenGLMatrix(modelMatrix_.a_);
        modelMatrix_ = modelMatrix_ * Matrix4x4::s_CreateScaling(Vector3(radius_));
        pGlslObject_->SetUniformMatrix4x4("u_modelMatrix", modelMatrix_);

        // ���C�g�ƃ}�e���A����ݒ�
        SetLight(pMainLight_);
        SetMaterial(pNowMaterial_);

        auto pOpenGlManager = OpenGL::C_OpenGlManager::s_GetInstance();
        auto pTextureManager = Texture::C_TextureManager::s_GetInstance();

        // �A�N�e�B�u�ȃe�N�X�`�����j�b�g��ݒ肵�A�e�N�X�`�����o�C���h
        pTextureManager->SetActiveUnit(0);
        pModelTextureData_ = Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pSMALL_BEAM_OPTION).get();
        pTextureManager->Bind(Texture::Type::s_2D, pModelTextureData_->handle_);

        pOpenGlManager->DrawPrimitiveWithIndices(OpenGL::Primitive::s_TRIANGLE,
                                                 pModelData_->GetVertexArrayObjectHandle(), 
                                                 pModelData_->GetIndexBufferObjectHandle(),
                                                 OpenGL::DataType::s_UNSIGNED_SHORT,
                                                 static_cast<int32_t>(pModelData_->GetIndexCount()));

        pTextureManager->Unbind(Texture::Type::s_2D);

        pGlslObject_->End();
    }
}