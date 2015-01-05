/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../../Math/Vector/Vector4.h"


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace OpenGL
{
    /* �ʖ� */
    using Vector2 = Math::S_Vector2<float>;                                 // Vector2�^
    using Vector3 = Math::S_Vector3<float>;                                 // Vector3�^
    using Vector4 = Math::S_Vector4<float>;                                 // Vector4�^


    //-------------------------------------------------------------
    //!
    //! @brief �o�[�e�b�N�XPC
    //! @brief ���W�E�F���܂ޒ��_��\���\����
    //!
    //-------------------------------------------------------------
    struct S_VertexPC
    {
        Vector3 position_;                                                  ///< @brief ���W
        Vector4 color_;                                                     ///< @brief �F
    };


    //-------------------------------------------------------------
    //!
    //! @brief �o�[�e�b�N�XPN
    //! @brief ���W�E�@���x�N�g�����܂ޒ��_��\���\����
    //!
    //-------------------------------------------------------------
    struct S_VertexPN
    {
        Vector3 position_;                                                  ///< @brief ���W
        Vector3 normal_;                                                    ///< @brief �@���x�N�g��
    };


    //-------------------------------------------------------------
    //!
    //! @brief �o�[�e�b�N�XPNT
    //! @brief ���W�E�@���x�N�g���E�e�N�X�`�����W���܂ޒ��_��\���\����
    //!
    //-------------------------------------------------------------
    struct S_VertexPNT
    {
        Vector3 position_;                                                  ///< @brief ���W
        Vector3 normal_;                                                    ///< @brief �@���x�N�g��
        Vector2 textureCoord_;                                              ///< @brief �e�N�X�`�����W
    };


    //-------------------------------------------------------------
    //!
    //! @brief �o�[�e�b�N�XPNTC
    //! @brief ���W�E�@���x�N�g���E�e�N�X�`�����W�E�F���܂ޒ��_��\���\����
    //!
    //-------------------------------------------------------------
    struct S_VertexPNTC
    {
        Vector3 position_;                                                  ///< @brief ���W
        Vector3 normal_;                                                    ///< @brief �@���x�N�g��
        Vector2 textureCoord_;                                              ///< @brief �e�N�X�`�����W
        Vector4 color_;                                                     ///< @brief �F
    };


    //-------------------------------------------------------------
    //!
    //! @brief �o�[�e�b�N�XPNTT
    //! @brief ���W�E�@���x�N�g���E�e�N�X�`�����W�E�ڃx�N�g�����܂ޒ��_��\���\����
    //!
    //-------------------------------------------------------------
    struct S_VertexPNTT
    {
        Vector3 position_;                                                  ///< @brief ���W
        Vector3 normal_;                                                    ///< @brief �@���x�N�g��
        Vector2 textureCoord_;                                              ///< @brief �e�N�X�`�����W
        Vector4 tangent_;                                                   ///< @brief �ڃx�N�g��
    };


    //-------------------------------------------------------------
    //!
    //! @brief �o�[�e�b�N�XPNTCT
    //! @brief ���W�E�@���x�N�g���E�e�N�X�`�����W�E�F�E�ڃx�N�g�����܂ޒ��_��\���\����
    //!
    //-------------------------------------------------------------
    struct S_VertexPNTCT
    {
        Vector3 position_;                                                  ///< @brief ���W
        Vector3 normal_;                                                    ///< @brief �@���x�N�g��
        Vector2 textureCoord_;                                              ///< @brief �e�N�X�`�����W
        Vector4 color_;                                                     ///< @brief �F
        Vector4 tangent_;                                                   ///< @brief �ڃx�N�g��
    };
}