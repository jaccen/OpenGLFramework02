/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Light.h"


//-------------------------------------------------------------
//!
//! @brief ���C�g
//! @brief ���C�g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Light
{
    //-------------------------------------------------------------
    //!
    //! @brief �|�C���g���C�g
    //! @brief �_������\���\����
    //!
    //-------------------------------------------------------------
    struct S_PointLight : public S_Light
    {
        Vector3 position_;                          ///< @brief ���W
        float constantAttenuation_;                 ///< @brief ��茸����
        float linearAttenuation_;                   ///< @brief �ꎟ������
        float quadraticAttenuation_;                ///< @brief �񎟌�����
        Vector3 diffuse_;                           ///< @brief �f�B�t���[�Y
	    Vector3 ambient_;                           ///< @brief �A���r�G���g
	    Vector3 specular_;                          ///< @brief �X�y�L����
    };
}