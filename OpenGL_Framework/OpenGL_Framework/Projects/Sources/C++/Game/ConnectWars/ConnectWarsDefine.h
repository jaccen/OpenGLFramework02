/* ��d�C���N���[�h�h�~ */
#pragma once


#include "../../Library/Math/Vector/Vector4.h"
#include "../../Library/Math/Matrix/Matrix4x4.h"
#include "../../Library/GameObject/Message/Telegram/Telegram.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* �^�ϊ� */
    using Vector2 = Math::S_Vector2<float>;                                                                                     // Vector2�^
    using Vector3 = Math::S_Vector3<float>;                                                                                     // Vector3�^    
    using Vector4 = Math::S_Vector4<float>;                                                                                     // Vector4�^
    using Matrix3x3 = Math::S_Matrix3x3<float>;                                                                                 // Matrix3x3�^
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                                                                 // Matrix4x4�^
    using Telegram = GameObject::Message::S_Telegram;                                                                           // Telegram�^


    /** �J�����̏�� */
    struct S_CameraData
    {
        Matrix4x4 viewMatrix_;                                                                                                  ///< @brief �r���[�s��
        Matrix4x4 projectionMatrix_;                                                                                            ///< @brief �v���W�F�N�V�����s��
        Matrix4x4 viewProjectionMatrix_;                                                                                        ///< @brief �r���[�v���W�F�N�V�����s��
    };


    namespace
    {
        /* ID */
        namespace ID
        {

            /* �J���� */
            namespace Camera
            {
                const char* s_pMAIN = "MainCamera";                                                                             ///< @brief ���C���J����
                const char* s_pUI = "UICamera";                                                                                 ///< @brief UI�J����
            }


            /* �V�F�[�_�[ */
            namespace Shader
            {
                const char* s_pHALF_LAMBERT_PHONG = "HalfLamberPhongShader";                                                    ///< @brief �n�[�t�����o�[�g�t�H��
                const char* s_pLOAD = "LoadShader";                                                                             ///< @brief ���[�h�p
            }


            /* �e�N�X�`�� */
            namespace Texture
            {
                const char* s_pLOAD = "LoadTexture";                                                                            ///< @brief ���[�h�p
            }


            /* �v���~�e�B�u */
            namespace Primitive
            {
                const char* s_pLOAD = "LoadPrimitive";                                                                          ///< @brief ���[�h�p
                const char* s_pNORMAL_PLAYER = "NormalPlayerPrimitive";                                                         ///< @brief �ʏ�v���C���[
            }


            /* ���j�t�H�[���o�b�t�@ */
            namespace UniformBuffer
            {
                const char* s_pMAIN_CAMERA = "MainCamera";                                                                      ///< @brief ���C���J�����p
            }


            /* �W�F�l���[�^ */
            namespace Generator
            {
                /* �v���C���[ */
                namespace Player
                {
                    const char* s_pNORMAL = "NormalPlayer";                                                                     ///< @brief �ʏ�v���C���[
                }

                /* �I�v�V���� */
                namespace Option
                {
                    const char* s_pSPEED_UP = "SpeedUpOption";                                                                  ///< @brief �X�s�[�h�A�b�v�I�v�V����
                    const char* s_pSMALL_BEAM = "SmallBeamOption";                                                              ///< @brief �X���[���r�[���I�v�V����
                }

                /* �e */
                namespace Bullet
                {
                    /* �v���C���[ */
                    namespace Player
                    {
                        const char* s_pBEAM = "PlayerBeamBullet";                                                               ///< @brief �r�[���e
                    }

                    /* �I�v�V���� */
                    namespace Option
                    {
                        const char* s_pSMALL_BEAM = "OptionSmallBeamBullet";                                                    ///< @brief �������r�[���e
                    }
                }

                /* �G�t�F�N�g */
                namespace Effect
                {
                    namespace Bomb
                    {
                        const char* s_pCHARGE = "BombChargeEffect";                                                             ///< @brief �{���`���[�W
                    }
                }
            }

            /* �V�[�� */
            namespace Scene
            {
                const char* s_pTITLE = "TitleScene";                                                                            ///< @brief �^�C�g��
                const char* s_pSTAGE01 = "Stage01Scene";                                                                        ///< @brief �X�e�[�W01
                const char* s_pLOAD = "LoadScene";                                                                              ///< @brief ���[�h
            }


            /* �Q�[���I�u�W�F�N�g */
            namespace GameObject
            {
                const char* s_pPLAYER = "Player";                                                                               ///< @brief �v���C���[
                const char* s_pOPTION = "Option";                                                                               ///< @brief �I�v�V����
                const char* s_pBULLET = "Bullet";                                                                               ///< @brief �e
                const char* s_pEFFECT = "Effect";                                                                               ///< @brief �G�t�F�N�g
            }


            /* JSON */
            namespace JSON
            {
                const char* s_pNORMAL_PLAYER = "NormalPlayerJson";                                                              ///< @brief �ʏ�v���C���[
                const char* s_pSPEED_UP_OPTION = "SpeedUpOptionJson";                                                           ///< @brief �X�s�[�h�A�b�v�I�v�V����
                const char* s_pSMALL_BEAM_OPTION = "SmallBeamOptionJson";                                                       ///< @brief �X���[���r�[���I�v�V����
                const char* s_pPLAYER_BULLET = "PlayerBulletJson";                                                              ///< @brief �v���C���[�e
                const char* s_pOPTION_BULLET = "OptionBulletJson";                                                              ///< @brief �I�v�V�����e
            }

            /* ���f�� */
            namespace Model
            {
                const char* s_pNORMAL_PLAYER = "NormalPlayerModel";                                                             ///< @brief �ʏ�v���C���[
            }

            /* �X�v���C�g */
            namespace Sprite
            {
                const char* s_pBULLET = "BulletSprite";                                                                         ///< @brief�@�e
            }

            /* �p�[�e�B�N�� */
            namespace Particle
            {
                const char* s_pCIRCLE_01 = "Circle01";                                                                          ///< @brief �~01
                const char* s_pCIRCLE_02 = "Circle02";                                                                          ///< @brief �~02
                const char* s_pRING_01 = "Ring01";                                                                              ///< @brief ��01
            }
        }


        /* �p�X */
        namespace Path
        {
            /* �e�N�X�`�� */
            namespace Texture
            {
                const char* s_pSPRITE_BULLET = "Projects/Images/ConnectWars/Bullet/SpriteBullet.png";                           ///< @brief �X�v���C�g�̒e
                const char* s_pCIRCLE_01 = "Projects/Images/ConnectWars/Effect/Circle01.png";                                   ///< @brief �~01
                const char* s_pCIRCLE_02 = "Projects/Images/ConnectWars/Effect/Circle02.png";                                   ///< @brief �~02
                const char* s_pRING_01 = "Projects/Images/ConnectWars/Effect/Ring01.png";                                       ///< @brief ��01
            }

            /* �t�H���g */
            namespace Font
            {
                const char* s_pLOAD = "Projects/Fonts/apjffont/APJapanesefontF.ttf";                                            ///< @brief ���[�h�p
            }


            /* ���f�� */
            namespace Model
            {
                const char* s_pNORMAL_PLAYER = "Projects/Models/Test/Sphere/Sphere.model";                                      ///< @brief �ʏ�v���C���[
            }


            /* JSON */
            namespace JSON
            {
                const char* s_pCAMERA = "Projects/GameDatas/ConnectWars/JSON/Camera/CameraData.json";                           ///< @brief �J����
                const char* s_pNORMAL_PLAYER = "Projects/GameDatas/ConnectWars/JSON/Player/NormalPlayerData.json";              ///< @brief �ʏ�v���C���[
                const char* s_pSPEED_UP_OPTION = "Projects/GameDatas/ConnectWars/JSON/Option/SpeedUpOptionData.json";           ///< @brief �X�s�[�h�A�b�v�I�v�V����
                const char* s_pSMALL_BEAM_OPTION = "Projects/GameDatas/ConnectWars/JSON/Option/SmallBeamOptionData.json";       ///< @brief �X���[���r�[���I�v�V����
                const char* s_pPLAYER_BULLET = "Projects/GameDatas/ConnectWars/JSON/Bullet/Player/PlayerBulletDatas.json";      ///< @brief �v���C���[�e
                const char* s_pOPTION_BULLET = "Projects/GameDatas/ConnectWars/JSON/Bullet/Option/OptionBulletDatas.json";      ///< @brief �I�v�V�����e
            }

            /* Lua */
            namespace Lua
            {
                const char* s_pBOMB_CHARGE_EFFECT = "Projects/Sources/Lua/Effect/BombChargeEffect.lua";                         ///< @brief �{���̃`���[�W�G�t�F�N�g
            }
        }


        /* �X�e�[�W�T�C�Y */
        namespace StageSize
        {
            float s_left = -16.0f;                                                                                              ///< @brief ���[
            float s_right = 16.0f;                                                                                              ///< @brief �E�[
            float s_top = 12.0f;                                                                                                ///< @brief ��[
            float s_bottom = -12.0f;                                                                                            ///< @brief ���[
        }


        /* �A�� */
        namespace Connect
        {
            float s_offsetFactor = 0.8f;                                                                                        ///< @brief �I�t�Z�b�g�W��
        }


        /* ���b�Z�[�W */
        namespace Message
        {
            const char* s_pCONNECT_CHECK = "ConnectCheck";                                                                      ///< @brief �A���m�F
        }


        /* �D��x */
        namespace Priority
        {
            /* �^�X�N */
            namespace Task
            {
                /* �X�V */
                namespace Update
                {
                    float s_player = 10.0f;                                                                                     ///< @brief �v���C���[
                    float s_option = 9.0f;                                                                                      ///< @brief �I�v�V����
                    float s_enemy = 8.0f;                                                                                       ///< @brief �G
                    float s_bullet = 7.0f;                                                                                      ///< @brief �e
                    float s_obstacle = 6.0f;                                                                                    ///< @brief ��Q��
                    float s_effect = 5.0f;                                                                                      ///< @brief �G�t�F�N�g
                    float s_bomb = 4.0f;                                                                                        ///< @brief �{��
                }

                /* �`�� */
                namespace Draw
                {
                    float s_bomb = 10.0f;                                                                                       ///< @brief �{��
                    float s_effect = 9.0f;                                                                                      ///< @brief �G�t�F�N�g
                    float s_obstacle = 8.0f;                                                                                    ///< @brief ��Q��
                    float s_bullet = 7.0f;                                                                                      ///< @brief �e
                    float s_enemy = 6.0f;                                                                                       ///< @brief �G
                    float s_option = 5.0f;                                                                                      ///< @brief �I�v�V����
                    float s_player = 4.0f;                                                                                      ///< @brief �v���C���[
                }
            }


            /* �X�v���C�g */
            namespace Sprite
            {
                const float s_BILLBOARD = 10.0f;                                                                                ///< @brief �r���{�[�h
                const float s_UI = 0.0f;                                                                                        ///< @brief UI
            }
        }
    }


    /* �Q�[���I�u�W�F�N�g�̎�� */
    enum eGameObjectType
    {
        TYPE_PLAYER,                                                                                                            ///< @brief �v���C���[
        TYPE_OPTION,                                                                                                            ///< @brief �I�v�V����
        TYPE_ENEMY,                                                                                                             ///< @brief �G
        TYPE_BULLET,                                                                                                            ///< @brief �e
        TYPE_OBSTACLE,                                                                                                          ///< @brief ��Q��
        TYPE_EFFECT,                                                                                                            ///< @brief �G�t�F�N�g
        TYPE_BOMB,                                                                                                              ///< @brief �{��

        TYPE_TYPE_NUMBER,                                                                                                       ///< @brief ��ނ̐�
    };

}