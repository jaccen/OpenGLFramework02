/* ��d�C���N���[�h�h�~ */
#pragma once


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
    //! @brief �x�N�^�[2
    //! @brief 2D�x�N�g����\���\����
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    struct S_Vector2
    {
        /* �萔 */
        static const S_Vector2 s_RIGHT_DIRECTION;                                               ///< @brief �E���� ( 1,  0)
        static const S_Vector2 s_LEFT_DIRECTION;                                                ///< @brief ������ (-1,  0)
        static const S_Vector2 s_UP_DIRECTION;                                                  ///< @brief ����� ( 0,  1)
        static const S_Vector2 s_DOWN_DIRECTION;                                                ///< @brief ������ ( 0, -1)
        static const S_Vector2 s_ZERO;                                                          ///< @brief �[���x�N�g��
        static const S_Vector2 s_ONE;                                                           ///< @brief �S�Ă̗v�f��1

        /* �����o�ϐ� */
        union
        {
            T a_[2];                                                                            ///< @brief 2�̗v�f�����z��

            struct
            {
                T x_;                                                                           ///< @brief X����
                T y_;                                                                           ///< @brief Y����
            };

            struct
            {
                T u_;                                                                           ///< @brief U����
                T v_;                                                                           ///< @brief V����
            };

            struct
            {
                T width_;                                                                       ///< @brief ��
                T height_;                                                                      ///< @brief ����
            };
        };

        /* �����o�֐� */
        S_Vector2();                                                                            // �R���X�g���N�^
        explicit S_Vector2(T value);                                                            // �R���X�g���N�^
        S_Vector2(T x, T y);                                                                    // �R���X�g���N�^
        explicit S_Vector2(const T a[2]);                                                       // �R���X�g���N�^
        S_Vector2(const S_Vector2& rOhter) = default;                                           // �R�s�[�R���X�g���N�^
        ~S_Vector2();                                                                           // �f�X�g���N�^
        void Zero();                                                                            // �[���x�N�g����
        void Fill(T value);                                                                     // �e���������̒l�ɕύX
        void Normalize();                                                                       // �P�ʃx�N�g����
        void Invert();                                                                          // �x�N�g���𔽓]
        void Perpendicular();                                                                   // �����ȃx�N�g���ɕϊ�
        void Rotate(T angle);                                                                   // �x�N�g������]
        void ClampLength(T minLength, T maxLength);                                             // �����Ńx�N�g�����N�����v
        T GetLength() const;                                                                    // �������擾
        T GetLengthSquare() const;                                                              // ������2����擾
        S_Vector2 GetNormalize() const;                                                         // �P�ʃx�N�g�����擾
        S_Vector2 GetInvert() const;                                                            // ���]�����x�N�g�����擾
        S_Vector2 GetPerpendicular() const;                                                     // �����ȃx�N�g�����擾
        S_Vector2 GetRotate(T angle) const;                                                     // ��]�����x�N�g�����擾
        T GetAngle() const;                                                                     // �x�N�g���̊p�x���擾
        S_Vector2 GetClampLength(T minLength, T maxLength) const;                               // �����ŃN�����v�����x�N�g�����擾
        std::string GetConvertToString() const;                                                 // �x�N�g���𕶎���֕ϊ����Ď擾

        /* �ÓI�����o�֐� */
        static T s_DotProduct(const S_Vector2& rLhs, const S_Vector2& rRhs);                    // ����
        static T s_CrossProduct(const S_Vector2& rLhs, const S_Vector2& rRhs);                  // �O��
        static S_Vector2 s_Lerp(const S_Vector2& rStartPoint,                                   // ���`���
                                const S_Vector2& rEndPoint,
                                T coefficient);
        static S_Vector2 s_Slerp(const S_Vector2& rStartPoint,                                  // ���ʐ��`���
                                 const S_Vector2& rEndPoint,
                                 T coefficient);
        static S_Vector2 s_Hermite(const S_Vector2& rStartPoint,                                // �G���~�[�g���
                                   const S_Vector2& rStartTangent,
                                   const S_Vector2& rEndPoint,
                                   const S_Vector2& rEndTangent,
                                   T coefficient);
        static S_Vector2 s_CatmullRomSpline(const S_Vector2& rPreviousStartPoint,               // Catmull-Rom�X�v���C�����
                                            const S_Vector2& rStartPoint,                       
                                            const S_Vector2& rEndPoint,
                                            const S_Vector2& rNextEndPoint,
                                            T coefficient);
        static S_Vector2 s_Bezier(const S_Vector2& rStartPoint,                                 // �x�W�F���
                                  const S_Vector2& rEndPoint,
                                  const S_Vector2& rControlPoint1,
                                  const S_Vector2& rControlPoint2,
                                  T coefficient);
        static S_Vector2 s_CreateWithAngle(T angle, T length = static_cast<T>(1.0));            // �p�x����x�N�g�����쐬
        static S_Vector2 s_InterceptPoint(const S_Vector2& rPosition,                           // �}���|�C���g���擾
                                          const S_Vector2& rVelocity,
                                          const S_Vector2& rAnotherPosition,
                                          const S_Vector2& rAnotherVelocity);
        static T s_AngleBetweenVectors(const S_Vector2& rLhs, const S_Vector2& rRhs);           // �x�N�g���Ԃ̊p�x���擾
        static T s_DistanceBetweenVectors(const S_Vector2& rLhs, const S_Vector2& rRhs);        // �x�N�g���Ԃ̋������擾
        static S_Vector2 s_Minimize(const S_Vector2& rLhs, const S_Vector2& rRhs);              // �e�����̍ŏ��l�𐬕��ɂ����x�N�g�����擾
        static S_Vector2 s_Maximize(const S_Vector2& rLhs, const S_Vector2& rRhs);              // �e�����̍ő�l�𐬕��ɂ����x�N�g�����擾
        static S_Vector2 s_MoveTowards(const S_Vector2& rStartPoint,                            // 2�_�Ԃ���̋����������i�񂾓_���擾
                                       const S_Vector2& rEndPoint,
                                       T distance);
        static S_Vector2 s_Project(const S_Vector2& rVector, const S_Vector2& rNormal);         // ���e�x�N�g�����擾
        static S_Vector2 s_Reflect(const S_Vector2& rVector, const S_Vector2& rNormal);         // ���˃x�N�g�����擾
        static S_Vector2 s_Refract(const S_Vector2& rIncidentVector,                            // ���܃x�N�g�����擾
                                   const S_Vector2& rNormal, 
                                   T refractiveIndex);
        static S_Vector2 s_Slide(const S_Vector2& rVector, const S_Vector2& rNormal);           // ����x�N�g�����擾
        static S_Vector2 s_CenterOfGravityWith3Points(const S_Vector2& rA,                      // 3�_����d�S���擾
                                                      const S_Vector2& rB,
                                                      const S_Vector2& rC);
            

        /* S_Vector2�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
        const S_Vector2 operator+(const S_Vector2& rAnother) const;                             // +���Z�q�̃I�[�o�[���[�h
        const S_Vector2 operator-(const S_Vector2& rAnother) const;                             // -���Z�q�̃I�[�o�[���[�h
        const S_Vector2 operator*(const S_Vector2& rAnother) const;                             // *���Z�q�̃I�[�o�[���[�h
        const S_Vector2 operator/(const S_Vector2& rAnother) const;                             // /���Z�q�̃I�[�o�[���[�h
        const S_Vector2& operator+=(const S_Vector2& rAnother);                                 // +=���Z�q�̃I�[�o�[���[�h
        const S_Vector2& operator-=(const S_Vector2& rAnother);                                 // -=���Z�q�̃I�[�o�[���[�h
        const S_Vector2& operator*=(const S_Vector2& rAnother);                                 // *=���Z�q�̃I�[�o�[���[�h
        const S_Vector2& operator/=(const S_Vector2& rAnother);                                 // /=���Z�q�̃I�[�o�[���[�h
        bool operator==(const S_Vector2& rAnother) const;                                       // ==���Z�q�̃I�[�o�[���[�h
        bool operator!=(const S_Vector2& rAnother) const;                                       // !=���Z�q�̃I�[�o�[���[�h

        /* T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
        const S_Vector2 operator*(T value) const;                                               // *���Z�q�̃I�[�o�[���[�h
        const S_Vector2 operator/(T value) const;                                               // /���Z�q�̃I�[�o�[���[�h
        const S_Vector2& operator*=(T value);                                                   // *=���Z�q�̃I�[�o�[���[�h
        const S_Vector2& operator/=(T value);                                                   // /=���Z�q�̃I�[�o�[���[�h

        /* �L���X�g���Z�q�̃I�[�o�[���[�h */
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
        friend const S_Vector2 operator*(T value, const S_Vector2& rVector)
        {
            return S_Vector2(rVector.x_ * value, rVector.y_ * value);
        }


        /*************************************************************//**
         *
         *  @brief  T�^�̒l�ƃx�N�g������Z����
         *  @param  T�^�̒l
         *  @param  �x�N�g��
         *  @return ��Z�����x�N�g��
         *
         ****************************************************************/
        friend const S_Vector2 operator/(T value, const S_Vector2& rVector)
        {
            assert(value != static_cast<T>(0));

            return S_Vector2(rVector.x_ / value, rVector.y_ / value);
        }


        #pragma endregion
    };

    /* �ʖ� */
    using Vector2 = S_Vector2<>;                                                                // Vector2�^
}