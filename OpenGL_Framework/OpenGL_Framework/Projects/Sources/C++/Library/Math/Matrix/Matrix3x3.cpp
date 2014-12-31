/* �w�b�_�t�@�C�� */
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "../Vector/Vector3.h"
#include "../Quaternion/Quaternion.h"
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
    static T s_GetDeterminant(const S_Matrix3x3<T>& rMatrix);


#pragma region �ÓI�����o�ϐ��̏�����


    template<typename T>
    const S_Matrix3x3<T> S_Matrix3x3<T>::s_ZERO(static_cast<T>(0));


    template<typename T>
    const S_Matrix3x3<T> S_Matrix3x3<T>::s_IDENTITY;


#pragma endregion


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T>::S_Matrix3x3() :

        // 9�̗v�f
        a11_(static_cast<T>(1)),
        a12_(static_cast<T>(0)),
        a13_(static_cast<T>(0)),

        a21_(static_cast<T>(0)),
        a22_(static_cast<T>(1)),
        a23_(static_cast<T>(0)),

        a31_(static_cast<T>(0)),
        a32_(static_cast<T>(0)),
        a33_(static_cast<T>(1))

    {
    }


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^( �e�v�f���w�肵��1�̒l�ŏ����� )
     *  @param  �l
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T>::S_Matrix3x3(T value) : S_Matrix3x3(value, value, value,
                                                       value, value, value,
                                                       value, value, value)
    {
    }


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^( �w�肵���l�Ŋe�v�f�̏����� )
     *  @param  �v�f1
     *  @param  �v�f2
     *  @param  �v�f3
     *  @param  �v�f4
     *  @param  �v�f5
     *  @param  �v�f6
     *  @param  �v�f7
     *  @param  �v�f8
     *  @param  �v�f9
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T>::S_Matrix3x3(T a11, T a12, T a13,
                                T a21, T a22, T a23,
                                T a31, T a32, T a33) :

        // 9�̗v�f
        a11_(a11),
        a12_(a12),
        a13_(a13),

        a21_(a21),
        a22_(a22),
        a23_(a23),

        a31_(a31),
        a32_(a32),
        a33_(a33)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^( �w�肵���z��ŗv�f�̏����� )
     *  @param  �v�f��9�̔z��
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T>::S_Matrix3x3(const T a[s_ELEMENT_NUMBER])
    {
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i) a_[i] = a[i];
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T>::~S_Matrix3x3()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �[���s�񉻂���
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix3x3<T>::Zero()
    {
        for (auto& a : a_) a = static_cast<T>(0);
    }


    /*************************************************************//**
     *
     *  @brief  �e�v�f�����̒l�ɕύX����
     *  @param  �l
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix3x3<T>::Fill(T value)
    {
        for (auto& a : a_) a = value;
    }


    /*************************************************************//**
     *
     *  @brief  �P�ʍs�񉻂���
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix3x3<T>::Identity()
    {
        a11_ = static_cast<T>(1);
        a12_ = static_cast<T>(0);
        a13_ = static_cast<T>(0);

        a21_ = static_cast<T>(0);
        a22_ = static_cast<T>(1);
        a23_ = static_cast<T>(0);

        a31_ = static_cast<T>(0);
        a32_ = static_cast<T>(0);
        a33_ = static_cast<T>(1);
    }


    /*************************************************************//**
     *
     *  @brief  �]�u�s�񉻂���
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix3x3<T>::Transpose()
    {
        std::swap(a12_, a21_);
        std::swap(a13_, a31_);
        std::swap(a23_, a32_);
    }


    /*************************************************************//**
     *
     *  @brief  �t�s�񉻂���
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix3x3<T>::Invert()
    {
        // �s�񎮂��擾
        T determinant = s_GetDeterminant(*this);

        if (determinant == static_cast<T>(0)) return;

        // �t�s��
        S_Matrix3x3 inverseMatrix;

        // �s�񎮂̋t��
        T reciprocalDeterminant = static_cast<T>(1) / determinant;

        // �t�s������߂�
        inverseMatrix.a11_ = (a22_ * a33_ - a23_ * a32_) * reciprocalDeterminant;
        inverseMatrix.a12_ = (a13_ * a32_ - a12_ * a33_) * reciprocalDeterminant;
        inverseMatrix.a13_ = (a12_ * a23_ - a13_ * a22_) * reciprocalDeterminant;
        inverseMatrix.a21_ = (a23_ * a31_ - a21_ * a33_) * reciprocalDeterminant;
        inverseMatrix.a22_ = (a11_ * a33_ - a13_ * a31_) * reciprocalDeterminant;
        inverseMatrix.a23_ = (a13_ * a21_ - a11_ * a23_) * reciprocalDeterminant;
        inverseMatrix.a31_ = (a21_ * a32_ - a22_ * a31_) * reciprocalDeterminant;
        inverseMatrix.a32_ = (a12_ * a31_ - a11_ * a32_) * reciprocalDeterminant;
        inverseMatrix.a33_ = (a11_ * a22_ - a12_ * a21_) * reciprocalDeterminant;

        // �t�s�����
        (*this) = inverseMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  �]�u�s����擾����
     *  @param  �Ȃ�
     *  @return �]�u�s��
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::GetTranspose() const
    {
        S_Matrix3x3 transposeMatrix(*this);
        transposeMatrix.Transpose();

        return transposeMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  �t�s����擾����
     *  @param  �Ȃ�
     *  @return �t�s��
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::GetInvert() const
    {
        S_Matrix3x3 inverseMatrix(*this);
        inverseMatrix.Invert();

        return inverseMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  �s���擾����
     *  @param  �Y����
     *  @return �s
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Matrix3x3<T>::GetRow(int32_t index) const
    {
        assert(index >= 0 && index < 3);
        return S_Vector3<T>(a_[index], a_[index + 3], a_[index + 6]);
    }


    /*************************************************************//**
     *
     *  @brief  ����擾����
     *  @param  �Y����
     *  @return ��
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Matrix3x3<T>::GetColumn(int32_t index) const
    {
        assert(index >= 0 && index < 3);

        index *= 3;
        return S_Vector3<T>(a_[index], a_[index + 1], a_[index + 2]);
    }


    /*************************************************************//**
     *
     *  @brief  �s��𕶎���ɕϊ����Ď擾����
     *  @param  �Ȃ�
     *  @return ������ɕϊ������s��
     *
     ****************************************************************/
    template<typename T>
    std::string S_Matrix3x3<T>::GetConvertToString() const
    {
        return "|" + std::to_string(a11_) + ", " + std::to_string(a21_) + ", " + std::to_string(a31_) + "|\n"
             + "|" + std::to_string(a12_) + ", " + std::to_string(a22_) + ", " + std::to_string(a32_) + "|\n"
             + "|" + std::to_string(a13_) + ", " + std::to_string(a23_) + ", " + std::to_string(a33_) + "|";
    }


    /*************************************************************//**
     *
     *  @brief  �s��ݒ肷��
     *  @param  ��
     *  @param  �Y����
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix3x3<T>::SetRow(const S_Vector3<T>& rRow, int32_t index)
    {
        assert(index >= 0 && index < 3);

        for (int32_t i = 0; i < 3; ++i) a_[index + i * 3] = rRow.a_[i];
    }


    /*************************************************************//**
     *
     *  @brief  ���ݒ肷��
     *  @param  ��
     *  @param  �Y����
     *  @return �Ȃ�
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix3x3<T>::SetColumn(const S_Vector3<T>& rColumn, int32_t index)
    {
        assert(index >= 0 && index < 3);

        for (int32_t i = 0; i < 3; ++i) a_[index + i] = rColumn.a_[i];
    }


    /*************************************************************//**
     *
     *  @brief  ��]�s����쐬����
     *  @param  �p�x( ���W�A���l )
     *  @return ��]�s��
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotation(T angle)
    {
        // ��]�s��
        S_Matrix3x3 rotationMatrix;

        // �T�C���ƃR�T�C�������߂�
        T sine = std::sin(angle);
        T cosine = std::cos(angle);

        // ��]�s������߂�
        rotationMatrix.a11_ = cosine;
        rotationMatrix.a12_ = sine;
        rotationMatrix.a21_ = sine * static_cast<T>(-1);
        rotationMatrix.a22_ = cosine;

        return rotationMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  X�������]�s����쐬����
     *  @param  �p�x( ���W�A���l )
     *  @return ��]�s��
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotationX(T angle)
    {
        // ��]�s��
        S_Matrix3x3 rotationMatrix;

        // �T�C���ƃR�T�C�������߂�
        T sine = std::sin(angle);
        T cosine = std::cos(angle);

        // ��]�s������߂�
        rotationMatrix.a22_ = cosine;
        rotationMatrix.a23_ = sine;
        rotationMatrix.a32_ = sine * static_cast<T>(-1);
        rotationMatrix.a33_ = cosine;;

        return rotationMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  Y�������]�s����쐬����
     *  @param  �p�x( ���W�A���l )
     *  @return ��]�s��
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotationY(T angle)
    {
        // ��]�s��
        S_Matrix3x3 rotationMatrix;

        // �T�C���ƃR�T�C�������߂�
        T sine = std::sin(angle);
        T cosine = std::cos(angle);

        // ��]�s������߂�
        rotationMatrix.a11_ = cosine;
        rotationMatrix.a13_ = sine * static_cast<T>(-1);
        rotationMatrix.a31_ = sine;
        rotationMatrix.a33_ = cosine;

        return rotationMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  Z�������]�s����쐬����
     *  @param  �p�x( ���W�A���l )
     *  @return ��]�s��
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotationZ(T angle)
    {
        // ��]�s��
        S_Matrix3x3 rotationMatrix;

        // �T�C���ƃR�T�C�������߂�
        T sine = std::sin(angle);
        T cosine = std::cos(angle);

        // ��]�s������߂�
        rotationMatrix.a11_ = cosine;
        rotationMatrix.a12_ = sine;
        rotationMatrix.a21_ = sine * static_cast<T>(-1);
        rotationMatrix.a22_ = cosine;

        return rotationMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  �C�ӎ������]�s����쐬����
     *  @param  �p�x( ���W�A���l )
     *  @return ��]�s��
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotationAxis(const S_Vector3<T>& rAxis, T angle)
    {
        // ��]�s��
        S_Matrix3x3 rotationMatrix;

        // �T�C���ƃR�T�C�������߂�
        T sine = std::sin(angle);
        T cosine = std::cos(angle);

        // 1 - cosine �̒l�����߂�
        T oneMinusCosine = static_cast<T>(1) - cosine;

        // ���̊e�l�̃T�C�������߂�
        T axisXsine = rAxis.x_ * sine;
        T axisYsine = rAxis.y_ * sine;
        T axisZsine = rAxis.z_ * sine;

        // ���̐����� 1 - cosine ���������l�����߂�
        T oneMinusCosineX = rAxis.x_ * oneMinusCosine;
        T oneMinusCosineY = rAxis.y_ * oneMinusCosine;
        T oneMinusCosineZ = rAxis.z_ * oneMinusCosine;

        // ��]�s������߂�
        rotationMatrix.a11_ = (rAxis.x_ * oneMinusCosineX) + cosine;
        rotationMatrix.a21_ = (rAxis.x_ * oneMinusCosineY) - axisZsine;
        rotationMatrix.a31_ = (rAxis.x_ * oneMinusCosineZ) + axisYsine;

        rotationMatrix.a12_ = (rAxis.y_ * oneMinusCosineX) + axisZsine;
        rotationMatrix.a22_ = (rAxis.y_ * oneMinusCosineY) + cosine;
        rotationMatrix.a32_ = (rAxis.y_ * oneMinusCosineZ) - axisXsine;

        rotationMatrix.a13_ = (rAxis.z_ * oneMinusCosineX) - axisYsine;
        rotationMatrix.a23_ = (rAxis.z_ * oneMinusCosineY) + axisXsine;
        rotationMatrix.a33_ = (rAxis.z_ * oneMinusCosineZ) + cosine;

        return rotationMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  �g�k�s����쐬����
     *  @param  X�����̊g�嗦
     *  @param  Y�����̊g�嗦
     *  @return �g�k�s��
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateScaling(T rateX, T rateY)
    {
        S_Matrix3x3 scalingMatrix;

        scalingMatrix.a11_ = rateX;
        scalingMatrix.a22_ = rateY;

        return scalingMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  ���s�ړ��s����쐬����
     *  @param  X�����̈ړ���
     *  @param  Y�����̈ړ���
     *  @return ���s�ړ��s��
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateTranslation(T movementX, T movementY)
    {
        S_Matrix3x3 toranslationMatrix;

        toranslationMatrix.a31_ = movementX;
        toranslationMatrix.a32_ = movementY;

        return toranslationMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  4 * 4�̍s���3 * 3�̍s��ɕϊ����A�擾����
     *  @param  4 * 4�̍s��
     *  @return 3 * 3�̍s��
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_ConvertMatrix4x4ToMatrix3x3(const S_Matrix4x4<T>& rMatrix4)
    {
        // �ϊ���̍s��
        S_Matrix3x3 convertedMatrix;

        // 4 * 4�s���3 * 3�ɕϊ�
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i)
        {
            size_t shiftIndex = i / 3;
            convertedMatrix.a_[i] = rMatrix4.a_[i + shiftIndex];
        }

        return convertedMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  �N�H�[�^�j�I����3 * 3�̍s��ɕϊ����A�擾����
     *  @param  �N�H�[�^�j�I��
     *  @return 3 * 3�s��
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_ConvertQuaternionToMatrix3x3(const S_Quaternion<T>& rQuaternion)
    {
        // �ϊ���̍s��
        S_Matrix3x3 convertionMatrix;

        // �e�����̊|�����킹���l�����߂�
        T xx = Square(rQuaternion.x_);
        T xy = rQuaternion.x_ * rQuaternion.y_;
        T xz = rQuaternion.x_ * rQuaternion.z_;
        T xt = rQuaternion.x_ * rQuaternion.t_;

        T yy = Square(rQuaternion.y_);
        T yz = rQuaternion.y_ * rQuaternion.z_;
        T yt = rQuaternion.y_ * rQuaternion.t_;

        T zz = Square(rQuaternion.z_);
        T zt = rQuaternion.z_ * rQuaternion.t_;

        // �N�H�[�^�j�I����3 * 3�̍s��֕ϊ�
        convertionMatrix.a11_ = static_cast<T>(1) - static_cast<T>(2) * (yy + zz);
        convertionMatrix.a12_ = static_cast<T>(2) * (xy + zt);
        convertionMatrix.a13_ = static_cast<T>(2) * (xz - yt);

        convertionMatrix.a21_ = static_cast<T>(2) * (xy - zt);
        convertionMatrix.a22_ = static_cast<T>(1) - static_cast<T>(2) * (xx + zz);
        convertionMatrix.a23_ = static_cast<T>(2) * (yt + xt);

        convertionMatrix.a31_ = static_cast<T>(2) * (xz + yt);
        convertionMatrix.a32_ = static_cast<T>(2) * (yz - xt);
        convertionMatrix.a33_ = static_cast<T>(1) - static_cast<T>(2) * (xx + yy);

        return convertionMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  �@���s����쐬����
     *  @param  4 * 4�̍s��
     *  @return �@���s��
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateNormal(const S_Matrix4x4<T>& rMatrix)
    {
        S_Matrix3x3 normalMatrix(s_ConvertMatrix4x4ToMatrix3x3(rMatrix));

        normalMatrix.Invert();
        normalMatrix.Transpose();

        return normalMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  �r���[�s����쐬����
     *  @param  ���_
     *  @param  �����_
     *  @param  �����
     *  @return �@���s��
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateLookAt(const S_Vector3<T>& rEyePoint,
                                                  const S_Vector3<T>& rTargetPoint,
                                                  const S_Vector3<T>& rUpVector)
    {
        // �r���[�s��
        S_Matrix3x3 viewMatrix;

        // Z�������߂�
        S_Vector3<T> zAxis = rTargetPoint - rEyePoint;
        zAxis.Normalize();

        // X�������߂�
        S_Vector3<T> xAxis = S_Vector3<T>::s_CrossProduct(zAxis, rUpVector);
        xAxis.Normalize();

        // Y�������߂�
        S_Vector3<T> yAxis = S_Vector3<T>::s_CrossProduct(xAxis, zAxis);
        yAxis.Normalize();

        // ���_�𔽓]�����x�N�g��
        S_Vector3<T> inversionEyeVector(rEyePoint.GetInvert());

        // Z���𔽓]����
        zAxis.Invert();

        // �r���[�s������߂�
        viewMatrix.a11_ = xAxis.x_;
        viewMatrix.a21_ = xAxis.y_;
        viewMatrix.a31_ = xAxis.z_;

        viewMatrix.a12_ = yAxis.x_;
        viewMatrix.a22_ = yAxis.y_;
        viewMatrix.a32_ = yAxis.z_;

        viewMatrix.a13_ = zAxis.x_;
        viewMatrix.a23_ = zAxis.y_;
        viewMatrix.a33_ = zAxis.z_;

        return viewMatrix;
    }


#pragma region S_Matrix3x3�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


    /*************************************************************//**
     *
     *  @brief  ������̍s������Z�����s������߂�
     *  @param  ������̍s��
     *  @return ���Z�����s��
     *
     ****************************************************************/
    template<typename T>
    const S_Matrix3x3<T> S_Matrix3x3<T>::operator+(const S_Matrix3x3<T>& rAnother) const
    {
        S_Matrix3x3 tempMatrix;
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i) tempMatrix.a_[i] = a_[i] + rAnother.a_[i];

        return tempMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  ������̍s��Ō��Z�����s������߂�
     *  @param  ������̍s��
     *  @return ���Z�����s��
     *
     ****************************************************************/
    template<typename T>
    const S_Matrix3x3<T> S_Matrix3x3<T>::operator-(const S_Matrix3x3<T>& rAnother) const
    {
        S_Matrix3x3 tempMatrix;
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i) tempMatrix.a_[i] = a_[i] - rAnother.a_[i];

        return tempMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  ������̍s�����Z�����s������߂�
     *  @param  ������̍s��
     *  @return ��Z�����s��
     *
     ****************************************************************/
    template<typename T>
    const S_Matrix3x3<T> S_Matrix3x3<T>::operator*(const S_Matrix3x3<T>& rAnother) const
    {
        // ���̍s��
        S_Matrix3x3 tempMatrix;

        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i)
        {
            // �e�s��̓Y���������߂�
            size_t index = i % 3;
            size_t anotherIndex = (i / 3) * 3;

            // �s�񓯎m�̏�Z
            tempMatrix.a_[i] = a_[index] * rAnother.a_[anotherIndex]
                             + a_[index + 3] * rAnother.a_[anotherIndex + 1]
                             + a_[index + 6] * rAnother.a_[anotherIndex + 2];
        }

        return tempMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  ������̍s������Z����
     *  @param  ������̍s��
     *  @return ���Z��̍s��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Matrix3x3<T>& S_Matrix3x3<T>::operator+=(const S_Matrix3x3<T>& rAnother)
    {
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i) a_[i] += rAnother.a_[i];

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  ������̍s��Ō��Z����
     *  @param  ������̍s��
     *  @return ���Z��̍s��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Matrix3x3<T>& S_Matrix3x3<T>::operator-=(const S_Matrix3x3<T>& rAnother)
    {
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i) a_[i] -= rAnother.a_[i];

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  ������̍s�����Z����
     *  @param  ������̍s��
     *  @return ��Z��̍s��( �������g )
     *
     ****************************************************************/
    template<typename T>
    const S_Matrix3x3<T>& S_Matrix3x3<T>::operator*=(const S_Matrix3x3<T>& rAnother)
    {
        // ���̍s��
        S_Matrix3x3 tempMatrix;

        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i)
        {
            // �e�s��̓Y���������߂�
            size_t index = i % 3;
            size_t anotherIndex = (i / 3) * 3;

            // �s�񓯎m�̏�Z
            tempMatrix.a_[i] = a_[index] * rAnother.a_[anotherIndex]
                             + a_[index + 3] * rAnother.a_[anotherIndex + 1]
                             + a_[index + 6] * rAnother.a_[anotherIndex + 2];
        }

        // ���̍s�����
        (*this) = tempMatrix;

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  ������̍s��Ɣ�r����
     *  @param  ������̍s��
     *  @return �����s��̏ꍇ�Ftrue
     *  @return �Ⴄ�s��̏ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool S_Matrix3x3<T>::operator==(const S_Matrix3x3<T>& rAnother) const
    {
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i)
        {
            if (std::abs(a_[i] - rAnother.a_[i]) > static_cast<T>(s_EPSILON)) return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  ������̍s��Ɣ�r����
     *  @param  ������̍s��
     *  @return �Ⴄ�s��̏ꍇ�Ftrue
     *  @return �����s��̏ꍇ�Ffalse
     *
     ****************************************************************/
    template<typename T>
    bool S_Matrix3x3<T>::operator!=(const S_Matrix3x3<T>& rAnother) const
    {
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i)
        {
            if (std::abs(a_[i] - rAnother.a_[i]) > static_cast<T>(s_EPSILON)) return true;
        }

        return false;
    }


#pragma endregion


#pragma region S_Vector3�^�Ƃ̉��Z�q�̃I�[�o�[���[�h


    /*************************************************************//**
     *
     *  @brief  �x�N�g���Ə�Z�����l�����߂�
     *  @param  3D�x�N�g��
     *  @return ��Z�����x�N�g��
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T> S_Matrix3x3<T>::operator*(const S_Vector3<T>& rVector) const
    {
        S_Vector3<T> tempVector;

        tempVector.x_ = a11_ * rVector.x_
                      + a21_ * rVector.y_
                      + a31_ * rVector.z_;

        tempVector.y_ = a12_ * rVector.x_
                      + a22_ * rVector.y_
                      + a32_ * rVector.z_;

        tempVector.z_ = a13_ * rVector.x_
                      + a23_ * rVector.y_
                      + a33_ * rVector.z_;

        return tempVector;
    }


#pragma endregion


#pragma region �L���X�g���Z�q�̃I�[�o�[���[�h


    /*************************************************************//**
     *
     *  @brief  string�^�փL���X�g����
     *  @param  �Ȃ�
     *  @return ������ɕϊ������s��
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T>::operator std::string() const
    {
        return GetConvertToString();
    }


#pragma endregion


    /* �����I�C���X�^���X�� */
    template struct S_Matrix3x3<float>;
    template struct S_Matrix3x3<double>;


    /*************************************************************//**
     *
     *  @brief  �s�񎮂��擾����
     *  @param  �s��
     *  @return �s��
     *
     ****************************************************************/
    template<typename T>
    static T s_GetDeterminant(const S_Matrix3x3<T>& rMatrix)
    {
        return (rMatrix.a11_ * rMatrix.a22_ * rMatrix.a33_)
             + (rMatrix.a21_ * rMatrix.a32_ * rMatrix.a13_)
             + (rMatrix.a31_ * rMatrix.a12_ * rMatrix.a23_)
             - (rMatrix.a11_ * rMatrix.a32_ * rMatrix.a23_)
             - (rMatrix.a31_ * rMatrix.a22_ * rMatrix.a13_)
             - (rMatrix.a21_ * rMatrix.a12_ * rMatrix.a33_);
    }

}