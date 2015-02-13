/* �w�b�_�t�@�C�� */
#include "ConnectMachine.h"
#include "../../Library/Light/Light/Point/PointLight.h"
#include "../../Library/Material/Material/Phong/PhongMaterial.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
#pragma region �ÓI�����o�ϐ��̏�����


    /* �����x���t���[�����̊Ԋu */
    uint32_t C_ConnectMachine::s_ownCrashDerayFrameInterval = 10;


#pragma endregion



    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  ID
     *  @param  ���
     *  @param  ���W
     *
     ****************************************************************/
    C_ConnectMachine::C_ConnectMachine(const std::string& rId, int32_t type) : C_Shooter(rId, type)
    {
        // �I�v�V����4���̃����������炩���ߊm�ۂ��Ă���
        pConnectOptionList_.reserve(4);

        // �e�}�e���A�����擾
        assert(Material::C_MaterialManager::s_GetInstance()->GetMaterial(ID::Material::s_pBASIC));
        pBasicMaterial_ = Material::C_MaterialManager::s_GetInstance()->GetMaterial(ID::Material::s_pBASIC).get();

        assert(Material::C_MaterialManager::s_GetInstance()->GetMaterial(ID::Material::s_pDAMAGE));
        pDamageMaterial_ = Material::C_MaterialManager::s_GetInstance()->GetMaterial(ID::Material::s_pDAMAGE).get();

        // ���݂̃}�e���A����ݒ�
        pNowMaterial_ = pBasicMaterial_;

        // �e���C�g���擾
        assert(Light::C_LightManager::s_GetInstance()->GetLight(ID::Light::s_pMAIN));
        pMainLight_ = Light::C_LightManager::s_GetInstance()->GetLight(ID::Light::s_pMAIN).get();
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_ConnectMachine::~C_ConnectMachine()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �A�����Ă���I�v�V�����̃��X�g���擾����
     *  @param  �Ȃ�
     *  @return �A�����Ă���I�v�V�����̃��X�g
     *
     ****************************************************************/
    std::vector<C_BaseOption*>* C_ConnectMachine::GetConnectOptionList()
    {
        return &pConnectOptionList_;
    }


    /*************************************************************//**
     *
     *  @brief  ���̂��擾����
     *  @param  �Ȃ�
     *  @return ����
     *
     ****************************************************************/
    Physics::C_RigidBody* C_ConnectMachine::GetRigidBody() const
    {
        return upRigidBody_.get();
    }


    /*************************************************************//**
     *
     *  @brief  ���a���擾����
     *  @param  �Ȃ�
     *  @return ���a
     *
     ****************************************************************/
    float C_ConnectMachine::GetRadius() const
    {
        return radius_;
    }


    /*************************************************************//**
     *
     *  @brief  ���W���擾����
     *  @param  �Ȃ�
     *  @return ���W
     *
     ****************************************************************/
    const Physics::Vector3& C_ConnectMachine::GetPosition() const
    {
        return upRigidBody_->GetTransform().getOrigin();
    }


    /*************************************************************//**
     *
     *  @brief  ���W��ݒ肷��
     *  @param  ���W
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ConnectMachine::SetPosition(const Physics::Vector3& rPosition)
    {
        auto transform = upRigidBody_->GetTransform();
        transform.setOrigin(rPosition);
        upRigidBody_->SetTransform(transform);
    }


    /*************************************************************//**
     *
     *  @brief  ��]�ʂ��擾����
     *  @param  �Ȃ�
     *  @return ��]��
     *
     ****************************************************************/
    const Physics::Matrix3x3& C_ConnectMachine::GetRotation() const
    {
        return upRigidBody_->GetTransform().getBasis();
    }


    /*************************************************************//**
     *
     *  @brief  �}�e���A����ݒ肷��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ConnectMachine::SetMaterial(const Material::MaterialPtr& prMaterial)
    {
        auto pMaterial = std::static_pointer_cast<Material::S_PhongMaterial>(prMaterial);

        pGlslObject_->SetUniformVector3("u_material.diffuse", pMaterial->diffuse_);
        pGlslObject_->SetUniformVector3("u_material.ambient", pMaterial->ambient_);
        pGlslObject_->SetUniformVector3("u_material.specular", pMaterial->specular_);
        pGlslObject_->SetUniform1f("u_material.shininess", pMaterial->shininess_);
    }


    /*************************************************************//**
     *
     *  @brief  ���C�����C�g��ݒ肷��
     *  @param  ���C�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ConnectMachine::SetLight(const Light::LightPtr& prLight)
    {
        auto pLight = std::static_pointer_cast<Light::S_PointLight>(prLight);

        pGlslObject_->SetUniformVector3("u_light.position", pLight->position_);
        pGlslObject_->SetUniform1f("u_light.constantAttenuation", pLight->constantAttenuation_);
        pGlslObject_->SetUniform1f("u_light.linearAttenuation", pLight->linearAttenuation_);
        pGlslObject_->SetUniform1f("u_light.quadraticAttenuation", pLight->quadraticAttenuation_);
        pGlslObject_->SetUniformVector3("u_light.diffuse", pLight->diffuse_);
        pGlslObject_->SetUniformVector3("u_light.ambient", pLight->ambient_);
        pGlslObject_->SetUniformVector3("u_light.specular", pLight->specular_);
    }


    /*************************************************************//**
     *
     *  @brief  �����x���t���[�����̊Ԋu��ݒ肷��
     *  @param  �����x���t���[�����̊Ԋu
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ConnectMachine::s_SetOwnCrashDerayFrameInterval(uint32_t ownCrashDerayFrameInterval)
    {
        s_ownCrashDerayFrameInterval = ownCrashDerayFrameInterval;
    }
}