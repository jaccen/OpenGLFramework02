/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Math/Matrix/Matrix4x4.h"


//-------------------------------------------------------------
//!
//! @brief �r���[
//! @brief �r���[�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace View
{
    /* �ʖ� */
    using Vector4 = Math::S_Vector4<float>;                                         // Vector4�^
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                     // Matrix4x4�^


    //-------------------------------------------------------------
    //!
    //! @brief �r���[�w���p�[
    //! @brief ���F�̕⏕���s���֐����܂Ƃ߂����[�e�B���e�B�N���X
    //!
    //-------------------------------------------------------------
    class C_ViewHelper
    {
    public:
        static void s_DrawGrid(float lineHelfLength,                                // �O���b�h��`��
                               float lineInterval,
                               uint32_t lineCount,
                               const Vector4& rLineColor,
                               const Matrix4x4& rViewProjectionMatrix);
        static void s_DrawAxis(float lineLength,                                    // ����`��
                               const Matrix4x4& rViewProjectionMatrix);
    };
}