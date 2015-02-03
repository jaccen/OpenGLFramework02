/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Material.h"


//-------------------------------------------------------------
//!
//! @brief �}�e���A��
//! @brief �}�e���A���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Material
{
    //-------------------------------------------------------------
    //!
    //! @brief �t�H���}�e���A��
    //! @brief �t�H���}�e���A����\���\����
    //!
    //-------------------------------------------------------------
    struct S_PhongMaterial : public S_Material
    {
        Vector3 ambient_;                       ///< @brief �A���r�G���g
        Vector3 diffuse_;                       ///< @brief �f�B�t���[�Y
        Vector3 specular_;                      ///< @brief �X�y�L�����[
        Vector3 emissive_;                      ///< @brief �G�~�b�V�u
        float shininess_ = 0.0f;                ///< @brief ����
        float opacity_ = 0.0f;                  ///< @brief �s�����x
        float reflectivity_ = 0.0f;             ///< @brief ���˗�
    };
}