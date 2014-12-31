/* �w�b�_�t�@�C�� */
#include "Detection3D.h"
#include "../../Math/Vector/Vector3.h"
#include "../../Math/Define/MathDefine.h"


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
     *  @brief  �_�Ɛ����̏Փ˔�����s��
     *  @param  �_
     *  @param  �����̎n�_
     *  @param  �����̏I�_
     *  @return �Փ˂����ꍇ�Ftrue
     *  @return �Փ˂��Ȃ������ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection3D<T>::s_CheckPointAndSegment(const Point3& rPoint,
                                                  const Point3& rSegmentBeginPoint,
                                                  const Point3& rSegmentEndPoint)
    {
        // �����̎n�_����I�_�܂ł̃x�N�g�������߁A�������擾
        Point3 segmentVector(rSegmentEndPoint - rSegmentBeginPoint);
        T segmentLength = segmentVector.GetLength();

        // �����̎n�_����_�܂ł̃x�N�g�������߁A�������擾
        Point3 vectorFromSegmentBeginToPoint(rPoint - rSegmentBeginPoint);
        T segmentBeginFromPointDistance = vectorFromSegmentBeginToPoint.GetLength();

        // 2�̃x�N�g���̊O��
        Point3 crossProduct(Point3::s_CrossProduct(segmentVector, vectorFromSegmentBeginToPoint));

        // 2�̃x�N�g���̊O�ς�0�Ɠ������A
        // �����̎n�_����_�܂ł̒����������̒������Z�������ꍇ�͏Փ�
        if ((std::abs(crossProduct.GetLength()) <= static_cast<T>(Math::s_EPSILON)) && (segmentBeginFromPointDistance <= segmentLength))
        {
            return true;
        }

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  �����ƕ��ʂ̏Փ˔�����s��
     *  @param  �����̎n�_
     *  @param  �����̏I�_
     *  @param  ���ʏ�̓_
     *  @param  ���ʂ̖@���x�N�g��
     *  @return �Փ˂����ꍇ�Ftrue
     *  @return �Փ˂��Ȃ������ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection3D<T>::s_CheckSegmentAndPlane(const Point3& rSegmentBeginPoint,
                                                  const Point3& rSegmentEndPoint,
                                                  const Point3& rPlanePoint,
                                                  const Point3& rPlaneNomal)
    {
        // ���ʏ�̓_��������̎n�_�܂ł̃x�N�g��
        Point3 vectorFromPlanePointToSegmentBegin(rSegmentBeginPoint - rPlanePoint);

        // ���ʏ�̓_��������̏I�_�܂ł̃x�N�g��
        Point3 vectorFromPlanePointToSegmenEnd(rSegmentEndPoint - rPlanePoint);

        // �e�x�N�g���ƕ��ʂ̖@���x�N�g���Ƃ̓��ς̏�Z��0�ȉ��ł���ΏՓ�
        if (Point3::s_DotProduct(vectorFromPlanePointToSegmentBegin, rPlaneNomal)
            * Point3::s_DotProduct(vectorFromPlanePointToSegmenEnd, rPlaneNomal) <= static_cast<T>(0.0))
        {
            return true;
        }

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  ���Ƌ��̏Փ˔�����s��
     *  @param  ���S���W
     *  @param  ���a
     *  @param  ������̒��S���W
     *  @param  ������̔��a
     *  @return �Փ˂����ꍇ�Ftrue
     *  @return �Փ˂��Ȃ������ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection3D<T>::s_CheckSphereAndSphere(const Point3& rCenterPosition,
                                                  T radius,
                                                  const Point3& rAnotherCenterPosition,
                                                  T anotherRadius)
    {
        // ����
        Point3 distance(rCenterPosition - rAnotherCenterPosition);

        // ���a�̍��v
        T sumRadius = radius + anotherRadius;

        // ������2�悪���a��2����Z���ꍇ�͏Փ�
        if (distance.GetLengthSquare() <= sumRadius * sumRadius) return true;

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  �_���畽�ʂ܂ł̋������擾����
     *  @param  �_
     *  @param  ���a
     *  @param  ���ʏ�̓_
     *  @param  ���ʂ̖@���x�N�g��
     *  @return �_���畽�ʂ܂ł̋���
     *
     ****************************************************************/
    template<typename T>
    T C_Detection3D<T>::s_GetLengthFromPointToPlane(const Point3& rPoint,
                                                    const Point3& rPlanePoint,
                                                    const Point3& rPlaneNormal)
    {
        // ���ʏ�̓_����_�܂ł̃x�N�g��
        Point3 vectorFromPlanePointToPoint(rPoint - rPlanePoint);

        // ���ʏ�̓_����_�܂ł̃x�N�g���ƒP�ʃx�N�g���������@���x�N�g���̓��ς̐�Βl
        return std::abs(Point3::s_DotProduct(vectorFromPlanePointToPoint, rPlaneNormal.GetNormalize()));
    }


    /* �����I�C���X�^���X�� */
    template class C_Detection3D<float>;
    template class C_Detection3D<double>;
}
