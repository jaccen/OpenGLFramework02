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
    //! @brief �f�B���N�V���i�����C�g
    //! @brief ���s������\���\����
    //!
    //-------------------------------------------------------------
    struct S_DirectionalLight : public S_Light
    {
        Vector3 direction_;                         ///< @brief ����
        Vector3 diffuse_;                           ///< @brief �f�B�t���[�Y
	    Vector3 ambient_;                           ///< @brief �A���r�G���g
	    Vector3 specular_;                          ///< @brief �X�y�L����
    };
}