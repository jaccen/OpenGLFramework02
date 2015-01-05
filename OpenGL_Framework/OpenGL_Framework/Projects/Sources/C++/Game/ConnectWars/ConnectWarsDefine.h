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
    using Vector2 = Math::S_Vector2<float>;                                     // Vector2�^
    using Vector3 = Math::S_Vector3<float>;                                     // Vector3�^    
    using Vector4 = Math::S_Vector4<float>;                                     // Vector4�^
    using Matrix3x3 = Math::S_Matrix3x3<float>;                                 // Matrix3x3�^
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                 // Matrix4x4�^
    using Telegram = GameObject::Message::S_Telegram;                           // Telegram�^


    /** �J�����̏�� */
    struct S_CameraData
    {
        Matrix4x4 viewMatrix_;                                                  ///< @brief �r���[�s��
        Matrix4x4 projectionMatrix_;                                            ///< @brief �v���W�F�N�V�����s��
        Matrix4x4 viewProjectionMatrix_;                                        ///< @brief �r���[�v���W�F�N�V�����s��
    };


    namespace
    {
        /* ID */
        namespace Id
        {
            /* �J���� */
            namespace Camera
            {
                const char* s_pMAIN = "MainCamera";                             ///< @brief ���C���J����
            }

            /* �V�F�[�_�[ */
            namespace Shader
            {
                const char* s_pHALF_LAMBERT = "HalfLambertShader";              ///< @brief �n�[�t�����o�[�g�V�F�[�_�[
            }

            /* �e�N�X�`�� */
            namespace Texture
            {
            }

            /* �Q�[���I�u�W�F�N�g */
            namespace GameObject
            {
                const char* s_pPLAYER = "Player";                               ///< @brief �v���C���[
                const char* s_pOPTION = "Option";                               ///< @brief �I�v�V����
                const char* s_pENEMY = "Enemy";                                 ///< @brief �G
                const char* s_pOBSTACLE = "Obstacle";                           ///< @brief ��Q��
                const char* s_pBULLET = "Bullet";                               ///< @brief �e
                const char* s_pBOMB = "Bomb";                                   ///< @brief �{��
                const char* s_pEFFECT = "Effect";                               ///< @brief �G�t�F�N�g
            }
        }

        /* �X�e�[�W�T�C�Y */
        namespace StageSize
        {
            float s_left = -16.0f;                                              ///<@brief ���[
            float s_right = 16.0f;                                              ///<@brief �E�[
            float s_top = 12.0f;                                                ///<@brief ��[
            float s_bottom = -12.0f;                                            ///<@brief ���[
        }

        /* �A�� */
        namespace Connect
        {
            float s_OffsetFactor = 0.8f;                                        ///< �I�t�Z�b�g�W��
        }
    }
}