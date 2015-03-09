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
                const char* s_pPHONG_NORMAL_TEXTURE = "PhongNormalTexture";                                                                         ///< @brief �t�H��( �m�[�}���e�N�X�`�� )
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
                const char* s_pSHELTER = "Shelter";                                                                                                 ///< @brief �V�F���^�[
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
                const char* s_pSHIELD_OPTION = "ShieldOptionPrimitive";                                                                             ///< @brief �V�[���h�I�v�V����
                const char* s_pLASER_OPTION = "LaserOptionPrimitive";                                                                               ///< @brief ���[�U�[�I�v�V����
                const char* s_pBOX_ENEMY = "BoxEnemyPrimitive";                                                                                     ///< @brief �{�b�N�X�G�l�~�[
                const char* s_pSLIME_ENEMY = "SlimeEnemyPrimitive";                                                                                 ///< @brief �X���C���G�l�~�[
                const char* s_pROUND_ENEMY = "RoundEnemyPrimitive";                                                                                 ///< @brief ���E���h�G�l�~�[
                const char* s_pGROUP_SHIP_ENEMY = "GroupShipEnemyPrimitive";                                                                        ///< @brief �O���[�v�V�b�v�G�l�~�[
                const char* s_pPYRAMID_ENEMY = "PyramidEnemyPrimitive";                                                                             ///< @brief �s���~�b�h�G�l�~�[
                const char* s_pPHALANX_CORE = "PhalanxCoreyPrimitive";                                                                              ///< @brief �t�@�����N�X( �R�A )
                const char* s_pPHALANX_RING = "PhalanxRingPrimitive";                                                                               ///< @brief �t�@�����N�X( �����O )
                const char* s_pSPACE = "SpacePrimitive";                                                                                            ///< @brief �F��
                const char* s_pSHELTER = "ShelterPrimitive";                                                                                        ///< @brief �V�F���^�[
                const char* s_pEXIT_RING = "ExitRingPrimitive";                                                                                     ///< @brief �G�O�W�b�g�����O
                const char* s_pMETEOR = "Meteor";                                                                                                   ///< @brief 覐�
                const char* s_pROCK = "Rock";                                                                                                       ///< @brief ��
                const char* s_pBACKGROUND_METEOR = "BackgroundMeteor";                                                                              ///< @brief �w�i覐�
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
                    const char* s_pSHIELD = "ShieldOption";                                                                                         ///< @brief �V�[���h�I�v�V����
                    const char* s_pLASER = "LaserOption";                                                                                           ///< @brief ���[�U�[
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
                    const char* s_pNORMAL_BOMB_CHARGE = "NormalBombChargeEffect";                                                                   ///< @brief �m�[�}���{���`���[�W
                    const char* s_pNORMAL_BOMB = "NormalBombEffect";                                                                                ///< @brief �m�[�}���{��   
                    const char* s_pOPTION_OWN_CRASH_01 = "OptionOwnCrash01Effect";                                                                  ///< @brief �I�v�V��������01
                    const char* s_pPLAYER_FLAREBACK = "PlayerFlaerBackEffect";                                                                      ///< @brief �v���C���[�t���[���[�o�b�N
                    const char* s_pCONNECT = "ConnectEffect";                                                                                       ///< @brief �A���G�t�F�N�g
                    const char* s_pPLAYER_EXPLOSION = "PlayerExplosionEffect";                                                                      ///< @brief �v���C���[����
                    const char* s_pOPTION_EXPLOSION = "OptionExplosionEffect";                                                                      ///< @brief �I�v�V��������
                    const char* s_pPLAYER_BEAM_COLLISION = "PlayerBeamCollisionEffect";                                                             ///< @brief �v���C���[�r�[���Փ�
                    const char* s_pOPTION_SMALL_BEAM_COLLISION = "OptionSmallBeamCollisionEffect";                                                  ///< @brief �I�v�V�����X���[���r�[���Փ�
                }

                /* �w�i */
                namespace Background
                {
                    const char* s_pSPACE = "Space";                                                                                                 ///< @brief ���
                    const char* s_pSHELTER = "Shelter";                                                                                             ///< @brief �V�F���^�[
                    const char* s_pEXIT_RING = "ExitRing";                                                                                          ///< @brief �G�O�W�b�g�����O 
                    const char* s_pEARTH = "Earth";                                                                                                 ///< @brief �n��
                    const char* s_pBACKGROUND_METEOR = "BackgroundMeteor";                                                                          ///< @brief �w�i覐�
                }

                /* �{�� */
                namespace Bomb
                {
                    const char* s_pNORMAL = "NormalBomb";                                                                                           ///< @brief �m�[�}��
                }

                /* �V�[���h */
                namespace Shield
                {
                    const char* s_pNORMAL = "NormalShield";                                                                                         ///< @brief �m�[�}��
                }
            }

            /* �V�[�� */
            namespace Scene
            {
                const char* s_pTITLE = "TitleScene";                                                                                                ///< @brief �^�C�g��
                const char* s_pRANKING = "RankingScene";                                                                                            ///< @brief �����L���O
                const char* s_pSTAGE01 = "Stage01Scene";                                                                                            ///< @brief �X�e�[�W01
                const char* s_pLOAD = "LoadScene";                                                                                                  ///< @brief ���[�h
            }


            /* �Q�[���I�u�W�F�N�g */
            namespace GameObject
            {
                const char* s_pUI = "Ui";                                                                                                           ///< @brief UI
                const char* s_pPAUSE_UI = "PauseUi";                                                                                                ///< @brief �|�[�YUI
                const char* s_pSCENE_CONTROLLER = "SceneController";                                                                                ///< @brief �V�[���R���g���[��
                const char* s_pPAUSE_CONTROLLER = "PauseController";                                                                                ///< @brief �|�[�Y�R���g���[��
                const char* s_pCAMERA_CONTROLLER = "CameraController";                                                                              ///< @brief �J�����R���g���[��
                const char* s_pPLAYER = "Player";                                                                                                   ///< @brief �v���C���[
                const char* s_pOPTION = "Option";                                                                                                   ///< @brief �I�v�V����
                const char* s_pENEMY = "Enemy";                                                                                                     ///< @brief �G
                const char* s_pBULLET = "Bullet";                                                                                                   ///< @brief �e
                const char* s_pEFFECT = "Effect";                                                                                                   ///< @brief �G�t�F�N�g
                const char* s_pBACKGROUND = "Background";                                                                                           ///< @brief �w�i
                const char* s_pFADE = "Fade";                                                                                                       ///< @brief �t�F�[�h
                const char* s_pBOMB = "Bomb";                                                                                                       ///< @brief �{��
                const char* s_pSHIELD = "Shield";                                                                                                   ///< @brief �V�[���h
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
                const char* s_pSTAGE_01_CAMERAWORK_DATA = "Stage01CameraworkDataJson";                                                              ///< @brief �X�e�[�W01�J�������[�N�f�[�^
                const char* s_pTITLE_UI_DATA = "TitleUiDataJson";                                                                                   ///< @brief �^�C�g��UI�f�[�^
                const char* s_pRANKING_UI_DATA = "RankingUiDataJson";                                                                               ///< @brief �����L���OUI�f�[�^
                const char* s_pGAME_UI_DATA = "GameUiData";                                                                                         ///< @brief �Q�[��UI�f�[�^
                const char* s_pCONFIG_DATA = "ConfigData";                                                                                          ///< @brief �R���t�B�O�f�[�^
                const char* s_pRANKING_DATA = "RankingData";                                                                                        ///< @brief �����L���O�f�[�^
                const char* s_pPAUSE_UI_DATA = "PauseUiDataJson";                                                                                   ///< @brief �|�[�YUI�f�[�^
                const char* s_pSTAGE_01_BACKGROUND_DATA = "Stage01BackgroundDataJson";                                                              ///< @brief �X�e�[�W01�w�i�f�[�^
                const char* s_pSHIELD_DATA = "ShieldDataJson";                                                                                      ///< @brief �V�[���h�f�[�^
            }

            /* ���f�� */
            namespace Model
            {
                const char* s_pNORMAL_PLAYER = "NormalPlayerModel";                                                                                 ///< @brief �ʏ�v���C���[
                const char* s_pSPPED_UP_OPTION = "SpeedUpOptionModel";                                                                              ///< @brief �X�s�[�h�A�b�v�I�v�V����
                const char* s_pSMALL_BEAM_OPTION = "SmallBeamOptionModel";                                                                          ///< @brief �X���[���r�[���I�v�V����
                const char* s_pSHIELD_OPTION = "ShieldOption";                                                                                      ///< @brief �V�[���h�I�v�V����
                const char* s_pLASER_OPTION = "LaserOption";                                                                                        ///< @brief ���[�U�[�I�v�V����
                const char* s_pBOX_ENEMY = "BoxEnemyModel";                                                                                         ///< @brief �{�b�N�X�G�l�~�[
                const char* s_pSLIME_ENEMY = "SlimeEnemyModel";                                                                                     ///< @brief �X���C���G�l�~�[
                const char* s_pROUND_ENEMY = "RoundEnemyModel";                                                                                     ///< @brief ���E���h�G�l�~�[
                const char* s_pPYRAMID_ENEMY = "PyramidEnemyModel";                                                                                 ///< @brief �s���~�b�h�G�l�~�[
                const char* s_pGROUP_SHIP_ENEMY = "GroupShipEnemyModel";                                                                            ///< @brief �O���[�v�V�b�v�G�l�~�[
                const char* s_pPHALANX_CORE = "PhalanxCoreModel";                                                                                   ///< @brief �t�@�����N�X( �R�A )
                const char* s_pPHALANX_RING = "PhalanxRingModel";                                                                                   ///< @brief �t�@�����N�X( �����O )
                const char* s_pSPACE = "SpaceModel";                                                                                                ///< @brief �F��
                const char* s_pSHELTER = "ShelterModel";                                                                                            ///< @brief �V�F���^�[
                const char* s_pEXIT_RING = "ExitRingModel";                                                                                         ///< @brief �G�O�W�b�g�����O
                const char* s_pMETEOR = "MeteorModel";                                                                                              ///< @brief 覐�
                const char* s_pROCK = "RockModel";                                                                                                  ///< @brief ��
            }

            /* �X�v���C�g */
            namespace Sprite
            {
                const char* s_pUI_FONT = "UiFontSprite";                                                                                            ///< @brief UI�t�H���g
                const char* s_pTITLE_BACKGROUND = "TitleBackgroundSprite";                                                                          ///< @brief �^�C�g���w�i
                const char* s_pBULLET = "BulletSprite";                                                                                             ///< @brief �e
                const char* s_pTITLE_UI = "TitleUiSPrite";                                                                                          ///< @brief �^�C�g��UI
                const char* s_pFADE = "FadeSprite";                                                                                                 ///< @brief �t�F�[�h
                const char* s_pRANKING_BACKGROUND = "RankingBackgroundSprite";                                                                      ///< @brief �����L���O�w�i
                const char* s_pPAUSE_BACKGROUND = "PauseBackgroundSprite";                                                                          ///< @brief �|�[�Y�w�i
                const char* s_pGAME_UI = "GameUiSprite";                                                                                            ///< @brief �Q�[��UI
                const char* s_pSHIELD = "ShieldSprite";                                                                                             ///< @brief �V�[���h
            }

            /* �p�[�e�B�N�� */
            namespace Particle
            {
                const char* s_pCIRCLE_01 = "Circle01Particle";                                                                                      ///< @brief �~01
                const char* s_pCIRCLE_02 = "Circle02Particle";                                                                                      ///< @brief �~02
                const char* s_pRING_01 = "Ring01Particle";                                                                                          ///< @brief ��01
                const char* s_pSMOKE_01 = "Smoke01Particle";                                                                                        ///< @brief ��01
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
                    const char* s_pPHONG_NORMAL_TEXTURE = "Projects/Shaders/GLSL/Phong/PhongNormal.vert";                                           ///< @brief �t�H��( �m�[�}�� )
                }


                namespace Geometry
                {
                }


                namespace Fragment
                {
                    const char* s_pPHONG = "Projects/Shaders/GLSL/Phong/Phong.frag";                                                                ///< @brief �t�H��
                    const char* s_pPHONG_TEXTURE = "Projects/Shaders/GLSL/Phong/PhongTexture.frag";                                                 ///< @brief �t�H��( �e�N�X�`�� )
                    const char* s_pCELESTINAL_SPHERE = "Projects/Shaders/GLSL/CelestialSphere/CelestialSphere.frag";                                ///< @brief �V��
                    const char* s_pPHONG_NORMAL_TEXTURE = "Projects/Shaders/GLSL/Phong/PhongNormal.frag";                                           ///< @brief �t�H��( �m�[�}�� )
                }
            }


            /* �e�N�X�`�� */
            namespace Texture
            {
                const char* s_pUI_FONT = "Projects/Images/ConnectWars/UI/UiFont.png";                                                               ///< @brief UI�t�H���g
                const char* s_pTITLE_UI = "Projects/Images/ConnectWars/UI/TitleUI.png";                                                             ///< @brief �^�C�g��UI
                const char* s_pTITLE_BACKGROUND = "Projects/Images/ConnectWars/Background/TitleBackground.png";                                     ///< @brief �^�C�g���w�i
                const char* s_pRANKING_BACKGROUND = "Projects/Images/ConnectWars/Background/RankingBackground.png";                                 ///< @brief �����L���O�w�i
                const char* s_pPAUSE_BACKGROUND = "Projects/Images/ConnectWars/Background/PauseBackground.png";                                     ///< @brief �|�[�Y�w�i
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
                const char* s_pFADE = "Projects/Images/ConnectWars/Fade/BlackDot.png";                                                              ///< @brief �t�F�[�h
                const char* s_pEARTH = "Projects/Images/ConnectWars/Background/Earth.png";                                                          ///< @brief �n��
                const char* s_pMETOAR = "Projects/Images/ConnectWars/Obstacle/Meteor.png";                                                          ///< @brief 覐�
                const char* s_pMETOAR_NORMAL = "Projects/Images/ConnectWars/Obstacle/MeteorNormalMap.png";                                          ///< @brief 覐�(  �@���}�b�v
                const char* s_pBACKGROND_METEOR = "Projects/Images/ConnectWars/Background/BackgroundMeteor.png";                                    ///< @brief �w�i覐�
                const char* s_pROCK = "Projects/Images/ConnectWars/Obstacle/Rock.png";                                                              ///< @brief ��
                const char* s_pROCK_NORMAL = "Projects/Images/ConnectWars/Obstacle/RockNormalMap.png";                                              ///< @brief ��( �@���}�b�v )
                const char* s_pGAME_UI = "Projects/Images/ConnectWars/UI/GameUI.png";                                                               ///< @brief �Q�[��UI
                const char* s_pSMOKE_01 = "Projects/Images/ConnectWars/Effect/Smoke01.png";                                                         ///< @brief ��01
                const char* s_pSPRITE_SHIELD = "Projects/Images/ConnectWars/Shield/SpriteShield.png";                                               ///< @brief �X�v���C�g�̃V�[���h
                const char* s_pROUND_ENEMY = "Projects/Images/ConnectWars/Enemy/Round.png";                                                         ///< @brief ���E���h�G�l�~�[
                const char* s_pGROUD_SHIP_ENEMY = "Projects/Images/ConnectWars/Enemy/GroupShip.png";                                                ///< @brief �O���[�v�V�b�v�G�l�~�[
                const char* s_pPHALANX_CORE = "Projects/Images/ConnectWars/Enemy/Core.png";                                                         ///< @brief �t�@�����N�X( �R�A )
                const char* s_pPHALANX_RING = "Projects/Images/ConnectWars/Enemy/Ring.png";                                                         ///< @brief �t�@�����N�X( �����O )
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
                const char* s_pSHIELD_OPTION = "Projects/Models/ConnectWars/Option/Shield/ShieldOption.model";                                      ///< @brief �V�[���h�I�v�V����
                const char* s_pLASER_OPTION = "Projects/Models/ConnectWars/Option/Laser/LaserOption.model";                                         ///< @brief ���[�U�[�I�v�V����
                const char* s_pBOX_ENEMY = "Projects/Models/ConnectWars/Enemy/Box/Box.model";                                                       ///< @brief �{�b�N�X�G�l�~�[
                const char* s_pSLIME_ENEMY = "Projects/Models/ConnectWars/Enemy/Slime/Sphere.model";                                                ///< @brief �X���C���G�l�~�[
                const char* s_pROUND_ENEMY = "Projects/Models/ConnectWars/Enemy/Round/RoundEnemy.model";                                            ///< @brief ���E���h�G�l�~�[
                const char* s_pPYRAMID_ENEMY = "Projects/Models/ConnectWars/Enemy/Pyramid/Pyramid.model";                                           ///< @brief �s���~�b�h�G�l�~�[
                const char* s_pGROUP_SHIP_ENEMY = "Projects/Models/ConnectWars/Enemy/GroupShip/GroupShip.model";                                    ///< @brief �O���[�v�V�b�v�G�l�~�[
                const char* s_pPHALANX_CORE = "Projects/Models/ConnectWars/Enemy/Boss/Phalanx/Core/Core.model";                                     ///< @brief �t�@�����N�X( �R�A )
                const char* s_pPHALANX_RING = "Projects/Models/ConnectWars/Enemy/Boss/Phalanx/Ring/RingEnemy.model";                                ///< @brief �t�@�����N�X( �����O )
                const char* s_pSPACE = "Projects/Models/ConnectWars/Background/Space/Sphere.model";                                                 ///< @brief �F��
                const char* s_pSHELTER = "Projects/Models/ConnectWars/Background/Shelter/Shelter.model";                                            ///< @brief �V�F���^�[
                const char* s_pEXIT_RING = "Projects/Models/ConnectWars/Background/ExitRing/ExitRing.model";                                        ///< @brief �G�O�W�b�g�����O
                const char* s_pMETEOR = "Projects/Models/ConnectWars/Obstacle/Meteor/Meteor.model";                                                 ///< @brief 覐�
                const char* s_pROCK = "Projects/Models/ConnectWars/Obstacle/Rock/Rock.model";                                                       ///< @brief ��
                const char* s_pBACKGROUND_METEOR = "Projects/Models/ConnectWars/Obstacle/Meteor/Rock.model";                                                       ///< @brief ��
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
                const char* s_pMATERIAL_DATA = "Projects/GameDatas/ConnectWars/JSON/Material/MaterialData.json";                                    ///< @brief �}�e���A���f�[�^
                const char* s_pLIGHT_DATA = "Projects/GameDatas/ConnectWars/JSON/Light/LightData.json";                                             ///< @brief ���C�g���
                const char* s_pSTAGE_01_CAMERAWORK_DATA = "Projects/GameDatas/ConnectWars/JSON/Camera/Stage01/Stage01CameraworkData.json";          ///< @brief �X�e�[�W01�J�������[�N�f�[�^
                const char* s_pTITLE_UI_DATA = "Projects/GameDatas/ConnectWars/JSON/UI/TitleUiData.json";                                           ///< @brief �^�C�g��UI�f�[�^
                const char* s_pRANKING_UI_DATA = "Projects/GameDatas/ConnectWars/JSON/UI/RankingUiData.json";                                       ///< @brief �����L���OUI�f�[�^
                const char* s_pGAME_UI_DATA = "Projects/GameDatas/ConnectWars/JSON/UI/GameUiData.json";                                             ///< @brief �Q�[��UI�f�[�^
                const char* s_pRANKING_DATA = "Projects/GameDatas/ConnectWars/JSON/Ranking/RankingData.json";                                       ///< @brief �����L���O�f�[�^
                const char* s_pCONFIG_DATA = "Projects/GameDatas/ConnectWars/JSON/Config/ConfigData.json";                                          ///< @brief �R���t�B�O�f�[�^
                const char* s_pPAUSE_UI_DATA = "Projects/GameDatas/ConnectWars/JSON/UI/PauseUiData.json";                                           ///< @brief �|�[�YUI�f�[�^
                const char* s_pSTAGE_01_BACKGROUND_DATA = "Projects/GameDatas/ConnectWars/JSON/Background/Stage01/Stage01BackgroundData.json";      ///< @brief �X�e�[�W01�w�i�f�[�^
                const char* s_pSHIELD_DATA = "Projects/GameDatas/ConnectWars/JSON/Shield/ShieldData.json";                                          ///< @brief �V�[���h�f�[�^
            }

            /* Lua */
            namespace Lua
            {
                const char* s_pNORMAL_BOMB_CHARGE_EFFECT = "Projects/Sources/Lua/Effect/NormalBombChargeEffect.lua";                                ///< @brief �m�[�}���{���`���[�W�G�t�F�N�g
                const char* s_pNORMAL_BOMB_EFFECT = "Projects/Sources/Lua/Effect/NormalBombEffect.lua";                                             ///< @brief �m�[�}���{���G�t�F�N�g
                const char* s_pOPTION_OWN_CRASH_EFFECT_01 = "Projects/Sources/Lua/Effect/OptionOwnCrashEffect01.lua";                               ///< @brief �I�v�V���������G�t�F�N�g01
                const char* s_pPLAYER_FLAREBACK_EFFECT = "Projects/Sources/Lua/Effect/PlayerFlarebackEffect.lua";                                   ///< @brief �v���C���[�t���[���[�o�b�N�G�t�F�N�g
                const char* s_pCONNECT_EFFECT = "Projects/Sources/Lua/Effect/ConnectEffect.lua";                                                    ///< @brief �A���G�t�F�N�g
                const char* s_pPLAYER_EXPLOSION_EFFECT = "Projects/Sources/Lua/Effect/PlayerExplosionEffect.lua";                                   ///< @brief �v���C���[�̔����G�t�F�N�g
                const char* s_pOPTION_EXPLOSION_EFFECT = "Projects/Sources/Lua/Effect/OptionExplosionEffect.lua";                                   ///< @brief �I�v�V�����̔����G�t�F�N�g
                const char* s_pPLAYER_BEAM_COLLISION_EFFECT = "Projects/Sources/Lua/Effect/PlayerBeamCollisionEffect.lua";                          ///< @brief �v���C���[�̃r�[���Փ˃G�t�F�N�g  
                const char* s_pOPTION_SMALL_BEAM_COLLISION_EFFECT = "Projects/Sources/Lua/Effect/OptionSmallBeamCollisionEffect.lua";               ///< @brief �I�v�V�����̃X���[���r�[���Փ˃G�t�F�N�g  
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
            const char* s_pTO_TITLE_SCENE = "ToTitleScene";                                                                                         ///< @brief �^�C�g���V�[���֕ύX
            const char* s_pTO_RANKING_SCENE = "ToRankingScene";                                                                                     ///< @brief �����L���O�V�[���֕ύX
            const char* s_pTO_GAME_01_SCENE = "ToGame01Scene";                                                                                      ///< @brief �Q�[��01�V�[���֕ύX
            const char* s_pTO_GAME_02_SCENE = "ToGame02Scene";                                                                                      ///< @brief �Q�[��02�V�[���֕ύX
            const char* s_pTO_GAME_03_SCENE = "ToGame03Scene";                                                                                      ///< @brief �Q�[��03�V�[���֕ύX
            const char* s_pTO_PAUSE = "ToPauseScene";                                                                                               ///< @brief �|�[�Y�V�[���֕ύX
            const char* s_pRESUME_GAME = "ResumeGame";                                                                                              ///< @brief �Q�[�����ĊJ
            const char* s_pRESTART_GAME = "RestartGame";                                                                                            ///< @brief �Q�[�������X�^�[�g
            const char* s_pEXIT_GAME = "ExitGame";                                                                                                  ///< @brief �Q�[���I��
            const char* s_pOWN_CRASH = "OwnCrash";                                                                                                  ///< @brief ����
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
                    float s_sceneController = 100.0f;                                                                                               ///< @brief �V�[���R���g���[��
                    float s_ui = 90.0f;                                                                                                             ///< @brief UI
                    float s_cameraController = 50.0f;                                                                                               ///< @brief �J�����R���g���[��
                    float s_player = 10.0f;                                                                                                         ///< @brief �v���C���[
                    float s_option = 9.0f;                                                                                                          ///< @brief �I�v�V����
                    float s_shield = 8.5f;                                                                                                          ///< @brief �V�[���h
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
                    float s_sceneController = 100.0f;                                                                                               ///< @brief �V�[���R���g���[��
                    float s_ui = 90.0f;                                                                                                             ///< @brief UI
                    float s_cameraController = 50.0f;                                                                                               ///< @brief �J�����R���g���[��
                    float s_background = 11.0f;                                                                                                     ///< @brief �w�i
                    float s_bomb = 10.0f;                                                                                                           ///< @brief �{��
                    float s_effect = 9.0f;                                                                                                          ///< @brief �G�t�F�N�g
                    float s_obstacle = 8.0f;                                                                                                        ///< @brief ��Q��
                    float s_bullet = 7.0f;                                                                                                          ///< @brief �e
                    float s_enemy = 6.0f;                                                                                                           ///< @brief �G
                    float s_shield = 5.5f;                                                                                                          ///< @brief �V�[���h
                    float s_option = 5.0f;                                                                                                          ///< @brief �I�v�V����
                    float s_player = 4.0f;                                                                                                          ///< @brief �v���C���[
                }
            }


            /* �X�v���C�g */
            namespace Sprite
            {
                const float s_BILLBOARD = 10.0f;                                                                                                    ///< @brief �r���{�[�h
                const float s_BACKGROUND = 3.0f;                                                                                                    ///< @brief �w�i
                const float s_IMAGE_UI = 2.0f;                                                                                                      ///< @brief �摜UI
                const float s_FONT = 1.0f;                                                                                                          ///< @brief �t�H���g
                const float s_FADE = 0.0f;                                                                                                          ///< @brief �t�F�[�h
            }
        }
    }


    /* �Q�[���I�u�W�F�N�g�̎�� */
    enum eGameObjectType
    {
        TYPE_SCENE_CONTROLLER,                                                                                                                      ///< @brief �V�[���R���g���[��
        TYPE_CAMERA_CONTROLLER,                                                                                                                     ///< @brief �J�����R���g���[��
        TYPE_PLAYER,                                                                                                                                ///< @brief �v���C���[
        TYPE_OPTION,                                                                                                                                ///< @brief �I�v�V����
        TYPE_ENEMY,                                                                                                                                 ///< @brief �G
        TYPE_BULLET,                                                                                                                                ///< @brief �e
        TYPE_OBSTACLE,                                                                                                                              ///< @brief ��Q��
        TYPE_EFFECT,                                                                                                                                ///< @brief �G�t�F�N�g
        TYPE_BOMB,                                                                                                                                  ///< @brief �{��
        TYPE_BACKGROUND,                                                                                                                            ///< @brief �w�i
        TYPE_UI,                                                                                                                                    ///< @brief UI
        TYPE_FADE,                                                                                                                                  ///< @brief �t�F�[�h
        TYPE_SHIELD,                                                                                                                                ///< @brief �V�[���h

        TYPE_TYPE_NUMBER,                                                                                                                           ///< @brief ��ނ̐�
    };
}