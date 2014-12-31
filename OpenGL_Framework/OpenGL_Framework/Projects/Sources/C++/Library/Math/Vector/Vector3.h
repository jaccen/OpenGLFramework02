/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "Vector2.h"
#include <tuple>


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
    //! @brief �x�N�^�[3
    //! @brief 3D�x�N�g����\���\����
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    struct S_Vector3
    {
        /* �萔 */
        static const S_Vector3 s_RIGHT_DIRECTION;                                                                   ///< @brief �E���� ( 1,  0,  0)
        static const S_Vector3 s_LEFT_DIRECTION;                                                                    ///< @brief ������ (-1,  0,  0)
        static const S_Vector3 s_UP_DIRECTION;                                                                      ///< @brief ����� ( 0,  1,  0)
        static const S_Vector3 s_DOWN_DIRECTION;                                                                    ///< @brief ������ ( 0, -1,  0)
        static const S_Vector3 s_FRONT_DIRECTION;                                                                   ///< @brief �O���� ( 0,  0,  1)
        static const S_Vector3 s_BACK_DIRECTION;                                                                    ///< @brief ����� ( 0,  0, -1)
        static const S_Vector3 s_ZERO;                                                                              ///< @brief �[���x�N�g��
        static const S_Vector3 s_ONE;                                                                               ///< @brief �S�Ă̗v�f��1

        /* �����o�ϐ� */
        union
        {
            T a_[3];                                                                                                ///< @brief 3�̗v�f�����z��

            struct
            {
                T x_;                                                                                               ///< @brief X����
                T y_;                                                                                               ///< @brief Y����
                T z_;                                                                                               ///< @brief Z����
            };

            struct
            {
                T u_;                                                                                               ///< @brief U����
                T v_;                                                                                               ///< @brief V����
                T w_;                                                                                               ///< @brief W����
            };

            struct
            {
                T red_;                                                                                             ///< @brief ��
                T green_;                                                                                           ///< @brief ��
                T blue_;                                                                                            ///< @brief ��
            };

            struct
            {
                T width_;                                                                                           ///< @brief ��
                T height_;                                                                                          ///< @brief ����
                T depth_;                                                                                           ///< @brief ���s��
            };

            struct
            {
                S_Vector2<T> xy_;                                                                                   ///< @brief X�EY����
            };
        };

        /* �����o�֐� */
        S_Vector3();                                                                                                // �R���X�g���N�^
        explicit S_Vector3(T value);                                                                                // �R���X�g���N�^
        S_Vector3(T x, T y, T z);                                                                                   // �R���X�g���N�^
        explicit S_Vector3(const T a[3]);                                                                           // �R���X�g���N�^
        S_Vector3(const S_Vector2<T>& rXY, T z);                                                                    // �R���X�g���N�^
        S_Vector3(const S_Vector3& rOther) = default;                                                               // �R�s�[�R���X�g���N�^
        ~S_Vector3();                                                                                               // �f�X�g���N�^
        void Zero();                                                                                                // �[���x�N�g����
        void Fill(T value);                                                                                         // �e���������̒l�ɕύX
        void Normalize();                                                                                           // �P�ʃx�N�g����
        void Invert();                                                                                              // �x�N�g���𔽓]
        void RotateX(T angle);                                                                                      // X������x�N�g������]
        void RotateY(T angle);                                                                                      // Y������x�N�g������]
        void RotateZ(T angle);                                                                                      // Z������x�N�g������]
        void RotateAxis(const S_Vector3<T>& rAxis, T angle);                                                        // �C�ӎ�����x�N�g������]
        void ClampLength(T minLength, T maxLength);                                                                 // �����Ńx�N�g�����N�����v
        T GetLength() const;                                                                                        // �������擾
        T GetLengthSquare() const;                                                                                  // ������2����擾
        S_Vector3 GetNormalize() const;                                                                             // �P�ʃx�N�g�����擾
        S_Vector3 GetInvert() const;                                                                                // ���]�����x�N�g�����擾
        S_Vector3 GetRotateX(T angle) const;                                                                        // X�������]�����x�N�g�����擾
        S_Vector3 GetRotateY(T angle) const;                                                                        // Y�������]�����x�N�g�����擾
        S_Vector3 GetRotateZ(T angle) const;                                                                        // Z�������]�����x�N�g�����擾
        S_Vector3 GetRotateAxis(const S_Vector3<T>& rAxis, T angle) const;                                          // �C�ӎ������]�����x�N�g�����擾
        S_Vector3 GetClampLength(T minLength, T maxLength) const;                                                   // �����ŃN�����v�����x�N�g�����擾
        std::string GetConvertToString() const;                                                                     // �x�N�g���𕶎���֕ϊ����Ď擾

        /* �ÓI�����o�ϐ� */
        static T s_DotProduct(const S_Vector3& rLhs, const S_Vector3& rRhs);                                        // ����
        static S_Vector3 s_CrossProduct(const S_Vector3& rLhs, const S_Vector3& rRhs);                              // �O��
        static T s_ScalarTripleProduct(const S_Vector3& rA,                                                         // �X�J���[�O�d��
                                       const S_Vector3& rB,
                                       const S_Vector3& rC);
        static S_Vector3 s_VectorTripleProduct(const S_Vector3& rA,                                                 // �x�N�g���O�d��
                                               const S_Vector3& rB,
                                               const S_Vector3& rC);
        static S_Vector3 s_Lerp(const S_Vector3& rStartPoint,                                                       // ���`���
                                const S_Vector3& rEndPoint,
                                T coefficient);
        static S_Vector3 s_Slerp(const S_Vector3& rStartPoint,                                                      // ���ʐ��`���
                                 const S_Vector3& rEndPoint,
                                 T coefficient);
        static S_Vector3 s_Hermite(const S_Vector3& rStartPoint,                                                    // �G���~�[�g���
                                   const S_Vector3& rStartTangent,
                                   const S_Vector3& rEndPoint,
                                   const S_Vector3& rEndTangent,
                                   T coefficient);
        static S_Vector3 s_CatmullRomSpline(const S_Vector3& rPreviousStartPoint,                                   // Catmull-Rom�X�v���C�����
                                            const S_Vector3& rStartPoint,                       
                                            const S_Vector3& rEndPoint,
                                            const S_Vector3& rNextEndPoint,
                                            T coefficient);
        static S_Vector3 s_Bezier(const S_Vector3& rStartPoint,                                                     // �x�W�F���
                                  const S_Vector3& rEndPoint,
                                  const S_Vector3& rControlPoint1,
                                  const S_Vector3& rControlPoint2,
                                  T coefficient);
        static S_Vector3 s_InterceptPoint(const S_Vector3& rPosition,                                               // �}���|�C���g���擾
                                          const S_Vector3& rVelocity,
                                          const S_Vector3& rAnotherPosition,
                                          const S_Vector3& rAnotherVelocity);
        static T s_AngleBetweenVectors(const S_Vector3& rLhs, const S_Vector3& rRhs);                               // �x�N�g���Ԃ̊p�x���擾
        static T s_DistanceBetweenVectors(const S_Vector3& rLhs, const S_Vector3& rRhs);                            // �x�N�g���Ԃ̋������擾
        static S_Vector3 s_Minimize(const S_Vector3& rLhs, const S_Vector3& rRhs);                                  // �e�����̍ŏ��l�𐬕��ɂ����x�N�g�����擾
        static S_Vector3 s_Maximize(const S_Vector3& rLhs, const S_Vector3& rRhs);                                  // �e�����̍ő�l�𐬕��ɂ����x�N�g�����擾
        static S_Vector3 s_MoveTowards(const S_Vector3& rStartPoint,                                                // 2�_�Ԃ���̋����������i�񂾓_���擾
                                       const S_Vector3& rEndPoint,
                                       T distance);
        static S_Vector3 s_Project(const S_Vector3& rVector, const S_Vector3& rNormal);                             // ���e�x�N�g�����擾
        static S_Vector3 s_Reflect(const S_Vector3& rVector, const S_Vector3& rNormal);                             // ���˃x�N�g�����擾
        static S_Vector3 s_Refract(const S_Vector3& rIncidentVector,                                                // ���܃x�N�g�����擾
                                   const S_Vector3& rNormal, 
                                   T refractiveIndex);
        static S_Vector3 s_Slide(const S_Vector3& rVector, const S_Vector3& rNormal);                               // ����x�N�g�����擾
        static S_Vector3 s_CreateNormal(const S_Vector3& rPositionA,                                                // �@���x�N�g�����쐬
                                        const S_Vector3& rPositionB,
                                        const S_Vector3& rPositionC);
        static std::tuple<S_Vector3, S_Vector3> s_CreateTangentAndBinormal(const S_Vector3& rPositionA,             // �ڐ��x�N�g���Ə]�@�����쐬( ���s���͂���ĂȂ� )
                                                                           const S_Vector2<T>& rTextureCoordA,
                                                                           const S_Vector3& rPositionB,
                                                                           const S_Vector2<T>& rTextureCoordB,
                                                                           const S_Vector3& rPositionC,
                                                                           const S_Vector2<T>& rTextureCoordC);
        static S_Vector3 s_CenterOfGravityWith3Points(const S_Vector3& rA,                                          // 3�_����d�S���擾
                                                      const S_Vector3& rB,
                                                      const S_Vector3& rC);
        

        /* S_Vector3�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
        const S_Vector3 operator+(const S_Vector3& rAnother) const;                                                 // +���Z�q�̃I�[�o�[���[�h
        const S_Vector3 operator-(const S_Vector3& rAnother) const;                                                 // -���Z�q�̃I�[�o�[���[�h
        const S_Vector3 operator*(const S_Vector3& rAnother) const;                                                 // *���Z�q�̃I�[�o�[���[�h
        const S_Vector3 operator/(const S_Vector3& rAnother) const;                                                 // /���Z�q�̃I�[�o�[���[�h
        const S_Vector3& operator+=(const S_Vector3& rAnother);                                                     // +=���Z�q�̃I�[�o�[���[�h
        const S_Vector3& operator-=(const S_Vector3& rAnother);                                                     // -=���Z�q�̃I�[�o�[���[�h
        const S_Vector3& operator*=(const S_Vector3& rAnother);                                                     // *=���Z�q�̃I�[�o�[���[�h
        const S_Vector3& operator/=(const S_Vector3& rAnother);                                                     // /=���Z�q�̃I�[�o�[���[�h
        bool operator==(const S_Vector3& rAnother) const;                                                           // ==���Z�q�̃I�[�o�[���[�h
        bool operator!=(const S_Vector3& rAnother) const;                                                           // !=���Z�q�̃I�[�o�[���[�h

        /* T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
        const S_Vector3 operator*(T value) const;                                                                   // *���Z�q�̃I�[�o�[���[�h
        const S_Vector3 operator/(T value) const;                                                                   // /���Z�q�̃I�[�o�[���[�h
        const S_Vector3& operator*=(T value);                                                                       // *=���Z�q�̃I�[�o�[���[�h
        const S_Vector3& operator/=(T value);                                                                       // /=���Z�q�̃I�[�o�[���[�h

        /* �L���X�g���Z�q�̃I�[�o�[���[�h */
        operator S_Vector2<T>() const;                                                                              // S_Vector2�^�ւ̃L���X�g
        operator std::string() const;                                                                               // string�^�ւ̃L���X�g


        #pragma region T�^�Ƃ̃t�����h���Z�q�̃I�[�o�[���[�h


        /*************************************************************//**
         *
         *  @brief  T�^�̒l�ƃx�N�g������Z����
         *  @param  T�^�̒l
         *  @param  �x�N�g��
         *  @return ��Z�����x�N�g��
         *
         ****************************************************************/
        friend const S_Vector3 operator*(T value, const S_Vector3& rVector)
        {
            return S_Vector3(rVector.x_ * value, rVector.y_ * value, rVector.z_ * value);
        }


        /*************************************************************//**
         *
         *  @brief  T�^�̒l�ƃx�N�g�������Z����
         *  @param  T�^�̒l
         *  @param  �x�N�g��
         *  @return ���Z�����x�N�g��
         *
         ****************************************************************/
        friend const S_Vector3 operator/(T value, const S_Vector3& rVector)
        {
            assert(value != static_cast<T>(0));

            return S_Vector3(rVector.x_ / value, rVector.y_ / value, rVector.z_ / value);
        }


        #pragma endregion
    };

    /* �ʖ� */
    using Vector3 = S_Vector3<>;                                                                                    // Vector3�^
}
