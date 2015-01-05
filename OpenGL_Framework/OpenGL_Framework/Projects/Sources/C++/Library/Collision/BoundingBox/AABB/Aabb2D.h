/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../../Math/Vector/Vector2.h"
#include "../../Detection/Detection2D.h"


//-------------------------------------------------------------
//!
//! @brief �R���W����
//! @brief �Փˊ֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Collision
{
    //-------------------------------------------------------------
    //!
    //! @brief AABB2D
    //! @brief 2D��AABB�̔�����s���\����
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    struct S_Aabb2D
    {
        /* �ʖ� */
        using Point2 = Point2<T>;                                       // Point2�^���ȗ�

        Point2 min_;                                                    ///< @brief �ŏ����W
        Point2 max_;                                                    ///< @brief �ő���W

        S_Aabb2D() = default;                                           // �f�t�H���g�R���X�g���N�^
        S_Aabb2D(const Point2& rMin, const Point2& rMax);               // �R���X�g���N�^
        S_Aabb2D(const Point2& rCenterPoint, T width, T height);        // �R���X�g���N�^
        bool Detection(const S_Aabb2D& rAnother);                       // �Փ˔���
    };


    /* �ʖ� */
    using Aabb2D = S_Aabb2D<>;                                          // Aabb2D�^
}



