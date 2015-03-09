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
                const char* s_pPHONG_NORMAL_TEXTURE = "PhongNormalTexture";                                                                         ///< @brief フォン( ノーマルテクスチャ )
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
                const char* s_pSHELTER = "Shelter";                                                                                                 ///< @brief シェルター
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
                const char* s_pSHIELD_OPTION = "ShieldOptionPrimitive";                                                                             ///< @brief シールドオプション
                const char* s_pLASER_OPTION = "LaserOptionPrimitive";                                                                               ///< @brief レーザーオプション
                const char* s_pBOX_ENEMY = "BoxEnemyPrimitive";                                                                                     ///< @brief ボックスエネミー
                const char* s_pSLIME_ENEMY = "SlimeEnemyPrimitive";                                                                                 ///< @brief スライムエネミー
                const char* s_pROUND_ENEMY = "RoundEnemyPrimitive";                                                                                 ///< @brief ラウンドエネミー
                const char* s_pGROUP_SHIP_ENEMY = "GroupShipEnemyPrimitive";                                                                        ///< @brief グループシップエネミー
                const char* s_pPYRAMID_ENEMY = "PyramidEnemyPrimitive";                                                                             ///< @brief ピラミッドエネミー
                const char* s_pPHALANX_CORE = "PhalanxCoreyPrimitive";                                                                              ///< @brief ファランクス( コア )
                const char* s_pPHALANX_RING = "PhalanxRingPrimitive";                                                                               ///< @brief ファランクス( リング )
                const char* s_pSPACE = "SpacePrimitive";                                                                                            ///< @brief 宇宙
                const char* s_pSHELTER = "ShelterPrimitive";                                                                                        ///< @brief シェルター
                const char* s_pEXIT_RING = "ExitRingPrimitive";                                                                                     ///< @brief エグジットリング
                const char* s_pMETEOR = "Meteor";                                                                                                   ///< @brief 隕石
                const char* s_pROCK = "Rock";                                                                                                       ///< @brief 岩
                const char* s_pBACKGROUND_METEOR = "BackgroundMeteor";                                                                              ///< @brief 背景隕石
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
                    const char* s_pSHIELD = "ShieldOption";                                                                                         ///< @brief シールドオプション
                    const char* s_pLASER = "LaserOption";                                                                                           ///< @brief レーザー
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
                    const char* s_pNORMAL_BOMB_CHARGE = "NormalBombChargeEffect";                                                                   ///< @brief ノーマルボムチャージ
                    const char* s_pNORMAL_BOMB = "NormalBombEffect";                                                                                ///< @brief ノーマルボム   
                    const char* s_pOPTION_OWN_CRASH_01 = "OptionOwnCrash01Effect";                                                                  ///< @brief オプション自爆01
                    const char* s_pPLAYER_FLAREBACK = "PlayerFlaerBackEffect";                                                                      ///< @brief プレイヤーフレーヤーバック
                    const char* s_pCONNECT = "ConnectEffect";                                                                                       ///< @brief 連結エフェクト
                    const char* s_pPLAYER_EXPLOSION = "PlayerExplosionEffect";                                                                      ///< @brief プレイヤー爆発
                    const char* s_pOPTION_EXPLOSION = "OptionExplosionEffect";                                                                      ///< @brief オプション爆発
                    const char* s_pPLAYER_BEAM_COLLISION = "PlayerBeamCollisionEffect";                                                             ///< @brief プレイヤービーム衝突
                    const char* s_pOPTION_SMALL_BEAM_COLLISION = "OptionSmallBeamCollisionEffect";                                                  ///< @brief オプションスモールビーム衝突
                }

                /* 背景 */
                namespace Background
                {
                    const char* s_pSPACE = "Space";                                                                                                 ///< @brief 空間
                    const char* s_pSHELTER = "Shelter";                                                                                             ///< @brief シェルター
                    const char* s_pEXIT_RING = "ExitRing";                                                                                          ///< @brief エグジットリング 
                    const char* s_pEARTH = "Earth";                                                                                                 ///< @brief 地球
                    const char* s_pBACKGROUND_METEOR = "BackgroundMeteor";                                                                          ///< @brief 背景隕石
                }

                /* ボム */
                namespace Bomb
                {
                    const char* s_pNORMAL = "NormalBomb";                                                                                           ///< @brief ノーマル
                }

                /* シールド */
                namespace Shield
                {
                    const char* s_pNORMAL = "NormalShield";                                                                                         ///< @brief ノーマル
                }
            }

            /* シーン */
            namespace Scene
            {
                const char* s_pTITLE = "TitleScene";                                                                                                ///< @brief タイトル
                const char* s_pRANKING = "RankingScene";                                                                                            ///< @brief ランキング
                const char* s_pSTAGE01 = "Stage01Scene";                                                                                            ///< @brief ステージ01
                const char* s_pLOAD = "LoadScene";                                                                                                  ///< @brief ロード
            }


            /* ゲームオブジェクト */
            namespace GameObject
            {
                const char* s_pUI = "Ui";                                                                                                           ///< @brief UI
                const char* s_pPAUSE_UI = "PauseUi";                                                                                                ///< @brief ポーズUI
                const char* s_pSCENE_CONTROLLER = "SceneController";                                                                                ///< @brief シーンコントローラ
                const char* s_pPAUSE_CONTROLLER = "PauseController";                                                                                ///< @brief ポーズコントローラ
                const char* s_pCAMERA_CONTROLLER = "CameraController";                                                                              ///< @brief カメラコントローラ
                const char* s_pPLAYER = "Player";                                                                                                   ///< @brief プレイヤー
                const char* s_pOPTION = "Option";                                                                                                   ///< @brief オプション
                const char* s_pENEMY = "Enemy";                                                                                                     ///< @brief 敵
                const char* s_pBULLET = "Bullet";                                                                                                   ///< @brief 弾
                const char* s_pEFFECT = "Effect";                                                                                                   ///< @brief エフェクト
                const char* s_pBACKGROUND = "Background";                                                                                           ///< @brief 背景
                const char* s_pFADE = "Fade";                                                                                                       ///< @brief フェード
                const char* s_pBOMB = "Bomb";                                                                                                       ///< @brief ボム
                const char* s_pSHIELD = "Shield";                                                                                                   ///< @brief シールド
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
                const char* s_pSTAGE_01_CAMERAWORK_DATA = "Stage01CameraworkDataJson";                                                              ///< @brief ステージ01カメラワークデータ
                const char* s_pTITLE_UI_DATA = "TitleUiDataJson";                                                                                   ///< @brief タイトルUIデータ
                const char* s_pRANKING_UI_DATA = "RankingUiDataJson";                                                                               ///< @brief ランキングUIデータ
                const char* s_pGAME_UI_DATA = "GameUiData";                                                                                         ///< @brief ゲームUIデータ
                const char* s_pCONFIG_DATA = "ConfigData";                                                                                          ///< @brief コンフィグデータ
                const char* s_pRANKING_DATA = "RankingData";                                                                                        ///< @brief ランキングデータ
                const char* s_pPAUSE_UI_DATA = "PauseUiDataJson";                                                                                   ///< @brief ポーズUIデータ
                const char* s_pSTAGE_01_BACKGROUND_DATA = "Stage01BackgroundDataJson";                                                              ///< @brief ステージ01背景データ
                const char* s_pSHIELD_DATA = "ShieldDataJson";                                                                                      ///< @brief シールドデータ
            }

            /* モデル */
            namespace Model
            {
                const char* s_pNORMAL_PLAYER = "NormalPlayerModel";                                                                                 ///< @brief 通常プレイヤー
                const char* s_pSPPED_UP_OPTION = "SpeedUpOptionModel";                                                                              ///< @brief スピードアップオプション
                const char* s_pSMALL_BEAM_OPTION = "SmallBeamOptionModel";                                                                          ///< @brief スモールビームオプション
                const char* s_pSHIELD_OPTION = "ShieldOption";                                                                                      ///< @brief シールドオプション
                const char* s_pLASER_OPTION = "LaserOption";                                                                                        ///< @brief レーザーオプション
                const char* s_pBOX_ENEMY = "BoxEnemyModel";                                                                                         ///< @brief ボックスエネミー
                const char* s_pSLIME_ENEMY = "SlimeEnemyModel";                                                                                     ///< @brief スライムエネミー
                const char* s_pROUND_ENEMY = "RoundEnemyModel";                                                                                     ///< @brief ラウンドエネミー
                const char* s_pPYRAMID_ENEMY = "PyramidEnemyModel";                                                                                 ///< @brief ピラミッドエネミー
                const char* s_pGROUP_SHIP_ENEMY = "GroupShipEnemyModel";                                                                            ///< @brief グループシップエネミー
                const char* s_pPHALANX_CORE = "PhalanxCoreModel";                                                                                   ///< @brief ファランクス( コア )
                const char* s_pPHALANX_RING = "PhalanxRingModel";                                                                                   ///< @brief ファランクス( リング )
                const char* s_pSPACE = "SpaceModel";                                                                                                ///< @brief 宇宙
                const char* s_pSHELTER = "ShelterModel";                                                                                            ///< @brief シェルター
                const char* s_pEXIT_RING = "ExitRingModel";                                                                                         ///< @brief エグジットリング
                const char* s_pMETEOR = "MeteorModel";                                                                                              ///< @brief 隕石
                const char* s_pROCK = "RockModel";                                                                                                  ///< @brief 岩
            }

            /* スプライト */
            namespace Sprite
            {
                const char* s_pUI_FONT = "UiFontSprite";                                                                                            ///< @brief UIフォント
                const char* s_pTITLE_BACKGROUND = "TitleBackgroundSprite";                                                                          ///< @brief タイトル背景
                const char* s_pBULLET = "BulletSprite";                                                                                             ///< @brief 弾
                const char* s_pTITLE_UI = "TitleUiSPrite";                                                                                          ///< @brief タイトルUI
                const char* s_pFADE = "FadeSprite";                                                                                                 ///< @brief フェード
                const char* s_pRANKING_BACKGROUND = "RankingBackgroundSprite";                                                                      ///< @brief ランキング背景
                const char* s_pPAUSE_BACKGROUND = "PauseBackgroundSprite";                                                                          ///< @brief ポーズ背景
                const char* s_pGAME_UI = "GameUiSprite";                                                                                            ///< @brief ゲームUI
                const char* s_pSHIELD = "ShieldSprite";                                                                                             ///< @brief シールド
            }

            /* パーティクル */
            namespace Particle
            {
                const char* s_pCIRCLE_01 = "Circle01Particle";                                                                                      ///< @brief 円01
                const char* s_pCIRCLE_02 = "Circle02Particle";                                                                                      ///< @brief 円02
                const char* s_pRING_01 = "Ring01Particle";                                                                                          ///< @brief 輪01
                const char* s_pSMOKE_01 = "Smoke01Particle";                                                                                        ///< @brief 煙01
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
                    const char* s_pPHONG_NORMAL_TEXTURE = "Projects/Shaders/GLSL/Phong/PhongNormal.vert";                                           ///< @brief フォン( ノーマル )
                }


                namespace Geometry
                {
                }


                namespace Fragment
                {
                    const char* s_pPHONG = "Projects/Shaders/GLSL/Phong/Phong.frag";                                                                ///< @brief フォン
                    const char* s_pPHONG_TEXTURE = "Projects/Shaders/GLSL/Phong/PhongTexture.frag";                                                 ///< @brief フォン( テクスチャ )
                    const char* s_pCELESTINAL_SPHERE = "Projects/Shaders/GLSL/CelestialSphere/CelestialSphere.frag";                                ///< @brief 天球
                    const char* s_pPHONG_NORMAL_TEXTURE = "Projects/Shaders/GLSL/Phong/PhongNormal.frag";                                           ///< @brief フォン( ノーマル )
                }
            }


            /* テクスチャ */
            namespace Texture
            {
                const char* s_pUI_FONT = "Projects/Images/ConnectWars/UI/UiFont.png";                                                               ///< @brief UIフォント
                const char* s_pTITLE_UI = "Projects/Images/ConnectWars/UI/TitleUI.png";                                                             ///< @brief タイトルUI
                const char* s_pTITLE_BACKGROUND = "Projects/Images/ConnectWars/Background/TitleBackground.png";                                     ///< @brief タイトル背景
                const char* s_pRANKING_BACKGROUND = "Projects/Images/ConnectWars/Background/RankingBackground.png";                                 ///< @brief ランキング背景
                const char* s_pPAUSE_BACKGROUND = "Projects/Images/ConnectWars/Background/PauseBackground.png";                                     ///< @brief ポーズ背景
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
                const char* s_pFADE = "Projects/Images/ConnectWars/Fade/BlackDot.png";                                                              ///< @brief フェード
                const char* s_pEARTH = "Projects/Images/ConnectWars/Background/Earth.png";                                                          ///< @brief 地球
                const char* s_pMETOAR = "Projects/Images/ConnectWars/Obstacle/Meteor.png";                                                          ///< @brief 隕石
                const char* s_pMETOAR_NORMAL = "Projects/Images/ConnectWars/Obstacle/MeteorNormalMap.png";                                          ///< @brief 隕石(  法線マップ
                const char* s_pBACKGROND_METEOR = "Projects/Images/ConnectWars/Background/BackgroundMeteor.png";                                    ///< @brief 背景隕石
                const char* s_pROCK = "Projects/Images/ConnectWars/Obstacle/Rock.png";                                                              ///< @brief 岩
                const char* s_pROCK_NORMAL = "Projects/Images/ConnectWars/Obstacle/RockNormalMap.png";                                              ///< @brief 岩( 法線マップ )
                const char* s_pGAME_UI = "Projects/Images/ConnectWars/UI/GameUI.png";                                                               ///< @brief ゲームUI
                const char* s_pSMOKE_01 = "Projects/Images/ConnectWars/Effect/Smoke01.png";                                                         ///< @brief 煙01
                const char* s_pSPRITE_SHIELD = "Projects/Images/ConnectWars/Shield/SpriteShield.png";                                               ///< @brief スプライトのシールド
                const char* s_pROUND_ENEMY = "Projects/Images/ConnectWars/Enemy/Round.png";                                                         ///< @brief ラウンドエネミー
                const char* s_pGROUD_SHIP_ENEMY = "Projects/Images/ConnectWars/Enemy/GroupShip.png";                                                ///< @brief グループシップエネミー
                const char* s_pPHALANX_CORE = "Projects/Images/ConnectWars/Enemy/Core.png";                                                         ///< @brief ファランクス( コア )
                const char* s_pPHALANX_RING = "Projects/Images/ConnectWars/Enemy/Ring.png";                                                         ///< @brief ファランクス( リング )
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
                const char* s_pSHIELD_OPTION = "Projects/Models/ConnectWars/Option/Shield/ShieldOption.model";                                      ///< @brief シールドオプション
                const char* s_pLASER_OPTION = "Projects/Models/ConnectWars/Option/Laser/LaserOption.model";                                         ///< @brief レーザーオプション
                const char* s_pBOX_ENEMY = "Projects/Models/ConnectWars/Enemy/Box/Box.model";                                                       ///< @brief ボックスエネミー
                const char* s_pSLIME_ENEMY = "Projects/Models/ConnectWars/Enemy/Slime/Sphere.model";                                                ///< @brief スライムエネミー
                const char* s_pROUND_ENEMY = "Projects/Models/ConnectWars/Enemy/Round/RoundEnemy.model";                                            ///< @brief ラウンドエネミー
                const char* s_pPYRAMID_ENEMY = "Projects/Models/ConnectWars/Enemy/Pyramid/Pyramid.model";                                           ///< @brief ピラミッドエネミー
                const char* s_pGROUP_SHIP_ENEMY = "Projects/Models/ConnectWars/Enemy/GroupShip/GroupShip.model";                                    ///< @brief グループシップエネミー
                const char* s_pPHALANX_CORE = "Projects/Models/ConnectWars/Enemy/Boss/Phalanx/Core/Core.model";                                     ///< @brief ファランクス( コア )
                const char* s_pPHALANX_RING = "Projects/Models/ConnectWars/Enemy/Boss/Phalanx/Ring/RingEnemy.model";                                ///< @brief ファランクス( リング )
                const char* s_pSPACE = "Projects/Models/ConnectWars/Background/Space/Sphere.model";                                                 ///< @brief 宇宙
                const char* s_pSHELTER = "Projects/Models/ConnectWars/Background/Shelter/Shelter.model";                                            ///< @brief シェルター
                const char* s_pEXIT_RING = "Projects/Models/ConnectWars/Background/ExitRing/ExitRing.model";                                        ///< @brief エグジットリング
                const char* s_pMETEOR = "Projects/Models/ConnectWars/Obstacle/Meteor/Meteor.model";                                                 ///< @brief 隕石
                const char* s_pROCK = "Projects/Models/ConnectWars/Obstacle/Rock/Rock.model";                                                       ///< @brief 岩
                const char* s_pBACKGROUND_METEOR = "Projects/Models/ConnectWars/Obstacle/Meteor/Rock.model";                                                       ///< @brief 岩
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
                const char* s_pMATERIAL_DATA = "Projects/GameDatas/ConnectWars/JSON/Material/MaterialData.json";                                    ///< @brief マテリアルデータ
                const char* s_pLIGHT_DATA = "Projects/GameDatas/ConnectWars/JSON/Light/LightData.json";                                             ///< @brief ライト情報
                const char* s_pSTAGE_01_CAMERAWORK_DATA = "Projects/GameDatas/ConnectWars/JSON/Camera/Stage01/Stage01CameraworkData.json";          ///< @brief ステージ01カメラワークデータ
                const char* s_pTITLE_UI_DATA = "Projects/GameDatas/ConnectWars/JSON/UI/TitleUiData.json";                                           ///< @brief タイトルUIデータ
                const char* s_pRANKING_UI_DATA = "Projects/GameDatas/ConnectWars/JSON/UI/RankingUiData.json";                                       ///< @brief ランキングUIデータ
                const char* s_pGAME_UI_DATA = "Projects/GameDatas/ConnectWars/JSON/UI/GameUiData.json";                                             ///< @brief ゲームUIデータ
                const char* s_pRANKING_DATA = "Projects/GameDatas/ConnectWars/JSON/Ranking/RankingData.json";                                       ///< @brief ランキングデータ
                const char* s_pCONFIG_DATA = "Projects/GameDatas/ConnectWars/JSON/Config/ConfigData.json";                                          ///< @brief コンフィグデータ
                const char* s_pPAUSE_UI_DATA = "Projects/GameDatas/ConnectWars/JSON/UI/PauseUiData.json";                                           ///< @brief ポーズUIデータ
                const char* s_pSTAGE_01_BACKGROUND_DATA = "Projects/GameDatas/ConnectWars/JSON/Background/Stage01/Stage01BackgroundData.json";      ///< @brief ステージ01背景データ
                const char* s_pSHIELD_DATA = "Projects/GameDatas/ConnectWars/JSON/Shield/ShieldData.json";                                          ///< @brief シールドデータ
            }

            /* Lua */
            namespace Lua
            {
                const char* s_pNORMAL_BOMB_CHARGE_EFFECT = "Projects/Sources/Lua/Effect/NormalBombChargeEffect.lua";                                ///< @brief ノーマルボムチャージエフェクト
                const char* s_pNORMAL_BOMB_EFFECT = "Projects/Sources/Lua/Effect/NormalBombEffect.lua";                                             ///< @brief ノーマルボムエフェクト
                const char* s_pOPTION_OWN_CRASH_EFFECT_01 = "Projects/Sources/Lua/Effect/OptionOwnCrashEffect01.lua";                               ///< @brief オプション自爆エフェクト01
                const char* s_pPLAYER_FLAREBACK_EFFECT = "Projects/Sources/Lua/Effect/PlayerFlarebackEffect.lua";                                   ///< @brief プレイヤーフレーヤーバックエフェクト
                const char* s_pCONNECT_EFFECT = "Projects/Sources/Lua/Effect/ConnectEffect.lua";                                                    ///< @brief 連結エフェクト
                const char* s_pPLAYER_EXPLOSION_EFFECT = "Projects/Sources/Lua/Effect/PlayerExplosionEffect.lua";                                   ///< @brief プレイヤーの爆発エフェクト
                const char* s_pOPTION_EXPLOSION_EFFECT = "Projects/Sources/Lua/Effect/OptionExplosionEffect.lua";                                   ///< @brief オプションの爆発エフェクト
                const char* s_pPLAYER_BEAM_COLLISION_EFFECT = "Projects/Sources/Lua/Effect/PlayerBeamCollisionEffect.lua";                          ///< @brief プレイヤーのビーム衝突エフェクト  
                const char* s_pOPTION_SMALL_BEAM_COLLISION_EFFECT = "Projects/Sources/Lua/Effect/OptionSmallBeamCollisionEffect.lua";               ///< @brief オプションのスモールビーム衝突エフェクト  
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
            const char* s_pTO_TITLE_SCENE = "ToTitleScene";                                                                                         ///< @brief タイトルシーンへ変更
            const char* s_pTO_RANKING_SCENE = "ToRankingScene";                                                                                     ///< @brief ランキングシーンへ変更
            const char* s_pTO_GAME_01_SCENE = "ToGame01Scene";                                                                                      ///< @brief ゲーム01シーンへ変更
            const char* s_pTO_GAME_02_SCENE = "ToGame02Scene";                                                                                      ///< @brief ゲーム02シーンへ変更
            const char* s_pTO_GAME_03_SCENE = "ToGame03Scene";                                                                                      ///< @brief ゲーム03シーンへ変更
            const char* s_pTO_PAUSE = "ToPauseScene";                                                                                               ///< @brief ポーズシーンへ変更
            const char* s_pRESUME_GAME = "ResumeGame";                                                                                              ///< @brief ゲームを再開
            const char* s_pRESTART_GAME = "RestartGame";                                                                                            ///< @brief ゲームをリスタート
            const char* s_pEXIT_GAME = "ExitGame";                                                                                                  ///< @brief ゲーム終了
            const char* s_pOWN_CRASH = "OwnCrash";                                                                                                  ///< @brief 自爆
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
                    float s_sceneController = 100.0f;                                                                                               ///< @brief シーンコントローラ
                    float s_ui = 90.0f;                                                                                                             ///< @brief UI
                    float s_cameraController = 50.0f;                                                                                               ///< @brief カメラコントローラ
                    float s_player = 10.0f;                                                                                                         ///< @brief プレイヤー
                    float s_option = 9.0f;                                                                                                          ///< @brief オプション
                    float s_shield = 8.5f;                                                                                                          ///< @brief シールド
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
                    float s_sceneController = 100.0f;                                                                                               ///< @brief シーンコントローラ
                    float s_ui = 90.0f;                                                                                                             ///< @brief UI
                    float s_cameraController = 50.0f;                                                                                               ///< @brief カメラコントローラ
                    float s_background = 11.0f;                                                                                                     ///< @brief 背景
                    float s_bomb = 10.0f;                                                                                                           ///< @brief ボム
                    float s_effect = 9.0f;                                                                                                          ///< @brief エフェクト
                    float s_obstacle = 8.0f;                                                                                                        ///< @brief 障害物
                    float s_bullet = 7.0f;                                                                                                          ///< @brief 弾
                    float s_enemy = 6.0f;                                                                                                           ///< @brief 敵
                    float s_shield = 5.5f;                                                                                                          ///< @brief シールド
                    float s_option = 5.0f;                                                                                                          ///< @brief オプション
                    float s_player = 4.0f;                                                                                                          ///< @brief プレイヤー
                }
            }


            /* スプライト */
            namespace Sprite
            {
                const float s_BILLBOARD = 10.0f;                                                                                                    ///< @brief ビルボード
                const float s_BACKGROUND = 3.0f;                                                                                                    ///< @brief 背景
                const float s_IMAGE_UI = 2.0f;                                                                                                      ///< @brief 画像UI
                const float s_FONT = 1.0f;                                                                                                          ///< @brief フォント
                const float s_FADE = 0.0f;                                                                                                          ///< @brief フェード
            }
        }
    }


    /* ゲームオブジェクトの種類 */
    enum eGameObjectType
    {
        TYPE_SCENE_CONTROLLER,                                                                                                                      ///< @brief シーンコントローラ
        TYPE_CAMERA_CONTROLLER,                                                                                                                     ///< @brief カメラコントローラ
        TYPE_PLAYER,                                                                                                                                ///< @brief プレイヤー
        TYPE_OPTION,                                                                                                                                ///< @brief オプション
        TYPE_ENEMY,                                                                                                                                 ///< @brief 敵
        TYPE_BULLET,                                                                                                                                ///< @brief 弾
        TYPE_OBSTACLE,                                                                                                                              ///< @brief 障害物
        TYPE_EFFECT,                                                                                                                                ///< @brief エフェクト
        TYPE_BOMB,                                                                                                                                  ///< @brief ボム
        TYPE_BACKGROUND,                                                                                                                            ///< @brief 背景
        TYPE_UI,                                                                                                                                    ///< @brief UI
        TYPE_FADE,                                                                                                                                  ///< @brief フェード
        TYPE_SHIELD,                                                                                                                                ///< @brief シールド

        TYPE_TYPE_NUMBER,                                                                                                                           ///< @brief 種類の数
    };
}