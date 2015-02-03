/* �w�b�_�t�@�C�� */
#include "Vector2.h"


//-------------------------------------------------------------
///
/// @brief �}�X
/// @brief ���w�֘A�̖��O���
///
//-------------------------------------------------------------
namespace Math
{

#pragma region �ÓI�����o�ϐ��̏�����


    template<typename T>
    const S_Vector2<T> S_Vector2<T>::s_RIGHT_DIRECTION(static_cast<T>(1), static_cast<T>(0));

    template<typename T>
    const S_Vector2<T> S_Vector2<T>::s_LEFT_DIRECTION(-static_cast<T>(-1), static_cast<T>(0));

    template<typename T>
    const S_Vector2<T> S_Vector2<T>::s_UP_DIRECTION(static_cast<T>(0), static_cast<T>(1));

    template<typename T>
    const S_Vector2<T> S_Vector2<T>::s_DOWN_DIRECTION(static_cast<T>(0), static_cast<T>(-1));

    template<typename T>
    const S_Vector2<T> S_Vector2<T>::s_ZERO;

    template<typename T>
    const S_Vector2<T> S_Vector2<T>::s_ONE(static_cast<T>(1));


#pragma endregion


    /*************************************************************//**
    *
    *  @brief  �R���X�g���N�^
    *  @param  �Ȃ�
    *
    ****************************************************************/
    template<typename T>
    S_Vector2<T>::S_Vector2() : S_Vector2(static_cast<T>(0))
    {
    }


    /*************************************************************//**
    *
    *  @brief  �R���X�g���N�^( �w�肵��1�̒l�Ŋe�����̏����� )
    *  @param  �l
    *
    ****************************************************************/
    template<typename T>
    S_Vector2<T>::S_Vector2(T value) : S_Vector2(value, value)
    {
    }


    /*************************************************************//**
    *
    *  @brief  �R���X�g���N�^( �w�肵���l�Ŋe�����̏����� )
    *  @param  X����
    *  @param  Y����
    *
    ****************************************************************/
    template<typename T>
    S_Vector2<T>::S_Vector2(T x, T y) :

        // X����
        x_(x),

        // Y����
        y_(y)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^( �w�肵���z��Ŋe�����̏����� )
     *  @param  �v�f��2�̔z��
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T>::S_Vector2(const T a[2]) : S_Vector2(a[0], a[1])
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T>::~S_Vector2()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �[���x�N�g��������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector2<T>::Zero()
    {
        x_ = static_cast<T>(0);
        y_ = static_cast<T>(0);
    }


    /*************************************************************//**
     *
     *  @brief  �e���������̒l�ɕύX����
     *  @param  �l
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector2<T>::Fill(T value)
    {
        x_ = value;
        y_ = value;
    }


    /*************************************************************//**
     *
     *  @brief  �P�ʃx�N�g��������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector2<T>::Normalize()
    {
        // �������擾
        T length = GetLength();
        assert(length != static_cast<T>(0));

        // �P�ʃx�N�g����
        x_ /= length;
        y_ /= length;
    }



    /*************************************************************//**
     *
     *  @brief  �x�N�g���𔽓]����
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector2<T>::Invert()
    {
        x_ *= static_cast<T>(-1);
        y_ *= static_cast<T>(-1);
    }


    /*************************************************************//**
     *
     *  @brief  �����ȃx�N�g���ɕϊ�����
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector2<T>::Perpendicular()
    {
        T tempX = x_;

        // �����ȃx�N�g���ɕϊ�
        x_ = -y_;
        y_ = tempX;
    }


    /*************************************************************//**
     *
     *  @brief  �x�N�g������]����
     *  @param  �p�x( ���W�A���l )
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector2<T>::Rotate(T angle)
    {
        T tempX = x_;

        x_ = tempX * std::cos(angle) - y_ * std::sin(angle);
        y_ = tempX * std::sin(angle) + y_ * std::cos(angle);
    }


    /*************************************************************//**
     *
     *  @brief  �x�N�g���̒����ŃN�����v����
     *  @param  �ŏ��̒���
     *  @param  �ő�̒���
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector2<T>::ClampLength(T minLength, T maxLength)
    {
        // �������擾���A���̒������N�����v
        T length = GetLength();
        Clamp(length, minLength, maxLength);

        // �P�ʃx�N�g�������āA�������X�P�[��
        Normalize();
        (*this) = (*this) * length;
    }


    /*************************************************************//**
     *
     *  @brief  �������擾����
     *  @param  �Ȃ�
     *  @return ����
     *
     ****************************************************************/
    template<typename T>
    T S_Vector2<T>::GetLength() const
    {
        return SquareRoot(GetLengthSquare());
    }


    /*************************************************************//**
     *
     *  @brief  ������2����擾����
     *  @param  �Ȃ�
     *  @return ������2��
     *
     ****************************************************************/
    template<typename T>
    T S_Vector2<T>::GetLengthSquare() const
    {
        return Square(x_) + Square(y_);
    }


    /*************************************************************//**
     *
     *  @brief  �P�ʃx�N�g�����擾����
     *  @param  �Ȃ�
     *  @return �P�ʃx�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::GetNormalize() const
    {
        S_Vector2 normalizationVector(*this);
        normalizationVector.Normalize();

        return normalizationVector;
    }


    /*************************************************************//**
     *
     *  @brief  ���]�����x�N�g�����擾����
     *  @param  �Ȃ�
     *  @return ���]�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::GetInvert() const
    {
        return S_Vector2(-x_, -y_);
    }


    /*************************************************************//**
     *
     *  @brief  �����ȃx�N�g�����擾����
     *  @param  �Ȃ�
     *  @return �����ȃx�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::GetPerpendicular() const
    {
        return S_Vector2(-y_, x_);
    }


    /*************************************************************//**
     *
     *  @brief  ��]�����x�N�g�����擾����
     *  @param  �p�x( ���W�A���l )
     *  @return ��]�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::GetRotate(T angle) const
    {
        S_Vector2 rotationVector(*this);
        rotationVector.Rotate(angle);

        return rotationVector;
    }


    /*************************************************************//**
     *
     *  @brief  �x�N�g���̊p�x���擾����
     *  @param  �Ȃ�
     *  @return �p�x( ���W�A���l )
     *
     ****************************************************************/
    template<typename T>
    T S_Vector2<T>::GetAngle() const
    {
        return std::atan2(y_, x_);
    }


    /*************************************************************//**
     *
     *  @brief  �����ŃN�����v�����x�N�g�����擾����
     *  @param  �ŏ��̒���
     *  @param  �ő�̒���
     *  @return �N�����v�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::GetClampLength(T minLength, T maxLength) const
    {
        S_Vector2 clampVector = (*this);
        clampVector.ClampLength(minLength, maxLength);

        return clampVector;
    }


    /*************************************************************//**
     *
     *  @brief  �x�N�g���𕶎���ɕϊ����Ď擾����
     *  @param  �Ȃ�
     *  @return ������ɕϊ������x�N�g��
     *
     ****************************************************************/
    template<typename T>
    std::string S_Vector2<T>::GetConvertToString() const
    {
        return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
    }


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g���Ƃ̓��ς��擾����
     *  @param  ��ڂ̃x�N�g��
     *  @param  ��ڂ̃x�N�g��
     *  @return ����
     *
     ****************************************************************/
    template<typename T>
    T S_Vector2<T>::s_DotProduct(const S_Vector2<T>& rLhs, const S_Vector2<T>& rRhs)
    {
        return (rLhs.x_ * rRhs.x_) + (rLhs.y_ * rRhs.y_);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g���Ƃ̊O�ς��擾����
     *  @param  ��ڂ̃x�N�g��
     *  @param  ��ڂ̃x�N�g��
     *  @return �O��
     *
     ****************************************************************/
    template<typename T>
    T S_Vector2<T>::s_CrossProduct(const S_Vector2<T>& rLhs, const S_Vector2<T>& rRhs)
    {
        return (rLhs.x_ * rRhs.y_) - (rRhs.x_ * rLhs.y_);
    }


    /*************************************************************//**
     *
     *  @brief  ���`��Ԃ��s��
     *  @param  �n�_
     *  @param  �I�_
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return ��̓_����`��Ԃ����_
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::s_Lerp(const S_Vector2<T>& rStartPoint,
                                      const S_Vector2<T>& rEndPoint,
                                      T coefficient)
    {
        S_Vector2 lerpPoint;

        lerpPoint.x_ = (rEndPoint.x_ - rStartPoint.x_) * coefficient + rStartPoint.x_;
        lerpPoint.y_ = (rEndPoint.y_ - rStartPoint.y_) * coefficient + rStartPoint.y_;

        return lerpPoint;
    }


    /*************************************************************//**
     *
     *  @brief  ���ʐ��`��Ԃ��s��
     *  @param  �n�_
     *  @param  �I�_
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return ��̓_�����ʐ��`��Ԃ����_
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::s_Slerp(const S_Vector2<T>& rStartPoint,
                                       const S_Vector2<T>& rEndPoint,
                                       T coefficient)
    {
        // �p�x�ƃT�C�������߂�
        T angle = s_AngleBetweenVectors(rStartPoint, rEndPoint);
        T sine = std::sin(angle);

        // �e��ԌW�������߂�
        T startCoefficient = std::sin(angle * (static_cast<T>(1) - coefficient));
        T endCoefficient = std::sin(angle * coefficient);

        // ���ʐ��`��Ԃ����_�����߂�
        S_Vector2 slerpPoint = rStartPoint * startCoefficient + rEndPoint * endCoefficient;

        return slerpPoint;
    }


    /*************************************************************//**
     *
     *  @brief  �G���~�[�g��Ԃ��s��
     *  @param  �n�_
     *  @param  �n�_�̐ڐ�
     *  @param  �I�_
     *  @param  �I�_�̐ڐ�
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return ��̓_���G���~�[�g��Ԃ����_
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::s_Hermite(const S_Vector2<T>& rStartPoint,
                                         const S_Vector2<T>& rStartTangent,
                                         const S_Vector2<T>& rEndPoint,
                                         const S_Vector2<T>& rEndTangent,
                                         T coefficient)
    {
        // �e�_�Ɗe�ړ_�̌W�������߂�
        T u1 = coefficient;
        T u2 = Square(coefficient);
        T u3 = u2 * coefficient;

        T p0 = (static_cast<T>(2) * u3) - (static_cast<T>(3) * u2) + static_cast<T>(1);
        T t0 = u3 - (static_cast<T>(2) * u2) + u1;
        T p1 = (static_cast<T>(-2) * u3) + static_cast<T>(3) * u2;
        T t1 = u3 - u2;

        // �G���~�[�g��Ԃ���
        S_Vector2 hermitePoint;

        hermitePoint.x_ = rStartPoint.x_ * p0 + rStartTangent.x_ * t0 + rEndPoint.x_ * p1 + rEndTangent.x_ * t1;
        hermitePoint.y_ = rStartPoint.y_ * p0 + rStartTangent.y_ * t0 + rEndPoint.y_ * p1 + rEndTangent.y_ * t1;

        return hermitePoint;
    }


    /*************************************************************//**
     *
     *  @brief  Catmull-Rom�X�v���C����Ԃ��s��
     *  @param  �n�_�̑O�̓_
     *  @param  �n�_
     *  @param  �I�_
     *  @param  ���̏I�_
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return ��̓_��Catmull-Rom�X�v���C����Ԃ����_
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::s_CatmullRomSpline(const S_Vector2<T>& rPreviousStartPoint,
                                                  const S_Vector2<T>& rStartPoint,
                                                  const S_Vector2<T>& rEndPoint,
                                                  const S_Vector2<T>& rNextEndPoint,
                                                  T coefficient)
    {
        // ���T�C�h�̓_����ڐ������߂�
        S_Vector2 startTangent = (rEndPoint - rPreviousStartPoint) * static_cast<T>(0.5);
        S_Vector2 endTangent = (rNextEndPoint - rStartPoint) * static_cast<T>(0.5);

        // �ڐ��𗘗p���āA�G���~�[�g���
        S_Vector2 catmullRomSplinePoint = s_Hermite(rStartPoint, startTangent, rEndPoint, endTangent, coefficient);

        return catmullRomSplinePoint;
    }


    /*************************************************************//**
     *
     *  @brief  �x�W�F��Ԃ��s��
     *  @param  �n�_
     *  @param  �I�_
     *  @param  ����_1
     *  @param  ����_2
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return ��̓_���x�W�F�\��Ԃ����_
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::s_Bezier(const S_Vector2<T>& rStartPoint,
                                        const S_Vector2<T>& rEndPoint,
                                        const S_Vector2<T>& rControlPoint1,
                                        const S_Vector2<T>& rControlPoint2,
                                        T coefficient)
    {
        // �e�_�̌W�������߂�
        T oneMinusCoefficient = static_cast<T>(1) - coefficient;

        T p0 = Cubic(oneMinusCoefficient);
        T p1 = Cubic(coefficient);
        T c0 = static_cast<T>(3) * coefficient * Square(oneMinusCoefficient);
        T c1 = static_cast<T>(3) * Square(coefficient) * oneMinusCoefficient;

        // �x�W�F��Ԃ���
        S_Vector2 bezierPoint;

        bezierPoint.x_ = rStartPoint.x_ * p0 + rEndPoint.x_ * p1 + rControlPoint1.x_ * c0 + rControlPoint2.x_ * c1;
        bezierPoint.y_ = rStartPoint.y_ * p0 + rEndPoint.y_ * p1 + rControlPoint1.y_ * c0 + rControlPoint2.y_ * c1;

        return bezierPoint;
    }


    /*************************************************************//**
     *
     *  @brief  �p�x����x�N�g�����쐬����
     *  @param  �p�x( ���W�A���l )
     *  @param  ����
     *  @return �x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::s_CreateWithAngle(T angle, T length)
    {
        return S_Vector2(std::cos(angle), std::sin(angle)) * length;
    }


    /*************************************************************//**
     *
     *  @brief  �}���|�C���g( �����ʒu )�����߂�
     *  @param  ���W
     *  @param  ���x
     *  @param  ������̍��W
     *  @param  ������̑��x
     *  @return �}���|�C���g
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::s_InterceptPoint(const S_Vector2<T>& rPosition,
                                                const S_Vector2<T>& rVelocity,
                                                const S_Vector2<T>& rAnotherPosition,
                                                const S_Vector2<T>& rAnotherVelocity)
    {
        // �����Ƒ��x�̍������߂�
        S_Vector2 distance = rPosition - rAnotherPosition;
        S_Vector2 velocityDifference = rVelocity - rAnotherVelocity;

        // �������瑬�x������A���Ԃ�����
        T time = distance.GetLength() / velocityDifference.GetLength();

        // �}���|�C���g�����߂�
        S_Vector2 interceptPoint = rPosition + (rVelocity * time);

        return interceptPoint;
    }


    /*************************************************************//**
     *
     *  @brief  �x�N�g���Ԃ̊p�x�����߂�
     *  @param  �x�N�g��
     *  @param  ������̃x�N�g��
     *  @return �p�x( ���W�A���l )
     *
     ****************************************************************/
    template<typename T>
    T S_Vector2<T>::s_AngleBetweenVectors(const S_Vector2<T>& rLhs, const S_Vector2<T>& rRhs)
    {
        T cosine = s_DotProduct(rLhs.GetNormalize(), rRhs.GetNormalize());
        T angle = std::acos(cosine);

        return angle;
    }


    /*************************************************************//**
     *
     *  @brief  �x�N�g���Ԃ̋��������߂�
     *  @param  ��ڂ̃x�N�g��
     *  @param  ��ڂ̃x�N�g��
     *  @return ����
     *
     ****************************************************************/
    template<typename T>
    T S_Vector2<T>::s_DistanceBetweenVectors(const S_Vector2<T>& rLhs, const S_Vector2<T>& rRhs)
    {
        S_Vector2 distance = rLhs - rRhs;

        return distance.GetLength();
    }


    /*************************************************************//**
     *
     *  @brief  �e�����̍ŏ��l�𐬕��ɂ����x�N�g�����擾����
     *  @param  ��ڂ̃x�N�g��
     *  @param  ��ڂ̃x�N�g��
     *  @return �ŏ��l�𐬕��ɂ����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::s_Minimize(const S_Vector2<T>& rLhs, const S_Vector2<T>& rRhs)
    {
        S_Vector2 minimizationVector;

        minimizationVector.x_ = (rLhs.x_ < rRhs.x_) ? rLhs.x_ : rRhs.x_;
        minimizationVector.y_ = (rLhs.y_ < rRhs.y_) ? rLhs.y_ : rRhs.y_;

        return minimizationVector;
    }


    /*************************************************************//**
     *
     *  @brief  �e�����̍ő�l�𐬕��ɂ����x�N�g�����擾����
     *  @param  ��ڂ̃x�N�g��
     *  @param  ��ڂ̃x�N�g��
     *  @return �ő�l�𐬕��ɂ����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::s_Maximize(const S_Vector2<T>& rLhs, const S_Vector2<T>& rRhs)
    {
        S_Vector2 maximizationVector;

        maximizationVector.x_ = (rLhs.x_ > rRhs.x_) ? rLhs.x_ : rRhs.x_;
        maximizationVector.y_ = (rLhs.y_ > rRhs.y_) ? rLhs.y_ : rRhs.y_;

        return maximizationVector;
    }


    /*************************************************************//**
     *
     *  @brief  2�_�Ԃ���̋����������i�񂾓_���擾����
     *  @param  �n�_
     *  @param  �I�_
     *  @param  ����
     *  @return �n�_���狗���������i�񂾓_
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::s_MoveTowards(const S_Vector2<T>& rStartPoint,
                                             const S_Vector2<T>& rEndPoint,
                                             T distance)
    {
        if (distance < static_cast<T>(0)) return rStartPoint;

        S_Vector2 difference = rStartPoint - rEndPoint;
        S_Vector2 movement = difference.GetNormalize() * distance;

        if (movement.GetLengthSquare() >= difference.GetLengthSquare()) return rEndPoint;

        return rStartPoint + movement;
    }


    /*************************************************************//**
     *
     *  @brief  ���e�x�N�g�����擾����
     *  @param  �x�N�g��
     *  @param  �@���x�N�g��
     *  @return ���e�x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::s_Project(const S_Vector2<T>& rVector,
                                         const S_Vector2<T>& rNormal)
    {
        // �P�ʃx�N�g���������@���Ɠ��e�̒������擾
        S_Vector2 normalizationNormal = rNormal.GetNormalize();
        T length = s_DotProduct(rVector, normalizationNormal);

        return normalizationNormal * length;
    }


    /*************************************************************//**
     *
     *  @brief  ���˃x�N�g�����擾����
     *  @param  �x�N�g��
     *  @param  �@���x�N�g��
     *  @return ���˃x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::s_Reflect(const S_Vector2<T>& rVector,
                                         const S_Vector2<T>& rNormal)
    {
        // �P�ʃx�N�g���������@�����擾
        S_Vector2 normalizationNormal = rNormal.GetNormalize();

        // ���˃x�N�g�������߂�
        S_Vector2 reflectionVector = rVector - static_cast<T>(2) * s_DotProduct(rVector, normalizationNormal) * normalizationNormal;

        return reflectionVector;
    }


    /*************************************************************//**
     *
     *  @brief  ���܃x�N�g�����擾����
     *  @param  ���˃x�N�g��
     *  @param  �@���x�N�g��
     *  @param  ���ܗ�
     *  @return ���܃x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::s_Refract(const S_Vector2<T>& rIncidentVector,
                                         const S_Vector2<T>& rNormal,
                                         T refractiveIndex)
    {
        // �e�x�N�g����P�ʃx�N�g����
        S_Vector2 normalizationIncidentVector = rIncidentVector.GetNormalize();
        S_Vector2 normalizationNormal = rNormal.GetNormalize();

        // ���˃x�N�g���Ɩ@���x�N�g���̓��ς����߂�
        T dotProduct = s_DotProduct(normalizationIncidentVector, normalizationNormal);

        // ���܂̊p�x
        T refractAngle = static_cast<T>(1) - refractiveIndex * refractiveIndex * (static_cast<T>(1) - dotProduct * dotProduct);

        // ���܃x�N�g�������߂�
        S_Vector2 refractVector;
        if (refractAngle < static_cast<T>(0)) return refractVector;

        refractVector = refractiveIndex * normalizationIncidentVector
            - (refractiveIndex * dotProduct * SquareRoot(refractAngle)) * normalizationNormal;

        return refractVector;
    }


    /*************************************************************//**
     *
     *  @brief  ���肵���x�N�g�����擾����
     *  @param  �x�N�g��
     *  @param  �@���x�N�g��
     *  @return ���肵���x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::s_Slide(const S_Vector2<T>& rVector,
        const S_Vector2<T>& rNormal)
    {
        // �P�ʃx�N�g���������@�����擾
        S_Vector2 normalizationNormal = rNormal.GetNormalize();

        // ����x�N�g�������߂�
        S_Vector2 slideVector = rVector - s_DotProduct(rVector, normalizationNormal) * normalizationNormal;

        return slideVector;
    }


    /*************************************************************//**
     *
     *  @brief  3�_����d�S���擾����
     *  @param  1�ڂ̓_
     *  @param  2�ڂ̓_
     *  @param  3�ڂ̓_
     *  @return �d�S
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T> S_Vector2<T>::s_CenterOfGravityWith3Points(const S_Vector2<T>& rA,
                                                            const S_Vector2<T>& rB,
                                                            const S_Vector2<T>& rC)
    {
        S_Vector2 centerOfGravity(rA + rB + rC);
        centerOfGravity /= static_cast<T>(3);

        return centerOfGravity;
    }


#pragma region S_Vector2�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g�������Z�����x�N�g�������߂�
     *  @param  ������̃x�N�g��
     *  @return ���Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector2<T> S_Vector2<T>::operator+(const S_Vector2<T>& rAnother) const
    {
        return S_Vector2(x_ + rAnother.x_, y_ + rAnother.y_);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g�������Z�����x�N�g�������߂�
     *  @param  ������̃x�N�g��
     *  @return ���Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector2<T> S_Vector2<T>::operator-(const S_Vector2<T>& rAnother) const
    {
        return S_Vector2(x_ - rAnother.x_, y_ - rAnother.y_);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g������Z�����x�N�g�������߂�
     *  @param  ������̃x�N�g��
     *  @return ��Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector2<T> S_Vector2<T>::operator*(const S_Vector2<T>& rAnother) const
    {
        return S_Vector2(x_ * rAnother.x_, y_ * rAnother.y_);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g�������Z�����x�N�g�������߂�
     *  @param  ������̃x�N�g��
     *  @return ���Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector2<T> S_Vector2<T>::operator/(const S_Vector2<T>& rAnother) const
    {
        assert(rAnother.x_ != static_cast<T>(0));
        assert(rAnother.y_ != static_cast<T>(0));

        return S_Vector2(x_ / rAnother.x_, y_ / rAnother.y_);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g�������Z����
     *  @param  ������̃x�N�g��
     *  @return ���Z��̃x�N�g��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector2<T>& S_Vector2<T>::operator+=(const S_Vector2<T>& rAnother)
    {
        x_ += rAnother.x_;
        y_ += rAnother.y_;

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g�������Z����
     *  @param  ������̃x�N�g��
     *  @return ���Z��̃x�N�g��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector2<T>& S_Vector2<T>::operator-=(const S_Vector2<T>& rAnother)
    {
        x_ -= rAnother.x_;
        y_ -= rAnother.y_;

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g������Z����
     *  @param  ������̃x�N�g��
     *  @return ��Z��̃x�N�g��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector2<T>& S_Vector2<T>::operator*=(const S_Vector2<T>& rAnother)
    {
        x_ *= rAnother.x_;
        y_ *= rAnother.y_;

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g�������Z����
     *  @param  ������̃x�N�g��
     *  @return ���Z��x�N�g��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector2<T>& S_Vector2<T>::operator/=(const S_Vector2<T>& rAnother)
    {
        assert(rAnother.x_ != static_cast<T>(0));
        assert(rAnother.y_ != static_cast<T>(0));

        x_ /= rAnother.x_;
        y_ /= rAnother.y_;

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g���Ɣ�r����
     *  @param  ������̃x�N�g��
     *  @return �����x�N�g���̏ꍇ�Ftrue
     *  @return �Ⴄ�x�N�g���̏ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool S_Vector2<T>::operator==(const S_Vector2<T>& rAnother) const
    {
        return std::abs(x_ - rAnother.x_) < static_cast<T>(s_EPSILON)
            && std::abs(y_ - rAnother.y_) < static_cast<T>(s_EPSILON);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g���Ɣ�r����
     *  @param  ������̃x�N�g��
     *  @return �Ⴄ�x�N�g���̏ꍇ�Ftrue
     *  @return �����x�N�g���̏ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool S_Vector2<T>::operator!=(const S_Vector2<T>& rAnother) const
    {
        return std::abs(x_ - rAnother.x_) > static_cast<T>(s_EPSILON)
            || std::abs(y_ - rAnother.y_) > static_cast<T>(s_EPSILON);
    }


#pragma endregion


#pragma region T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


    /*************************************************************//**
     *
     *  @brief  T�^�̒l���e�����ɏ�Z�����x�N�g�������߂�
     *  @param  T�^�̒l
     *  @return ��Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector2<T> S_Vector2<T>::operator*(T value) const
    {
        return S_Vector2(x_ * value, y_ * value);
    }


    /*************************************************************//**
     *
     *  @brief  T�^�̒l�Ŋe���������Z�����x�N�g�������߂�
     *  @param  T�^�̒l
     *  @return ���Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector2<T> S_Vector2<T>::operator/(T value) const
    {
        assert(value != static_cast<T>(0));

        return S_Vector2(x_ / value, y_ / value);
    }


    /*************************************************************//**
     *
     *  @brief  T�^�̒l���e�����ɏ�Z����
     *  @param  T�^�̒l
     *  @return ��Z��̃x�N�g��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector2<T>& S_Vector2<T>::operator*=(T value)
    {
        x_ *= value;
        y_ *= value;

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  T�^�̒l�Ŋe���������Z����
     *  @param  T�^�̒l
     *  @return ���Z��̃x�N�g��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector2<T>& S_Vector2<T>::operator/=(T value)
    {
        assert(value != static_cast<T>(0));

        x_ /= value;
        y_ /= value;

        return (*this);
    }


#pragma endregion


#pragma region �L���X�g���Z�q�̃I�[�o�[���[�h


    /*************************************************************//**
     *
     *  @brief  string�^�փL���X�g����
     *  @param  �Ȃ�
     *  @return ������ɕϊ������x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector2<T>::operator std::string() const
    {
        return GetConvertToString();
    }


#pragma endregion


    /* �����I�C���X�^���X�� */
    template struct S_Vector2<float>;
    template struct S_Vector2<double>;

}