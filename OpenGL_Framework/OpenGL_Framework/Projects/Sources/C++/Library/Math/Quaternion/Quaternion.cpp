/* �w�b�_�t�@�C�� */
#include "Quaternion.h"
#include "../Matrix/Matrix3x3.h"
#include "../Matrix/Matrix4x4.h"
#include "../Define/MathDefine.h"


//-------------------------------------------------------------
///
/// @brief �}�X
/// @brief ���w�֘A�̖��O���
///
//-------------------------------------------------------------
namespace Math
{

    /* �v���g�^�C�v�錾 */
    template<typename T>
    static S_Quaternion<T> s_LerpQuaternion(const S_Quaternion<T>& rStartQuaternion,
                                            const S_Quaternion<T>& rEndQuaternion,
                                            T coefficient);


#pragma region �ÓI�����o�ϐ��̏�����


    template<typename T>
    const S_Quaternion<T> S_Quaternion<T>::s_IDENTITY(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));


#pragma endregion


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T>::S_Quaternion() : S_Quaternion(static_cast<T>(0))
    {
    }


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �l
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T>::S_Quaternion(T value) : S_Quaternion(value, value, value, value)
    {
    }


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  T����
     *  @param  X����
     *  @param  Y����
     *  @param  Z����
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T>::S_Quaternion(T t, T x, T y, T z) :

        // T����
        t_(t),

        // X�EY�EZ����
        xyz_(x, y, z)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  T����
     *  @param  X�EY�EZ����
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T>::S_Quaternion(T t, const S_Vector3<T>& rXYZ) :

        // T����
        t_(t),

        // X�EY�EZ����
        xyz_(rXYZ)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T>::~S_Quaternion()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �e���������̒l�ɕύX����
     *  @param  �l
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Quaternion<T>::Fill(T value)
    {
        t_ = value;
        x_ = value;
        y_ = value;
        z_ = value;
    }


    /*************************************************************//**
     *
     *  @brief  �P�ʃN�H�[�^�j�I��������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Quaternion<T>::Identity()
    {
        t_ = static_cast<T>(1);
        xyz_.Zero();
    }


    /*************************************************************//**
     *
     *  @brief  ���K�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Quaternion<T>::Normalize()
    {
        // �������擾
        T length = GetLength();
        assert(length != static_cast<T>(0));

        // ���K��
        t_ /= length;
        xyz_ /= length;
    }


    /*************************************************************//**
     *
     *  @brief  �t�N�H�[�^�j�I�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Quaternion<T>::Invert()
    {
        xyz_.Invert();
    }


    /*************************************************************//**
     *
     *  @brief  �������擾����
     *  @param  �Ȃ�
     *  @return ����
     *
     ****************************************************************/
    template<typename T>
    T S_Quaternion<T>::GetLength() const
    {
        return SquareRoot(GetLengthSquare());
    }


    /*************************************************************//**
     *
     *  @brief  ������2����擾����
     *  @param  �Ȃ�
     *  @return �����̂Q��
     *
     ****************************************************************/
    template<typename T>
    T S_Quaternion<T>::GetLengthSquare() const
    {
        return Square(t_) + Square(x_) + Square(y_) + Square(z_);
    }


    /*************************************************************//**
     *
     *  @brief  ���K�������N�H�[�^�j�I�����擾����
     *  @param  �Ȃ�
     *  @return ���K�������N�H�[�^�j�I��
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::GetNormalize() const
    {
        S_Quaternion normalizeQuaternion(*this);
        normalizeQuaternion.Normalize();

        return normalizeQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  �t�N�H�[�^�j�I�����擾����
     *  @param  �Ȃ�
     *  @return �t�N�H�[�^�j�I��
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::GetInvert() const
    {
        S_Quaternion inverseQuaternion(*this);
        inverseQuaternion.Invert();

        return inverseQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  X������̊p�x���擾����
     *  @param  �Ȃ�
     *  @return �p�x( ���W�A���l )
     *
     ****************************************************************/
    template<typename T>
    T S_Quaternion<T>::GetAngleFromXAxis() const
    {
        T angle = std::atan2(static_cast<T>(2) * (y_ * z_ + t_ * x_),
                             Square(t_) - Square(x_) - Square(y_) + Square(z_));

        return angle;
    }


    /*************************************************************//**
     *
     *  @brief  Y������̊p�x���擾����
     *  @param  �Ȃ�
     *  @return �p�x( ���W�A���l )
     *
     ****************************************************************/
    template<typename T>
    T S_Quaternion<T>::GetAngleFromYAxis() const
    {
        T angle = std::asin(static_cast<T>(-2) * (x_ * z_ - t_ * y_));

        return angle;
    }


    /*************************************************************//**
     *
     *  @brief  Z������̊p�x���擾����
     *  @param  �Ȃ�
     *  @return �p�x( ���W�A���l )
     *
     ****************************************************************/
    template<typename T>
    T S_Quaternion<T>::GetAngleFromZAxis() const
    {
        T angle = std::atan2(static_cast<T>(2) * (x_ * y_ + t_ * z_),
                             Square(t_) + Square(x_) - Square(y_) - Square(z_));

        return angle;
    }


    /*************************************************************//**
     *
     *  @brief  ���Ɗp�x���擾����
     *  @param  �Ȃ�
     *  @return ���Ɗp�x( ���W�A���l )
     *
     ****************************************************************/
    template<typename T>
    std::tuple<S_Vector3<T>, T> S_Quaternion<T>::GetAxisAndAngle() const
    {
        // �p�x�̔����ƃT�C�������߂�
        T halfAngle = static_cast<T>(0), sine = static_cast<T>(0);

        halfAngle = std::acos(t_);

        sine = std::sqrt(Square(x_) + Square(y_) + Square(z_));
        T absoluteSine = std::abs(sine);

        // �T�C�����玲�Ɗp�x��ݒ�
        T angle = static_cast<T>(0);
        S_Vector3<T> axis;

        if (absoluteSine < static_cast<T>(s_EPSILON) || std::abs(absoluteSine - s_PI2) < static_cast<T>(s_EPSILON))
        {
            axis.x_ = static_cast<T>(0);;
            axis.y_ = static_cast<T>(0);
            axis.z_ = static_cast<T>(1);
        }
        else
        {
            angle = halfAngle * static_cast<T>(2);

            axis = xyz_ / sine;
            axis.Normalize();
        }

        return std::make_tuple(axis, angle);
    }


    /*************************************************************//**
     *
     *  @brief  �x�N�g���𕶎���ɕϊ����Ď擾����
     *  @param  �Ȃ�
     *  @return ������ɕϊ������x�N�g��
     *
     ****************************************************************/
    template<typename T>
    std::string S_Quaternion<T>::GetConvertToString() const
    {
        return "(" + std::to_string(t_) + ", " + std::to_string(x_) + ", " + std::to_string(y_) + ", " + std::to_string(z_) + ")";
    }



    /*************************************************************//**
     *
     *  @brief  ���ς����߂�
     *  @param  �Ȃ�
     *  @return ����
     *
     ****************************************************************/
    template<typename T>
    T S_Quaternion<T>::s_DotProduct(const S_Quaternion<T>& rLhs, const S_Quaternion<T>& rRhs)
    {
        return (rLhs.t_ * rRhs.t_)
             + (rLhs.x_ * rRhs.x_)
             + (rLhs.y_ * rRhs.y_)
             + (rLhs.z_ * rRhs.z_);
    }


    /*************************************************************//**
     *
     *  @brief  �C�ӎ������]�N�H�[�^�j�I�����쐬����
     *  @param  ��
     *  @param  �p�x( ���W�A���l )
     *  @return ��]�N�H�[�^�j�I��
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_CreateRotationAxis(const S_Vector3<T>& rAxis, T angle)
    {
        // �p�x�̔����Ƃ��̃T�C�������߂�
        T halfAngle = angle * static_cast<T>(0.5);
        T sine = static_cast<T>(std::sin(static_cast<T>(halfAngle)));

        // ��]�N�H�[�^�j�I�������߂�
        S_Quaternion rotationQuaternion(std::cos(halfAngle),
                                        rAxis.x_ * sine,
                                        rAxis.y_ * sine,
                                        rAxis.z_ * sine);

        rotationQuaternion.Normalize();

        return rotationQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  3���̉�]�𔽉f������]�N�H�[�^�j�I�����쐬����
     *  @param  �s�b�`( X���̊p�x�E���W�A���l )
     *  @param  ���[( Y���̊p�x�E���W�A���l )
     *  @param  ���[��( Z���̊p�x�E���W�A���l )
     *  @return ��]�N�H�[�^�j�I��
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_CreateRotationPitchYawRoll(T pitch,
        T yaw,
        T roll)
    {
        // �e�p�x�𒲐�
        pitch = AdjustAngleFrom0ToPI2(pitch);
        yaw = AdjustAngleFrom0ToPI2(yaw);
        roll = AdjustAngleFrom0ToPI2(roll);

        // ��]�N�H�[�^�j�I��
        S_Quaternion rotationQuaternion;

        // �e���̃T�C���ƃR�T�C�������߂�
        T sineX = std::sin(pitch * static_cast<T>(0.5));
        T cosineX = std::cos(pitch * static_cast<T>(0.5));

        T sineY = std::sin(yaw * static_cast<T>(0.5));
        T cosineY = std::cos(yaw * static_cast<T>(0.5));

        T sineZ = std::sin(roll * static_cast<T>(0.5));
        T cosineZ = std::cos(roll * static_cast<T>(0.5));

        // ��]�N�H�[�^�j�I�������߂�
        rotationQuaternion.t_ = (cosineY * cosineZ * cosineX) - (sineY * sineZ   * sineX);
        rotationQuaternion.x_ = (sineY *   sineZ * cosineX) + (cosineY * cosineZ * sineX);
        rotationQuaternion.y_ = (sineY * cosineZ * cosineX) + (cosineY * sineZ   * sineX);
        rotationQuaternion.z_ = (cosineY *   sineZ * cosineX) - (sineY * cosineZ * sineX);

        return rotationQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  3���̉�]�𔽉f������]�N�H�[�^�j�I�����쐬����
     *  @param  ��]��
     *  @return ��]�N�H�[�^�j�I��
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_CreateRotationPitchYawRoll(const S_Vector3<T>& rRotation)
    {
        return s_CreateRotationPitchYawRoll(rRotation.x_, rRotation.y_, rRotation.z_);
    }


    /*************************************************************//**
     *
     *  @brief  �C�ӂ̌����֌������߂̉�]�N�H�[�^�j�I�����쐬����
     *  @param  ����
     *  @param  �����
     *  @return ��]�N�H�[�^�j�I��
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_CreateLookRotation(const S_Vector3<T>& rDirection,
        const S_Vector3<T>& rUpVector)
    {
        // 3 * 3�s��̃r���[�s����쐬���A�N�H�[�^�j�I���ɕϊ�
        S_Matrix3x3<T> viewMatrix;
        viewMatrix = S_Matrix3x3<T>::s_CreateLookAt(S_Vector3<T>::s_ZERO, rDirection, rUpVector);

        S_Quaternion rotationQuaternion = s_ConvertMatrix3x3ToQuaternion(viewMatrix);
        rotationQuaternion.Normalize();

        return rotationQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  ������������։�]�������]�N�H�[�^�j�I�����쐬����
     *  @param  ��]�O�̌���
     *  @param  ��]��̌���
     *  @return ��]�N�H�[�^�j�I��
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_CreateFromToRotation(const S_Vector3<T>& rFromDirection,
        const S_Vector3<T>& rToDirection)
    {
        // �p�x�Ǝ������߂�
        T angle = S_Vector3<T>::s_AngleBetweenVectors(rFromDirection, rToDirection);
        S_Vector3<T> axis = S_Vector3<T>::s_CrossProduct(rFromDirection, rToDirection);

        // ��]�N�H�[�^�j�I�����쐬
        S_Quaternion rotationQuaternion = s_CreateRotationAxis(axis, angle);

        return rotationQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  3 * 3�̍s�񂩂�N�H�[�^�j�I���֕ϊ����A�擾����
     *  @param  3 * 3�̍s��
     *  @return �N�H�[�^�j�I��
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_ConvertMatrix3x3ToQuaternion(const S_Matrix3x3<T>& rMatrix)
    {
        // �덷�͈͂�\���ɏ��̒l
        const T EPSILON = static_cast<T>(0.000001);

        // �ϊ���̃N�H�[�^�j�I��
        S_Quaternion<T> convertionQuaternion;

        // �]�u�s����擾
        S_Matrix3x3<T> transposeMatrix(rMatrix.GetTranspose());

        // ( 4x4�s��̏ꍇ�� )�Ίp���̍��v
        T diagonalSum = transposeMatrix.a11_
            + transposeMatrix.a22_
            + transposeMatrix.a33_
            + static_cast<T>(1);

        // �Ίp���̃X�P�[��
        T diagonalScale = static_cast<T>(0);

        // �Ίp���̍��v��0���߂̏ꍇ
        if (diagonalSum > EPSILON)
        {
            // �Ίp���̃X�P�[�������߂�
            diagonalScale = SquareRoot(diagonalSum) * static_cast<T>(2);

            // �e���������߂�
            convertionQuaternion.t_ = static_cast<T>(0.25) * diagonalScale;
            convertionQuaternion.x_ = (transposeMatrix.a32_ - transposeMatrix.a23_) / diagonalScale;
            convertionQuaternion.y_ = (transposeMatrix.a13_ - transposeMatrix.a31_) / diagonalScale;
            convertionQuaternion.z_ = (transposeMatrix.a21_ - transposeMatrix.a12_) / diagonalScale;
        }
        else
        {
            // �Ίp���̍ő�l�ɉ����Đ��������߂�
            if (transposeMatrix.a11_ > transposeMatrix.a22_ && transposeMatrix.a11_ > transposeMatrix.a33_)
            {
                // �Ίp���̃X�P�[�������߂�
                diagonalScale = SquareRoot(static_cast<T>(1) + transposeMatrix.a11_ - transposeMatrix.a22_ - transposeMatrix.a33_) * static_cast<T>(2);

                // �e���������߂�
                convertionQuaternion.t_ = (transposeMatrix.a32_ - transposeMatrix.a23_) / diagonalScale;
                convertionQuaternion.x_ = static_cast<T>(0.25) * diagonalScale;
                convertionQuaternion.y_ = (transposeMatrix.a21_ - transposeMatrix.a12_) / diagonalScale;
                convertionQuaternion.z_ = (transposeMatrix.a13_ - transposeMatrix.a31_) / diagonalScale;
            }
            else if (transposeMatrix.a22_ > transposeMatrix.a33_)
            {
                // �Ίp���̃X�P�[�������߂�
                diagonalScale = SquareRoot(static_cast<T>(1) + transposeMatrix.a22_ - transposeMatrix.a11_ - transposeMatrix.a33_) * static_cast<T>(2);

                // �e���������߂�
                convertionQuaternion.t_ = (transposeMatrix.a13_ - transposeMatrix.a31_) / diagonalScale;
                convertionQuaternion.x_ = (transposeMatrix.a21_ - transposeMatrix.a12_) / diagonalScale;
                convertionQuaternion.y_ = static_cast<T>(0.25) * diagonalScale;
                convertionQuaternion.z_ = (transposeMatrix.a32_ - transposeMatrix.a23_) / diagonalScale;
            }
            else
            {
                // �Ίp���̃X�P�[�������߂�
                diagonalScale = SquareRoot(static_cast<T>(1) + transposeMatrix.a33_ - transposeMatrix.a11_ - transposeMatrix.a22_) * static_cast<T>(2);

                // �e���������߂�
                convertionQuaternion.t_ = (transposeMatrix.a21_ - transposeMatrix.a12_) / diagonalScale;
                convertionQuaternion.x_ = (transposeMatrix.a13_ - transposeMatrix.a31_) / diagonalScale;
                convertionQuaternion.y_ = (transposeMatrix.a32_ - transposeMatrix.a23_) / diagonalScale;
                convertionQuaternion.z_ = static_cast<T>(0.25) * diagonalScale;
            }
        }

        return convertionQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  4 * 4�̍s�񂩂�N�H�[�^�j�I���֕ϊ����A�擾����
     *  @param  4 * 4�̍s��
     *  @return �N�H�[�^�j�I��
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_ConvertMatrix4x4ToQuaternion(const S_Matrix4x4<T>& rMatrix)
    {
        return s_ConvertMatrix3x3ToQuaternion(S_Matrix3x3<T>::s_ConvertMatrix4x4ToMatrix3x3(rMatrix));
    }


    /*************************************************************//**
     *
     *  @brief  ���`��Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return ��̓_����`��Ԃ����_
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_Lerp(const S_Quaternion<T>& rStart,
                                            const S_Quaternion<T>& rEnd,
                                            T coefficient)
    {
        S_Quaternion lerpPoint;

        if (s_DotProduct(rStart, rEnd) > static_cast<T>(0))
        {
            lerpPoint = s_LerpQuaternion(rStart, rEnd, coefficient);
        }
        else
        {
            lerpPoint = s_LerpQuaternion(rStart, rEnd * static_cast<T>(-1), coefficient);
        }

        return lerpPoint;
    }


    /*************************************************************//**
     *
     *  @brief  ���ʐ��`��Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return ��̂����ʐ��`��Ԃ����_
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_Slerp(const S_Quaternion<T>& rStart,
                                             const S_Quaternion<T>& rEnd,
                                             T coefficient)
    {
        // ���ʐ��`��Ԍ�̃N�H�[�^�j�I��
        S_Quaternion slerpQuaternion;

        // ����
        T dotProduct = s_DotProduct(rStart, rEnd);

        // ���ς̂������l
        const T DOT_THRESHOLD = static_cast<T>(0.9995);

        // �������l�𒴉߂��Ă����ꍇ
        if (dotProduct > DOT_THRESHOLD)
        {
            // ������̃N�H�[�^�j�I���Ƃ̍�
            S_Quaternion difference(rEnd - rStart);

            // ���ɕ�ԌW�����|���A����Ɏ��g�𑫂����l�����߂�
            difference *= coefficient;
            slerpQuaternion = rStart + difference;

            // �N�H�[�^�j�I���𐳋K��
            slerpQuaternion.Normalize();
        }
        else
        {
            // ���ς��N�����v���A�p�x�����߂�
            Clamp(dotProduct, static_cast<T>(-1), static_cast<T>(1));
            T angle = std::acos(dotProduct);

            // �p�x�ɕ�ԌW�����|����
            T interpolationAngle = angle * coefficient;

            // ���g�ɓ��ς��������l�����߁A������̃N�H�[�^�j�I���Ƃ̍��������߂�
            S_Quaternion dotQuaternion(rStart * dotProduct);
            S_Quaternion difference(rEnd - dotQuaternion);

            // �����𐳋K��
            difference.Normalize();

            // ���g�ƕ�ԌW�����|�����p�x�̃R�T�C�����|�����N�H�[�^�j�I��
            S_Quaternion cosineQuaternion(rStart * ::cos(interpolationAngle));

            // �����ƕ�ԌW�����������p�x�̃T�C�����|�����N�H�[�^�j�I��
            S_Quaternion sineQuaternion(difference * ::sin(interpolationAngle));

            // 2�̃N�H�[�^�j�I�������킹��
            slerpQuaternion = cosineQuaternion + sineQuaternion;
        }

        return slerpQuaternion;
    }


#pragma region S_Quaternion�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


    /*************************************************************//**
     *
     *  @brief  ������̃N�H�[�^�j�I�������Z�����N�H�[�^�j�I�������߂�
     *  @param  ������̃N�H�[�^�j�I��
     *  @return ���Z�����N�H�[�^�j�I��
     *
     ****************************************************************/
    template<typename T>
    const S_Quaternion<T> S_Quaternion<T>::operator+(const S_Quaternion<T>& rAnother) const
    {
        S_Quaternion tempQuaternion;

        tempQuaternion.t_ = t_ + rAnother.t_;
        tempQuaternion.x_ = x_ + rAnother.x_;
        tempQuaternion.y_ = y_ + rAnother.y_;
        tempQuaternion.z_ = z_ + rAnother.z_;

        return tempQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  ������̃N�H�[�^�j�I�������Z����
     *  @param  ������̃N�H�[�^�j�I��
     *  @return ���Z�����N�H�[�^�j�I��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Quaternion<T>& S_Quaternion<T>::operator+=(const S_Quaternion<T>& rAnother)
    {
        t_ += rAnother.t_;
        x_ += rAnother.x_;
        y_ += rAnother.y_;
        z_ += rAnother.z_;

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃N�H�[�^�j�I�������Z�����N�H�[�^�j�I�������߂�
     *  @param  ������̃N�H�[�^�j�I��
     *  @return ���Z�����N�H�[�^�j�I��
     *
     ****************************************************************/
    template<typename T>
    const S_Quaternion<T> S_Quaternion<T>::operator-(const S_Quaternion<T>& rAnother) const
    {
        S_Quaternion tempQuaternion;

        tempQuaternion.t_ = t_ - rAnother.t_;
        tempQuaternion.x_ = x_ - rAnother.x_;
        tempQuaternion.y_ = y_ - rAnother.y_;
        tempQuaternion.z_ = z_ - rAnother.z_;

        return tempQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  ������̃N�H�[�^�j�I�������Z����
     *  @param  ������̃N�H�[�^�j�I��
     *  @return ���Z�����N�H�[�^�j�I��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Quaternion<T>& S_Quaternion<T>::operator-=(const S_Quaternion<T>& rAnother)
    {
        t_ -= rAnother.t_;
        x_ -= rAnother.x_;
        y_ -= rAnother.y_;
        z_ -= rAnother.z_;

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃N�H�[�^�j�I������Z�����N�H�[�^�j�I�������߂�
     *  @param  ������̃N�H�[�^�j�I��
     *  @return ��Z�����N�H�[�^�j�I��
     *
     ****************************************************************/
    template<typename T>
    const S_Quaternion<T> S_Quaternion<T>::operator*(const S_Quaternion<T>& rAnother) const
    {
        S_Quaternion tempQuaternion;

        // ���������߂�
        tempQuaternion.t_ = (t_ * rAnother.t_) - S_Vector3<T>::s_DotProduct(xyz_, rAnother.xyz_);

        // ���������߂�
        tempQuaternion.xyz_ = (t_ * rAnother.xyz_)
                            + (rAnother.t_ * xyz_)
                            + S_Vector3<T>::s_CrossProduct(xyz_, rAnother.xyz_);

        return tempQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  ������̃N�H�[�^�j�I������Z����
     *  @param  ������̃N�H�[�^�j�I��
     *  @return ��Z�����N�H�[�^�j�I��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Quaternion<T>& S_Quaternion<T>::operator*=(const S_Quaternion<T>& rAnother)
    {
        S_Quaternion tempQuaternion;

        // ���������߂�
        tempQuaternion.t_ = (t_ * rAnother.t_) - S_Vector3<T>::s_DotProduct(xyz_, rAnother.xyz_);

        // ���������߂�
        tempQuaternion.xyz_ = (t_ * rAnother.xyz_)
            + (rAnother.t_ * xyz_)
            + S_Vector3<T>::s_CrossProduct(xyz_, rAnother.xyz_);

        (*this) = tempQuaternion;

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃N�H�[�^�j�I���Ɣ�r����
     *  @param  ������̃N�H�[�^�j�I��
     *  @return �����x�N�g���̏ꍇ�Ftrue
     *  @return �Ⴄ�x�N�g���̏ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool S_Quaternion<T>::operator==(const S_Quaternion<T>& rAnother) const
    {
        return std::abs(t_ - rAnother.t_) < static_cast<T>(s_EPSILON)
            && std::abs(x_ - rAnother.x_) < static_cast<T>(s_EPSILON)
            && std::abs(y_ - rAnother.y_) < static_cast<T>(s_EPSILON)
            && std::abs(z_ - rAnother.z_) < static_cast<T>(s_EPSILON);
    }


    /*************************************************************//**
     *
     *  @brief  ������̃N�H�[�^�j�I���Ɣ�r����
     *  @param  ������̃N�H�[�^�j�I��
     *  @return �Ⴄ�x�N�g���̏ꍇ�Ftrue
     *  @return �����x�N�g���̏ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool S_Quaternion<T>::operator!=(const S_Quaternion<T>& rAnother) const
    {
        return std::abs(t_ - rAnother.t_) > static_cast<T>(s_EPSILON)
            || std::abs(x_ - rAnother.x_) > static_cast<T>(s_EPSILON)
            || std::abs(y_ - rAnother.y_) > static_cast<T>(s_EPSILON)
            || std::abs(z_ - rAnother.z_) > static_cast<T>(s_EPSILON);
    }



#pragma endregion


#pragma region T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


    /*************************************************************//**
     *
     *  @brief  T�^�̒l����Z�����N�H�[�^�j�I�������߂�
     *  @param  T�^�̒l
     *  @return ��Z�����N�H�[�^�j�I��
     *
     ****************************************************************/
    template<typename T>
    const S_Quaternion<T> S_Quaternion<T>::operator*(T value) const
    {
        return S_Quaternion(t_ * value, x_ * value, y_ * value, z_ * value);
    }


    /*************************************************************//**
     *
     *  @brief  T�^�̒l���e�����ɏ�Z����
     *  @param  T�^�̒l
     *  @return ��Z��̃N�H�[�^�j�I��
     *
     ****************************************************************/
    template<typename T>
    const S_Quaternion<T>& S_Quaternion<T>::operator*=(T value)
    {
        t_ *= value;
        x_ *= value;
        y_ *= value;
        z_ *= value;

        return (*this);
    }


#pragma endregion


#pragma region �L���X�g���Z�q�̃I�[�o�[���[�h


    /*************************************************************//**
     *
     *  @brief  S_Vector3�^�փL���X�g����
     *  @param  �Ȃ�
     *  @return 3D�x�N�g��
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T>::operator S_Vector3<T>() const
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
    S_Quaternion<T>::operator std::string() const
    {
        return GetConvertToString();
    }


#pragma endregion



    /* �����I�C���X�^���X�� */
    template struct S_Quaternion<float>;
    template struct S_Quaternion<double>;


    /*************************************************************//**
     *
     *  @brief  �N�H�[�^�j�I���̐��`��Ԃ��s��
     *  @param  �J�n���̃N�H�[�^�j�I��
     *  @param  �I�����̃N�H�[�^�j�I��
     *  @param  ��ԌW��
     *  @return ���`��Ԃ����N�H�[�^�j�I��
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> s_LerpQuaternion(const S_Quaternion<T>& rStartQuaternion,
                                     const S_Quaternion<T>& rEndQuaternion,
                                     T coefficient)
    {
        S_Quaternion<T> lerpPoint;

        lerpPoint.t_ = (rEndQuaternion.t_ - rStartQuaternion.t_) * coefficient + rStartQuaternion.t_;
        lerpPoint.x_ = (rEndQuaternion.x_ - rStartQuaternion.x_) * coefficient + rStartQuaternion.x_;
        lerpPoint.y_ = (rEndQuaternion.y_ - rStartQuaternion.y_) * coefficient + rStartQuaternion.y_;
        lerpPoint.z_ = (rEndQuaternion.z_ - rStartQuaternion.z_) * coefficient + rStartQuaternion.z_;

        return lerpPoint;
    }

}