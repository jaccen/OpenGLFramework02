/* ヘッダファイル */
#include "BaseEnemy.h"
#include "BaseGun.h"
#include "CollisionProcess.h"
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
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ID
     *  @param  種類
     *
     ****************************************************************/
    C_BaseEnemy::C_BaseEnemy(const std::string& rId, int32_t type) : C_Shooter(rId, type),

        // ステートマシーン
        upStateMachine_(std::make_unique<State::C_StateMachine<C_BaseEnemy>>(this))

    {
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
    C_BaseEnemy::~C_BaseEnemy()
    {
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return タスク続行：true
     *  @return タスク終了：false
     *
     ****************************************************************/
    bool C_BaseEnemy::Update()
    {
        DoUpdate();

        return C_GameObject::existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseEnemy::Draw()
    {
        DoDraw();
    }


    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_BaseEnemy::MessageProcess(const Telegram& rTelegram)
    {
        if (DoMessageProcess(rTelegram) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  衝突検知の発行を行う
     *  @param  衝突オブジェクト
     *  @return なし
     *
     ****************************************************************/
    void C_BaseEnemy::DispatchCollision(C_CollisionObject* pCollisionObject)
    {
        pCollisionObject->CollisionProcess(this);
    }


    /*************************************************************//**
     *
     *  @brief  プレイヤーとの衝突時処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_BaseEnemy::CollisionProcess(C_BasePlayer* pPlayer)
    {
        C_CollisionProcess::s_PlayerAndEnemy(pPlayer, this);
    }


    /*************************************************************//**
     *
     *  @brief  オプションとの衝突時処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_BaseEnemy::CollisionProcess(C_BaseOption* pOption)
    {
        C_CollisionProcess::s_OptionAndEnemy(pOption, this);
    }


    /*************************************************************//**
     *
     *  @brief  敵との衝突時処理を行う
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_BaseEnemy::CollisionProcess(C_BaseEnemy* pEnemy)
    {
        C_CollisionProcess::s_EnemyAndEnemy(this, pEnemy);
    }


    /*************************************************************//**
     *
     *  @brief  弾との衝突時処理を行う
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_BaseEnemy::CollisionProcess(C_BaseBullet* pBullet)
    {
        C_CollisionProcess::s_EnemyAndBullet(this, pBullet);
    }


    /*************************************************************//**
     *
     *  @brief  障害物との衝突時処理を行う
     *  @param  障害物
     *  @return なし
     *
     ****************************************************************/
    void C_BaseEnemy::CollisionProcess(C_BaseObstacle* pObstacle)
    {
        C_CollisionProcess::s_EnemyAndObstacle(this, pObstacle);
    }


    /*************************************************************//**
     *
     *  @brief  ボムとの衝突時処理を行う
     *  @param  ボム
     *  @return なし
     *
     ****************************************************************/
    void C_BaseEnemy::CollisionProcess(C_BaseBomb* pBomb)
    {
        C_CollisionProcess::s_EnemyAndBomb(this, pBomb);
    }


     /*************************************************************//**
     *
     *  @brief  シールドとの衝突時処理を行う
     *  @param  シールド
     *  @return なし
     *
     ****************************************************************/
    void C_BaseEnemy::CollisionProcess(C_BaseShield* pShield)
    {
        C_CollisionProcess::s_EnemyAndShield(this, pShield);
    }


    /*************************************************************//**
     *
     *  @brief  射撃処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseEnemy::Shot()
    {
    }
    

    /*************************************************************//**
     *
     *  @brief  マテリアルを設定する
     *  @param  マテリアル
     *  @return なし
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
     *  @brief  メインライトを設定する
     *  @param  ライト
     *  @return なし
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
     *  @brief  出現を終了しているか確認する
     *  @param  なし
     *  @return 終了している場合  ：true
     *  @return 終了していない場合：false
     *
     ****************************************************************/
    bool C_BaseEnemy::IsFinishAdvent() const
    {
        return true;
    }


    /*************************************************************//**
     *
     *  @brief  ステートマシーンを取得する
     *  @param  なし
     *  @return ステートマシーン
     *
     ****************************************************************/
    State::C_StateMachine<C_BaseEnemy>* C_BaseEnemy::GetStateMachine() const
    {
        return upStateMachine_.get();
    }
}