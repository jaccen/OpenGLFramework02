/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "Vector3.h"


//-------------------------------------------------------------
///
/// @brief �}�X
/// @brief ���w�֘A�̖��O���
///
//-------------------------------------------------------------
namespace Math
{
    //-------------------------------------------------------------
    //!
    //! @brief �x�N�^�[4
    //! @brief 4D�x�N�g����\���\����
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    struct S_Vector4
    {
        /* �萔 */
        static const S_Vector4 s_ZERO;                                                          ///< @brief �[���x�N�g��
        static const S_Vector4 s_ONE;                                                           ///< @brief �S�Ă̗v�f��1

        /* �����o�ϐ� */
        union
        {
            T a_[4];                                                                            ///< @brief 4�̗v�f�����z��

            struct
            {
                T x_;                                                                           ///< @brief X����
                T y_;                                                                           ///< @brief Y����
                T z_;                                                                           ///< @brief Z����
                T w_;                                                                           ///< @brief W����
            };

            struct
            {
                T red_;                                                                         ///< @brief ��
                T green_;                                                                       ///< @brief ��
                T blue_;                                                                        ///< @brief ��
                T alpha_;                                                                       ///< @brief �A���t�@
            };

            struct
            {
                S_Vector3<T> xyz_;                                                              ///< @brief X�EY�EZ����
            };
        };

        /* �����o�֐� */
        S_Vector4();                                                                            // �R���X�g���N�^
        explicit S_Vector4(T value);                                                            // �R���X�g���N�^
        S_Vector4(T x, T y, T z, T w);                                                          // �R���X�g���N�^
        explicit S_Vector4(const T a[4]);                                                       // �R���X�g���N�^
        S_Vector4(const S_Vector2<T>& rXY, T z, T w);                                           // �R���X�g���N�^
        S_Vector4(const S_Vector3<T>& rXYZ, T w);                                               // �R���X�g���N�^
        S_Vector4(const S_Vector4& rOther) = default;                                           // �R�s�[�R���X�g���N�^
        ~S_Vector4();                                                                           // �f�X�g���N�^
        void Zero();                                                                            // �[���x�N�g����
        void Fill(T value);                                                                     // �e���������̒l�ɕύX
        void Normalize();                                                                       // �P�ʃx�N�g����
        void Invert();                                                                          // �x�N�g���𔽓]
        void ClampLength(T minLength, T maxLength);                                             // �x�N�g���̒����ŃN�����v
        T GetLength() const;                                                                    // �������擾
        T GetLengthSquare() const;                                                              // ������2����擾
        S_Vector4 GetNormalize() const;                                                         // �P�ʃx�N�g�����擾
        S_Vector4 GetInvert() const;                                                            // ���]�����x�N�g�����擾
        S_Vector4 GetClampLength(T minLength, T maxLength) const;                               // �����ŃN�����v�����x�N�g�����擾
        std::string GetConvertToString() const;                                                 // �x�N�g���𕶎���֕ϊ����Ď擾

        /* Swizzle */
        template<eVectorFactor factor0>
        S_Vector4 Get() const
        {
            return S_Vector4(a_[factor0], a_[factor0], a_[factor0], a_[factor0]);
        }
         
        template<eVectorFactor factor0, eVectorFactor factor1>
        S_Vector4 Get() const
        {
            return S_Vector4(a_[factor0], a_[factor1], a_[factor1], a_[factor1]);
        }
         
        template<eVectorFactor factor0, eVectorFactor factor1, eVectorFactor factor2>
        S_Vector4 Get() const
        {
            return S_Vector4(a_[factor0], a_[factor1], a_[factor2], a_[factor2]);
        }
         
        template<eVectorFactor factor0, eVectorFactor factor1, eVectorFactor factor2, eVectorFactor factor3>
        S_Vector4 Get() const
        {
            return S_Vector4(a_[factor0], a_[factor1], a_[factor2], a_[factor3]);
        }

        /* �ÓI�����o�֐� */
        static T s_DotProduct(const S_Vector4& rVector, const S_Vector4& rAnotherVector);       // ����
        static S_Vector4 s_Lerp(const S_Vector4& rStartPoint,                                   // ���`���
                                const S_Vector4& rEndPoint,
                                T coefficient);
        static S_Vector4 s_Minimize(const S_Vector4& rLhs, const S_Vector4& rRhs);              // �e�����̍ŏ��l�𐬕��ɂ����x�N�g�����擾
        static S_Vector4 s_Maximize(const S_Vector4& rLhs, const S_Vector4& rRhs);              // �e�����̍ő�l�𐬕��ɂ����x�N�g�����擾

        /* S_Vector4�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
        const S_Vector4 operator+(const S_Vector4& rAnother) const;                             // +���Z�q�̃I�[�o�[���[�h
        const S_Vector4 operator-(const S_Vector4& rAnother) const;                             // -���Z�q�̃I�[�o�[���[�h
        const S_Vector4 operator*(const S_Vector4& rAnother) const;                             // *���Z�q�̃I�[�o�[���[�h
        const S_Vector4 operator/(const S_Vector4& rAnother) const;                             // /���Z�q�̃I�[�o�[���[�h
        const S_Vector4& operator+=(const S_Vector4& rAnother);                                 // +=���Z�q�̃I�[�o�[���[�h
        const S_Vector4& operator-=(const S_Vector4& rAnother);                                 // -=���Z�q�̃I�[�o�[���[�h
        const S_Vector4& operator*=(const S_Vector4& rAnother);                                 // *=���Z�q�̃I�[�o�[���[�h
        const S_Vector4& operator/=(const S_Vector4& rAnother);                                 // /=���Z�q�̃I�[�o�[���[�h
        bool operator==(const S_Vector4& rAnother) const;                                       // ==���Z�q�̃I�[�o�[���[�h
        bool operator!=(const S_Vector4& rAnother) const;                                       // !=���Z�q�̃I�[�o�[���[�h

        /* T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
        const S_Vector4 operator*(T value) const;                                               // *���Z�q�̃I�[�o�[���[�h
        const S_Vector4 operator/(T value) const;                                               // /���Z�q�̃I�[�o�[���[�h
        const S_Vector4& operator*=(T value);                                                   // *=���Z�q�̃I�[�o�[���[�h
        const S_Vector4& operator/=(T value);                                                   // /=���Z�q�̃I�[�o�[���[�h

        /* �L���X�g���Z�q�̃I�[�o�[���[�h */
        operator S_Vector2<T>() const;                                                          // S_Vector2�^�ւ̃L���X�g
        operator S_Vector3<T>() const;                                                          // S_Vector3�^�ւ̃L���X�g
        operator std::string() const;                                                           // string�^�ւ̃L���X�g

        #pragma region T�^�Ƃ̃t�����h���Z�q�̃I�[�o�[���[�h


        /*************************************************************//**
         *
         *  @brief  T�^�̒l�ƃx�N�g������Z����
         *  @param  T�^�̒l
         *  @param  �x�N�g��
         *  @return ��Z�����x�N�g��
         *
         ****************************************************************/
        friend S_Vector4 operator*(T value, const S_Vector4& rVector)
        {
            return S_Vector4(rVector.x_ * value, rVector.y_ * value, rVector.z_ * value, rVector.w_ * value);
        }


        /*************************************************************//**
         *
         *  @brief  T�^�̒l�ƃx�N�g�������Z����
         *  @param  T�^�̒l
         *  @param  �x�N�g��
         *  @return ���Z�����x�N�g��
         *
         ****************************************************************/
        friend S_Vector4 operator/(T value, const S_Vector4& rVector)
        {
            assert(value != static_cast<T>(0));

            return S_Vector4(rVector.x_ / value, rVector.y_ / value, rVector.z_ / value, rVector.w_ / value);
        }


        #pragma endregion
    };


    /* �ʖ� */
    using Vector4 = S_Vector4<>;                                                                // Vector4�^
}