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
    /* �O���錾 */
    template<typename T>
    struct S_Vector3;

    template<typename T>
    struct S_Matrix4x4;

    template<typename T>
    struct S_Quaternion;

    //-------------------------------------------------------------
    //!
    //! @brief �}�g���N�X3x3
    //! @brief 3 * 3�̍s���\���\����
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    struct S_Matrix3x3
    {
        /* �萔 */
        static const uint8_t s_ELEMENT_NUMBER = 9;                                                      ///< @brief �v�f��
        static const S_Matrix3x3 s_ZERO;                                                                ///< @brief �[���s��
        static const S_Matrix3x3 s_IDENTITY;                                                            ///< @brief �P�ʍs��

        /* �����o�ϐ� */
        union
        {
            T a_[s_ELEMENT_NUMBER];                                                                     ///< @brief 9�̗v�f�����z��
            T a3x3_[3][3];                                                                              ///< @brief 3 * 3�̓񎟌��z��

            /// @brief �s��̊e�v�f
            struct
            {
                T a11_, a12_, a13_;
                T a21_, a22_, a23_;
                T a31_, a32_, a33_;
            };
        };

        /* �����o�֐� */
        S_Matrix3x3();                                                                                  // �R���X�g���N�^
        S_Matrix3x3(T value);                                                                           // �R���X�g���N�^
        S_Matrix3x3(T a11, T a12, T a13,                                                                // �R���X�g���N�^
                    T a21, T a22, T a23,
                    T a31, T a32, T a33);
        explicit S_Matrix3x3(const T a[s_ELEMENT_NUMBER]);                                              // �R���X�g���N�^
        S_Matrix3x3(const S_Matrix3x3& rOther) = default;                                               // �R�s�[�R���X�g���N�^ 
        ~S_Matrix3x3();                                                                                 // �f�X�g���N�^
        void Zero();                                                                                    // �[���s��
        void Fill(T value);                                                                             // �e�v�f�����̒l�ɕύX
        void Identity();                                                                                // �P�ʍs��
        void Transpose();                                                                               // �]�u�s��
        void Invert();                                                                                  // �t�s��
        S_Matrix3x3 GetTranspose() const;                                                               // �]�u�s����擾
        S_Matrix3x3 GetInvert() const;                                                                  // �t�s����擾
        S_Vector3<T> GetRow(int32_t index = 0) const;                                                   // �s���擾
        S_Vector3<T> GetColumn(int32_t index = 0) const;                                                // ����擾
        std::string GetConvertToString() const;                                                         // �s��𕶎���֕ϊ����Ď擾
        void SetRow(const S_Vector3<T>& rRow, int32_t index = 0);                                       // �s��ݒ�
        void SetColumn(const S_Vector3<T>& rColumn, int32_t index = 0);                                 // ���ݒ�
        
        /* �ÓI�����o�֐� */
        static S_Matrix3x3 s_CreateRotation(T angle);                                                   // ��]�s����쐬
        static S_Matrix3x3 s_CreateRotationX(T angle);                                                  // X�������]�s����쐬
        static S_Matrix3x3 s_CreateRotationY(T angle);                                                  // Y�������]�s����쐬
        static S_Matrix3x3 s_CreateRotationZ(T angle);                                                  // Z�������]�s����쐬
        static S_Matrix3x3 s_CreateRotationAxis(const S_Vector3<T>& rAxis, T angle);                    // �C�ӎ������]�s����쐬 
        static S_Matrix3x3 s_CreateScaling(T scalingRateX, T scalingRateY);                             // �g�k�s����쐬
        static S_Matrix3x3 s_CreateTranslation(T movementX, T movementY);                               // ���s�ړ��s����쐬
        static S_Matrix3x3 s_ConvertMatrix4x4ToMatrix3x3(const S_Matrix4x4<T>& rMatirx);                // 4 * 4�̍s���3 * 3�̍s��ɕϊ�
        static S_Matrix3x3 s_ConvertQuaternionToMatrix3x3(const S_Quaternion<T>& rQuaternion);          // �N�H�[�^�j�I������3 * 3�̍s��֕ϊ����A�擾
        static S_Matrix3x3 s_CreateNormal(const S_Matrix4x4<T>& rMatrix);                               // �@���s����쐬
        static S_Matrix3x3 s_CreateLookAt(const S_Vector3<T>& rEyePoint,                                // �r���[�s����쐬
                                          const S_Vector3<T>& rTargetPoint,
                                          const S_Vector3<T>& rUpVector);

        /* S_Matrix3x3�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
        const S_Matrix3x3 operator+(const S_Matrix3x3& rAnother) const;                                 // +���Z�q�̃I�[�o�[���[�h
        const S_Matrix3x3 operator-(const S_Matrix3x3& rAnother) const;                                 // -���Z�q�̃I�[�o�[���[�h
        const S_Matrix3x3 operator*(const S_Matrix3x3& rAnother) const;                                 // *���Z�q�̃I�[�o�[���[�h
        const S_Matrix3x3& operator+=(const S_Matrix3x3& rAnother);                                     // +=���Z�q�̃I�[�o�[���[�h
        const S_Matrix3x3& operator-=(const S_Matrix3x3& rAnother);                                     // -=���Z�q�̃I�[�o�[���[�h
        const S_Matrix3x3& operator*=(const S_Matrix3x3& rAnother);                                     // *=���Z�q�̃I�[�o�[���[�h
        bool operator==(const S_Matrix3x3& rAnother) const;                                             // ==���Z�q�̃I�[�o�[���[�h
        bool operator!=(const S_Matrix3x3& rAnother) const;                                             // !=���Z�q�̃I�[�o�[���[�h

        /* S_Vector3�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
        const S_Vector3<T> operator*(const S_Vector3<T>& rVector) const;                                // *���Z�q�̃I�[�o�[���[�h

        /* �L���X�g���Z�q�̃I�[�o�[���[�h */
        operator std::string() const;                                                                   // string�^�ւ̃L���X�g
    };

    /* �ʖ� */
    using Matrix3x3 = S_Matrix3x3<>;                                                                     // Matrix3x3�^
};