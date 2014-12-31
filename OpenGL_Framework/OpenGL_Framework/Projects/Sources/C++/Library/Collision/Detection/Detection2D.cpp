/* �w�b�_�t�@�C�� */
#include "Detection2D.h"
#include "../../Math/Vector/Vector2.h"
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
     *  @brief  ��`���m�̏Փ˔�����s��
     *  @param  ���S���W
     *  @param  ���̔���
     *  @param  �����̔���
     *  @param  ������̒��S���W
     *  @param  ������̕��̔���
     *  @param  ������̍����̔���
     *  @return �Փ˂����ꍇ�Ftrue
     *  @return �Փ˂��Ȃ������ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckRectangleAndRectangle(const Point2& rCenterPosition,
                                                        T halfWidth,
                                                        T halfHeight,
                                                        const Point2& rAnotherCenterPosition,
                                                        T anotherHalfWidth,
                                                        T anotherHalfHeihgt)
    {
        // ��`��4�̒[���r���đS�Ă̏����𖞂������ꍇ�͏Փ�
        if ((rCenterPosition.x_ - halfWidth <= rAnotherCenterPosition.x_ + anotherHalfWidth)
         && (rCenterPosition.x_ + halfWidth >= rAnotherCenterPosition.x_ - anotherHalfWidth)
         && (rCenterPosition.y_ - halfHeight <= rAnotherCenterPosition.y_ + anotherHalfHeihgt)
         && (rCenterPosition.y_ + halfHeight >= rAnotherCenterPosition.y_ - anotherHalfHeihgt))
        {
            return true;
        }

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  ��`���m�̏Փ˔�����s��
     *  @param  ���S���W
     *  @param  ���̔���
     *  @param  �����̔���
     *  @param  �p�x
     *  @param  ������̒��S���W
     *  @param  ������̕��̔���
     *  @param  ������̍����̔���
     *  @param  ������̊p�x
     *  @return �Փ˂����ꍇ�Ftrue
     *  @return �Փ˂��Ȃ������ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckRectangleAndRectangle(const Point2& rCenterPosition,
                                                        T halfWidth,
                                                        T halfHeight,
                                                        T angle,
                                                        const Point2& rAnotherCenterPosition,
                                                        T anotherHalfWidth,
                                                        T anotherHalfHeight,
                                                        T anotherAngle)
    {
        // ���S���W�ɉ�������W
        Point2 addPositions[4] = { Point2(-halfWidth, halfHeight),
                                   Point2(-halfWidth, -halfHeight),
                                   Point2(halfWidth, halfHeight),
                                   Point2(halfWidth, -halfHeight) };

        Point2 anotherAddPositions[4] = { Point2(-anotherHalfWidth, anotherHalfHeight),
                                          Point2(-anotherHalfWidth, -anotherHalfHeight),
                                          Point2(anotherHalfWidth, anotherHalfHeight),
                                          Point2(anotherHalfWidth, -anotherHalfHeight) };
        for (size_t i = 0; i < 4; ++i)
        {
            addPositions[i].Rotate(angle);
            anotherAddPositions[i].Rotate(anotherAngle);
        }

        // ���_
        Point2 vertices[4] = { rCenterPosition + addPositions[0],
                               rCenterPosition + addPositions[1],
                               rCenterPosition + addPositions[2],
                               rCenterPosition + addPositions[3] };

        Point2 anotherVertices[4] = { rAnotherCenterPosition + anotherAddPositions[0],
                                      rAnotherCenterPosition + anotherAddPositions[1],
                                      rAnotherCenterPosition + anotherAddPositions[2],
                                      rAnotherCenterPosition + anotherAddPositions[3] };

        // ���_����ł���x�N�g��
        Point2 vertexVectors[4] = { vertices[2] - vertices[0],
                                    vertices[0] - vertices[1],
                                    vertices[1] - vertices[3],
                                    vertices[3] - vertices[2] };

        Point2 anotherVertexVectors[4] = { anotherVertices[2] - anotherVertices[0],
                                           anotherVertices[0] - anotherVertices[1],
                                           anotherVertices[1] - anotherVertices[3],
                                           anotherVertices[3] - anotherVertices[2] };

        // �e���_���琶�����ꂽ�x�N�g���ƊO�ς����A2�̋�`�̒��_��
        for (auto& rVertexVector : vertexVectors)
        {
            for (size_t i = 0; i < 4; ++i)
            {
                if (Point2::s_CrossProduct(rVertexVector, anotherVertexVectors[i]) > 0.0f)  break;

                if (i == 4) return true;
            }
        }

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  �~���m�̏Փ˔�����s��
     *  @param  ���S���W
     *  @param  ���a
     *  @param  ������̒��S���W
     *  @param  ������̔��a
     *  @return �Փ˂����ꍇ�Ftrue
     *  @return �Փ˂��Ȃ������ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckCircleAndCircle(const Point2& rCenterPosition,
                                                  T radius,
                                                  const Point2& rAnotherCenterPosition,
                                                  T anotherRadius)
    {
        // ����
        Point2 distance(rCenterPosition - rAnotherCenterPosition);

        // ���a�̍��v
        T sumRadius = radius + anotherRadius;

        // ������2��̔��a�̘a��2����Z���ꍇ�͏Փ�
        if (distance.GetLengthSquare() <= sumRadius * sumRadius) return true;

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  ��`�Ɖ~�̏Փ˔�����s��
     *  @param  ��`�̒��S���W
     *  @param  ��`�̕��̔���
     *  @param  ��`�̍����̔���
     *  @param  ��`�̊p�x( ���W�A���l )
     *  @param  �~�̒��S���W
     *  @param  �~�̔��a
     *  @return �Փ˂����ꍇ�Ftrue
     *  @return �Փ˂��Ȃ������ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckRectangleAndCircle(const Point2& rRectangleCenterPosition,
                                                     T rectangleHalfWidth,
                                                     T rectangleHalfHeight,
                                                     T rectangleAngle,
                                                     const Point2& rCircleCenterPosition,
                                                     T circleRadius)
    {
        // ��`����~�܂ł̋���
        Point2 distance(rCircleCenterPosition - rRectangleCenterPosition);

        // ���]������`�̊p�x
        T inverseRectangleAngle = -rectangleAngle;

        // ��`�𒆐S�ɔ��]������`�̊p�x��������]�����~�̍��W�����߂�
        Point2 circleRotateCenterPosition;

        circleRotateCenterPosition.x_ = std::cos(inverseRectangleAngle) * distance.x_ - std::sin(inverseRectangleAngle) * distance.y_;
        circleRotateCenterPosition.y_ = std::sin(inverseRectangleAngle) * distance.x_ + std::cos(inverseRectangleAngle) * distance.y_;

        // ��`�̍��[���W�Ə�[���W
        T rectangleLeft = -rectangleHalfWidth;
        T rectangleTop = -rectangleHalfHeight;

        // ��]��̉~�����`�ɑ΂��čł��߂��_
        Point2 shortestPoint;

        // ��]��̉~�����`�ɑ΂��čł��߂�X���W�����߂�
        if (circleRotateCenterPosition.x_ < rectangleLeft)
        {
            shortestPoint.x_ = rectangleLeft;
        }
        else
        {
            // ��`�̉E�[���W�����߂�
            T rectangleRight = rectangleHalfWidth;

            if (circleRotateCenterPosition.x_ > rectangleRight)
            {
                shortestPoint.x_ = rectangleRight;
            }
            else
            {
                shortestPoint.x_ = circleRotateCenterPosition.x_;
            }
        }

        // ��]��̉~�^��`�ɑ΂��Ă��ł��߂�Y���W�����߂�
        if (circleRotateCenterPosition.y_ < rectangleTop)
        {
            shortestPoint.y_ = rectangleTop;
        }
        else
        {
            // ��`�̉��[���W�����߂�
            T rectangleBottom = rectangleHalfHeight;

            if (circleRotateCenterPosition.y_ > rectangleBottom)
            {
                shortestPoint.y_ = rectangleBottom;
            }
            else
            {
                shortestPoint.y_ = circleRotateCenterPosition.y_;
            }
        }

        // ��]��̉~�̒��S�ƍł��߂��_���Փ˂��Ă�����Փ�
        if (s_CheckCircleAndPoint(circleRotateCenterPosition, circleRadius, shortestPoint) == true) return true;

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  �~�Ɠ_�̏Փ˔�����s��
     *  @param  ��`�̒��S���W
     *  @param  �~�̔��a
     *  @param  �_
     *  @return �Փ˂����ꍇ�Ftrue
     *  @return �Փ˂��Ȃ������ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckCircleAndPoint(const Point2& rCircleCenterPosition,
                                                 T circleRadius,
                                                 const Point2& rPoint)
    {
        // �_����~�̒��S�܂ł̋���
        Point2 distance(rCircleCenterPosition - rPoint);

        // �_����~�̒��S�܂ł̋�����2�悪�~��2����Z���ꍇ�͏Փ�
        if (distance.GetLengthSquare() <= circleRadius * circleRadius) return true;

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  �~�Ɛ����̏Փ˔�����s��
     *  @param  �~�̒��S���W
     *  @param  �~�̔��a
     *  @param  �����̎n�_
     *  @param  �����̏I�_
     *  @return �Փ˂����ꍇ�Ftrue
     *  @return �Փ˂��Ȃ������ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckCircleAndSegment(const Point2& rCircleCenterPosition,
                                                   T circleRadius,
                                                   const Point2& rSegmentBeginPoint,
                                                   const Point2& rSegmentEndPoint)
    {
        // �����̎n�_����I�_�܂ł̃x�N�g��
        Point2 segmentVector(rSegmentEndPoint - rSegmentBeginPoint);

        // �����̎n�_����~�̒��S���W�܂ł̃x�N�g��
        Point2 vectorFromSegmentBeginToCircleCenter(rCircleCenterPosition - rSegmentBeginPoint);

        // 2�̃x�N�g���̊O��
        T crossProduct = Point2::s_CrossProduct(segmentVector, vectorFromSegmentBeginToCircleCenter);

        // ��������~�܂ł̋���
        T distance = std::abs(crossProduct) / segmentVector.GetLength();

        // ��������~�܂ł̋������~�̔��a���Z���ꍇ
        if (distance <= circleRadius)
        {
            // �����̏I�_����~�̒��S���W�܂ł̃x�N�g�������߂�
            Point2 vectorFromSegmentEndToCircleCenter(rCircleCenterPosition - rSegmentEndPoint);

            // �����̎n�_����I�_�܂ł̃x�N�g���ɐ����̎n�_����~�̒��S���W�܂ł̃x�N�g����
            // �����̏I�_����~�̒��S���W�܂ł̃x�N�g������ς��A���̒l�̏�Z��0�ȉ��̏ꍇ�͏Փ�
            if (Point2::s_DotProduct(segmentVector, vectorFromSegmentBeginToCircleCenter)
                * Point2::s_DotProduct(segmentVector, vectorFromSegmentEndToCircleCenter) <= static_cast<T>(0.0))
            {
                return true;
            }
            else
            {
                // �~�̔��a��2������߂�
                T radiusSquare = circleRadius * circleRadius;

                // �����̎n�_����~�̒��S���W�̋�����2��A
                // �܂��͐����̏I�_����~�̒��S���W�̋�����2�悪�~�̔��a��2����Z���ꍇ�͏Փ�
                if ((vectorFromSegmentBeginToCircleCenter.GetLengthSquare() <= radiusSquare)
                    || (vectorFromSegmentEndToCircleCenter.GetLengthSquare() < radiusSquare))
                {
                    return true;
                }
            }
        }

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  2D�̓_�Ɠ_�̏Փ˔�����s��
     *  @param  �_
     *  @param  ������̓_
     *  @return �Փ˂����ꍇ�Ftrue
     *  @return �Փ˂��Ȃ������ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckPointAndPoint(const Point2& rPoint,
                                                const Point2& rAnotherPoint)
    {
        // �_�̍��W���덷�͈͓��ł���ΏՓ�
        if ((std::abs(rPoint.x_ - rAnotherPoint.x_) <= static_cast<T>(Math::s_EPSILON))
            && (std::abs(rPoint.y_ - rAnotherPoint.y_) <= static_cast<T>(Math::s_EPSILON)))
        {
            return true;
        }

        return false;
    }


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
    bool C_Detection2D<T>::s_CheckPointAndSegment(const Point2& rPoint,
                                                  const Point2& rSegmentBeginPoint,
                                                  const Point2& rSegmentEndPoint)
    {
        // �����̎n�_����I�_�܂ł̃x�N�g�������߁A�������擾
        Point2 segmentVector(rSegmentEndPoint - rSegmentBeginPoint);
        T segmentLength = segmentVector.GetLength();

        // �����̎n�_����_�܂ł̃x�N�g�������߁A�������擾
        Point2 vectorFromSegmentBeginToPoint(rPoint - rSegmentBeginPoint);
        T segmentBeginFromPointDistance = vectorFromSegmentBeginToPoint.GetLength();

        // 2�̃x�N�g���̊O��
        T crossProduct = Point2::s_CrossProduct(segmentVector, vectorFromSegmentBeginToPoint);

        // 2�̃x�N�g���̊O�ς�0�Ɠ������A
        // �����̎n�_����_�܂ł̒����������̒������Z�������ꍇ�͏Փ�
        if ((std::abs(crossProduct) <= static_cast<T>(Math::s_EPSILON)) && (segmentBeginFromPointDistance <= segmentLength))
        {
            return true;
        }

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  �_�Ƒȉ~�̏Փ˔�����s��
     *  @param  �_
     *  @param  �ȉ~�̒��S���W
     *  @param  �ȉ~�̎���
     *  @param  �ȉ~�̊p�x( ���W�A���l )
     *  @return �Փ˂����ꍇ�Ftrue
     *  @return �Փ˂��Ȃ������ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckPointAndEllipse(const Point2& rPoint,
                                                  const Point2& rEllipseCenterPosition,
                                                  const Point2& rEllipseSemidiameter,
                                                  T ellipseAngle)
    {
        // �ȉ~�̒��S���W����_�܂ł̋���
        Point2 distance(rPoint - rEllipseCenterPosition);

        // ���]�����ȉ~�̊p�x
        T inverseEllipseAngle = -ellipseAngle;

        // �ȉ~�𒆐S�ɔ��]�����ȉ~�̊p�x��������]�����_�����߂�
        Point2 rotatePoint;

        rotatePoint.x_ = std::cos(inverseEllipseAngle) * distance.x_ - std::sin(inverseEllipseAngle) * distance.y_;
        rotatePoint.y_ = std::sin(inverseEllipseAngle) * distance.x_ + std::cos(inverseEllipseAngle) * distance.y_;

        // �ȉ~�̔��a��X�����ɍ��킹�A�~�ɕό`�����ꍇ�̓_�̍��W�����߂�
        rotatePoint.y_ *= rEllipseSemidiameter.x_ / rEllipseSemidiameter.y_;

        // �ȉ~�̒��S����_�܂ł̋�����2�悪�ȉ~��X����( �~�̔��a )��2����Z���ꍇ�͏Փ�
        if (rotatePoint.GetLengthSquare() <= rEllipseSemidiameter.x_ * rEllipseSemidiameter.x_) return true;

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  �����Ɛ����̏Փ˔�����s��
     *  @param  �n�_
     *  @param  �I�_
     *  @param  ������̎n�_
     *  @param  ������̏I�_
     *  @return �Փ˂����ꍇ�Ftrue
     *  @return �Փ˂��Ȃ������ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckSegmentAndSegment(const Point2& rBeginPoint,
                                                    const Point2& rEndPoint,
                                                    const Point2& rAnotherBeginPoint,
                                                    const Point2& rAnotherEndPoint,
                                                    Point2* pIntersectionPoint)
    {
        // �n�_����I�_�܂ł̃x�N�g��
        Point2 vector(rEndPoint - rBeginPoint);

        // �n�_���������̎n�_�܂ł̃x�N�g��
        Point2 beginFromAnotherBegin(rAnotherBeginPoint - rBeginPoint);

        // �n�_���������̏I�_�܂ł̃x�N�g��
        Point2 beginFromAnotherEnd(rAnotherEndPoint - rBeginPoint);

        // ������̐����̎n�_����I�_�܂ł̃x�N�g��
        Point2 anotherVector(rAnotherEndPoint - rAnotherBeginPoint);

        // ������̐����̎n�_��������̎n�_�܂ł̃x�N�g��
        Point2 anotherBeginFromBegin(beginFromAnotherBegin.GetInvert());

        // ������̐����̎n�_��������̏I�_�܂ł̃x�N�g��
        Point2 anotherBeginFromEnd(rEndPoint - rAnotherBeginPoint);

        // ������̐����̎n�_����I�_�܂ł̃x�N�g���Ƃ�����̐����̎n�_����n�܂�x�N�g��2�̊O�ς����߂�
        T anotherCrossAnotherBeginFromBegin = Point2::s_CrossProduct(anotherVector, anotherBeginFromBegin);
        T anotherCrossAnotherBeginFromEnd = Point2::s_CrossProduct(anotherVector, anotherBeginFromEnd);

        // �e�x�N�g���̊O�ϓ��m�̏�Z�������Ƃ�0�̏ꍇ�͏Փ�
        if ((Point2::s_CrossProduct(vector, beginFromAnotherBegin) * Point2::s_CrossProduct(vector, beginFromAnotherEnd) <= static_cast<T>(0.0))
         && (anotherCrossAnotherBeginFromBegin * anotherCrossAnotherBeginFromEnd <= static_cast<T>(0.0)))
        {
            // ��_���ݒ肳��Ă���ꍇ�͌�_�����߂�
            if (pIntersectionPoint)
            {
                // �����̌�_�܂ł̒����̔䗦�����߂�
                T ratio1 = std::abs(anotherCrossAnotherBeginFromBegin);
                T ratio2 = std::abs(anotherCrossAnotherBeginFromEnd);

                // �䗦�̍��v
                T sumRatio = ratio1 + ratio2;

                // ��_�����߂�
                (*pIntersectionPoint) = rBeginPoint + (vector * (ratio1 / sumRatio));
            }

            return true;
        }

        return false;
    }


    /* �����I�C���X�^���X�� */
    template class C_Detection2D<float>;
    template class C_Detection2D<double>;
}


