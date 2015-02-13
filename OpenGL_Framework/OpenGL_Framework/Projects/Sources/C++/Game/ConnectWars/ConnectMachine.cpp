/* ヘッダファイル */
#include "ConnectMachine.h"
#include "../../Library/Light/Light/Point/PointLight.h"
#include "../../Library/Material/Material/Phong/PhongMaterial.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
#pragma region 静的メンバ変数の初期化


    /* 自爆遅延フレーム数の間隔 */
    uint32_t C_ConnectMachine::s_ownCrashDerayFrameInterval = 10;


#pragma endregion



    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ID
     *  @param  種類
     *  @param  座標
     *
     ****************************************************************/
    C_ConnectMachine::C_ConnectMachine(const std::string& rId, int32_t type) : C_Shooter(rId, type)
    {
        // オプション4個分のメモリをあらかじめ確保しておく
        pConnectOptionList_.reserve(4);

        // 各マテリアルを取得
        assert(Material::C_MaterialManager::s_GetInstance()->GetMaterial(ID::Material::s_pBASIC));
        pBasicMaterial_ = Material::C_MaterialManager::s_GetInstance()->GetMaterial(ID::Material::s_pBASIC).get();

        assert(Material::C_MaterialManager::s_GetInstance()->GetMaterial(ID::Material::s_pDAMAGE));
        pDamageMaterial_ = Material::C_MaterialManager::s_GetInstance()->GetMaterial(ID::Material::s_pDAMAGE).get();

        // 現在のマテリアルを設定
        pNowMaterial_ = pBasicMaterial_;

        // 各ライトを取得
        assert(Light::C_LightManager::s_GetInstance()->GetLight(ID::Light::s_pMAIN));
        pMainLight_ = Light::C_LightManager::s_GetInstance()->GetLight(ID::Light::s_pMAIN).get();
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_ConnectMachine::~C_ConnectMachine()
    {
    }


    /*************************************************************//**
     *
     *  @brief  連結しているオプションのリストを取得する
     *  @param  なし
     *  @return 連結しているオプションのリスト
     *
     ****************************************************************/
    std::vector<C_BaseOption*>* C_ConnectMachine::GetConnectOptionList()
    {
        return &pConnectOptionList_;
    }


    /*************************************************************//**
     *
     *  @brief  剛体を取得する
     *  @param  なし
     *  @return 剛体
     *
     ****************************************************************/
    Physics::C_RigidBody* C_ConnectMachine::GetRigidBody() const
    {
        return upRigidBody_.get();
    }


    /*************************************************************//**
     *
     *  @brief  半径を取得する
     *  @param  なし
     *  @return 半径
     *
     ****************************************************************/
    float C_ConnectMachine::GetRadius() const
    {
        return radius_;
    }


    /*************************************************************//**
     *
     *  @brief  座標を取得する
     *  @param  なし
     *  @return 座標
     *
     ****************************************************************/
    const Physics::Vector3& C_ConnectMachine::GetPosition() const
    {
        return upRigidBody_->GetTransform().getOrigin();
    }


    /*************************************************************//**
     *
     *  @brief  座標を設定する
     *  @param  座標
     *  @return なし
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
     *  @brief  回転量を取得する
     *  @param  なし
     *  @return 回転量
     *
     ****************************************************************/
    const Physics::Matrix3x3& C_ConnectMachine::GetRotation() const
    {
        return upRigidBody_->GetTransform().getBasis();
    }


    /*************************************************************//**
     *
     *  @brief  マテリアルを設定する
     *  @param  なし
     *  @return なし
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
     *  @brief  メインライトを設定する
     *  @param  ライト
     *  @return なし
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
     *  @brief  自爆遅延フレーム数の間隔を設定する
     *  @param  自爆遅延フレーム数の間隔
     *  @return なし
     *
     ****************************************************************/
    void C_ConnectMachine::s_SetOwnCrashDerayFrameInterval(uint32_t ownCrashDerayFrameInterval)
    {
        s_ownCrashDerayFrameInterval = ownCrashDerayFrameInterval;
    }
}