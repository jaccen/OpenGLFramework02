/* �w�b�_�t�@�C�� */
#include "Vector4.h"
#include "../Define/MathDefine.h"


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
    const S_Vector4<T> S_Vector4<T>::s_ZERO;

    template<typename T>
    const S_Vector4<T> S_Vector4<T>::s_ONE(static_cast<T>(1));


#pragma endregion


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::S_Vector4() : S_Vector4(static_cast<T>(0))
    {
    }


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^( �w�肵��1�̒l�Ŋe������������ )
     *  @param  �l
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::S_Vector4(T value) : S_Vector4(value, value, value, value)
    {
    }


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^( �w�肵���l�Ŋe������������ )
     *  @param  X����
     *  @param  Y����
     *  @param  Z����
     *  @param  W����
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::S_Vector4(T x, T y, T z, T w) :

        // X�EY�EZ����
        xyz_(x, y, z),

        // W����
        w_(w)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^( �w�肵���z��Ŋe������������ )
     *  @param  �v�f��4�̔z��
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::S_Vector4(const T a[4]) : S_Vector4(a[0], a[1], a[2], a[3])
    {
    }


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^( �w�肵��3D�x�N�g���ƒl�Ŋe������������ )
     *  @param  X�EY����
     *  @param  Z����
     *  @param  W����
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::S_Vector4(const S_Vector2<T>& rXY, T z, T w) :

        // X�EY�EZ����
        xyz_(rXY, z),

        // W����
        w_(w)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^( �w�肵��3D�x�N�g���ƒl�Ŋe������������ )
     *  @param  X�EY�EZ����
     *  @param  W����
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::S_Vector4(const S_Vector3<T>& rXYZ, T w) :

        // X�EY�EZ����
        xyz_(rXYZ),

        // W����
        w_(w)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::~S_Vector4()
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
    void S_Vector4<T>::Zero()
    {
        x_ = static_cast<T>(0);
        y_ = static_cast<T>(0);
        z_ = static_cast<T>(0);
        w_ = static_cast<T>(0);
    }


    /*************************************************************//**
     *
     *  @brief  �e���������̒l�ɕύX����
     *  @param  �l
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector4<T>::Fill(T value)
    {
        x_ = value;
        y_ = value;
        z_ = value;
        w_ = value;
    }


    /*************************************************************//**
     *
     *  @brief  �P�ʃx�N�g��������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector4<T>::Normalize()
    {
        // �������擾
        T length = GetLength();

        assert(length != static_cast<T>(0));

        // �P�ʃx�N�g����
        x_ /= length;
        y_ /= length;
        z_ /= length;
        w_ /= length;
    }


    /*************************************************************//**
     *
     *  @brief  �x�N�g���𔽓]����
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Vector4<T>::Invert()
    {
        x_ *= static_cast<T>(-1);
        y_ *= static_cast<T>(-1);
        z_ *= static_cast<T>(-1);
        w_ *= static_cast<T>(-1);
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
    void S_Vector4<T>::ClampLength(T minLength, T maxLength)
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
    T S_Vector4<T>::GetLength() const
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
    T S_Vector4<T>::GetLengthSquare() const
    {
        return Square(x_) + Square(y_) + Square(z_) + Square(w_);
    }


    /*************************************************************//**
     *
     *  @brief  �P�ʃx�N�g�����擾����
     *  @param  �Ȃ�
     *  @return �P�ʃx�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T> S_Vector4<T>::GetNormalize() const
    {
        S_Vector4 normalizationVector(*this);
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
    S_Vector4<T> S_Vector4<T>::GetInvert() const
    {
        return S_Vector4(-x_, -y_, -z_, -w_);
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
    S_Vector4<T> S_Vector4<T>::GetClampLength(T minLength, T maxLength) const
    {
        S_Vector4 clampVector = (*this);
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
    std::string S_Vector4<T>::GetConvertToString() const
    {
        return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ", " + std::to_string(z_) + ", " + std::to_string(w_) + ")";
    }


    /*************************************************************//**
     *
     *  @brief  ���ς����߂�
     *  @param  �x�N�g��
     *  @param  ������̃x�N�g��
     *  @return ����
     *
     ****************************************************************/
    template<typename T>
    T S_Vector4<T>::s_DotProduct(const S_Vector4<T>& rVector, const S_Vector4<T>& rAnotherVector)
    {
        return (rVector.x_ * rAnotherVector.x_)
             + (rVector.y_ * rAnotherVector.y_)
             + (rVector.z_ * rAnotherVector.z_)
             + (rVector.w_ * rAnotherVector.w_);
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
    S_Vector4<T> S_Vector4<T>::s_Lerp(const S_Vector4<T>& rStartPoint,
                                      const S_Vector4<T>& rEndPoint,
                                      T coefficient)
    {
        S_Vector4 lerpPoint;

        lerpPoint.x_ = (rEndPoint.x_ - rStartPoint.x_) * coefficient + rStartPoint.x_;
        lerpPoint.y_ = (rEndPoint.y_ - rStartPoint.y_) * coefficient + rStartPoint.y_;
        lerpPoint.z_ = (rEndPoint.z_ - rStartPoint.z_) * coefficient + rStartPoint.z_;
        lerpPoint.w_ = (rEndPoint.w_ - rStartPoint.w_) * coefficient + rStartPoint.w_;

        return lerpPoint;
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
    S_Vector4<T> S_Vector4<T>::s_Minimize(const S_Vector4<T>& rLhs, const S_Vector4<T>& rRhs)
    {
        S_Vector4 minimizationVector;

        minimizationVector.x_ = (rLhs.x_ < rRhs.x_) ? rLhs.x_ : rRhs.x_;
        minimizationVector.y_ = (rLhs.y_ < rRhs.y_) ? rLhs.y_ : rRhs.y_;
        minimizationVector.z_ = (rLhs.z_ < rRhs.z_) ? rLhs.z_ : rRhs.z_;
        minimizationVector.w_ = (rLhs.w_ < rRhs.w_) ? rLhs.w_ : rRhs.w_;

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
    S_Vector4<T> S_Vector4<T>::s_Maximize(const S_Vector4<T>& rLhs, const S_Vector4<T>& rRhs)
    {
        S_Vector4 maximizationVector;

        maximizationVector.x_ = (rLhs.x_ > rRhs.x_) ? rLhs.x_ : rRhs.x_;
        maximizationVector.y_ = (rLhs.y_ > rRhs.y_) ? rLhs.y_ : rRhs.y_;
        maximizationVector.z_ = (rLhs.z_ > rRhs.z_) ? rLhs.z_ : rRhs.z_;
        maximizationVector.w_ = (rLhs.w_ > rRhs.w_) ? rLhs.w_ : rRhs.w_;

        return maximizationVector;
    }


#pragma region S_Vector4�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g�������Z�����x�N�g�������߂�
     *  @param  ������̃x�N�g��
     *  @return ���Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector4<T> S_Vector4<T>::operator+(const S_Vector4<T>& rAnother) const
    {
        return S_Vector4(x_ + rAnother.x_,
                         y_ + rAnother.y_,
                         z_ + rAnother.z_,
                         w_ + rAnother.w_);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g���Ō��Z�����x�N�g�������߂�
     *  @param  ������̃x�N�g��
     *  @return ���Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector4<T> S_Vector4<T>::operator-(const S_Vector4<T>& rAnother) const
    {
        return S_Vector4(x_ - rAnother.x_,
                         y_ - rAnother.y_,
                         z_ - rAnother.z_,
                         w_ - rAnother.w_);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g������Z�����x�N�g�������߂�
     *  @param  ������̃x�N�g��
     *  @return ��Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector4<T> S_Vector4<T>::operator*(const S_Vector4<T>& rAnother) const
    {
        return S_Vector4(x_ * rAnother.x_,
                         y_ * rAnother.y_,
                         z_ * rAnother.z_,
                         w_ * rAnother.w_);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g���ŏ��Z�����x�N�g�������߂�
     *  @param  ������̃x�N�g��
     *  @return ���Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector4<T> S_Vector4<T>::operator/(const S_Vector4<T>& rAnother) const
    {
        assert(rAnother.x_ != static_cast<T>(0));
        assert(rAnother.y_ != static_cast<T>(0));
        assert(rAnother.z_ != static_cast<T>(0));
        assert(rAnother.w_ != static_cast<T>(0));

        return S_Vector4(x_ / rAnother.x_,
                         y_ / rAnother.y_,
                         z_ / rAnother.z_,
                         w_ / rAnother.w_);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃x�N�g�������Z����
     *  @param  ������̃x�N�g��
     *  @return ���Z��̃x�N�g��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector4<T>& S_Vector4<T>::operator+=(const S_Vector4<T>& rAnother)
    {
        x_ += rAnother.x_;
        y_ += rAnother.y_;
        z_ += rAnother.z_;
        w_ += rAnother.w_;

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
    const S_Vector4<T>& S_Vector4<T>::operator-=(const S_Vector4<T>& rAnother)
    {
        x_ -= rAnother.x_;
        y_ -= rAnother.y_;
        z_ -= rAnother.z_;
        w_ -= rAnother.w_;

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
    const S_Vector4<T>& S_Vector4<T>::operator*=(const S_Vector4<T>& rAnother)
    {
        x_ *= rAnother.x_;
        y_ *= rAnother.y_;
        z_ *= rAnother.z_;
        w_ *= rAnother.w_;

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
    const S_Vector4<T>& S_Vector4<T>::operator/=(const S_Vector4<T>& rAnother)
    {
        assert(rAnother.x_ != static_cast<T>(0));
        assert(rAnother.y_ != static_cast<T>(0));
        assert(rAnother.z_ != static_cast<T>(0));
        assert(rAnother.w_ != static_cast<T>(0));

        x_ /= rAnother.x_;
        y_ /= rAnother.y_;
        z_ /= rAnother.z_;
        w_ /= rAnother.w_;

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
    bool S_Vector4<T>::operator==(const S_Vector4<T>& rAnother) const
    {
        return std::abs(x_ - rAnother.x_) < static_cast<T>(s_EPSILON)
            && std::abs(y_ - rAnother.y_) < static_cast<T>(s_EPSILON)
            && std::abs(z_ - rAnother.z_) < static_cast<T>(s_EPSILON)
            && std::abs(w_ - rAnother.w_) < static_cast<T>(s_EPSILON);
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
    bool S_Vector4<T>::operator!=(const S_Vector4<T>& rAnother) const
    {
        return std::abs(x_ - rAnother.x_) > static_cast<T>(s_EPSILON)
            || std::abs(y_ - rAnother.y_) > static_cast<T>(s_EPSILON)
            || std::abs(z_ - rAnother.z_) > static_cast<T>(s_EPSILON)
            || std::abs(w_ - rAnother.w_) > static_cast<T>(s_EPSILON);
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
    const S_Vector4<T> S_Vector4<T>::operator*(T value) const
    {
        return S_Vector4(x_ * value,
                         y_ * value,
                         z_ * value,
                         w_ * value);
    }


    /*************************************************************//**
     *
     *  @brief  T�^�̒l�Ŋe���������Z�����x�N�g�������߂�
     *  @param  T�^�̒l
     *  @return ���Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector4<T> S_Vector4<T>::operator/(T value) const
    {
        assert(value != static_cast<T>(0));

        return S_Vector4(x_ / value,
                         y_ / value,
                         z_ / value,
                         w_ / value);
    }


    /*************************************************************//**
     *
     *  @brief  T�^�̒l���e�����ɏ�Z����
     *  @param  T�^�̒l
     *  @return ��Z��̃x�N�g��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector4<T>& S_Vector4<T>::operator*=(T value)
    {
        x_ *= value;
        y_ *= value;
        z_ *= value;
        w_ *= value;

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
    const S_Vector4<T>& S_Vector4<T>::operator/=(T value)
    {
        assert(value != static_cast<T>(0));

        x_ /= value;
        y_ /= value;
        z_ /= value;
        w_ /= value;

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
    S_Vector4<T>::operator S_Vector2<T>() const
    {
        return xyz_.xy_;
    }


    /*************************************************************//**
     *
     *  @brief  S_Vector3�^�փL���X�g����
     *  @param  �Ȃ�
     *  @return 3D�x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::operator S_Vector3<T>() const
    {
        return xyz_;
    }


    /*************************************************************//**
     *
     *  @brief  string�^�փL���X�g����
     *  @param  �Ȃ�
     *  @return ������ɕϊ������x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::operator std::string() const
    {
        return GetConvertToString();
    }


#pragma endregion


    /* �����I�C���X�^���X�� */
    template struct S_Vector4<float>;
    template struct S_Vector4<double>;

}