/* �w�b�_�t�@�C�� */
#include "AABB2D.h"


//-------------------------------------------------------------
//!
//! @brief �R���W����
//! @brief �Փˊ֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Collision
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �ŏ����W
     *  @param  �ő���W
     *
     ****************************************************************/
    template<typename T>
    S_Aabb2D<T>::S_Aabb2D(const Point2& rMin, const Point2& rMax) :

        // �e���W
        min_(rMin),
        max_(rMax)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  ���S�_
     *  @param  ��
     *  @param  ����
     *
     ****************************************************************/
    template<typename T>
    S_Aabb2D<T>::S_Aabb2D(const Point2& rCenterPoint, T width, T height)
    {
        T halfWidth = width * static_cast<T>(0.5);
        T halfHeight = height * static_cast<T>(0.5);

        min_.x_ = rCenterPoint.x_ - halfWidth;
        min_.y_ = rCenterPoint.y_ - halfHeight;

        max_.x_ = rCenterPoint.x_ + halfWidth;
        max_.y_ = rCenterPoint.y_ + halfHeight;
    }


    /*************************************************************//**
     *
     *  @brief  �Փ˔�����s��
     *  @param  �������AABB
     *  @return �Փ˂����ꍇ    �Ftrue
     *  @return �Փ˂��ĂȂ��ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool S_Aabb2D<T>::Detection(const S_Aabb2D<T>& rAnother)
    {
        return C_Detection2D<T>::s_CheckRectangleAndRectangle(min_, max_, rAnother.min_, rAnother.max_);
    }


    /* �����I�C���X�^���X�� */
    template struct S_Aabb2D<float>;
    template struct S_Aabb2D<double>;
}


