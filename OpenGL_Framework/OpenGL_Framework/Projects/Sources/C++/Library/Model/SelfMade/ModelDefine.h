/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Math/MathAll.h"
#include <array>
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
    //! @brief SelfMade
    //! @brief ����֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace SelfMade
    {
        /* �ʖ� */
        using Vector2 = Math::S_Vector2<float>;                                 // Vector2�^
        using Vector3 = Math::S_Vector3<float>;                                 // Vector3�^
        using Vector4 = Math::S_Vector4<float>;                                 // Vector4�^
        using Matrix3x3 = Math::S_Matrix3x3<float>;                             // Matrix3x3�^
        using Matrix4x4 = Math::S_Matrix4x4<float>;                             // Matrix4x4�^

        //-------------------------------------------------------------
        //!
        //! @brief �{�[���E�F�C�g
        //! @brief �{�[���̃E�F�C�g��\���\����
        //!
        //-------------------------------------------------------------
        struct S_BoneWeight
        {
            std::array<uint8_t, 4> indices_;                                    ///< @brief �C���f�b�N�X
            Vector4 weights_;                                                   ///< @brief �E�F�C�g

            S_BoneWeight() = default;                                           //!< @brief �f�t�H���g�R���X�g���N�^

            /*************************************************************//**
             *
             *  @brief  ���[�u�R���X�g���N�^
             *  @param  �{�[���E�F�C�g
             *
             ****************************************************************/
            S_BoneWeight(S_BoneWeight&& rrOther) :

                // �C���f�b�N�X
                indices_(std::move(rrOther.indices_)),

                // �E�F�C�g
                weights_(rrOther.weights_)

            {
            }
        };

        //-------------------------------------------------------------
        //!
        //! @brief �o�[�e�b�N�X
        //! @brief ���_��\���\����
        //!
        //-------------------------------------------------------------
        struct S_Vertex
        {
            Vector3 position_;                                                  ///< @brief ���W
            Vector3 normal_;                                                    ///< @brief �@���x�N�g��
            Vector2 textureCoord_;                                              ///< @brief �e�N�X�`�����W
            Vector4 color_;                                                     ///< @brief �F
            Vector4 tangent_;                                                   ///< @brief �ڃx�N�g��
            S_BoneWeight boneWeights_;                                          ///< @brief �{�[���̃E�F�C�g

            S_Vertex() = default;                                               //!< @brief �f�t�H���g�R���X�g���N�^

            /*************************************************************//**
             *
             *  @brief  ���[�u�R���X�g���N�^
             *  @param  ���_
             *
             ****************************************************************/
            S_Vertex(S_Vertex&& rrOther) :

                // ���W
                position_(rrOther.position_),

                // �@���x�N�g��
                normal_(rrOther.normal_),

                // �e�N�X�`�����W
                textureCoord_(rrOther.textureCoord_),

                // �F
                color_(rrOther.color_),

                // �ڃx�N�g��
                tangent_(rrOther.tangent_),

                // �{�[���̃E�F�C�g
                boneWeights_(rrOther.boneWeights_)

            {
            }

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
            std::string name_;                                                  ///< @brief ���O
            Vector3 ambient_;                                                   ///< @brief �A���r�G���g
            Vector3 diffuse_;                                                   ///< @brief �f�B�t���[�Y
            Vector3 specular_;                                                  ///< @brief �X�y�L�����[
            Vector3 emissive_;                                                  ///< @brief �G�~�b�V�u
            float shininess_ = 0.0f;                                            ///< @brief ����
            float opacity_ = 0.0f;                                              ///< @brief �s�����x
            float reflectivity_ = 0.0f;                                         ///< @brief ���˗�
            std::string ambientTextureFileName_;                                ///< @brief �A���r�G���g�e�N�X�`���̃t�@�C����
            std::string diffuseTextureFileName_;                                ///< @brief �f�B�t���[�Y�e�N�X�`���̃t�@�C����
            std::string specularTextureFileName_;                               ///< @brief �X�y�L�����[�e�N�X�`���̃t�@�C����

            S_Material() = default;                                             //!< @brief �f�t�H���g�R���X�g���N�^

            /*************************************************************//**
             *
             *  @brief  ���[�u�R���X�g���N�^
             *  @param  �}�e���A��
             *
             ****************************************************************/
            S_Material(S_Material&& rrOther) :

                // ���O
                name_(std::move(rrOther.name_)),

                // �}�e���A���̊e�f�[�^
                ambient_(rrOther.ambient_),
                diffuse_(rrOther.diffuse_),
                specular_(rrOther.specular_),
                emissive_(rrOther.emissive_),
                shininess_(rrOther.shininess_),
                opacity_(rrOther.opacity_),
                reflectivity_(rrOther.reflectivity_),

                // �e�e�N�X�`���t�@�C����
                ambientTextureFileName_(std::move(rrOther.ambientTextureFileName_)),
                diffuseTextureFileName_(std::move(rrOther.diffuseTextureFileName_)),
                specularTextureFileName_(std::move(rrOther.specularTextureFileName_))

            {
            }
        };


        //-------------------------------------------------------------
        //!
        //! @brief �{�[��
        //! @brief �{�[����\���\����
        //!
        //-------------------------------------------------------------
        struct S_Bone
        {
            std::string name_;                                                  ///< @brief ���O
            std::string parentName_;                                            ///< @brief �e�̖��O
            Matrix4x4 inverseBaseposeMatrix_;                                   ///< @brief ��{�p���̋t�s��
            std::vector<Matrix4x4> eachFrameAnimationMatrices_;                 ///< @brief �e�t���[���̍s��

            S_Bone() = default;                                                 //!< @brief �f�t�H���g�R���X�g���N�^

            /*************************************************************//**
             *
             *  @brief  ���[�u�R���X�g���N�^
             *  @param  �{�[��
             *
             ****************************************************************/
            S_Bone(S_Bone&& rrOther) :

                // ���O
                name_(std::move(rrOther.name_)),

                // �e�̖��O
                parentName_(std::move(rrOther.parentName_)),

                // ��{�p���̋t�s��
                inverseBaseposeMatrix_(rrOther.inverseBaseposeMatrix_),

                // �e�t���[���̃A�j���[�V�����s��
                eachFrameAnimationMatrices_(std::move(rrOther.eachFrameAnimationMatrices_))

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
            std::string name_;                                                  ///< @brief ���O
            std::string parentName_;                                            ///< @brief �e�̖��O
            std::string materialName_;                                          ///< @brief �}�e���A����
            std::vector<S_Vertex> vertices_;                                    ///< @brief ���_
            std::vector<uint16_t> indices_;                                     ///< @brief �C���f�b�N�X
            Matrix4x4 inverseBaseposeMatrix_;                                   ///< @brief ��{�p���̋t�s��
            std::vector<S_Bone> bones_;                                         ///< @brief �{�[��
            std::vector<Matrix4x4> eachFrameAnimationMatrices_;                 ///< @brief �e�t���[���̃A�j���[�V�����s��

            S_Mesh() = default;                                                 //!< @brief �f�t�H���g�R���X�g���N�^

            /*************************************************************//**
             *
             *  @brief  ���[�u�R���X�g���N�^
             *  @param  ���b�V��
             *
             ****************************************************************/
            S_Mesh(S_Mesh&& rrOther) :

                // ���O
                name_(std::move(rrOther.name_)),

                // �e�̖��O
                parentName_(std::move(rrOther.parentName_)),

                // �}�e���A����
                materialName_(std::move(rrOther.materialName_)),

                // ���_
                vertices_(std::move(rrOther.vertices_)),

                // �C���f�b�N�X
                indices_(std::move(rrOther.indices_)),

                // ��{�p���̋t�s��
                inverseBaseposeMatrix_(rrOther.inverseBaseposeMatrix_),

                // �{�[��
                bones_(std::move(rrOther.bones_)),

                // �e�t���[���̍s��
                eachFrameAnimationMatrices_(std::move(rrOther.eachFrameAnimationMatrices_))

            {
            }
        };
    }
}