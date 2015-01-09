/* ヘッダファイル */
#include "ParticleSystemImpl.h"


//-------------------------------------------------------------
//!
//! @brief パーティクル
//! @brief パーティクル関連の名前空間
//!
//-------------------------------------------------------------
namespace Particle
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_ParticleSystem::C_ParticleSystem() :

        // 実装情報
        upImpl_(std::make_unique<C_ParticleSystemImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_ParticleSystem::~C_ParticleSystem()
    {
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  カメラ
     *  @param  テクスチャハンドル
     *  @param  パーティクルの最大数
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_ParticleSystem::Initialize(const Camera::CameraPtr& prCamera,
                                      Texture::TextureHandle textureHandle,
                                      uint32_t maxParticleCount)
    {
        if (upImpl_->Initialize(prCamera, textureHandle, maxParticleCount) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    void C_ParticleSystem::Update()
    {
        upImpl_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::Draw()
    {
        upImpl_->Draw();
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::Finalize()
    {
        upImpl_->Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  登録処理を行う
     *  @param  生存フレーム数
     *  @param  座標
     *  @param  速度
     *  @param  開始時の加速度
     *  @param  終了時の加速度
     *  @param  開始時の角度( ラジアン値 )
     *  @param  終了時の角度( ラジアン値 )
     *  @param  開始時の幅
     *  @param  終了時の幅
     *  @param  開始時の高さ
     *  @param  終了時の高さ
     *  @param  開始時の色
     *  @param  終了時の色
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::Entry(int32_t lifeFrame,
                                 const Vector3& rPosition,
                                 const Vector3& rVelocity,
                                 const Vector3& rStartAcceleration,
                                 const Vector3& rEndAcceleration,
                                 float startAngle,
                                 float endAngle,
                                 float startWidth,
                                 float endWidth,
                                 float startHeight,
                                 float endHeight,
                                 const Vector4& rStartColor,
                                 const Vector4& rEndColor)
    {
        upImpl_->Entry(S_CreateDara(lifeFrame,
                                    rPosition,
                                    rVelocity,
                                    rStartAcceleration,
                                    rEndAcceleration,
                                    startAngle,
                                    endAngle,
                                    startWidth,
                                    endWidth,
                                    startHeight,
                                    endHeight,
                                    rStartColor,
                                    rEndColor));
    }


    /*************************************************************//**
     *
     *  @brief  登録処理を行う
     *  @param  生成情報
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::Entry(const S_CreateDara& rCreateData)
    {
        upImpl_->Entry(rCreateData);
    }


    /*************************************************************//**
     *
     *  @brief  パーティクルの最大数の設定を行う
     *  @param  パーティクルの最大数
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::SetMaxParticleCount(uint32_t maxParticleCount)
    {
        upImpl_->SetMaxParticleCount(maxParticleCount);
    }


    /*************************************************************//**
     *
     *  @brief  ビルボードの自動化を有効化する
     *  @param  有効化を判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::EnableAutoBillboard(bool validFlag)
    {

    }


    /*************************************************************//**
     *
     *  @brief  カメラを設定する
     *  @param  カメラ
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::SetCamera(const Camera::CameraPtr& prCamera)
    {
        upImpl_->SetCamera(prCamera);
    }


    /*************************************************************//**
     *
     *  @brief  モデル行列を設定する
     *  @param  モデル行列
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::SetModelMatrix(const Matrix4x4& rModelMatrix)
    {
        upImpl_->SetModelMatrix(rModelMatrix);
    }


    /*************************************************************//**
     *
     *  @brief  ビルボードさせるための行列を設定する
     *  @param  ビルボードさせるための行列
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::SetBillboardMatrix(const Matrix4x4& rBillboardMatrix)
    {
        upImpl_->SetBillboardMatrix(rBillboardMatrix);
    }


    /*************************************************************//**
     *
     *  @brief  外部の力を設定する
     *  @param  外部の力
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::SetExternalPower(const Vector3& rExternalPower)
    {
        upImpl_->SetExternalPower(rExternalPower);
    }


    /*************************************************************//**
     *
     *  @brief  テクスチャハンドルを設定する
     *  @param  テクスチャハンドル
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::SetTextureHandle(Texture::TextureHandle textureHandle)
    {
        upImpl_->SetTextureHandle(textureHandle);
    }


    /*************************************************************//**
     *
     *  @brief  加速度に用いる補間関数を設定する
     *  @param  加速度に用いる補間関数
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::SetAccelerationInterpolationFunction(const InterpolationFunction& rFunction)
    {
        upImpl_->SetAccelerationInterpolationFunction(rFunction);
    }


    /*************************************************************//**
     *
     *  @brief  角度に用いる補間関数を設定する
     *  @param  角度に用いる補間関数
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::SetAngleInterpolationFunction(const InterpolationFunction& rFunction)
    {
        upImpl_->SetAngleInterpolationFunction(rFunction);
    }


    /*************************************************************//**
     *
     *  @brief  スケールに用いる補間関数を設定する
     *  @param  スケールに用いる補間関数
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::SetScaleInterpolationFunction(const InterpolationFunction& rFunction)
    {
        upImpl_->SetScaleInterpolationFunction(rFunction);
    }


    /*************************************************************//**
     *
     *  @brief  色に用いる補間関数を設定する
     *  @param  色に用いる補間関数
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::SetColorInterpolationFunction(const InterpolationFunction& rFunction)
    {
        upImpl_->SetColorInterpolationFunction(rFunction);
    }


    /*************************************************************//**
     *
     *  @brief  テクスチャ座標の左上を設定
     *  @param  テクスチャ座標の左上
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::SetTextureCoordUpperLeft(const Vector2& rTextureCoordUpperLeft)
    {
        upImpl_->SetTextureCoordUpperLeft(rTextureCoordUpperLeft);
    }


    /*************************************************************//**
     *
     *  @brief  テクスチャ座標の右下を設定
     *  @param  テクスチャ座標の右下
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::SetTextureCoordLowerRight(const Vector2& rTextureCoordLowerRight)
    {
        upImpl_->SetTextureCoordLowerRight(rTextureCoordLowerRight);
    }
}