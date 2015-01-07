/* 二重インクルード防止 */
#pragma once


#include "../../Library/Math/Vector/Vector4.h"
#include "../../Library/Math/Matrix/Matrix4x4.h"
#include "../../Library/GameObject/Message/Telegram/Telegram.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* 型変換 */
    using Vector2 = Math::S_Vector2<float>;                                                     // Vector2型
    using Vector3 = Math::S_Vector3<float>;                                                     // Vector3型    
    using Vector4 = Math::S_Vector4<float>;                                                     // Vector4型
    using Matrix3x3 = Math::S_Matrix3x3<float>;                                                 // Matrix3x3型
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                                 // Matrix4x4型
    using Telegram = GameObject::Message::S_Telegram;                                           // Telegram型


    /** カメラの情報 */
    struct S_CameraData
    {
        Matrix4x4 viewMatrix_;                                                                  ///< @brief ビュー行列
        Matrix4x4 projectionMatrix_;                                                            ///< @brief プロジェクション行列
        Matrix4x4 viewProjectionMatrix_;                                                        ///< @brief ビュープロジェクション行列
    };


    namespace
    {
        /* ID */
        namespace Id
        {
            /* カメラ */
            namespace Camera
            {
                const char* s_pMAIN = "MainCamera";                                             ///< @brief メインカメラ
                const char* s_pUI = "UICamera";                                                 ///< @brief UIカメラ
            }

            /* シェーダー */
            namespace Shader
            {
                const char* s_pHALF_LAMBERT = "HalfLambertShader";                              ///< @brief ハーフランバートシェーダー
                const char* s_pLOAD = "LoadShader";                                             ///< @brief ロード用のシェーダー
            }

            /* テクスチャ */
            namespace Texture
            {
                const char* s_pLOAD = "LoadTexture";                                            ///< @brief ロード用のテクスチャ
            }

            /* ゲームオブジェクト */
            namespace GameObject
            {
                const char* s_pPLAYER = "Player";                                               ///< @brief プレイヤー
                const char* s_pOPTION = "Option";                                               ///< @brief オプション
                const char* s_pENEMY = "Enemy";                                                 ///< @brief 敵
                const char* s_pOBSTACLE = "Obstacle";                                           ///< @brief 障害物
                const char* s_pBULLET = "Bullet";                                               ///< @brief 弾
                const char* s_pBOMB = "Bomb";                                                   ///< @brief ボム
                const char* s_pEFFECT = "Effect";                                               ///< @brief エフェクト
            }

            /* プリミティブ */
            namespace Primitive
            {
                const char* s_pLOAD = "LoadPrimitive";                                          ///< @brief ロード用のプリミティブ
            }
        }

        /* パス */
        namespace Path
        {
            /* フォント */
            namespace Font
            {
                const char* s_pLOAD = "Projects/Fonts/apjffont/APJapanesefontF.ttf";            ///< @brief ロード時用のフォント
            }
        }

        /* ステージサイズ */
        namespace StageSize
        {
            float s_left = -16.0f;                                                              ///<@brief 左端
            float s_right = 16.0f;                                                              ///<@brief 右端
            float s_top = 12.0f;                                                                ///<@brief 上端
            float s_bottom = -12.0f;                                                            ///<@brief 下端
        }

        /* 連結 */
        namespace Connect
        {
            float s_OffsetFactor = 0.8f;                                                        ///< オフセット係数
        }
    }

    /* ゲームオブジェクトの種類 */
    enum eGameObjectType
    {
        TYPE_PLAYER,                                                                            ///< @brief プレイヤー
        TYPE_OPTION,                                                                            ///< @brief オプション
        TYPE_ENEMY,                                                                             ///< @brief 敵
        TYPE_BULLET,                                                                            ///< @brief 弾
        TYPE_OBSTACLE,                                                                          ///< @brief 障害物
        TYPE_EFFECT,                                                                            ///< @brief エフェクト
        TYPE_BOMB,                                                                              ///< @brief ボム

        TYPE_TYPE_NUMBER,                                                                       ///< @brief 種類の数
    };
}