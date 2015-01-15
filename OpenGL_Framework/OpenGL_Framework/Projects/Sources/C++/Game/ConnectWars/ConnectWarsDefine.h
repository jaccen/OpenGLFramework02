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
    using Vector2 = Math::S_Vector2<float>;                                                                                     // Vector2型
    using Vector3 = Math::S_Vector3<float>;                                                                                     // Vector3型    
    using Vector4 = Math::S_Vector4<float>;                                                                                     // Vector4型
    using Matrix3x3 = Math::S_Matrix3x3<float>;                                                                                 // Matrix3x3型
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                                                                 // Matrix4x4型
    using Telegram = GameObject::Message::S_Telegram;                                                                           // Telegram型


    /** カメラの情報 */
    struct S_CameraData
    {
        Matrix4x4 viewMatrix_;                                                                                                  ///< @brief ビュー行列
        Matrix4x4 projectionMatrix_;                                                                                            ///< @brief プロジェクション行列
        Matrix4x4 viewProjectionMatrix_;                                                                                        ///< @brief ビュープロジェクション行列
    };


    namespace
    {
        /* ID */
        namespace ID
        {

            /* カメラ */
            namespace Camera
            {
                const char* s_pMAIN = "MainCamera";                                                                             ///< @brief メインカメラ
                const char* s_pUI = "UICamera";                                                                                 ///< @brief UIカメラ
            }


            /* シェーダー */
            namespace Shader
            {
                const char* s_pHALF_LAMBERT_PHONG = "HalfLamberPhongShader";                                                    ///< @brief ハーフランバートフォン
                const char* s_pLOAD = "LoadShader";                                                                             ///< @brief ロード用
            }


            /* テクスチャ */
            namespace Texture
            {
                const char* s_pLOAD = "LoadTexture";                                                                            ///< @brief ロード用
            }


            /* プリミティブ */
            namespace Primitive
            {
                const char* s_pLOAD = "LoadPrimitive";                                                                          ///< @brief ロード用
                const char* s_pNORMAL_PLAYER = "NormalPlayerPrimitive";                                                         ///< @brief 通常プレイヤー
            }


            /* ユニフォームバッファ */
            namespace UniformBuffer
            {
                const char* s_pMAIN_CAMERA = "MainCamera";                                                                      ///< @brief メインカメラ用
            }


            /* ジェネレータ */
            namespace Generator
            {
                /* プレイヤー */
                namespace Player
                {
                    const char* s_pNORMAL = "NormalPlayer";                                                                     ///< @brief 通常プレイヤー
                }


                /* オプション */
                namespace Option
                {
                    const char* s_pSPEED_UP = "SpeedUpOption";                                                                  ///< @brief スピードアップオプション
                }


                /* 弾 */
                namespace Bullet
                {
                    /* プレイヤー */
                    namespace Player
                    {
                        const char* s_pBEAM = "PlayerBeamBullet";                                                               ///< @brief ビーム弾
                    }
                }
            }

            /* シーン */
            namespace Scene
            {
                const char* s_pTITLE = "TitleScene";                                                                            ///< @brief タイトル
                const char* s_pSTAGE01 = "Stage01Scene";                                                                        ///< @brief ステージ01
                const char* s_pLOAD = "LoadScene";                                                                              ///< @brief ロード
            }


            /* ゲームオブジェクト */
            namespace GameObject
            {
                const char* s_pPLAYER = "Player";                                                                               ///< @brief プレイヤー
                const char* s_pOPTION = "Option";                                                                               ///< @brief オプション
                const char* s_pBULLET = "Bullet";                                                                               ///< @brief 弾
            }


            /* JSON */
            namespace JSON
            {
                const char* s_pNORMAL_PLAYER = "NormalPlayerJson";                                                              ///< @brief 通常プレイヤー
                const char* s_pSPEED_UP_OPTION = "SpeedUpOption";                                                               ///< @brief スピードアップオプション
            }

            /* モデル */
            namespace Model
            {
                const char* s_pNORMAL_PLAYER = "NormalPlayerModel";                                                             ///< @brief 通常プレイヤー
            }

            /* スプライト */
            namespace Sprite
            {
                const char* s_pBULLET = "BulletSprite";                                                                         ///< @brief　弾
            }
        }


        /* パス */
        namespace Path
        {
            /* テクスチャ */
            namespace Texture
            {
                const char* s_pSPRITE_BULLET = "Projects/Images/ConnectWars/Bullet/SpriteBullet.png";                           ///< @brief スプライトの弾
            }

            /* フォント */
            namespace Font
            {
                const char* s_pLOAD = "Projects/Fonts/apjffont/APJapanesefontF.ttf";                                            ///< @brief ロード用
            }


            /* モデル */
            namespace Model
            {
                const char* s_pNORMAL_PLAYER = "Projects/Models/Test/Sphere/Sphere.model";                                      ///< @brief 通常プレイヤー
            }


            /* JSON */
            namespace JSON
            {
                const char* s_pCAMERA = "Projects/GameDatas/ConnectWars/JSON/Camera/CameraData.json";                           ///< @brief カメラ
                const char* s_pNORMAL_PLAYER = "Projects/GameDatas/ConnectWars/JSON/Player/NormalPlayerData.json";              ///< @brief 通常プレイヤー
                const char* s_pSPEED_UP_OPTION = "Projects/GameDatas/ConnectWars/JSON/Option/SpeedUpOptionData.json";           ///< @brief 通常プレイヤー
            }
        }


        /* ステージサイズ */
        namespace StageSize
        {
            float s_left = -16.0f;                                                                                              ///< @brief 左端
            float s_right = 16.0f;                                                                                              ///< @brief 右端
            float s_top = 12.0f;                                                                                                ///< @brief 上端
            float s_bottom = -12.0f;                                                                                            ///< @brief 下端
        }


        /* 連結 */
        namespace Connect
        {
            float s_offsetFactor = 0.8f;                                                                                        ///< @brief オフセット係数
        }


        /* メッセージ */
        namespace Message
        {
            const char* s_pCONNECT_CHECK = "ConnectCheck";                                                                      ///< @brief 連結確認
        }


        /* 優先度 */
        namespace Priority
        {
            /* タスク */
            namespace Task
            {
                /* 更新 */
                namespace Update
                {
                    float s_player = 10.0f;                                                                                     ///< @brief プレイヤー
                    float s_option = 9.0f;                                                                                      ///< @brief オプション
                    float s_enemy = 8.0f;                                                                                       ///< @brief 敵
                    float s_bullet = 7.0f;                                                                                      ///< @brief 弾
                    float s_obstacle = 6.0f;                                                                                    ///< @brief 障害物
                    float s_effect = 5.0f;                                                                                      ///< @brief エフェクト
                    float s_bomb = 4.0f;                                                                                        ///< @brief ボム
                }

                /* 描画 */
                namespace Draw
                {
                    float s_bomb = 10.0f;                                                                                       ///< @brief ボム
                    float s_effect = 9.0f;                                                                                      ///< @brief エフェクト
                    float s_obstacle = 8.0f;                                                                                    ///< @brief 障害物
                    float s_bullet = 7.0f;                                                                                      ///< @brief 弾
                    float s_enemy = 6.0f;                                                                                       ///< @brief 敵
                    float s_option = 5.0f;                                                                                      ///< @brief オプション
                    float s_player = 4.0f;                                                                                      ///< @brief プレイヤー
                }
            }


            /* スプライト */
            namespace Sprite
            {
                const float s_BILLBOARD = 10.0f;                                                                                ///< @brief ビルボード
                const float s_UI = 0.0f;                                                                                        ///< @brief UI
            }
        }
    }


    /* ゲームオブジェクトの種類 */
    enum eGameObjectType
    {
        TYPE_PLAYER,                                                                                                            ///< @brief プレイヤー
        TYPE_OPTION,                                                                                                            ///< @brief オプション
        TYPE_ENEMY,                                                                                                             ///< @brief 敵
        TYPE_BULLET,                                                                                                            ///< @brief 弾
        TYPE_OBSTACLE,                                                                                                          ///< @brief 障害物
        TYPE_EFFECT,                                                                                                            ///< @brief エフェクト
        TYPE_BOMB,                                                                                                              ///< @brief ボム

        TYPE_TYPE_NUMBER,                                                                                                       ///< @brief 種類の数
    };

}