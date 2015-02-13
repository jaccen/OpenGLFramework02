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
    using Vector2 = Math::S_Vector2<float>;                                                                                                         // Vector2型
    using Vector3 = Math::S_Vector3<float>;                                                                                                         // Vector3型    
    using Vector4 = Math::S_Vector4<float>;                                                                                                         // Vector4型
    using Matrix3x3 = Math::S_Matrix3x3<float>;                                                                                                     // Matrix3x3型
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                                                                                     // Matrix4x4型
    using Telegram = GameObject::Message::S_Telegram;                                                                                               // Telegram型


    /** カメラの情報 */
    struct S_CameraData
    {
        Matrix4x4 viewMatrix_;                                                                                                                      ///< @brief ビュー行列
        Matrix4x4 projectionMatrix_;                                                                                                                ///< @brief プロジェクション行列
        Matrix4x4 viewProjectionMatrix_;                                                                                                            ///< @brief ビュープロジェクション行列
    };


    namespace
    {
        /* ID */
        namespace ID
        {

            /* カメラ */
            namespace Camera
            {
                const char* s_pMAIN = "Main";                                                                                                       ///< @brief メインカメラ
                const char* s_pBACKGROUND = "Background";                                                                                           ///< @brief 背景用カメラ
                const char* s_pUI = "UICamera";                                                                                                     ///< @brief UIカメラ
            }


            /* シェーダー */
            namespace Shader
            {
                const char* s_pPHONG = "PhongShader";                                                                                               ///< @brief フォン
                const char* s_pPHONG_TEXTURE = "PhongTextureShader";                                                                                ///< @brief フォン( テクスチャ )
                const char* s_pCELESTIAL_SPHERE = "CelestialSphereShader";                                                                          ///< @brief 天球
                const char* s_pLOAD = "LoadShader";                                                                                                 ///< @brief ロード用
            }


            /* マテリアル */
            namespace Material
            {
                const char* s_pBASIC = "Basic";                                                                                                     ///< @brief 基本
                const char* s_pDAMAGE = "Damage";                                                                                                   ///< @brief ダメージ
            }

            /* ライト */
            namespace Light
            {
                const char* s_pMAIN = "Main";                                                                                                       ///< @brief メイン
            }


            /* テクスチャ */
            namespace Texture
            {
                const char* s_pLOAD = "LoadTexture";                                                                                                ///< @brief ロード用
            }


            /* プリミティブ */
            namespace Primitive
            {
                const char* s_pLOAD = "LoadPrimitive";                                                                                              ///< @brief ロード用
                const char* s_pNORMAL_PLAYER = "NormalPlayerPrimitive";                                                                             ///< @brief 通常プレイヤー
                const char* s_pSPEED_UP_OPTION = "SpeedUpOptionPrimitive";                                                                          ///< @brief スピードアップオプション
                const char* s_pSMALL_BEAM_OPTION = "SmallBeamOptionPrimitive";                                                                      ///< @brief スモールビームオプション
                const char* s_pBOX_ENEMY = "BoxEnemyPrimitive";                                                                                     ///< @brief ボックスエネミー
                const char* s_pSPACE = "SpacePrimitive";                                                                                            ///< @brief 宇宙
                const char* s_pSHELTER = "ShelterPrimitive";                                                                                        ///< @brief シェルター
            }


            /* ユニフォームバッファ */
            namespace UniformBuffer
            {
                const char* s_pMAIN_CAMERA = "MainCamera";                                                                                          ///< @brief メインカメラ
                const char* s_pBACKGROUND_CAMERA = "BackgroungCamera";                                                                              ///< @brief 背景カメラ
                const char* s_pUI_CAMERA = "UiCamera";                                                                                              ///< @brief UIカメラ
            }


            /* ジェネレータ */
            namespace Generator
            {
                /* プレイヤー */
                namespace Player
                {
                    const char* s_pNORMAL = "NormalPlayer";                                                                                         ///< @brief 通常プレイヤー
                }

                /* オプション */
                namespace Option
                {
                    const char* s_pSPEED_UP = "SpeedUpOption";                                                                                      ///< @brief スピードアップオプション
                    const char* s_pSMALL_BEAM = "SmallBeamOption";                                                                                  ///< @brief スモールビームオプション
                }

                /* 敵 */
                namespace Enemy
                {
                    const char* s_pBOX = "BoxEnemy";                                                                                                ///< @brief ボックスエネミー
                }


                /* 弾 */
                namespace Bullet
                {
                    /* プレイヤー */
                    namespace Player
                    {
                        const char* s_pBEAM = "PlayerBeamBullet";                                                                                   ///< @brief ビーム弾
                    }

                    /* オプション */
                    namespace Option
                    {
                        const char* s_pSMALL_BEAM = "OptionSmallBeamBullet";                                                                        ///< @brief 小さいビーム弾
                    }
                }

                /* エフェクト */
                namespace Effect
                {
                    namespace Bomb
                    {
                        const char* s_pCHARGE = "BombChargeEffect";                                                                                 ///< @brief ボムチャージ
                    }
                }
            }

            /* シーン */
            namespace Scene
            {
                const char* s_pTITLE = "TitleScene";                                                                                                ///< @brief タイトル
                const char* s_pSTAGE01 = "Stage01Scene";                                                                                            ///< @brief ステージ01
                const char* s_pLOAD = "LoadScene";                                                                                                  ///< @brief ロード
            }


            /* ゲームオブジェクト */
            namespace GameObject
            {
                const char* s_pGAME_CONTROLLER = "GameController";                                                                                  ///< @brief ゲームコントローラー
                const char* s_pCAMERA_CONTROLLER = "CameraController";                                                                              ///< @brief カメラコントローラー
                const char* s_pPLAYER = "Player";                                                                                                   ///< @brief プレイヤー
                const char* s_pOPTION = "Option";                                                                                                   ///< @brief オプション
                const char* s_pENEMY = "Enemy";                                                                                                     ///< @brief 敵
                const char* s_pBULLET = "Bullet";                                                                                                   ///< @brief 弾
                const char* s_pEFFECT = "Effect";                                                                                                   ///< @brief エフェクト
                const char* s_pBACKGROUND = "Background";                                                                                           ///< @brief 背景
            }


            /* JSON */
            namespace JSON
            {
                const char* s_pNORMAL_PLAYER = "NormalPlayerJson";                                                                                  ///< @brief 通常プレイヤー
                const char* s_pSPEED_UP_OPTION = "SpeedUpOptionJson";                                                                               ///< @brief スピードアップオプション
                const char* s_pSMALL_BEAM_OPTION = "SmallBeamOptionJson";                                                                           ///< @brief スモールビームオプション
                const char* s_pSHIELD_OPTION = "ShieldOptionJson";                                                                                  ///< @brief シールドオプション
                const char* s_pPLAYER_BULLET = "PlayerBulletJson";                                                                                  ///< @brief プレイヤー弾
                const char* s_pOPTION_BULLET = "OptionBulletJson";                                                                                  ///< @brief オプション弾
                const char* s_pSTAGE_01_ENEMY_DATA = "Stage01EnemyDataJson";                                                                        ///< @brief ステージ01敵データ
                const char* s_pSPACE = "SpaceJson";                                                                                                 ///< @brief 宇宙
                const char* s_pSHELTER = "ShelterJson";                                                                                             ///< @brief シェルター
                const char* s_pSTAGE_01_CAMERAWORK_DATA = "Stage01CameraworkDataJson";                                                              ///< @brief ステージ01カメラワークデータ
            }

            /* モデル */
            namespace Model
            {
                const char* s_pNORMAL_PLAYER = "NormalPlayerModel";                                                                                 ///< @brief 通常プレイヤー
                const char* s_pSPPED_UP_OPTION = "SpeedUpOptionModel";                                                                              ///< @brief スピードアップオプション
                const char* s_pSMALL_BEAM_OPTION = "SmallBeamOptionModel";                                                                          ///< @brief スモールビームオプション
                const char* s_pBOX_ENEMY = "BoxEnemyModel";                                                                                         ///< @brief ボックスエネミー
                const char* s_pSPACE = "SpaceModel";                                                                                                ///< @brief 宇宙
                const char* s_pSHELTER = "ShelterModel";                                                                                            ///< @brief シェルター
            }

            /* スプライト */
            namespace Sprite
            {
                const char* s_pBULLET = "BulletSprite";                                                                                             ///< @brief　弾
            }

            /* パーティクル */
            namespace Particle
            {
                const char* s_pCIRCLE_01 = "Circle01Particle";                                                                                      ///< @brief 円01
                const char* s_pCIRCLE_02 = "Circle02Particle";                                                                                      ///< @brief 円02
                const char* s_pRING_01 = "Ring01Particle";                                                                                          ///< @brief 輪01
            }
        }


        /* パス */
        namespace Path
        {
            /* シェーダー */
            namespace Shader
            {
                namespace Vertex
                {
                    const char* s_pPHONG = "Projects/Shaders/GLSL/Phong/Phong.vert";                                                                ///< @brief フォン
                    const char* s_pPHONG_TEXTURE = "Projects/Shaders/GLSL/Phong/PhongTexture.vert";                                                 ///< @brief フォン( テクスチャ )
                    const char* s_pCELESTINAL_SPHERE = "Projects/Shaders/GLSL/CelestialSphere/CelestialSphere.vert";                                ///< @brief 天球
                }


                namespace Geometry
                {
                }


                namespace Fragment
                {
                    const char* s_pPHONG = "Projects/Shaders/GLSL/Phong/Phong.frag";                                                                ///< @brief フォン
                    const char* s_pPHONG_TEXTURE = "Projects/Shaders/GLSL/Phong/PhongTexture.frag";                                                 ///< @brief フォン( テクスチャ )
                    const char* s_pCELESTINAL_SPHERE = "Projects/Shaders/GLSL/CelestialSphere/CelestialSphere.frag";                                ///< @brief 天球
                }
            }


            /* テクスチャ */
            namespace Texture
            {
                const char* s_pNORMAL_PLAYER = "Projects/Images/ConnectWars/Player/NormalPlayer.png";                                               ///< @brief 通常プレイヤー
                const char* s_pSPPED_UP_OPTION = "Projects/Images/ConnectWars/Option/SpeedUpOption.png";                                            ///< @brief スピードアップオプション
                const char* s_pSMALL_BEAM_OPTION = "Projects/Images/ConnectWars/Option/SmallBeamOption.png";                                        ///< @brief スモールビームオプション
                const char* s_pSPRITE_BULLET = "Projects/Images/ConnectWars/Bullet/SpriteBullet.png";                                               ///< @brief スプライトの弾
                const char* s_pCIRCLE_01 = "Projects/Images/ConnectWars/Effect/Circle01.png";                                                       ///< @brief 円01
                const char* s_pCIRCLE_02 = "Projects/Images/ConnectWars/Effect/Circle02.png";                                                       ///< @brief 円02
                const char* s_pRING_01 = "Projects/Images/ConnectWars/Effect/Ring01.png";                                                           ///< @brief 輪01
                const char* s_pSPACE = "Projects/Images/ConnectWars/Background/Space.png";                                                          ///< @brief 宇宙
                const char* s_pSHELTER = "Projects/Images/ConnectWars/Background/Shelter.png";                                                      ///< @brief シェルター
                const char* s_pSHALTER_NORMAL = "Projects/Images/ConnectWars/Background/Shelter_NormalMap.png";                                     ///< @brief シェルター( 法線マップ )
            }

            /* フォント */
            namespace Font
            {
                const char* s_pLOAD = "Projects/Fonts/apjffont/APJapanesefontF.ttf";                                                                ///< @brief ロード用
            }


            /* モデル */
            namespace Model
            {
                const char* s_pNORMAL_PLAYER = "Projects/Models/ConnectWars/Player/Normal/NormalPlayer.model";                                      ///< @brief 通常プレイヤー
                const char* s_pSPEED_UP_OPTION = "Projects/Models/ConnectWars/Option/SpeedUp/SpeedUpOption.model";                                  ///< @brief スピードアップオプション
                const char* s_pSMALL_BEAM_OPTION = "Projects/Models/ConnectWars/Option/SmallBeam/SmallBeamOption.model";                            ///< @brief スモールビームオプション
                const char* s_pBOX_ENEMY = "Projects/Models/Test/Box/Box.model";                                                                    ///< @brief ボックスエネミー
                const char* s_pSPACE = "Projects/Models/ConnectWars/Background/Space/Sphere.model";                                                 ///< @brief 宇宙
                const char* s_pSHELTER = "Projects/Models/ConnectWars/Background/Shelter/Shelter.model";                                            ///< @brief シェルター
            }


            /* JSON */
            namespace JSON
            {
                const char* s_pCAMERA = "Projects/GameDatas/ConnectWars/JSON/Camera/CameraData.json";                                               ///< @brief カメラ
                const char* s_pNORMAL_PLAYER = "Projects/GameDatas/ConnectWars/JSON/Player/NormalPlayerData.json";                                  ///< @brief 通常プレイヤー
                const char* s_pSPEED_UP_OPTION = "Projects/GameDatas/ConnectWars/JSON/Option/SpeedUpOptionData.json";                               ///< @brief スピードアップオプション
                const char* s_pSMALL_BEAM_OPTION = "Projects/GameDatas/ConnectWars/JSON/Option/SmallBeamOptionData.json";                           ///< @brief スモールビームオプション
                const char* s_pPLAYER_BULLET = "Projects/GameDatas/ConnectWars/JSON/Bullet/Player/PlayerBulletDatas.json";                          ///< @brief プレイヤー弾
                const char* s_pOPTION_BULLET = "Projects/GameDatas/ConnectWars/JSON/Bullet/Option/OptionBulletDatas.json";                          ///< @brief オプション弾
                const char* s_pSTAGE_01_ENEMY_DATA = "Projects/GameDatas/ConnectWars/JSON/Enemy/Stage01/Stage01EnemyData.json";                     ///< @breif ステージ01敵データ
                const char* s_pTASK_PRIORITY_DATA = "Projects/GameDatas/ConnectWars/JSON/Task/TaskPriorityData.json";                               ///< @breif タスクの優先度データ
                const char* s_pSPACE = "Projects/GameDatas/ConnectWars/JSON/Background/SpaceData.json";                                             ///< @brief 宇宙
                const char* s_pSHELTER = "Projects/GameDatas/ConnectWars/JSON/Background/ShelterData.json";                                         ///< @brief シェルター
                const char* s_pMATERIAL_DATA = "Projects/GameDatas/ConnectWars/JSON/Material/MaterialData.json";                                    ///< @brief マテリアルデータ
                const char* s_pLIGHT_DATA = "Projects/GameDatas/ConnectWars/JSON/Light/LightData.json";                                             ///< @brief ライト情報
                const char* s_pSTAGE_01_CAMERAWORK_DATA = "Projects/GameDatas/ConnectWars/JSON/Camera/Stage01/Stage01CameraworkData.json";          ///< @brief ステージ01カメラワークデータ
            }

            /* Lua */
            namespace Lua
            {
                const char* s_pBOMB_CHARGE_EFFECT = "Projects/Sources/Lua/Effect/BombChargeEffect.lua";                                             ///< @brief ボムのチャージエフェクト
            }
        }


        /* ステージサイズ */
        namespace StageSize
        {
            float s_left = -16.0f;                                                                                                                  ///< @brief 左端
            float s_right = 16.0f;                                                                                                                  ///< @brief 右端
            float s_top = 12.0f;                                                                                                                    ///< @brief 上端
            float s_bottom = -12.0f;                                                                                                                ///< @brief 下端
        }


        /* 連結 */
        namespace Connect
        {
            float s_offsetFactor = 0.92f;                                                                                                           ///< @brief オフセット係数
        }


        /* メッセージ */
        namespace Message
        {
            const char* s_pCONNECT_CHECK = "ConnectCheck";                                                                                          ///< @brief 連結確認
            const char* s_pWAIT = "Wait";                                                                                                           ///< @brief 待機
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
                    float s_gameController = 100.0f;                                                                                                ///< @brief ゲームコントローラ
                    float s_cameraController = 50.0f;                                                                                               ///< @brief カメラコントローラ
                    float s_player = 10.0f;                                                                                                         ///< @brief プレイヤー
                    float s_option = 9.0f;                                                                                                          ///< @brief オプション
                    float s_enemy = 8.0f;                                                                                                           ///< @brief 敵
                    float s_bullet = 7.0f;                                                                                                          ///< @brief 弾
                    float s_obstacle = 6.0f;                                                                                                        ///< @brief 障害物
                    float s_effect = 5.0f;                                                                                                          ///< @brief エフェクト
                    float s_bomb = 4.0f;                                                                                                            ///< @brief ボム
                    float s_background = 3.0f;                                                                                                      ///< @brief 背景
                }

                /* 描画 */
                namespace Draw
                {
                    float s_gameController = 100.0f;                                                                                                ///< @brief ゲームコントローラ
                    float s_cameraController = 50.0f;                                                                                               ///< @brief カメラコントローラ
                    float s_background = 11.0f;                                                                                                     ///< @brief 背景
                    float s_bomb = 10.0f;                                                                                                           ///< @brief ボム
                    float s_effect = 9.0f;                                                                                                          ///< @brief エフェクト
                    float s_obstacle = 8.0f;                                                                                                        ///< @brief 障害物
                    float s_bullet = 7.0f;                                                                                                          ///< @brief 弾
                    float s_enemy = 6.0f;                                                                                                           ///< @brief 敵
                    float s_option = 5.0f;                                                                                                          ///< @brief オプション
                    float s_player = 4.0f;                                                                                                          ///< @brief プレイヤー
                }
            }


            /* スプライト */
            namespace Sprite
            {
                const float s_BILLBOARD = 10.0f;                                                                                                    ///< @brief ビルボード
                const float s_UI = 0.0f;                                                                                                            ///< @brief UI
            }
        }
    }


    /* ゲームオブジェクトの種類 */
    enum eGameObjectType
    {
        TYPE_GAME_CONTROLLER,                                                                                                                       ///< @brief ゲームコントローラ
        TYPE_CAMERA_CONTROLLER,                                                                                                                     ///< @brief カメラコントローラ
        TYPE_PLAYER,                                                                                                                                ///< @brief プレイヤー
        TYPE_OPTION,                                                                                                                                ///< @brief オプション
        TYPE_ENEMY,                                                                                                                                 ///< @brief 敵
        TYPE_BULLET,                                                                                                                                ///< @brief 弾
        TYPE_OBSTACLE,                                                                                                                              ///< @brief 障害物
        TYPE_EFFECT,                                                                                                                                ///< @brief エフェクト
        TYPE_BOMB,                                                                                                                                  ///< @brief ボム
        TYPE_BACKGROUND,                                                                                                                            ///< @brief 背景

        TYPE_TYPE_NUMBER,                                                                                                                           ///< @brief 種類の数
    };
}