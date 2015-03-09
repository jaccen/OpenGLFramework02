/* �w�b�_�t�@�C�� */
#include "BaseEnemy.h"
#include "BaseGun.h"
#include "CollisionProcess.h"
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
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  ID
     *  @param  ���
     *
     ****************************************************************/
    C_BaseEnemy::C_BaseEnemy(const std::string& rId, int32_t type) : C_Shooter(rId, type),

        // �X�e�[�g�}�V�[��
        upStateMachine_(std::make_unique<State::C_StateMachine<C_BaseEnemy>>(this))

    {
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
    C_BaseEnemy::~C_BaseEnemy()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �^�X�N���s�Ftrue
     *  @return �^�X�N�I���Ffalse
     *
     ****************************************************************/
    bool C_BaseEnemy::Update()
    {
        DoUpdate();

        return C_GameObject::existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseEnemy::Draw()
    {
        DoDraw();
    }


    /*************************************************************//**
     *
     *  @brief  ���b�Z�[�W�������s��
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_BaseEnemy::MessageProcess(const Telegram& rTelegram)
    {
        if (DoMessageProcess(rTelegram) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �Փˌ��m�̔��s���s��
     *  @param  �Փ˃I�u�W�F�N�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseEnemy::DispatchCollision(C_CollisionObject* pCollisionObject)
    {
        pCollisionObject->CollisionProcess(this);
    }


    /*************************************************************//**
     *
     *  @brief  �v���C���[�Ƃ̏Փˎ��������s��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseEnemy::CollisionProcess(C_BasePlayer* pPlayer)
    {
        C_CollisionProcess::s_PlayerAndEnemy(pPlayer, this);
    }


    /*************************************************************//**
     *
     *  @brief  �I�v�V�����Ƃ̏Փˎ��������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseEnemy::CollisionProcess(C_BaseOption* pOption)
    {
        C_CollisionProcess::s_OptionAndEnemy(pOption, this);
    }


    /*************************************************************//**
     *
     *  @brief  �G�Ƃ̏Փˎ��������s��
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseEnemy::CollisionProcess(C_BaseEnemy* pEnemy)
    {
        C_CollisionProcess::s_EnemyAndEnemy(this, pEnemy);
    }


    /*************************************************************//**
     *
     *  @brief  �e�Ƃ̏Փˎ��������s��
     *  @param  �e
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseEnemy::CollisionProcess(C_BaseBullet* pBullet)
    {
        C_CollisionProcess::s_EnemyAndBullet(this, pBullet);
    }


    /*************************************************************//**
     *
     *  @brief  ��Q���Ƃ̏Փˎ��������s��
     *  @param  ��Q��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseEnemy::CollisionProcess(C_BaseObstacle* pObstacle)
    {
        C_CollisionProcess::s_EnemyAndObstacle(this, pObstacle);
    }


    /*************************************************************//**
     *
     *  @brief  �{���Ƃ̏Փˎ��������s��
     *  @param  �{��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseEnemy::CollisionProcess(C_BaseBomb* pBomb)
    {
        C_CollisionProcess::s_EnemyAndBomb(this, pBomb);
    }


     /*************************************************************//**
     *
     *  @brief  �V�[���h�Ƃ̏Փˎ��������s��
     *  @param  �V�[���h
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseEnemy::CollisionProcess(C_BaseShield* pShield)
    {
        C_CollisionProcess::s_EnemyAndShield(this, pShield);
    }


    /*************************************************************//**
     *
     *  @brief  �ˌ��������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseEnemy::Shot()
    {
    }
    

    /*************************************************************//**
     *
     *  @brief  �}�e���A����ݒ肷��
     *  @param  �}�e���A��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseEnemy::SetMaterial(const Material::MaterialPtr& prMaterial)
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
    void C_BaseEnemy::SetLight(const Light::LightPtr& prLight)
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
     *  @brief  �o�����I�����Ă��邩�m�F����
     *  @param  �Ȃ�
     *  @return �I�����Ă���ꍇ  �Ftrue
     *  @return �I�����Ă��Ȃ��ꍇ�Ffalse
     *
     ****************************************************************/
    bool C_BaseEnemy::IsFinishAdvent() const
    {
        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�[�g�}�V�[�����擾����
     *  @param  �Ȃ�
     *  @return �X�e�[�g�}�V�[��
     *
     ****************************************************************/
    State::C_StateMachine<C_BaseEnemy>* C_BaseEnemy::GetStateMachine() const
    {
        return upStateMachine_.get();
    }
}