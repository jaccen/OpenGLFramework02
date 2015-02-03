/* �w�b�_�t�@�C�� */
#include "Vector3.h"
#include "../Quaternion/Quaternion.h"


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
    const S_Vector3<T> S_Vector3<T>::s_RIGHT_DIRECTION(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
    
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::s_LEFT_DIRECTION(-static_cast<T>(-1), static_cast<T>(0), static_cast<T>(0));
    
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::s_UP_DIRECTION(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
    
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::s_DOWN_DIRECTION(static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0));
    
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::s_FRONT_DIRECTION(static_cast<T>(0), static_cast<T>(0), static_cast<T>(-1));
    
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::s_BACK_DIRECTION(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
    
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::s_ZERO;
    
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::s_ONE(static_cast<T>(1));
    
    
#pragma endregion
    
    
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T>::S_Vector3() : S_Vector3(static_cast<T>(0))
    {
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^( �w�肵��1�̒l�Ŋe�����̏����� )
     *  @param  �l
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T>::S_Vector3(T value) : S_Vector3(value, value ,value)
    {
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^( �w�肵���l�Ŋe�����̏����� )
     *  @param  X����
     *  @param  Y����
     *  @param  Z����
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T>::S_Vector3(T x, T y, T z) : 
    
        // X�EY����
        xy_(x, y),
    
        // Z����
        z_(z)
    
    {
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^( �w�肵���z��Ŋe�����̏����� )
     *  @param  �v�f��3�̔z��
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T>::S_Vector3(const T a[3]) : S_Vector3(a[0], a[1], a[2])
    {
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^( 2D�x�N�g����Z�����ŏ����������� )
     *  @param  X�EY����
     *  @param  Z����
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T>::S_Vector3(const S_Vector2<T>& rXY, T z) : 
    
        // X�EY����
        xy_(rXY),
    
        // Z����
        z_(z)
    
    {
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T>::~S_Vector3()
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
    void S_Vector3<T>::Zero()
    {
        x_ = static_cast<T>(0);
        y_ = static_cast<T>(0);
        z_ = static_cast<T>(0);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �e���������̒l�ɕύX����
     *  @param  �l
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::Fill(T value)
    {
        x_ = value;
        y_ = value;
        z_ = value;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �P�ʃx�N�g��������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::Normalize()
    {
        // �������擾
        T length = GetLength();
    
        assert(length != static_cast<T>(0));
    
        // �P�ʃx�N�g����
        x_ /= length;
        y_ /= length;
        z_ /= length;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �x�N�g���𔽓]����
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::Invert()
    {
        x_ *= static_cast<T>(-1);
        y_ *= static_cast<T>(-1);
        z_ *= static_cast<T>(-1);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  X������x�N�g������]����
     *  @param  �p�x( ���W�A���l )
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::RotateX(T angle)
    {
        T tempZ = z_;
    
        z_ = tempZ * std::cos(angle) - y_ * std::sin(angle);
        y_ = tempZ * std::sin(angle) + y_ * std::cos(angle);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  Y������x�N�g������]����
     *  @param  �p�x( ���W�A���l )
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::RotateY(T angle)
    {
        T tempX = x_;
    
        x_ = tempX * std::cos(angle) - z_ * std::sin(angle);
        z_ = tempX * std::sin(angle) + z_ * std::cos(angle);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  Z������x�N�g������]����
     *  @param  �p�x( ���W�A���l )
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::RotateZ(T angle)
    {
        T tempX = x_;
    
        x_ = tempX * std::cos(angle) - y_ * std::sin(angle);
        y_ = tempX * std::sin(angle) + y_ * std::cos(angle);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �C�ӎ�����x�N�g������]����
     *  @param  ��
     *  @param  �p�x( ���W�A���l )
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::RotateAxis(const S_Vector3<T>& rAxis, T angle)
    {
        // ��]����x�N�g��
        S_Quaternion<T> rotationVector(static_cast<T>(0), *this);
    
        // ��]�N�H�[�^�j�I�����쐬
        S_Quaternion<T> rotationQuaternion = S_Quaternion<T>::s_CreateRotationAxis(rAxis, angle);
        S_Quaternion<T> inverseRotationQuaternion = S_Quaternion<T>::s_CreateRotationAxis(rAxis.GetInvert(), angle);
    
        // �x�N�g������]���A���g�ɑ��
        rotationVector =  inverseRotationQuaternion * rotationVector * rotationQuaternion;
        (*this) = rotationVector.xyz_;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �����Ńx�N�g�����N�����v����
     *  @param  �ŏ��̒���
     *  @param  �ő�̒���
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::ClampLength(T minLength, T maxLength)
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
    T S_Vector3<T>::GetLength() const
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
    T S_Vector3<T>::GetLengthSquare() const
    {
        return Square(x_) + Square(y_) + Square(z_);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �P�ʃx�N�g�����擾����
     *  @param  �Ȃ�
     *  @return �P�ʃx�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::GetNormalize() const
    {
        S_Vector3 normalizationVector(*this);
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
    S_Vector3<T> S_Vector3<T>::GetInvert() const
    {
        return S_Vector3(-x_, -y_, -z_);
    }

    
    /*************************************************************//**
     *
     *  @brief  X�������]�����x�N�g�����擾����
     *  @param  �p�x( ���W�A���l )
     *  @return ��]�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::GetRotateX(T angle) const
    {
        S_Vector3 rotationVector(*this);
        rotationVector.RotateX(angle);
    
        return rotationVector;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  Y�������]�����x�N�g�����擾����
     *  @param  �p�x( ���W�A���l )
     *  @return ��]�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::GetRotateY(T angle) const
    {
        S_Vector3 rotationVector(*this);
        rotationVector.RotateY(angle);
    
        return rotationVector;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  Z�������]�����x�N�g�����擾����
     *  @param  �p�x( ���W�A���l )
     *  @return ��]�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::GetRotateZ(T angle) const
    {
        S_Vector3 rotationVector(*this);
        rotationVector.RotateZ(angle);
    
        return rotationVector;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �C�ӎ������]�����x�N�g�����擾����
     *  @param  ��
     *  @param  �p�x( ���W�A���l )
     *  @return ��]�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::GetRotateAxis(const S_Vector3<T>& rAxis, T angle) const
    {
        S_Vector3 rotationPosition(*this);
        rotationPosition.RotateAxis(rAxis, angle);
    
        return rotationPosition;
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
    S_Vector3<T> S_Vector3<T>::GetClampLength(T minLength, T maxLength) const
    {
        S_Vector3 clampVector = (*this);
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
    std::string S_Vector3<T>::GetConvertToString() const
    {
        return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ", " + std::to_string(z_) + ")";
    }
    
    
    /*************************************************************//**
     *
     *  @brief  ���ς����߂�
     *  @param  ��ڂ̃x�N�g��
     *  @param  ��ڂ̃x�N�g��
     *  @return ����
     *
     ****************************************************************/
    template<typename T>
    T S_Vector3<T>::s_DotProduct(const S_Vector3<T>& rLhs, const S_Vector3<T>& rRhs)
    {
        return (rLhs.x_ * rRhs.x_) + (rLhs.y_ * rRhs.y_) + (rLhs.z_ * rRhs.z_);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �O�ς����߂�
     *  @param  ��ڂ̃x�N�g��
     *  @param  ��ڂ̃x�N�g��
     *  @return �O��
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_CrossProduct(const S_Vector3<T>& rLhs, const S_Vector3<T>& rRhs)
    {
        S_Vector3 crossVector;
    
        crossVector.x_ = (rLhs.y_ * rRhs.z_) - (rLhs.z_ * rRhs.y_);
        crossVector.y_ = (rLhs.z_ * rRhs.x_) - (rLhs.x_ * rRhs.z_);
        crossVector.z_ = (rLhs.x_ * rRhs.y_) - (rLhs.y_ * rRhs.x_);
        
        return crossVector;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �X�J���[�O�d�ς����߂�
     *  @param  ��ڂ̃x�N�g��
     *  @param  ��ڂ̃x�N�g��
     *  @param  �O�ڂ̃x�N�g��
     *  @return �X�J���[�O�d��
     *
     ****************************************************************/
    template<typename T>
    T S_Vector3<T>::s_ScalarTripleProduct(const S_Vector3<T>& rA,
                                          const S_Vector3<T>& rB,
                                          const S_Vector3<T>& rC)
    {
        return s_DotProduct(rA, s_CrossProduct(rB, rC));
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �x�N�g���O�d�ς����߂�
     *  @param  ��ڂ̃x�N�g��
     *  @param  ��ڂ̃x�N�g��
     *  @param  �O�ڂ̃x�N�g��
     *  @return �x�N�g���O�d��
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_VectorTripleProduct(const S_Vector3<T>& rA,
                                                     const S_Vector3<T>& rB,
                                                     const S_Vector3<T>& rC)
    {
        return s_CrossProduct(rA, s_CrossProduct(rB, rC));
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
    S_Vector3<T> S_Vector3<T>::s_Lerp(const S_Vector3<T>& rStartPoint,
                                      const S_Vector3<T>& rEndPoint,
                                      T coefficient)
    {
        S_Vector3 lerpPoint;
    
        lerpPoint.x_ = (rEndPoint.x_ - rStartPoint.x_) * coefficient + rStartPoint.x_;
        lerpPoint.y_ = (rEndPoint.y_ - rStartPoint.y_) * coefficient + rStartPoint.y_;
        lerpPoint.z_ = (rEndPoint.z_ - rStartPoint.z_) * coefficient + rStartPoint.z_;
    
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
    S_Vector3<T> S_Vector3<T>::s_Slerp(const S_Vector3<T>& rStartPoint,
                                       const S_Vector3<T>& rEndPoint,
                                       T coefficient)
    {
        // �p�x�ƃT�C�������߂�
        T angle = s_AngleBetweenVectors(rStartPoint, rEndPoint);
        T sine = std::sin(angle);
    
        // �e��ԌW�������߂�
        T startCoefficient = std::sin(angle * (static_cast<T>(1) - coefficient));
        T endCoefficient = std::sin(angle * coefficient);
    
        // ���ʐ��`��Ԃ����_�����߂�
        S_Vector3 slerpPoint = rStartPoint * startCoefficient + rEndPoint * endCoefficient;
    
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
    S_Vector3<T> S_Vector3<T>::s_Hermite(const S_Vector3<T>& rStartPoint,
                                         const S_Vector3<T>& rStartTangent,
                                         const S_Vector3<T>& rEndPoint,
                                         const S_Vector3<T>& rEndTangent,
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
        S_Vector3 hermitePoint;
    
        hermitePoint.x_ = rStartPoint.x_ * p0 + rStartTangent.x_ * t0 + rEndPoint.x_ * p1 + rEndTangent.x_ * t1;
        hermitePoint.y_ = rStartPoint.y_ * p0 + rStartTangent.y_ * t0 + rEndPoint.y_ * p1 + rEndTangent.y_ * t1;
        hermitePoint.z_ = rStartPoint.z_ * p0 + rStartTangent.z_ * t0 + rEndPoint.z_ * p1 + rEndTangent.z_ * t1;
    
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
    S_Vector3<T> S_Vector3<T>::s_CatmullRomSpline(const S_Vector3<T>& rPreviousStartPoint,
                                                  const S_Vector3<T>& rStartPoint,
                                                  const S_Vector3<T>& rEndPoint,
                                                  const S_Vector3<T>& rNextEndPoint,
                                                  T coefficient)
    {
        // ���T�C�h�̓_����ڐ������߂�
        S_Vector3 startTangent = (rEndPoint - rPreviousStartPoint) * static_cast<T>(0.5);
        S_Vector3 endTangent = (rNextEndPoint - rStartPoint) * static_cast<T>(0.5);
    
        // �ڐ��𗘗p���āA�G���~�[�g���
        S_Vector3 catmullRomSplinePoint = s_Hermite(rStartPoint, startTangent, rEndPoint, endTangent, coefficient);
    
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
    S_Vector3<T> S_Vector3<T>::s_Bezier(const S_Vector3<T>& rStartPoint,
                                        const S_Vector3<T>& rEndPoint,
                                        const S_Vector3<T>& rControlPoint1,
                                        const S_Vector3<T>& rControlPoint2,
                                        T coefficient)
    {
        // �e�_�̌W�������߂�
        T oneMinusCoefficient = static_cast<T>(1) - coefficient;
        
        T p0 = Cubic(oneMinusCoefficient);
        T p1 = Cubic(coefficient);
        T c0 = static_cast<T>(3) * coefficient * Square(oneMinusCoefficient);
        T c1 = static_cast<T>(3) * Square(coefficient) * oneMinusCoefficient;
    
        // �x�W�F��Ԃ���
        S_Vector3 bezierPoint;
    
        bezierPoint.x_ = rStartPoint.x_ * p0 + rEndPoint.x_ * p1 + rControlPoint1.x_ * c0 + rControlPoint2.x_ * c1;
        bezierPoint.y_ = rStartPoint.y_ * p0 + rEndPoint.y_ * p1 + rControlPoint1.y_ * c0 + rControlPoint2.y_ * c1;
        bezierPoint.z_ = rStartPoint.z_ * p0 + rEndPoint.z_ * p1 + rControlPoint1.z_ * c0 + rControlPoint2.z_ * c1;
    
        return bezierPoint;
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
    S_Vector3<T> S_Vector3<T>::s_InterceptPoint(const S_Vector3<T>& rPosition,
                                                const S_Vector3<T>& rVelocity,
                                                const S_Vector3<T>& rAnotherPosition,
                                                const S_Vector3<T>& rAnotherVelocity)
    {
        // �����Ƒ��x�̍������߂�
        S_Vector3 distance = rPosition - rAnotherPosition;
        S_Vector3 velocityDifference = rVelocity - rAnotherVelocity;
    
        // �������瑬�x������A���Ԃ�����
        T time = distance.GetLength() / velocityDifference.GetLength();
    
        // �}���|�C���g�����߂�
        S_Vector3 interceptPoint = rPosition + (rVelocity * time);
    
        return interceptPoint;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �x�N�g���Ԃ̊p�x�����߂�
     *  @param  ��ڂ̃x�N�g��
     *  @param  ��ڂ̃x�N�g��
     *  @return �p�x( ���W�A���l )
     *
     ****************************************************************/
    template<typename T>
    T S_Vector3<T>::s_AngleBetweenVectors(const S_Vector3<T>& rLhs, const S_Vector3<T>& rRhs)
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
    T S_Vector3<T>::s_DistanceBetweenVectors(const S_Vector3<T>& rLhs, const S_Vector3<T>& rRhs)
    {
        S_Vector3 distance = rLhs - rRhs;
    
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
    S_Vector3<T> S_Vector3<T>::s_Minimize(const S_Vector3<T>& rLhs, const S_Vector3<T>& rRhs)
    {
        S_Vector3 minimizationVector;
    
        minimizationVector.x_ = (rLhs.x_ < rRhs.x_) ? rLhs.x_ : rRhs.x_;
        minimizationVector.y_ = (rLhs.y_ < rRhs.y_) ? rLhs.y_ : rRhs.y_;
        minimizationVector.z_ = (rLhs.z_ < rRhs.z_) ? rLhs.z_ : rRhs.z_;
    
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
    S_Vector3<T> S_Vector3<T>::s_Maximize(const S_Vector3<T>& rLhs, const S_Vector3<T>& rRhs)
    {
        S_Vector3 maximizationVector;
    
        maximizationVector.x_ = (rLhs.x_ > rRhs.x_) ? rLhs.x_ : rRhs.x_;
        maximizationVector.y_ = (rLhs.y_ > rRhs.y_) ? rLhs.y_ : rRhs.y_;
        maximizationVector.z_ = (rLhs.z_ > rRhs.z_) ? rLhs.z_ : rRhs.z_;
    
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
    S_Vector3<T> S_Vector3<T>::s_MoveTowards(const S_Vector3<T>& rStartPoint, 
                                             const S_Vector3<T>& rEndPoint,
                                             T distance)
    {
        if (distance < static_cast<T>(0)) return rStartPoint;
    
        S_Vector3 difference = rStartPoint - rEndPoint;
        S_Vector3 movement = difference.GetNormalize() * distance;
    
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
    S_Vector3<T> S_Vector3<T>::s_Project(const S_Vector3<T>& rVector, 
                                         const S_Vector3<T>& rNormal)
    {
        // �P�ʃx�N�g���������@���Ɠ��e�̒������擾
        S_Vector3 normalizationNormal = rNormal.GetNormalize();
        T projectLength = s_DotProduct(rVector, normalizationNormal);
    
        return normalizationNormal * projectLength;
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
    S_Vector3<T> S_Vector3<T>::s_Reflect(const S_Vector3<T>& rVector, 
                                         const S_Vector3<T>& rNormal)
    {
        // �P�ʃx�N�g���������@�����擾
        S_Vector3 normalizationNormal = rNormal.GetNormalize();
    
        // ���˃x�N�g�������߂�
        S_Vector3 reflectionVector = rVector - static_cast<T>(2) * s_DotProduct(rVector, normalizationNormal) * normalizationNormal;
    
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
    S_Vector3<T> S_Vector3<T>::s_Refract(const S_Vector3<T>& rIncidentVector, 
                                         const S_Vector3<T>& rNormal,
                                         T refractiveIndex)
    {
        // �e�x�N�g����P�ʃx�N�g����
        S_Vector3 normalizationIncidentVector = rIncidentVector.GetNormalize();
        S_Vector3 normalizationNormal = rNormal.GetNormalize();
    
        // ���˃x�N�g���Ɩ@���x�N�g���̓��ς����߂�
        T dotProduct = s_DotProduct(normalizationIncidentVector, normalizationNormal);
    
        // ���܂̊p�x
        T refractAngle = static_cast<T>(1) - refractiveIndex * refractiveIndex * (static_cast<T>(1) - dotProduct * dotProduct);
    
        // ���܃x�N�g�������߂�
        S_Vector3 refractVector;
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
    S_Vector3<T> S_Vector3<T>::s_Slide(const S_Vector3<T>& rVector, 
                                       const S_Vector3<T>& rNormal)
    {
        // �P�ʃx�N�g���������@�����擾
        S_Vector3 normalizationNormal = rNormal.GetNormalize();
    
        // ����x�N�g�������߂�
        S_Vector3 sliderVector = rVector - s_DotProduct(rVector, normalizationNormal) * normalizationNormal;
    
        return sliderVector;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �@���x�N�g�����쐬
     *  @param  1�ڂ̍��W
     *  @param  2�ڂ̍��W
     *  @param  3�ڂ̍��W
     *  @return �@���x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_CreateNormal(const S_Vector3<T>& rPositionA, 
                                              const S_Vector3<T>& rPositionB,
                                              const S_Vector3<T>& rPositionC)
    {
        // �e���W����x�N�g�������߂�
        S_Vector3 vectorAB = rPositionB - rPositionA;
        S_Vector3 vectorBC = rPositionC - rPositionB;
    
        // �@���x�N�g�������߂�
        S_Vector3 normal = s_CrossProduct(vectorAB, vectorBC);
        normal.Normalize();
    
        return normal;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �ڐ��x�N�g���Ə]�@�����쐬
     *  @param  1�ڂ̍��W
     *  @param  1�ڂ̃e�N�X�`�����W
     *  @param  2�ڂ̍��W
     *  @param  2�ڂ̃e�N�X�`�����W
     *  @param  3�ڂ̍��W
     *  @param  3�ڂ̃e�N�X�`�����W
     *  @return �ڐ��x�N�g���Ə]�@���x�N�g��
     *
     ****************************************************************/
    template<typename T>
    std::tuple<S_Vector3<T>, S_Vector3<T>> S_Vector3<T>::s_CreateTangentAndBinormal(const S_Vector3<T>& rPositionA,   
                                                                                    const S_Vector2<T>& rTextureCoordA,
                                                                                    const S_Vector3<T>& rPositionB,
                                                                                    const S_Vector2<T>& rTextureCoordB,
                                                                                    const S_Vector3<T>& rPositionC,
                                                                                    const S_Vector2<T>& rTextureCoordC)
    {
        // ���_A�ɑ΂��鑊�ΓI�ȃx�N�g�������߂�
        S_Vector3 vectorPositionAB = rPositionB - rPositionA;
        S_Vector3 vectorPositionAC = rPositionC - rPositionA;
    
        S_Vector2<T> vectorTextureCoordAB = rTextureCoordB - rTextureCoordA;
        S_Vector2<T> vectorTextureCoordAC = rTextureCoordC - rTextureCoordA;
    
        // �ڐ��x�N�g���Ə]�@���x�N�g�������߂�
        T denominator = vectorTextureCoordAB.x_ * vectorTextureCoordAC.y_ - vectorTextureCoordAB.y_ * vectorTextureCoordAC.x_;
        assert(denominator != static_cast<T>(0));
        
        T partOfInverseMatrix = static_cast<T>(1) / denominator;
    
        S_Vector3 tangent((vectorTextureCoordAC.y_ * vectorPositionAB.x_ - vectorTextureCoordAB.y_ * vectorPositionAC.x_) * partOfInverseMatrix,
                          (vectorTextureCoordAC.y_ * vectorPositionAB.y_ - vectorTextureCoordAB.y_ * vectorPositionAC.y_) * partOfInverseMatrix,
                          (vectorTextureCoordAC.y_ * vectorPositionAB.z_ - vectorTextureCoordAB.y_ * vectorPositionAC.z_) * partOfInverseMatrix);
    
        S_Vector3 binormal((vectorTextureCoordAB.x_ * vectorPositionAC.x_ - vectorTextureCoordAC.x_ * vectorPositionAB.x_) * partOfInverseMatrix,
                           (vectorTextureCoordAB.x_ * vectorPositionAC.y_ - vectorTextureCoordAC.x_ * vectorPositionAB.y_) * partOfInverseMatrix,
                           (vectorTextureCoordAB.x_ * vectorPositionAC.z_ - vectorTextureCoordAC.x_ * vectorPositionAB.z_) * partOfInverseMatrix);
    
        return std::make_tuple(tangent, binormal);
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
    S_Vector3<T> S_Vector3<T>::s_CenterOfGravityWith3Points(const S_Vector3<T>& rA,
                                                            const S_Vector3<T>& rB,
                                                            const S_Vector3<T>& rC)
    {
        S_Vector3 centerOfGravity(rA + rB + rC);
        centerOfGravity /= static_cast<T>(3);
    
        return centerOfGravity;
    }
    
    
    #pragma region S_Vector3�^�Ƃ̉��Z�q�̃I�[�o�[���[�h
    
    
    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g�������Z�����x�N�g�������߂�
     *  @param  ������̃x�N�g��
     *  @return ���Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::operator+(const S_Vector3<T>& rAnother) const
    {
        return S_Vector3(x_ + rAnother.x_, 
                         y_ + rAnother.y_,
                         z_ + rAnother.z_);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g�������Z�����x�N�g�������߂�
     *  @param  ������̃x�N�g��
     *  @return ���Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::operator-(const S_Vector3<T>& rAnother) const
    {
        return S_Vector3(x_ - rAnother.x_,
                         y_ - rAnother.y_,
                         z_ - rAnother.z_);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g������Z�����x�N�g�������߂�
     *  @param  ������̃x�N�g��
     *  @return ��Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::operator*(const S_Vector3<T>& rAnother) const
    {
        return S_Vector3(x_ * rAnother.x_,
                         y_ * rAnother.y_,
                         z_ * rAnother.z_);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g�������Z�����x�N�g�������߂�
     *  @param  ������̃x�N�g��
     *  @return ���Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::operator/(const S_Vector3<T>& rAnother) const
    {
        assert(rAnother.x_ != static_cast<T>(0));
        assert(rAnother.y_ != static_cast<T>(0));
        assert(rAnother.z_ != static_cast<T>(0));
    
        return S_Vector3(x_ / rAnother.x_,
                         y_ / rAnother.y_,
                         z_ / rAnother.z_);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g�������Z����
     *  @param  ������̃x�N�g��
     *  @return ���Z��̃x�N�g��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T>& S_Vector3<T>::operator+=(const S_Vector3<T>& rAnother)
    {
        x_ += rAnother.x_;
        y_ += rAnother.y_;
        z_ += rAnother.z_;
    
        return (*this);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g���Ō��Z����
     *  @param  ������̃x�N�g��
     *  @return ���Z��̃x�N�g��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T>& S_Vector3<T>::operator-=(const S_Vector3<T>& rAnother)
    {
        x_ -= rAnother.x_;
        y_ -= rAnother.y_;
        z_ -= rAnother.z_;
    
        return (*this);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g���ŏ�Z����
     *  @param  ������̃x�N�g��
     *  @return ��Z��̃x�N�g��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T>& S_Vector3<T>::operator*=(const S_Vector3<T>& rAnother)
    {
        x_ *= rAnother.x_;
        y_ *= rAnother.y_;
        z_ *= rAnother.z_;
    
        return (*this);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g���ŏ��Z����
     *  @param  ������̃x�N�g��
     *  @return ���Z��̃x�N�g��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T>& S_Vector3<T>::operator/=(const S_Vector3<T>& rAnother)
    {
        assert(rAnother.x_ != static_cast<T>(0));
        assert(rAnother.y_ != static_cast<T>(0));
        assert(rAnother.z_ != static_cast<T>(0));
    
        x_ /= rAnother.x_;
        y_ /= rAnother.y_;
        z_ /= rAnother.z_;
    
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
    bool S_Vector3<T>::operator==(const S_Vector3<T>& rAnother) const
    {
        return std::abs(x_ - rAnother.x_) < static_cast<T>(s_EPSILON)
            && std::abs(y_ - rAnother.y_) < static_cast<T>(s_EPSILON)
            && std::abs(z_ - rAnother.z_) < static_cast<T>(s_EPSILON);
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
    bool S_Vector3<T>::operator!=(const S_Vector3<T>& rAnother) const
    {
        return std::abs(x_ - rAnother.x_) > static_cast<T>(s_EPSILON)
            || std::abs(y_ - rAnother.y_) > static_cast<T>(s_EPSILON)
            || std::abs(z_ - rAnother.z_) > static_cast<T>(s_EPSILON);
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
    const S_Vector3<T> S_Vector3<T>::operator*(T value) const
    {
        return S_Vector3(x_ * value, y_ * value, z_ * value);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  T�^�̒l�Ŋe���������Z�����x�N�g�������߂�
     *  @param  T�^�̒l
     *  @return ���Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::operator/(T value) const
    {
        assert(value != static_cast<T>(0));
    
        return S_Vector3(x_ / value, y_ / value, z_ / value);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  T�^�̒l���e�����ɏ�Z����
     *  @param  T�^�̒l
     *  @return ��Z��̃x�N�g��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T>& S_Vector3<T>::operator*=(T value)
    {
        x_ *= value;
        y_ *= value;
        z_ *= value;
    
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
    const S_Vector3<T>& S_Vector3<T>::operator/=(T value)
    {
        assert(value != static_cast<T>(0));
    
        x_ /= value;
        y_ /= value;
        z_ /= value;
    
        return (*this);
    }
    
    
    #pragma endregion
    
    
    #pragma region �L���X�g���Z�q�̃I�[�o�[���[�h
    
    
    /*************************************************************//**
     *
     *  @brief  S_Vector2�^�փL���X�g����
     *  @param  �Ȃ�
     *  @return 2D�x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T>::operator S_Vector2<T>() const
    {
        return xy_;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  string�^�փL���X�g����
     *  @param  �Ȃ�
     *  @return ������ɕϊ������x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T>::operator std::string() const
    {
        return GetConvertToString();
    }
    
    
    #pragma endregion
    
    
    /* �����I�C���X�^���X�� */
    template struct S_Vector3<float>;
    template struct S_Vector3<double>;

}