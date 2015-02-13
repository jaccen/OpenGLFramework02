/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Camera/Manager/CameraManager.h"
#include "../../Texture/Manager/TextureManager.h"
#include "../../Shader/GLSL/Object/Manager/GlslObjectManager.h"
#include "../../OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"
#include "../../Math/Vector/Vector4.h"
#include "../../Math/Matrix/Matrix4x4.h"


//-------------------------------------------------------------
//!
//! @brief スプライト
//! @brief スプライト関連の名前空間
//!
//-------------------------------------------------------------
namespace Sprite
{
    /* 前方宣言 */
    class IC_SpriteCreater;


    /* 別名 */
    using Vector2 = Math::S_Vector2<float>;                                                                 // Vector2型
    using Vector3 = Math::S_Vector3<float>;                                                                 // Vector3型
    using Vector4 = Math::S_Vector4<float>;                                                                 // Vector4型
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                                             // Matrix4x4型
    using SpriteCreaterWeakPtr = std::weak_ptr<IC_SpriteCreater>;                                           // SpriteCreaterWeakPtr型


    /** 作成データ */
    struct S_CreateData
    {
        Vector3 position_;                                                                                  ///< @brief 座標
        Vector2 size_;                                                                                      ///< @brief サイズ
        float angle_ = 0.0f;                                                                                ///< @brief 角度
        Vector4 color_;                                                                                     ///< @brief 色
        Vector2 textureUpperLeft_;                                                                          ///< @brief テクスチャの左上座標
        Vector2 textureLowerRight_;                                                                         ///< @brief テクスチャの右下座標

        S_CreateData() = default;                                                                           //!< @brief デフォルトコンストラクタ
        ~S_CreateData() = default;                                                                          //!< @brief デストラクタ

        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  座標
         *  @param  サイズ
         *  @param  角度
         *  @param  色
         *  @param  テクスチャの左上座標
         *  @param  テクスチャの右下座標
         *
         ****************************************************************/
        S_CreateData(const Vector3& rPosition,
                     const Vector2& rSize,
                     float angle,
                     const Vector4& rColor,
                     const Vector2& rTextureUpperLeft,
                     const Vector2& rTextureLowerRight) :

            position_(rPosition),
            size_(rSize),
            angle_(angle),
            color_(rColor),
            textureUpperLeft_(rTextureUpperLeft),
            textureLowerRight_(rTextureLowerRight)

        {
        }
    };


    /* スプライトの頂点 */
    struct S_SpriteVertex
    {
        Vector3 position_;                                                                                  ///< @brief 座標
        Vector2 size_;                                                                                      ///< @brief サイズ
        float angle_ = 0.0f;                                                                                ///< @brief 角度
        Vector4 color_;                                                                                     ///< @brief 色
        Vector2 textureUpperLeft_;                                                                          ///< @brief テクスチャの左上座標
        Vector2 textureLowerRight_;                                                                         ///< @brief テクスチャの右下座標
        Vector2 textureSize_;                                                                               ///< @brief テクスチャのサイズ
    };


    namespace
    {
        /* 固定 */
        namespace Fixed
        {
            /* シェーダー */
            namespace Shader
            {
                const char* s_pVERTEX_FILE_PATH = "Projects/Shaders/GLSL/Sprite/Sprite.vert";               ///< @brief 頂点シェーダーのファイルパス
                const char* s_pGEOMETRY_FILE_PATH = "Projects/Shaders/GLSL/Sprite/Sprite.geom";             ///< @brief ジオメトリシェーダーのファイルパス
                const char* s_pFRAGMENT_FILE_PATH = "Projects/Shaders/GLSL/Sprite/Sprite.frag";             ///< @brief フラグメントシェーダーのファイルパス
                const char* s_pGLSL_OBJECT_ID = "SpriteCreater";                                            ///< @brief シェーダーオブジェクトのID
            }

            /* プリミティブ */
            namespace Primitive
            {
                const char* s_pSPRITE_ID = "SpritePrimitive";                                               ///< @brief スプライト用のプリミティブID
            }

            /* テクスチャ */
            namespace Texture
            {
                const int32_t s_UNIT_NUMBER = 28;                                                           ///< @brief ユニット番号
            }
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief スプライトクリエイター( インターフェース )
    //! @brief スプライトクリエイターのインターフェースクラス
    //!
    //-------------------------------------------------------------
    class IC_SpriteCreater
    {
    public:
        IC_SpriteCreater() = default;                                                                       //!< @brief コンストラクタ
        virtual ~IC_SpriteCreater() = default;                                                              //!< @brief デストラクタ
        virtual void Entry(const Vector3& rPosition,                                                        //!< @brief 登録処理
                           const Vector2& rSize,
                           float angle,
                           const Vector4& rColor,
                           const Vector2& rTextureUpperLeft,
                           const Vector2& rTextureLowerRight) = 0;
        virtual void Entry(const S_CreateData& rCreateData) = 0;                                            //!< @brief 登録処理
        virtual void SetAutoBillboardFlag(bool autoBillboardFlag = true) = 0;                               //!< @brief ビルボードの自動化をさせるフラグを設定
        virtual void SetCamera(const Camera::CameraPtr& prCamera) = 0;                                      //!< @brief カメラを設定
        virtual void SetCameraType(Camera::eType cameraType) = 0;                                           //!< @brief カメラの種類を設定
    };


    //-------------------------------------------------------------
    //!
    //! @brief スプライトクリエイター
    //! @brief スプライトの生成を行うクラス
    //!
    //-------------------------------------------------------------
    class C_SpriteCreater : public IC_SpriteCreater
    {
    public:
        C_SpriteCreater();                                                                                  // コンストラクタ
        virtual ~C_SpriteCreater() override;                                                                // デストラクタ
        bool Initialize(const Camera::CameraPtr& prCamera,                                                  // 初期化処理
                        const Texture::TextureDataPtr& prTextureData,
                        uint32_t maxSpriteCount = 100);
        void Draw();                                                                                        // 描画処理
        void Finalize();                                                                                    // 終了処理
        void Entry(const Vector3& rPosition,                                                                // 登録処理
                   const Vector2& rSize,                                   
                   float angle,                                            
                   const Vector4& rColor,                                  
                   const Vector2& rTextureUpperLeft,                       
                   const Vector2& rTextureLowerRight);                     
        void Entry(const S_CreateData& rCreateData);                                                        // 登録処理
        void SetAutoBillboardFlag(bool autoBillboardFlag = true);                                           // ビルボードの自動化をさせるフラグを設定
        void SetCamera(const Camera::CameraPtr& prCamera);                                                  // カメラを設定
        void SetCameraType(Camera::eType cameraType);                                                       // カメラの種類を設定
    private:
        Shader::GLSL::GlslObjectPtr pGlslObject_;                                                           ///< @brief GLSLオブジェクト
        Camera::CameraPtr pCamera_;                                                                         ///< @brief カメラ
        Texture::TextureDataPtr pTextureData_;                                                              ///< @brief テクスチャ情報
        OpenGL::PrimitiveBufferPtr pPointDatas_;                                                            ///< @brief 点の情報
        std::vector<S_SpriteVertex> vertices_;                                                              ///< @brief 頂点
        uint32_t drawSpriteCount_ = 0;                                                                      ///< @brief 描画するスプライトの数
        Matrix4x4 billboardMatrix_;                                                                         ///< @brief ビルボード行列
        bool autoBillboardFlag_ = true;                                                                     ///< @brief ビルボードの自動化をさせるフラグ
        int32_t subroutineIndices_[2];                                                                      ///< @brief サブルーチンのインデックス
        Camera::eType cameraType_ = Camera::PERSPECTIVE;                                                    ///< @brief カメラの種類

        void SetUniformVariable();                                                                          // ユニフォーム変数を設定
    };
}