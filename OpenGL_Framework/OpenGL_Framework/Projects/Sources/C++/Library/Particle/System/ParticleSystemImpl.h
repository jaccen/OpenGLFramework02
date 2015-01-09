/* ヘッダファイル */
#include "ParticleSystem.h"
#include "../../Texture/Manager/TextureManager.h"
#include "../../Math/Matrix/Matrix4x4.h"
#include "../../Math/Easing/Easing.h"
#include "../../Shader/GLSL/Object/Manager/GlslObjectManager.h"
#include "../../OpenGL/Manager/OpenGlManager.h"
#include "../../Debug/Helper/DebugHelper.h"
#include "../../Camera/Camera/Perspective/PerspectiveCamera.h"
#include <vector>
#include <forward_list>


//-------------------------------------------------------------
//!
//! @brief パーティクル
//! @brief パーティクル関連の名前空間
//!
//-------------------------------------------------------------
namespace Particle
{
    /* 別名 */
    using VertexArrayObjectHandle = GLuint;                                                     // VertexArrayObjectHandle型
    using VertexBufferObjectHandle = GLuint;                                                    // VertexBufferObjectHandle型


    /** パーティクル情報 */
    struct S_ParticleInfo
    {
        int32_t lifeFrame_ = 0;                                                                 ///< @brief 生存フレーム数
        int32_t elapsedFrame_ = 0;                                                              ///< @brief 経過フレーム数
        Vector3 position_;                                                                      ///< @brief 座標
        Vector3 velocity_;                                                                      ///< @brief 速度
        Vector3 acceleration_;                                                                  ///< @brief 加速度
        Vector3 startAcceleration_;                                                             ///< @brief 開始時の加速度
        Vector3 endAcceleration_;                                                               ///< @brief 終了時の加速度
        float angle_ = 0.0f;                                                                    ///< @brief 角度
        float startAngle_ = 0.0f;                                                               ///< @brief 開始時の角度
        float endAngle_ = 0.0f;                                                                 ///< @brief 終了時の角度
        float width_ = 0.0f;                                                                    ///< @brief 幅
        float startWidth_ = 0.0f;                                                               ///< @brief 開始時の幅
        float endWidth_ = 0.0f;                                                                 ///< @brief 終了時の幅
        float height_ = 0.0f;                                                                   ///< @brief 高さ
        float startHeight_ = 0.0f;                                                              ///< @brief 開始時の高さ
        float endHeight_ = 0.0f;                                                                ///< @brief 開始時の高さ
        Vector4 color_;                                                                         ///< @brief 色
        Vector4 startColor_;                                                                    ///< @brief 開始時の色
        Vector4 endColor_;                                                                      ///< @brief 終了時の色

        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  生存フレーム数
         *  @param  経過フレーム数
         *  @param  座標
         *  @param  速度
         *  @param  加速度
         *  @param  開始時の加速度
         *  @param  終了時の加速度
         *  @param  角度
         *  @param  開始時の角度
         *  @param  終了時の角度
         *  @param  スケール
         *  @param  開始時のスケール
         *  @param  終了時のスケール
         *  @param  色
         *  @param  開始時の色
         *  @param  終了時の色
         *
         ****************************************************************/
        S_ParticleInfo(int32_t lifeFrame,
                       int32_t elapsedFrame,
                       const Vector3& rPosition,
                       const Vector3& rVelocity,
                       const Vector3& rAcceleration,
                       const Vector3& rStartAcceleration,
                       const Vector3& rEndAcceleration,
                       float angle,
                       float startAngle,
                       float endAngle,
                       float width,
                       float startWidth,
                       float endWidth,
                       float height,
                       float startHeight,
                       float endHeight,
                       const Vector4& rColor,
                       const Vector4& rStartColor,
                       const Vector4& rEndColor) :

                       // 各情報を設定
                       lifeFrame_(lifeFrame),
                       elapsedFrame_(elapsedFrame),
                       position_(rPosition),
                       velocity_(rVelocity),
                       acceleration_(rAcceleration),
                       startAcceleration_(rStartAcceleration),
                       endAcceleration_(rEndAcceleration),
                       angle_(angle),
                       startAngle_(startAngle),
                       endAngle_(endAngle),
                       width_(width),
                       startWidth_(startWidth),
                       endWidth_(endWidth),
                       height_(height),
                       startHeight_(startHeight),
                       endHeight_(endHeight),
                       color_(rColor),
                       startColor_(rStartColor),
                       endColor_(rEndColor)
        {
        }
    };


    /** パーティクルの頂点情報 */
    struct S_ParticleVertex
    {
        Vector3 position_;                                                                              ///< @brief 座標
        float angle_ = 0.0f;                                                                            ///< @brief 角度
        float width_ = 0.0f;                                                                            ///< @brief 幅
        float height_ = 0.0f;                                                                           ///< @brief 高さ
        Vector4 color_;                                                                                 ///< @brief 色
    };

    //-------------------------------------------------------------
    //!
    //! @brief パーティクルステムインプリメント
    //! @brief パーティクシステムのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_ParticleSystem::C_ParticleSystemImpl
    {
    private:
        
    public:
        C_ParticleSystemImpl();                                                                         // コンストラクタ  
        ~C_ParticleSystemImpl();                                                                        // デストラクタ
        bool Initialize(const Camera::CameraPtr& prCamera,                                              // 初期化処理
                        Texture::TextureHandle textureHandle,
                        uint32_t maxParticleCount);
        void Update();                                                                                  // 更新処理
        void Draw();                                                                                    // 描画処理
        void Finalize();                                                                                // 終了処理
        void Entry(const S_CreateDara& rCreateData);                                                    // 登録処理
        void SetMaxParticleCount(uint32_t maxParticleNumber);                                           // パーティクルの最大数を設定
        void EnableModelMatrix(bool validFlag);                                                         // モデル行列を有効化
        void EnableAutoBillboard(bool validFlag);                                                       // ビルボードの自動化を有効化
        void SetCamera(const Camera::CameraPtr& prCamera);                                              // カメラを設定
        void SetModelMatrix(const Matrix4x4& rModelMatrix);                                             // モデル行列を設定
        void SetBillboardMatrix(const Matrix4x4& rBillboardMatrix);                                     // ビルボードさせるための行列を設定
        void SetExternalPower(const Vector3& rExternalPower);                                           // 外部の力を設定
        void SetTextureHandle(Texture::TextureHandle textureHandle);                                    // テクスチャハンドルを設定
        void SetAccelerationInterpolationFunction(const InterpolationFunction& rFunction);              // 加速度に用いる補間関数を設定
        void SetAngleInterpolationFunction(const InterpolationFunction& rFunction);                     // 角度に用いる補間関数を設定
        void SetScaleInterpolationFunction(const InterpolationFunction& rFunction);                     // スケールに用いる補間関数を設定
        void SetColorInterpolationFunction(const InterpolationFunction& rFunction);                     // 色に用いる補間関数を設定
        virtual void SetTextureCoordUpperLeft(const Vector2& textureCoordUpperLeft);                    // テクスチャ座標の左上を設定
        virtual void SetTextureCoordLowerRight(const Vector2& textureCoordLowerRight);                  // テクスチャ座標の右下を設定
    private:
        std::string id_;                                                                                ///< @brief ID
        std::forward_list<S_ParticleInfo> infoList_;                                                    ///< @brief 情報のリスト
        Shader::GLSL::GlslObjectPtr pGlslObject_;                                                       ///< @brief GLSLオブジェクト
        Vector3 externalPower_;                                                                         ///< @brief 外部の力
        std::vector<S_ParticleVertex> vertices_;                                                        ///< @brief 頂点データ
        VertexBufferObjectHandle vertexBufferObjectHandle_ = 0;                                         ///< @brief 頂点バッファオブジェクトハンドル
        VertexArrayObjectHandle vertexArrayObjectHandle_ = 0;                                           ///< @brief 頂点配列オブジェクトハンドル
        Camera::CameraPtr pCamera_;                                                                     ///< @brief カメラ
        Matrix4x4 modelMatrix_;                                                                         ///< @brief モデル行列
        Matrix4x4 billboardMatrix_;                                                                     ///< @brief ビルボードさせるための行列
        bool autoBillboardFlag_ = true;                                                                 ///< @brief ビルボードの自動化をさせるフラグ
        Texture::TextureHandle textureHandle_ = 0;                                                      ///< @brief テクスチャハンドル
        uint32_t drawParticleCount_ = 0;                                                                ///< @brief 描画するパーティクルのカウンタ
        InterpolationFunction accelerationInterpolationFunction_ = Math::C_Easing<float>::s_Linear;     ///< @brief 加速度に用いる補間関数
        InterpolationFunction angleInterpolationFunction_ = Math::C_Easing<float>::s_Linear;            ///< @brief 角度に用いる補間関数
        InterpolationFunction scaleInterpolationFunction_ = Math::C_Easing<float>::s_Linear;            ///< @brief スケールに用いる補間関数
        InterpolationFunction colorInterpolationFunction_ = Math::C_Easing<float>::s_Linear;            ///< @brief 色に用いる補間関数
        Vector2 textureCoordUpperLeft_ = Vector2(0.0f);                                                 ///< @brief テクスチャ座標の左上
        Vector2 textureCoordLowerRight_ = Vector2(1.0f);                                                ///< @brief テクスチャ座標の右下

        void CreateVertexArrayObject();                                                                 // 頂点配列オブジェクトを作成
        void DeleteVertexArrayObject();                                                                 // 頂点配列オブジェクトを破棄
        void RewriteVertex();                                                                           // 頂点データの書き換え
        void AddParticle(const Vector3& rPosition,                                                      // パーティクルの追加処理
                         float angle,
                         float width,
                         float height,
                         const Vector4& rColor);
        void ResetParticle();                                                                           // 描画するパーティクルのリセット
        bool UpdateParticle(S_ParticleInfo& rInfo);                                                     // パーティクルの更新処理
        void SetUniformVariable();                                                                      // ユニフォーム変数を設定
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_ParticleSystem::C_ParticleSystemImpl::C_ParticleSystemImpl() :

        // GLSLオブジェクト
        pGlslObject_(std::make_shared<Shader::GLSL::C_GlslObject>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_ParticleSystem::C_ParticleSystemImpl::~C_ParticleSystemImpl()
    {
        if (vertexArrayObjectHandle_ != 0) Finalize();
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
    bool C_ParticleSystem::C_ParticleSystemImpl::Initialize(const Camera::CameraPtr& prCamera,
                                                            Texture::TextureHandle textureHandle,
                                                            uint32_t maxParticleCount)
    {
        // GLSLオブジェクトを作成し、登録
        if (!Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID))
        {
            auto pGlslObject = Shader::GLSL::C_GlslObject::s_Create();

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pVERTEX_FILE_PATH, Shader::GLSL::Type::s_VERTEX) == false)
            {
                PrintLog("[ C_ParticleSystemImpl::Initialize ] : 頂点シェーダーのコンパイルに失敗しました。\n");

                return false;
            }

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pGEOMETRY_FILE_PATH, Shader::GLSL::Type::s_GEOMETRY) == false)
            {
                PrintLog("[ C_ParticleSystemImpl::Initialize ] : ジオメトリシェーダーのコンパイルに失敗しました。\n");

                return false;
            }

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pFRAGMENT_FILE_PATH, Shader::GLSL::Type::s_FRAGMENT) == false)
            {
                PrintLog("[ C_ParticleSystemImpl::Initialize ] : フラグメントシェーダーのコンパイルに失敗しました。\n");

                return false;
            }

            if (pGlslObject->Link() == false)
            {
                PrintLog("[ C_ParticleSystemImpl::Initialize ] : シェーダーのリンクに失敗しました。\n");

                return false;
            }

            // GLSLオブジェクトを保持し、登録
            pGlslObject_ = pGlslObject;
            Shader::GLSL::C_GlslObjectManager::s_GetInstance()->Entry(pGlslObject_, Fixed::Shader::s_pGLSL_OBJECT_ID);
        }
        else
        {
            pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID).get();
        }

        // テクスチャユニットを設定
        pGlslObject_->Begin();
        pGlslObject_->SetUniform1i("texture", Fixed::Texture::s_UNIT_NUMBER);
        pGlslObject_->End();

        // 頂点配列オブジェクトを作成
        CreateVertexArrayObject();

        // カメラとテクスチャハンドルを設定
        SetCamera(prCamera);
        SetTextureHandle(textureHandle);

        // 頂点の領域を確保
        vertices_.resize(maxParticleCount);

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
    void C_ParticleSystem::C_ParticleSystemImpl::Update()
    {
        // 描画するパーティクルをリセット
        ResetParticle();

        // ループカウンタ
        int32_t loopCount = 0;

        // イテレータ
        auto iterator = infoList_.begin();

        // パーティクルの更新
        while (iterator != infoList_.end())
        {
            if (UpdateParticle(*iterator) == false)
            {
                iterator = infoList_.erase_after(std::next(infoList_.before_begin(), loopCount));
                continue;
            }

            ++iterator;
            ++loopCount;
        }
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::Draw()
    {
        // 頂点の書き換え
        RewriteVertex();

        // シェーダーの使用開始
        pGlslObject_->Begin();

        // ユニフォーム変数を設定
        SetUniformVariable();

        // テクスチャマネージャーとOpenGLマネージャーを取得
        auto pTextureManager = Texture::C_TextureManager::s_GetInstance();
        auto pOpenGlManager = OpenGL::C_OpenGlManager::s_GetInstance();

        // ブレンドを有効化し、ブレンドに使用する関数を設定
        pOpenGlManager->EnableBlend(true);
        pOpenGlManager->SetBlendFunction(OpenGL::BlendFactor::s_SOURCE_ALPHA, OpenGL::BlendFactor::s_ALL_ONE);

        // カリングを無効化
        pOpenGlManager->EnableCulling(false);

        // 深度のマスクを有効化
        pOpenGlManager->EnableDepthMask(true);

        // アクティブなテクスチャユニットを設定し、テクスチャをバインド
        pTextureManager->SetActiveUnit(Fixed::Texture::s_UNIT_NUMBER);
        pTextureManager->Bind(Texture::Type::s_2D, textureHandle_);

        // パーティクルを描画
        const int32_t BYTE_OFFSET = 0;

        glBindVertexArray(vertexArrayObjectHandle_);
        ::glDrawArrays(GL_POINTS, BYTE_OFFSET, drawParticleCount_);
        glBindVertexArray(0);


        // 深度のマスクを無効化
        pOpenGlManager->EnableDepthMask(false);

        // カリングを有効化
        pOpenGlManager->EnableCulling(true);

        // ブレンドを無効化
        pOpenGlManager->EnableBlend(false);

        // テクスチャをアンバインド
        pTextureManager->Unbind(Texture::Type::s_2D);

        // シェーダーの使用終了
        pGlslObject_->End();
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::Finalize()
    {
        // 頂点配列オブジェクトを破棄
        DeleteVertexArrayObject();

        // 情報のリストと頂点を削除
        infoList_.clear();
        vertices_.clear();

        // 描画するパーティクルの数をリセット
        drawParticleCount_ = 0;

        // GLSLオブジェクトの管理を破棄
        pGlslObject_.reset();
    }


    /*************************************************************//**
     *
     *  @brief  登録処理を行う
     *  @param  生成情報
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::Entry(const S_CreateDara& rCreateData)
    {
        // 最大数を超えていた場合は何もしない
        if (drawParticleCount_ >= vertices_.size()) return;

        // 情報をリストに追加
        const int32_t ELAPSED_FRAME = 0;

        infoList_.emplace_front(rCreateData.lifeFrame_,
                                ELAPSED_FRAME,
                                rCreateData.position_,
                                rCreateData.velocity_,
                                rCreateData.startAcceleration_,
                                rCreateData.startAcceleration_,
                                rCreateData.endAcceleration_,
                                rCreateData.startAngle_,
                                rCreateData.startAngle_,
                                rCreateData.endAngle_,
                                rCreateData.startWidth_,
                                rCreateData.startWidth_,
                                rCreateData.endWidth_,
                                rCreateData.startHeight_,
                                rCreateData.startHeight_,
                                rCreateData.endHeight_,
                                rCreateData.startColor_,
                                rCreateData.startColor_,
                                rCreateData.endColor_);

        // パーティクルを追加
        AddParticle(rCreateData.position_, rCreateData.startAngle_, rCreateData.startWidth_, rCreateData.startHeight_, rCreateData.startColor_);
    }


    /*************************************************************//**
     *
     *  @brief  パーティクルの最大数の設定を行う
     *  @param  パーティクルの最大数
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetMaxParticleCount(uint32_t maxParticleCount)
    {
        // 頂点の領域を再確保
        vertices_.resize(maxParticleCount);

        // 頂点配列オブジェクトを作成し直す
        DeleteVertexArrayObject();
        CreateVertexArrayObject();

        // 更新処理
        Update();
    }


    /*************************************************************//**
     *
     *  @brief  ビルボードの自動化を有効化する
     *  @param  有効化を判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::EnableAutoBillboard(bool validFlag)
    {
        autoBillboardFlag_ = validFlag;
    }


    /*************************************************************//**
     *
     *  @brief  カメラを設定する
     *  @param  カメラ
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetCamera(const Camera::CameraPtr& prCamera)
    {
        pCamera_ = prCamera;
    }


    /*************************************************************//**
     *
     *  @brief  モデル行列を設定する
     *  @param  モデル行列
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetModelMatrix(const Matrix4x4& rModelMatrix)
    {
        modelMatrix_ = rModelMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  ビルボードさせるための行列を設定する
     *  @param  ビルボードさせるための行列
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetBillboardMatrix(const Matrix4x4& rBillboardMatrix)
    {
        billboardMatrix_ = rBillboardMatrix;
        autoBillboardFlag_ = false;
    }


    /*************************************************************//**
     *
     *  @brief  外部の力を設定する
     *  @param  外部の力
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetExternalPower(const Vector3& rExternalPower)
    {
        externalPower_ = rExternalPower;
    }


    /*************************************************************//**
     *
     *  @brief  テクスチャハンドルを設定する
     *  @param  テクスチャハンドル
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetTextureHandle(Texture::TextureHandle textureHandle)
    {
        textureHandle_ = textureHandle;
    }


    /*************************************************************//**
     *
     *  @brief  加速度に用いる補間関数を設定する
     *  @param  加速度に用いる補間関数
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetAccelerationInterpolationFunction(const InterpolationFunction& rFunction)
    {
        accelerationInterpolationFunction_ = rFunction;
    }


    /*************************************************************//**
     *
     *  @brief  角度に用いる補間関数を設定する
     *  @param  角度に用いる補間関数
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetAngleInterpolationFunction(const InterpolationFunction& rFunction)
    {
        angleInterpolationFunction_ = rFunction;
    }


    /*************************************************************//**
     *
     *  @brief  スケールに用いる補間関数を設定する
     *  @param  スケールに用いる補間関数
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetScaleInterpolationFunction(const InterpolationFunction& rFunction)
    {
        scaleInterpolationFunction_ = rFunction;
    }


    /*************************************************************//**
     *
     *  @brief  色に用いる補間関数を設定する
     *  @param  色に用いる補間関数
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetColorInterpolationFunction(const InterpolationFunction& rFunction)
    {
        colorInterpolationFunction_ = rFunction;
    }


    /*************************************************************//**
     *
     *  @brief  テクスチャ座標の左上を設定
     *  @param  テクスチャ座標の左上
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetTextureCoordUpperLeft(const Vector2& rTextureCoordUpperLeft)
    {
        textureCoordUpperLeft_ = rTextureCoordUpperLeft;
    }


    /*************************************************************//**
     *
     *  @brief  テクスチャ座標の右下を設定
     *  @param  テクスチャ座標の右下
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetTextureCoordLowerRight(const Vector2& rTextureCoordLowerRight)
    {
        textureCoordLowerRight_ = rTextureCoordLowerRight;
    }


    /*************************************************************//**
     *
     *  @brief  頂点配列オブジェクトを作成する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::CreateVertexArrayObject()
    {
        // 頂点バッファのインデックス
        GLuint vertexBufferIndex = 0;

        // バイトの総数
        const int32_t BYTE_TOTAL_NUMBER = sizeof(S_ParticleVertex);

        // 頂点バッファオブジェクトを作成
        const int32_t CREATE_VERTEX_BUFFER_OBJECT_NUMBER = 1;
        glGenBuffers(CREATE_VERTEX_BUFFER_OBJECT_NUMBER, &vertexBufferObjectHandle_);

        // 頂点バッファをバインドし、全てのデータを転送
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectHandle_);
        glBufferData(GL_ARRAY_BUFFER, vertices_.size() * BYTE_TOTAL_NUMBER, vertices_.data(), OpenGL::Modify::s_DYNAMIC);

        // 頂点配列オブジェクトを作成し、バインド
        const int32_t CREATE_VERTEX_ARRAY_OBJECT_NUMBER = 1;
        glGenVertexArrays(CREATE_VERTEX_ARRAY_OBJECT_NUMBER, &vertexArrayObjectHandle_);
        glBindVertexArray(vertexArrayObjectHandle_);

        // 頂点配列オブジェクトに座標をバインド
        const int32_t POSITION_ELEMENT_NUMBER = 3;
        const int32_t POSITION_BYTE_OFFSET = 0;

        glEnableVertexAttribArray(vertexBufferIndex);
        glVertexAttribPointer(vertexBufferIndex, POSITION_ELEMENT_NUMBER, GL_FLOAT, GL_FALSE, BYTE_TOTAL_NUMBER, reinterpret_cast<GLubyte*>(POSITION_BYTE_OFFSET));
        ++vertexBufferIndex;

        // 頂点配列オブジェクトに角度をバインド
        const int32_t ANGLE_ELEMENT_NUMBER = 1;
        const int32_t ANGLE_BYTE_OFFSET = sizeof(float)* POSITION_ELEMENT_NUMBER;

        glEnableVertexAttribArray(vertexBufferIndex);
        glVertexAttribPointer(vertexBufferIndex, ANGLE_ELEMENT_NUMBER, GL_FLOAT, GL_FALSE, BYTE_TOTAL_NUMBER, reinterpret_cast<GLubyte*>(ANGLE_BYTE_OFFSET));
        ++vertexBufferIndex;

        // 頂点配列オブジェクトに幅と高さをバインド
        const int32_t WIDTH_ELEMENT_NUMBER = 1;
        const int32_t WIDTH_BYTE_OFFSET = ANGLE_BYTE_OFFSET + sizeof(float)* ANGLE_ELEMENT_NUMBER;

        glEnableVertexAttribArray(vertexBufferIndex);
        glVertexAttribPointer(vertexBufferIndex, WIDTH_ELEMENT_NUMBER, GL_FLOAT, GL_FALSE, BYTE_TOTAL_NUMBER, reinterpret_cast<GLubyte*>(WIDTH_BYTE_OFFSET));
        ++vertexBufferIndex;

        const int32_t HEIGHT_ELEMENT_NUMBER = 1;
        const int32_t HEIGHT_BYTE_OFFSET = WIDTH_BYTE_OFFSET + sizeof(float)* WIDTH_ELEMENT_NUMBER;

        glEnableVertexAttribArray(vertexBufferIndex);
        glVertexAttribPointer(vertexBufferIndex, HEIGHT_ELEMENT_NUMBER, GL_FLOAT, GL_FALSE, BYTE_TOTAL_NUMBER, reinterpret_cast<GLubyte*>(HEIGHT_BYTE_OFFSET));
        ++vertexBufferIndex;

        // 頂点配列オブジェクトに色をバインド
        const int32_t COLOR_ELEMENT_NUMBER = 4;
        const int32_t COLOR_BYTE_OFFSET = HEIGHT_BYTE_OFFSET + sizeof(float)* HEIGHT_ELEMENT_NUMBER;

        glEnableVertexAttribArray(vertexBufferIndex);
        glVertexAttribPointer(vertexBufferIndex, COLOR_ELEMENT_NUMBER, GL_FLOAT, GL_FALSE, BYTE_TOTAL_NUMBER, reinterpret_cast<GLubyte*>(COLOR_BYTE_OFFSET));

        // 各オブジェクトをアンバインド
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }


    /*************************************************************//**
     *
     *  @brief  頂点配列オブジェクトを破棄する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::DeleteVertexArrayObject()
    {
        // 各バッファを削除
        glDeleteBuffers(1, &vertexBufferObjectHandle_);
        glDeleteVertexArrays(1, &vertexArrayObjectHandle_);

        vertexArrayObjectHandle_ = 0;
        vertexBufferObjectHandle_ = 0;
    }


    /*************************************************************//**
     *
     *  @brief  頂点データの書き換えを行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::RewriteVertex()
    {
        assert(vertexBufferObjectHandle_ != 0);

        // 頂点バッファオブジェクトをバインドし、マップ
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectHandle_);
        S_ParticleVertex* pVertices = reinterpret_cast<S_ParticleVertex*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

        for (size_t i = 0; i < drawParticleCount_; ++i) pVertices[i] = vertices_[i];

        // 頂点バッファをアンマップし、アンバインド
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    /*************************************************************//**
     *
     *  @brief  パーティクルの追加を行う
     *  @param  座標
     *  @param  角度
     *  @param  幅
     *  @param  高さ
     *  @param  色
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::AddParticle(const Vector3& rPosition,
                                                             float angle,
                                                             float width,
                                                             float height,
                                                             const Vector4& rColor)
    {
        // 頂点情報を設定し、描画するパーティクルの数を1増加
        auto& vertex = vertices_[drawParticleCount_];

        vertex.position_ = rPosition;
        vertex.angle_ = angle;
        vertex.width_ = width;
        vertex.height_ = height;
        vertex.color_ = rColor;

        ++drawParticleCount_;
    }


    /*************************************************************//**
     *
     *  @brief  描画するパーティクルをリセットする
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::ResetParticle()
    {
        drawParticleCount_ = 0;
    }


    /*************************************************************//**
     *
     *  @brief  パーティクルの更新処理を行う
     *  @param  パーティクルの情報
     *  @return パーティクルを続行：true
     *  @return パーティクルを終了：false
     *
     ****************************************************************/
    bool C_ParticleSystem::C_ParticleSystemImpl::UpdateParticle(S_ParticleInfo& rInfo)
    {
        // 経過フレーム数を1増やし、生存フレーム数に達していないか確認する
        ++rInfo.elapsedFrame_;
        if (rInfo.elapsedFrame_ > rInfo.lifeFrame_) return false;

        // 補間係数を求める
        float coefficient = static_cast<float>(rInfo.elapsedFrame_) / static_cast<float>(rInfo.lifeFrame_);

        // 速度に加速度と外部の力を加える
        rInfo.velocity_.x_ += accelerationInterpolationFunction_(rInfo.startAcceleration_.x_, rInfo.endAcceleration_.x_, coefficient);
        rInfo.velocity_.y_ += accelerationInterpolationFunction_(rInfo.startAcceleration_.y_, rInfo.endAcceleration_.y_, coefficient);
        rInfo.velocity_.z_ += accelerationInterpolationFunction_(rInfo.startAcceleration_.z_, rInfo.endAcceleration_.z_, coefficient);
        rInfo.velocity_ += externalPower_;

        // 座標に速度を加える
        rInfo.position_ += rInfo.velocity_;

        // 角度・幅・高さを求める
        rInfo.angle_ = angleInterpolationFunction_(rInfo.startAngle_, rInfo.endAngle_, coefficient);
        rInfo.width_ = scaleInterpolationFunction_(rInfo.startWidth_, rInfo.endWidth_, coefficient);
        rInfo.height_ = scaleInterpolationFunction_(rInfo.startHeight_, rInfo.endHeight_, coefficient);

        // 色を求める
        rInfo.color_.red_ = colorInterpolationFunction_(rInfo.startColor_.red_, rInfo.endColor_.red_, coefficient);
        rInfo.color_.green_ = colorInterpolationFunction_(rInfo.startColor_.green_, rInfo.endColor_.green_, coefficient);
        rInfo.color_.blue_ = colorInterpolationFunction_(rInfo.startColor_.blue_, rInfo.endColor_.blue_, coefficient);
        rInfo.color_.alpha_ = colorInterpolationFunction_(rInfo.startColor_.alpha_, rInfo.endColor_.alpha_, coefficient);

        // パーティクルを追加
        AddParticle(rInfo.position_, rInfo.angle_, rInfo.width_, rInfo.height_, rInfo.color_);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  ユニフォーム変数の設定を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystem::C_ParticleSystemImpl::SetUniformVariable()
    {
        // ビルボードを自動化するフラグが立っている場合、
        // ビュー行列からビルボードさせる行列を求める
        if (autoBillboardFlag_ == true)
        {
            billboardMatrix_ = pCamera_->GetViewMatrix();

            std::swap(billboardMatrix_.a12_, billboardMatrix_.a21_);
            std::swap(billboardMatrix_.a13_, billboardMatrix_.a31_);
            std::swap(billboardMatrix_.a23_, billboardMatrix_.a32_);

            billboardMatrix_.a41_ = 0.0f;
            billboardMatrix_.a42_ = 0.0f;
            billboardMatrix_.a43_ = 0.0f;
        }

        // 各行列を設定
        pGlslObject_->SetUniformMatrix4x4("modelMatrix", modelMatrix_);
        pGlslObject_->SetUniformMatrix4x4("viewProjectionMatrix", pCamera_->GetViewProjectionMatrix());
        pGlslObject_->SetUniformMatrix4x4("billboardMatrix", billboardMatrix_);
        pGlslObject_->SetUniformVector2("textureCoordUpperLeft", textureCoordUpperLeft_);
        pGlslObject_->SetUniformVector2("textureCoordLowerRight", textureCoordLowerRight_);
    }
}