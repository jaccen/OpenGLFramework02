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
    using Vector2 = Math::S_Vector2<float>;                                                                                                         // Vector2�^
    using Vector3 = Math::S_Vector3<float>;                                                                                                         // Vector3�^    
    using Vector4 = Math::S_Vector4<float>;                                                                                                         // Vector4�^
    using Matrix3x3 = Math::S_Matrix3x3<float>;                                                                                                     // Matrix3x3�^
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                                                                                     // Matrix4x4�^
    using Telegram = GameObject::Message::S_Telegram;                                                                                               // Telegram�^


    /** �J�����̏�� */
    struct S_CameraData
    {
        Matrix4x4 viewMatrix_;                                                                                                                      ///< @brief �r���[�s��
        Matrix4x4 projectionMatrix_;                                                                                                                ///< @brief �v���W�F�N�V�����s��
        Matrix4x4 viewProjectionMatrix_;                                                                                                            ///< @brief �r���[�v���W�F�N�V�����s��
    };


    namespace
    {
        /* ID */
        namespace ID
        {

            /* �J���� */
            namespace Camera
            {
                const char* s_pMAIN = "Main";                                                                                                       ///< @brief ���C���J����
                const char* s_pBACKGROUND = "Background";                                                                                           ///< @brief �w�i�p�J����
                const char* s_pUI = "UICamera";                                                                                                     ///< @brief UI�J����
            }


            /* �V�F�[�_�[ */
            namespace Shader
            {
                const char* s_pPHONG = "PhongShader";                                                                                               ///< @brief �t�H��
                const char* s_pPHONG_TEXTURE = "PhongTextureShader";                                                                                ///< @brief �t�H��( �e�N�X�`�� )
                const char* s_pCELESTIAL_SPHERE = "CelestialSphereShader";                                                                          ///< @brief �V��
                const char* s_pLOAD = "LoadShader";                                                                                                 ///< @brief ���[�h�p
            }


            /* �}�e���A�� */
            namespace Material
            {
                const char* s_pBASIC = "Basic";                                                                                                     ///< @brief ��{
                const char* s_pDAMAGE = "Damage";                                                                                                   ///< @brief �_���[�W
            }

            /* ���C�g */
            namespace Light
            {
                const char* s_pMAIN = "Main";                                                                                                       ///< @brief ���C��
            }


            /* �e�N�X�`�� */
            namespace Texture
            {
                const char* s_pLOAD = "LoadTexture";                                                                                                ///< @brief ���[�h�p
            }


            /* �v���~�e�B�u */
            namespace Primitive
            {
                const char* s_pLOAD = "LoadPrimitive";                                                                                              ///< @brief ���[�h�p
                const char* s_pNORMAL_PLAYER = "NormalPlayerPrimitive";                                                                             ///< @brief �ʏ�v���C���[
                const char* s_pSPEED_UP_OPTION = "SpeedUpOptionPrimitive";                                                                          ///< @brief �X�s�[�h�A�b�v�I�v�V����
                const char* s_pSMALL_BEAM_OPTION = "SmallBeamOptionPrimitive";                                                                      ///< @brief �X���[���r�[���I�v�V����
                const char* s_pBOX_ENEMY = "BoxEnemyPrimitive";                                                                                     ///< @brief �{�b�N�X�G�l�~�[
                const char* s_pSPACE = "SpacePrimitive";                                                                                            ///< @brief �F��
                const char* s_pSHELTER = "ShelterPrimitive";                                                                                        ///< @brief �V�F���^�[
            }


            /* ���j�t�H�[���o�b�t�@ */
            namespace UniformBuffer
            {
                const char* s_pMAIN_CAMERA = "MainCamera";                                                                                          ///< @brief ���C���J����
                const char* s_pBACKGROUND_CAMERA = "BackgroungCamera";                                                                              ///< @brief �w�i�J����
                const char* s_pUI_CAMERA = "UiCamera";                                                                                              ///< @brief UI�J����
            }


            /* �W�F�l���[�^ */
            namespace Generator
            {
                /* �v���C���[ */
                namespace Player
                {
                    const char* s_pNORMAL = "NormalPlayer";                                                                                         ///< @brief �ʏ�v���C���[
                }

                /* �I�v�V���� */
                namespace Option
                {
                    const char* s_pSPEED_UP = "SpeedUpOption";                                                                                      ///< @brief �X�s�[�h�A�b�v�I�v�V����
                    const char* s_pSMALL_BEAM = "SmallBeamOption";                                                                                  ///< @brief �X���[���r�[���I�v�V����
                }

                /* �G */
                namespace Enemy
                {
                    const char* s_pBOX = "BoxEnemy";                                                                                                ///< @brief �{�b�N�X�G�l�~�[
                }


                /* �e */
                namespace Bullet
                {
                    /* �v���C���[ */
                    namespace Player
                    {
                        const char* s_pBEAM = "PlayerBeamBullet";                                                                                   ///< @brief �r�[���e
                    }

                    /* �I�v�V���� */
                    namespace Option
                    {
                        const char* s_pSMALL_BEAM = "OptionSmallBeamBullet";                                                                        ///< @brief �������r�[���e
                    }
                }

                /* �G�t�F�N�g */
                namespace Effect
                {
                    namespace Bomb
                    {
                        const char* s_pCHARGE = "BombChargeEffect";                                                                                 ///< @brief �{���`���[�W
                    }
                }
            }

            /* �V�[�� */
            namespace Scene
            {
                const char* s_pTITLE = "TitleScene";                                                                                                ///< @brief �^�C�g��
                const char* s_pSTAGE01 = "Stage01Scene";                                                                                            ///< @brief �X�e�[�W01
                const char* s_pLOAD = "LoadScene";                                                                                                  ///< @brief ���[�h
            }


            /* �Q�[���I�u�W�F�N�g */
            namespace GameObject
            {
                const char* s_pGAME_CONTROLLER = "GameController";                                                                                  ///< @brief �Q�[���R���g���[���[
                const char* s_pCAMERA_CONTROLLER = "CameraController";                                                                              ///< @brief �J�����R���g���[���[
                const char* s_pPLAYER = "Player";                                                                                                   ///< @brief �v���C���[
                const char* s_pOPTION = "Option";                                                                                                   ///< @brief �I�v�V����
                const char* s_pENEMY = "Enemy";                                                                                                     ///< @brief �G
                const char* s_pBULLET = "Bullet";                                                                                                   ///< @brief �e
                const char* s_pEFFECT = "Effect";                                                                                                   ///< @brief �G�t�F�N�g
                const char* s_pBACKGROUND = "Background";                                                                                           ///< @brief �w�i
            }


            /* JSON */
            namespace JSON
            {
                const char* s_pNORMAL_PLAYER = "NormalPlayerJson";                                                                                  ///< @brief �ʏ�v���C���[
                const char* s_pSPEED_UP_OPTION = "SpeedUpOptionJson";                                                                               ///< @brief �X�s�[�h�A�b�v�I�v�V����
                const char* s_pSMALL_BEAM_OPTION = "SmallBeamOptionJson";                                                                           ///< @brief �X���[���r�[���I�v�V����
                const char* s_pSHIELD_OPTION = "ShieldOptionJson";                                                                                  ///< @brief �V�[���h�I�v�V����
                const char* s_pPLAYER_BULLET = "PlayerBulletJson";                                                                                  ///< @brief �v���C���[�e
                const char* s_pOPTION_BULLET = "OptionBulletJson";                                                                                  ///< @brief �I�v�V�����e
                const char* s_pSTAGE_01_ENEMY_DATA = "Stage01EnemyDataJson";                                                                        ///< @brief �X�e�[�W01�G�f�[�^
                const char* s_pSPACE = "SpaceJson";                                                                                                 ///< @brief �F��
                const char* s_pSHELTER = "ShelterJson";                                                                                             ///< @brief �V�F���^�[
                const char* s_pSTAGE_01_CAMERAWORK_DATA = "Stage01CameraworkDataJson";                                                              ///< @brief �X�e�[�W01�J�������[�N�f�[�^
            }

            /* ���f�� */
            namespace Model
            {
                const char* s_pNORMAL_PLAYER = "NormalPlayerModel";                                                                                 ///< @brief �ʏ�v���C���[
                const char* s_pSPPED_UP_OPTION = "SpeedUpOptionModel";                                                                              ///< @brief �X�s�[�h�A�b�v�I�v�V����
                const char* s_pSMALL_BEAM_OPTION = "SmallBeamOptionModel";                                                                          ///< @brief �X���[���r�[���I�v�V����
                const char* s_pBOX_ENEMY = "BoxEnemyModel";                                                                                         ///< @brief �{�b�N�X�G�l�~�[
                const char* s_pSPACE = "SpaceModel";                                                                                                ///< @brief �F��
                const char* s_pSHELTER = "ShelterModel";                                                                                            ///< @brief �V�F���^�[
            }

            /* �X�v���C�g */
            namespace Sprite
            {
                const char* s_pBULLET = "BulletSprite";                                                                                             ///< @brief�@�e
            }

            /* �p�[�e�B�N�� */
            namespace Particle
            {
                const char* s_pCIRCLE_01 = "Circle01Particle";                                                                                      ///< @brief �~01
                const char* s_pCIRCLE_02 = "Circle02Particle";                                                                                      ///< @brief �~02
                const char* s_pRING_01 = "Ring01Particle";                                                                                          ///< @brief ��01
            }
        }


        /* �p�X */
        namespace Path
        {
            /* �V�F�[�_�[ */
            namespace Shader
            {
                namespace Vertex
                {
                    const char* s_pPHONG = "Projects/Shaders/GLSL/Phong/Phong.vert";                                                                ///< @brief �t�H��
                    const char* s_pPHONG_TEXTURE = "Projects/Shaders/GLSL/Phong/PhongTexture.vert";                                                 ///< @brief �t�H��( �e�N�X�`�� )
                    const char* s_pCELESTINAL_SPHERE = "Projects/Shaders/GLSL/CelestialSphere/CelestialSphere.vert";                                ///< @brief �V��
                }


                namespace Geometry
                {
                }


                namespace Fragment
                {
                    const char* s_pPHONG = "Projects/Shaders/GLSL/Phong/Phong.frag";                                                                ///< @brief �t�H��
                    const char* s_pPHONG_TEXTURE = "Projects/Shaders/GLSL/Phong/PhongTexture.frag";                                                 ///< @brief �t�H��( �e�N�X�`�� )
                    const char* s_pCELESTINAL_SPHERE = "Projects/Shaders/GLSL/CelestialSphere/CelestialSphere.frag";                                ///< @brief �V��
                }
            }


            /* �e�N�X�`�� */
            namespace Texture
            {
                const char* s_pNORMAL_PLAYER = "Projects/Images/ConnectWars/Player/NormalPlayer.png";                                               ///< @brief �ʏ�v���C���[
                const char* s_pSPPED_UP_OPTION = "Projects/Images/ConnectWars/Option/SpeedUpOption.png";                                            ///< @brief �X�s�[�h�A�b�v�I�v�V����
                const char* s_pSMALL_BEAM_OPTION = "Projects/Images/ConnectWars/Option/SmallBeamOption.png";                                        ///< @brief �X���[���r�[���I�v�V����
                const char* s_pSPRITE_BULLET = "Projects/Images/ConnectWars/Bullet/SpriteBullet.png";                                               ///< @brief �X�v���C�g�̒e
                const char* s_pCIRCLE_01 = "Projects/Images/ConnectWars/Effect/Circle01.png";                                                       ///< @brief �~01
                const char* s_pCIRCLE_02 = "Projects/Images/ConnectWars/Effect/Circle02.png";                                                       ///< @brief �~02
                const char* s_pRING_01 = "Projects/Images/ConnectWars/Effect/Ring01.png";                                                           ///< @brief ��01
                const char* s_pSPACE = "Projects/Images/ConnectWars/Background/Space.png";                                                          ///< @brief �F��
                const char* s_pSHELTER = "Projects/Images/ConnectWars/Background/Shelter.png";                                                      ///< @brief �V�F���^�[
                const char* s_pSHALTER_NORMAL = "Projects/Images/ConnectWars/Background/Shelter_NormalMap.png";                                     ///< @brief �V�F���^�[( �@���}�b�v )
            }

            /* �t�H���g */
            namespace Font
            {
                const char* s_pLOAD = "Projects/Fonts/apjffont/APJapanesefontF.ttf";                                                                ///< @brief ���[�h�p
            }


            /* ���f�� */
            namespace Model
            {
                const char* s_pNORMAL_PLAYER = "Projects/Models/ConnectWars/Player/Normal/NormalPlayer.model";                                      ///< @brief �ʏ�v���C���[
                const char* s_pSPEED_UP_OPTION = "Projects/Models/ConnectWars/Option/SpeedUp/SpeedUpOption.model";                                  ///< @brief �X�s�[�h�A�b�v�I�v�V����
                const char* s_pSMALL_BEAM_OPTION = "Projects/Models/ConnectWars/Option/SmallBeam/SmallBeamOption.model";                            ///< @brief �X���[���r�[���I�v�V����
                const char* s_pBOX_ENEMY = "Projects/Models/Test/Box/Box.model";                                                                    ///< @brief �{�b�N�X�G�l�~�[
                const char* s_pSPACE = "Projects/Models/ConnectWars/Background/Space/Sphere.model";                                                 ///< @brief �F��
                const char* s_pSHELTER = "Projects/Models/ConnectWars/Background/Shelter/Shelter.model";                                            ///< @brief �V�F���^�[
            }


            /* JSON */
            namespace JSON
            {
                const char* s_pCAMERA = "Projects/GameDatas/ConnectWars/JSON/Camera/CameraData.json";                                               ///< @brief �J����
                const char* s_pNORMAL_PLAYER = "Projects/GameDatas/ConnectWars/JSON/Player/NormalPlayerData.json";                                  ///< @brief �ʏ�v���C���[
                const char* s_pSPEED_UP_OPTION = "Projects/GameDatas/ConnectWars/JSON/Option/SpeedUpOptionData.json";                               ///< @brief �X�s�[�h�A�b�v�I�v�V����
                const char* s_pSMALL_BEAM_OPTION = "Projects/GameDatas/ConnectWars/JSON/Option/SmallBeamOptionData.json";                           ///< @brief �X���[���r�[���I�v�V����
                const char* s_pPLAYER_BULLET = "Projects/GameDatas/ConnectWars/JSON/Bullet/Player/PlayerBulletDatas.json";                          ///< @brief �v���C���[�e
                const char* s_pOPTION_BULLET = "Projects/GameDatas/ConnectWars/JSON/Bullet/Option/OptionBulletDatas.json";                          ///< @brief �I�v�V�����e
                const char* s_pSTAGE_01_ENEMY_DATA = "Projects/GameDatas/ConnectWars/JSON/Enemy/Stage01/Stage01EnemyData.json";                     ///< @breif �X�e�[�W01�G�f�[�^
                const char* s_pTASK_PRIORITY_DATA = "Projects/GameDatas/ConnectWars/JSON/Task/TaskPriorityData.json";                               ///< @breif �^�X�N�̗D��x�f�[�^
                const char* s_pSPACE = "Projects/GameDatas/ConnectWars/JSON/Background/SpaceData.json";                                             ///< @brief �F��
                const char* s_pSHELTER = "Projects/GameDatas/ConnectWars/JSON/Background/ShelterData.json";                                         ///< @brief �V�F���^�[
                const char* s_pMATERIAL_DATA = "Projects/GameDatas/ConnectWars/JSON/Material/MaterialData.json";                                    ///< @brief �}�e���A���f�[�^
                const char* s_pLIGHT_DATA = "Projects/GameDatas/ConnectWars/JSON/Light/LightData.json";                                             ///< @brief ���C�g���
                const char* s_pSTAGE_01_CAMERAWORK_DATA = "Projects/GameDatas/ConnectWars/JSON/Camera/Stage01/Stage01CameraworkData.json";          ///< @brief �X�e�[�W01�J�������[�N�f�[�^
            }

            /* Lua */
            namespace Lua
            {
                const char* s_pBOMB_CHARGE_EFFECT = "Projects/Sources/Lua/Effect/BombChargeEffect.lua";                                             ///< @brief �{���̃`���[�W�G�t�F�N�g
            }
        }


        /* �X�e�[�W�T�C�Y */
        namespace StageSize
        {
            float s_left = -16.0f;                                                                                                                  ///< @brief ���[
            float s_right = 16.0f;                                                                                                                  ///< @brief �E�[
            float s_top = 12.0f;                                                                                                                    ///< @brief ��[
            float s_bottom = -12.0f;                                                                                                                ///< @brief ���[
        }


        /* �A�� */
        namespace Connect
        {
            float s_offsetFactor = 0.92f;                                                                                                           ///< @brief �I�t�Z�b�g�W��
        }


        /* ���b�Z�[�W */
        namespace Message
        {
            const char* s_pCONNECT_CHECK = "ConnectCheck";                                                                                          ///< @brief �A���m�F
            const char* s_pWAIT = "Wait";                                                                                                           ///< @brief �ҋ@
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
                    float s_gameController = 100.0f;                                                                                                ///< @brief �Q�[���R���g���[��
                    float s_cameraController = 50.0f;                                                                                               ///< @brief �J�����R���g���[��
                    float s_player = 10.0f;                                                                                                         ///< @brief �v���C���[
                    float s_option = 9.0f;                                                                                                          ///< @brief �I�v�V����
                    float s_enemy = 8.0f;                                                                                                           ///< @brief �G
                    float s_bullet = 7.0f;                                                                                                          ///< @brief �e
                    float s_obstacle = 6.0f;                                                                                                        ///< @brief ��Q��
                    float s_effect = 5.0f;                                                                                                          ///< @brief �G�t�F�N�g
                    float s_bomb = 4.0f;                                                                                                            ///< @brief �{��
                    float s_background = 3.0f;                                                                                                      ///< @brief �w�i
                }

                /* �`�� */
                namespace Draw
                {
                    float s_gameController = 100.0f;                                                                                                ///< @brief �Q�[���R���g���[��
                    float s_cameraController = 50.0f;                                                                                               ///< @brief �J�����R���g���[��
                    float s_background = 11.0f;                                                                                                     ///< @brief �w�i
                    float s_bomb = 10.0f;                                                                                                           ///< @brief �{��
                    float s_effect = 9.0f;                                                                                                          ///< @brief �G�t�F�N�g
                    float s_obstacle = 8.0f;                                                                                                        ///< @brief ��Q��
                    float s_bullet = 7.0f;                                                                                                          ///< @brief �e
                    float s_enemy = 6.0f;                                                                                                           ///< @brief �G
                    float s_option = 5.0f;                                                                                                          ///< @brief �I�v�V����
                    float s_player = 4.0f;                                                                                                          ///< @brief �v���C���[
                }
            }


            /* �X�v���C�g */
            namespace Sprite
            {
                const float s_BILLBOARD = 10.0f;                                                                                                    ///< @brief �r���{�[�h
                const float s_UI = 0.0f;                                                                                                            ///< @brief UI
            }
        }
    }


    /* �Q�[���I�u�W�F�N�g�̎�� */
    enum eGameObjectType
    {
        TYPE_GAME_CONTROLLER,                                                                                                                       ///< @brief �Q�[���R���g���[��
        TYPE_CAMERA_CONTROLLER,                                                                                                                     ///< @brief �J�����R���g���[��
        TYPE_PLAYER,                                                                                                                                ///< @brief �v���C���[
        TYPE_OPTION,                                                                                                                                ///< @brief �I�v�V����
        TYPE_ENEMY,                                                                                                                                 ///< @brief �G
        TYPE_BULLET,                                                                                                                                ///< @brief �e
        TYPE_OBSTACLE,                                                                                                                              ///< @brief ��Q��
        TYPE_EFFECT,                                                                                                                                ///< @brief �G�t�F�N�g
        TYPE_BOMB,                                                                                                                                  ///< @brief �{��
        TYPE_BACKGROUND,                                                                                                                            ///< @brief �w�i

        TYPE_TYPE_NUMBER,                                                                                                                           ///< @brief ��ނ̐�
    };
}