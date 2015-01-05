/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Math/Vector/Vector4.h"
#include "../../Texture/TextureDefine.h"


/* 前方宣言 */
namespace Math
{
    template<typename T>
    struct S_Matrix4x4;
};

namespace Camera
{
    class C_PerspectiveCamera;
}


//-------------------------------------------------------------
//!
//! @brief パーティクル
//! @brief パーティクル関連の名前空間
//!
//-------------------------------------------------------------
namespace Particle
{
    /* 別名 */
    using Vector2 = Math::S_Vector2<float>;                                                 // Vector2型
    using Vector3 = Math::S_Vector3<float>;                                                 // Vector3型
    using Vector4 = Math::S_Vector4<float>;                                                 // Vector4型
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                             // Matrix4x4型
    using InterpolationFunction = std::function<float(float, float, float)>;                // InterpolationFunction型


    /** パーティクルデータ */
    struct S_CreateDara
    {
        int32_t lifeFrame_ = 0;                                                             ///< @brief 生存フレーム数
        Vector3 position_;                                                                  ///< @brief 座標
        Vector3 velocity_;                                                                  ///< @brief 速度
        Vector3 startAcceleration_;                                                         ///< @brief 開始時の加速度
        Vector3 endAcceleration_;                                                           ///< @brief 終了時の加速度
        float startAngle_ = 0.0f;                                                           ///< @brief 開始時の角度
        float endAngle_ = 0.0f;                                                             ///< @brief 終了時の角度
        float startWidth_ = 0.0f;                                                           ///< @brief 開始時の幅
        float endWidth_ = 0.0f;                                                             ///< @brief 終了時の幅
        float startHeight_ = 0.0f;                                                          ///< @brief 開始時の高さ
        float endHeight_ = 0.0f;                                                            ///< @brief 終了時の高さ
        Vector4 startColor_;                                                                ///< @brief 開始時の色
        Vector4 endColor_;                                                                  ///< @brief 終了時の色

        S_CreateDara() = default;                                                           //!< @brief デフォルトコンストラクタ
        ~S_CreateDara() = default;                                                          //!< @brief デストラクタ

        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  生存フレーム数
         *  @param  座標
         *  @param  速度
         *  @param  開始時の加速度
         *  @param  終了時の加速度
         *  @param  開始時の角度
         *  @param  終了時の角度
         *  @param  開始時のスケール
         *  @param  終了時のスケール
         *  @param  開始時の色
         *  @param  終了時の色
         *
         ****************************************************************/
        S_CreateDara(int32_t lifeFrame,
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
                     const Vector4& rEndColor) :

            lifeFrame_(lifeFrame),
            position_(rPosition),
            velocity_(rVelocity),
            startAcceleration_(rStartAcceleration),
            endAcceleration_(rEndAcceleration),
            startAngle_(startAngle),
            endAngle_(endAngle),
            startWidth_(startWidth),
            endWidth_(endWidth),
            startHeight_(startHeight),
            endHeight_(endHeight),
            startColor_(rStartColor),
            endColor_(rEndColor)
        {
        }
    };

    namespace
    {
        /* 固定 */
        namespace Fixed
        {
            /* シェーダー */
            namespace Shader
            {
                const char* s_pVERTEX_FILE_PATH = "Projects/Shaders/GLSL/Particle/Particle.vert";               ///< @brief 頂点シェーダーのファイルパス
                const char* s_pGEOMETRY_FILE_PATH = "Projects/Shaders/GLSL/Particle/Particle.geom";             ///< @brief ジオメトリシェーダーのファイルパス
                const char* s_pFRAGMENT_FILE_PATH = "Projects/Shaders/GLSL/Particle/Particle.frag";             ///< @brief フラグメントシェーダーのファイルパス
                const char* s_pGLSL_OBJECT_ID = "ParticleSystem";                                               ///< @brief シェーダーオブジェクトのID
            }

            /* テクスチャ */
            namespace Texture
            {
                const int32_t s_UNIT_NUMBER = 27;                                                               ///< @brief ユニット番号
            }
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief パーティクルシステム( インターフェース )
    //! @brief パーティクルシステムのインターフェース
    //!
    //-------------------------------------------------------------
    class IC_ParticleSystem
    {
    public:
        IC_ParticleSystem() = default;                                                                          // コンストラクタ
        virtual ~IC_ParticleSystem() = default;                                                                 // デストラクタ
        virtual void Entry(int32_t lifeFrame,                                                                   // パーティクルを追加
                           const Vector3& rPosition,
                           const Vector3& rVelocity,
                           const Vector3& rStartAcceleration,
                           const Vector3& rEndAcceleration,
                           float startAngle = 0.0f,
                           float endAngle = 0.0f,
                           float startWidht = 1.0f,
                           float endWidth = 1.0f,
                           float startHeight = 1.0f,
                           float endHeight = 1.0f,
                           const Vector4& rStartColor = Vector4(1.0f),
                           const Vector4& rEndColor = Vector4(1.0f)) = 0;
        virtual void Entry(const S_CreateDara& rCreateData) = 0;                                                // パーティクルの情報からをパーティクルを追加
        virtual void SetMaxParticleCount(uint32_t maxParticleCount) = 0;                                        // パーティクルの最大数を設定
        virtual void EnableAutoBillboard(bool validFlag = true) = 0;                                            // ビルボードの自動化を有効化
        virtual void SetCamera(const std::shared_ptr<Camera::C_PerspectiveCamera>& sprCamera) = 0;              // カメラを設定
        virtual void SetBillboardMatrix(const Matrix4x4& rBillboardMatrix) = 0;                                 // ビルボードさせるための行列を設定
        virtual void SetExternalPower(const Vector3& rExternalPower) = 0;                                       // 外部の力を設定
        virtual void SetModelMatrix(const Matrix4x4& rModelMatrix) = 0;                                         // モデル行列を設定
        virtual void SetTextureHandle(Texture::TextureHandle textureHandle) = 0;                                // テクスチャハンドルを設定
        virtual void SetAccelerationInterpolationFunction(const InterpolationFunction& rFunction) = 0;          // 加速度に用いる補間関数を設定
        virtual void SetAngleInterpolationFunction(const InterpolationFunction& rFunction) = 0;                 // 角度に用いる補間関数を設定
        virtual void SetScaleInterpolationFunction(const InterpolationFunction& rFunction) = 0;                 // スケールに用いる補間関数を設定
        virtual void SetColorInterpolationFunction(const InterpolationFunction& rFunction) = 0;                 // 色に用いる補間関数を設定
        virtual void SetTextureCoordUpperLeft(const Vector2& textureCoordUpperLeft) = 0;                        // テクスチャ座標の左上を設定
        virtual void SetTextureCoordLowerRight(const Vector2& textureCoordLowerRight) = 0;                      // テクスチャ座標の右下を設定
    };


    //-------------------------------------------------------------
    //!
    //! @brief パーティクルステム
    //! @brief パーティクル生成を行うためのクラス
    //!
    //-------------------------------------------------------------
    class C_ParticleSystem : public IC_ParticleSystem
    {
    public:
        C_ParticleSystem();                                                                                 // コンストラクタ
        virtual ~C_ParticleSystem();                                                                        // デストラクタ
        bool Initialize(const std::shared_ptr<Camera::C_PerspectiveCamera>& sprCamera,                      // 初期化処理
                        Texture::TextureHandle textureHandle,
                        uint32_t maxParticleNumber = 10000);
        void Update();                                                                                      // 更新処理
        void Draw();                                                                                        // 描画処理
        void Finalize();                                                                                    // 終了処理
        void Entry(int32_t lifeFrame,                                                                       // パーティクルを追加
                   const Vector3& rPosition,
                   const Vector3& rVelocity,
                   const Vector3& rStartAcceleration,
                   const Vector3& rEndAcceleration,
                   float startAngle = 0.0f,
                   float endAngle = 0.0f,
                   float startWidht = 1.0f,
                   float endWidth = 1.0f,
                   float startHeight = 1.0f,
                   float endHeight = 1.0f,
                   const Vector4& rStartColor = Vector4(1.0f),
                   const Vector4& rEndColor = Vector4(1.0f)) override;
        void Entry(const S_CreateDara& rCreateData) override;                                               // パーティクルの情報からをパーティクルを追加
        void SetMaxParticleCount(uint32_t maxParticleNumber) override;                                      // パーティクルの最大数を設定
        void EnableAutoBillboard(bool validFlag = true) override;                                           // ビルボードの自動化を有効化
        void SetCamera(const std::shared_ptr<Camera::C_PerspectiveCamera>& sprCamera) override;             // カメラを設定
        void SetBillboardMatrix(const Matrix4x4& rBillboardMatrix) override;                                // ビルボードさせるための行列を設定
        void SetExternalPower(const Vector3& rExternalPower) override;                                      // 外部の力を設定
        void SetModelMatrix(const Matrix4x4& rModelMatrix) override;                                        // モデル行列を設定
        void SetTextureHandle(Texture::TextureHandle textureHandle);                                        // テクスチャハンドルを設定
        void SetAccelerationInterpolationFunction(const InterpolationFunction& rFunction);                  // 加速度に用いる補間関数を設定
        void SetAngleInterpolationFunction(const InterpolationFunction& rFunction);                         // 角度に用いる補間関数を設定
        void SetScaleInterpolationFunction(const InterpolationFunction& rFunction);                         // スケールに用いる補間関数を設定
        void SetColorInterpolationFunction(const InterpolationFunction& rFunction);                         // 色に用いる補間関数を設定
        void SetTextureCoordUpperLeft(const Vector2& rTextureCoordUpperLeft);                               // テクスチャ座標の左上を設定
        void SetTextureCoordLowerRight(const Vector2& rTextureCoordLowerRight);                             // テクスチャ座標の右下を設定
    private:
        /* 前方宣言 */
        class C_ParticleSystemImpl;

        std::unique_ptr<C_ParticleSystemImpl> upImpl_;                                                      ///< @brief 実装情報
    };
}