/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Math/Vector/Vector3.h"


//-------------------------------------------------------------
//!
//! @brief ���C�g
//! @brief ���C�g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Light
{
    /* �O���錾 */
    struct S_Light;


    /* �ʖ� */
    using Vector3 = Math::S_Vector3<float>;             // Vector3�^
    using LightPtr = std::shared_ptr<S_Light>;          // LightPtr�^


    //-------------------------------------------------------------
    //!
    //! @brief ���C�g
    //! @brief ���C�g�̊��\����
    //!
    //-------------------------------------------------------------
    struct S_Light
    {
    };
}