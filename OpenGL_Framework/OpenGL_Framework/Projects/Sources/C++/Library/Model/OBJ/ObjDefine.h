/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Math/MathAll.h"
#include <vector>


//-------------------------------------------------------------
//!
//! @brief ���f��
//! @brief ���f���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Model
{
    //-------------------------------------------------------------
    //!
    //! @brief OBJ
    //! @brief OBJ�֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace OBJ
    {
        /* �ʖ� */
        using Vector2 = Math::S_Vector2<float>;             // Vector2�^
        using Vector3 = Math::S_Vector3<float>;             // Vector3�^
        using Vector4 = Math::S_Vector4<float>;             // Vector4�^
        using Matrix3x3 = Math::S_Matrix3x3<float>;         // Matrix3x3�^
        using Matrix4x4 = Math::S_Matrix4x4<float>;         // Matrix4x4�^


        //-------------------------------------------------------------
        //!
        //! @brief �o�[�e�b�N�X
        //! @brief ���_��\���\����
        //!
        //-------------------------------------------------------------
        struct S_Vertex
        {
            Vector3 position_;                              ///< @brief ���W
            Vector3 normal_;                                ///< @brief �@���x�N�g��
            Vector2 textureCoord_;                          ///< @brief �e�N�X�`�����W

            S_Vertex() = default;                           //!< @brief �f�t�H���g�R���X�g���N�^
            S_Vertex(const S_Vertex& rOther) = default;     //!< @brief �f�t�H���g�R�s�[�R���X�g���N�^

            /*************************************************************//**
             *
             *  @brief  ��r���Z�q( ���� )�̃I�[�o�[���[�h
             *  @param  ���_
             *
             ****************************************************************/
            bool operator ==(const S_Vertex& rOther) const
            {
                return std::memcmp(this, &rOther, sizeof(S_Vertex)) == 0;
            }
        };

        //-------------------------------------------------------------
        //!
        //! @brief �}�e���A��
        //! @brief �}�e���A����\���\����
        //!
        //-------------------------------------------------------------
        struct S_Material
        {
            std::string name_;                              ///< @brief ���O
            std::string ambientTextureFileName_;            ///< @brief �A���r�G���g�e�N�X�`���̃t�@�C����
            std::string diffuseTextureFileName_;            ///< @brief �f�B�t���[�Y�e�N�X�`���̃t�@�C����
            std::string specularTextureFileName_;           ///< @brief �X�y�L�����[�e�N�X�`���̃t�@�C����
            Vector3 ambient_;                               ///< @brief �A���r�G���g
            Vector3 diffuse_;                               ///< @brief �f�B�t���[�Y
            Vector3 specular_;                              ///< @brief �X�y�L�����[
            float shininess_ = 0.0f;                        ///< @brief ����
            float opacity_ = 0.0f;                          ///< @brief �s�����x

            S_Material() = default;                         //!< @brief �f�t�H���g�R���X�g���N�^

            /*************************************************************//**
             *
             *  @brief  ���[�u�R���X�g���N�^
             *  @param  �}�e���A��
             *
             ****************************************************************/
            S_Material(S_Material&& rrOther) :

                // ���O
                name_(std::move(rrOther.name_)),

                // �e�e�N�X�`���t�@�C����
                ambientTextureFileName_(std::move(rrOther.ambientTextureFileName_)),
                diffuseTextureFileName_(std::move(rrOther.diffuseTextureFileName_)),
                specularTextureFileName_(std::move(rrOther.specularTextureFileName_)),

                // �}�e���A���̊e�f�[�^
                ambient_(rrOther.ambient_),
                diffuse_(rrOther.diffuse_),
                specular_(rrOther.specular_),
                shininess_(rrOther.shininess_),
                opacity_(rrOther.opacity_)

            {
            }
        };

        //-------------------------------------------------------------
        //!
        //! @brief ���b�V��
        //! @brief ���b�V����\���\����
        //!
        //-------------------------------------------------------------
        struct S_Mesh
        {
            std::string materialName_;                      ///< @brief �}�e���A����
            std::vector<S_Vertex> vertices_;                ///< @brief ���_
            std::vector<uint16_t> indices_;                 ///< @brief �C���f�b�N�X

            S_Mesh() = default;                             //!< @brief �f�t�H���g�R���X�g���N�^

            /*************************************************************//**
             *
             *  @brief  ���[�u�R���X�g���N�^
             *  @param  ���b�V��
             *
             ****************************************************************/
            S_Mesh(S_Mesh&& rrOther) :

                // �}�e���A����
                materialName_(std::move(rrOther.materialName_)),

                // ���_
                vertices_(std::move(rrOther.vertices_)),

                // �C���f�b�N�X
                indices_(std::move(rrOther.indices_))

            {
            }
        };
    }
}