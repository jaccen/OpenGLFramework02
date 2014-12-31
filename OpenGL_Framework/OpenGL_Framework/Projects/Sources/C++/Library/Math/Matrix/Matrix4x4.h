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
    struct S_Vector4;

    template<typename T>
    struct S_Quaternion;

    template <typename T>
    struct S_Matrix3x3;

    //-------------------------------------------------------------
    //!
    //! @brief �}�g���N�X4x4
    //! @brief 4 * 4�̍s���\���\����
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    struct S_Matrix4x4
    {
        /* �萔 */
        static const uint8_t s_ELEMENT_NUMBER = 16;                                                                 ///< @brief �v�f��
        static const T s_ORTHOGRAPHIC_2D_NEAR;                                                                      ///< @brief 2D�p�̐����e�̎ˉe�s����쐬���̎��_����ł��߂��N���b�v��
        static const T s_ORTHOGRAPHIC_2D_FAR;                                                                       ///< @brief 2D�p�̐����e�̎ˉe�s����쐬���̎��_����ł������N���b�v��
        static const S_Matrix4x4 s_ZERO;                                                                            ///< @brief �[���s��
        static const S_Matrix4x4 s_IDENTITY;                                                                        ///< @brief �P�ʍs��

        /* �����o�ϐ� */
        union
        {
            T a_[s_ELEMENT_NUMBER];                                                                                 ///< @brief 16�̗v�f�����z��
            T a4x4_[4][4];                                                                                          ///< @brief 4 * 4�̓񎟌��z��

            /// @brief �s��̊e�v�f
            struct
            {
                T a11_, a12_, a13_, a14_;
                T a21_, a22_, a23_, a24_;
                T a31_, a32_, a33_, a34_;
                T a41_, a42_, a43_, a44_;
            };
        };

        /* �����o�֐� */
        S_Matrix4x4();                                                                                              // �R���X�g���N�^
        S_Matrix4x4(T value);                                                                                       // �R���X�g���N�^
        S_Matrix4x4(T a11, T a12, T a13, T a14,                                                                     // �R���X�g���N�^
                    T a21, T a22, T a23, T a24,
                    T a31, T a32, T a33, T a34,
                    T a41, T a42, T a43, T a44);
        explicit S_Matrix4x4(const T a[s_ELEMENT_NUMBER]);                                                          // �R���X�g���N�^
        S_Matrix4x4(const S_Matrix3x3<T>& rMatrix);                                                                 // �R���X�g���N�^
        S_Matrix4x4(const S_Matrix4x4& rOther) = default;                                                           // �R�s�[�R���X�g���N�^
        ~S_Matrix4x4();                                                                                             // �f�X�g���N�^
        void Zero();                                                                                                // �[���s��
        void Identity();                                                                                            // �P�ʍs��
        void Transpose();                                                                                           // �]�u�s��
        void Invert();                                                                                              // �t�s��
        S_Matrix4x4 GetTranspose() const;                                                                           // �]�u�s����擾
        S_Matrix4x4 GetInvert() const;                                                                              // �t�s����擾
        S_Vector3<T> GetTranslationComponent() const;                                                               // ���s�ړ��������擾
        S_Vector3<T> GetScalingComponent() const;                                                                   // �g�k�������擾
        S_Vector3<T> GetLocalAxisX() const;                                                                         // ���[�J�����W��X�����擾
        S_Vector3<T> GetLocalAxisY() const;                                                                         // ���[�J�����W��Y�����擾
        S_Vector3<T> GetLocalAxisZ() const;                                                                         // ���[�J�����W��Z�����擾
        S_Vector4<T> GetRow(int32_t index = 0) const;                                                               // �s���擾
        S_Vector4<T> GetColumn(int32_t index = 0) const;                                                            // ����擾
        std::string GetConvertToString() const;                                                                     // �s��𕶎���֕ϊ����Ď擾
        void SetRow(const S_Vector4<T>& rRow, int32_t index = 0);                                                   // �s��ݒ�
        void SetColumn(const S_Vector4<T>& rColumn, int32_t index = 0);                                             // ���ݒ�
        
        /* �ÓI�����o�֐� */
        static S_Matrix4x4 s_CreateRotationX(T angle);                                                              // X�������]�s����쐬
        static S_Matrix4x4 s_CreateRotationY(T angle);                                                              // Y�������]�s����쐬
        static S_Matrix4x4 s_CreateRotationZ(T angle);                                                              // Z�������]�s����쐬
        static S_Matrix4x4 s_CreateRotationAxis(const S_Vector3<T>& rAxis, T angle);                                // �C�ӎ������]�s����쐬
        static S_Matrix4x4 s_CreateRotationYawPitchRoll(T pitch,                                                    // 3���̉�]�𔽉f������]�s����쐬
                                                        T yaw,
                                                        T roll);
        static S_Matrix4x4 s_CreateRotationYawPitchRoll(const S_Vector3<T>& rRotation);                             // 3���̉�]�𔽉f������]�s����쐬
        static S_Matrix4x4 s_CreateScaling(T scalingRateX, T scalingRateY, T scalingRateZ);                         // �g�k�s����쐬
        static S_Matrix4x4 s_CreateScaling(const S_Vector3<T>& rScalingRate);                                       // �g�k�s����쐬
        static S_Matrix4x4 s_CreateTranslation(T movementX,                                                         // ���s�ړ��s����쐬
                                               T movementY,
                                               T movementZ);
        static S_Matrix4x4 s_CreateTranslation(const S_Vector3<T>& rMovement);                                      // ���s�ړ��s����쐬
        static S_Matrix4x4 s_CreateTRS(const S_Vector3<T>& rMovement,                                               // �g�k�E��]�E���s�ړ����|�����킹���s����쐬 
                                       const S_Vector3<T>& rRotation,
                                       const S_Vector3<T>& rScalingRate);
        static S_Matrix4x4 s_CreateLookAt(const S_Vector3<T>& rEyePoint,                                            // �r���[�s����쐬
                                          const S_Vector3<T>& rTargetPoint,
                                          const S_Vector3<T>& rUpVector);
        static S_Matrix4x4 s_CreatePerspectiveProjection(T fieldOfViewY,                                            // �������e�̎ˉe�s����쐬
                                                         T aspectRatio,
                                                         T nearClippingPlane,
                                                         T farClippingPlane);
        static S_Matrix4x4 s_CreateOrthographicProjection(T clipSpaceLeft,                                          // �����e�̎ˉe�s����쐬
                                                          T clipSpaceRight,
                                                          T clipSpaceBottom,
                                                          T clipSpaceTop,
                                                          T nearClippingPlane = s_ORTHOGRAPHIC_2D_NEAR,
                                                          T farClippingPlane = s_ORTHOGRAPHIC_2D_FAR);
        static S_Matrix4x4 s_ConvertMatrix3x3ToMatrix4x4(const S_Matrix3x3<T>& rMatrix);                            // 3 * 3�s�񂩂�4 * 4�̍s��֕ϊ����A�擾
        static S_Matrix4x4 s_ConvertQuaternionToMatrix4x4(const S_Quaternion<T>& rQuaternion);                      // �N�H�[�^�j�I������4 * 4�̍s��֕ϊ����A�擾
        static S_Matrix4x4 s_CreateViewport(T windowWidth, T windowHeight);                                         // �r���[�|�[�g�s����쐬 
        static S_Matrix4x4 s_SlerpRotation(const S_Matrix4x4& rStartMatrix,                                         // ��]�s������ʐ��`���
                                           const S_Matrix4x4& rEndMatix,
                                           T coefficient);

        /* S_Matrix4x4�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
        const S_Matrix4x4 operator+(const S_Matrix4x4& rAnother) const;                                             // +���Z�q�̃I�[�o�[���[�h
        const S_Matrix4x4 operator-(const S_Matrix4x4& rAnother) const;                                             // -���Z�q�̃I�[�o�[���[�h
        const S_Matrix4x4 operator*(const S_Matrix4x4& rAnother) const;                                             // *���Z�q�̃I�[�o�[���[�h
        const S_Matrix4x4& operator+=(const S_Matrix4x4& rAnother);                                                 // +=���Z�q�̃I�[�o�[���[�h
        const S_Matrix4x4& operator-=(const S_Matrix4x4& rAnother);                                                 // -=���Z�q�̃I�[�o�[���[�h
        const S_Matrix4x4& operator*=(const S_Matrix4x4& rAnother);                                                 // *=���Z�q�̃I�[�o�[���[�h
        bool operator==(const S_Matrix4x4& rAnother) const;                                                         // ==���Z�q�̃I�[�o�[���[�h
        bool operator!=(const S_Matrix4x4& rAnother) const;                                                         // !=���Z�q�̃I�[�o�[���[�h

        /* S_Vector4�Ƃ̉��Z�q�̃I�[�o�[���[�h */
        const S_Vector4<T> operator*(const S_Vector4<T>& rVector) const;                                            // *���Z�q�̃I�[�o�[���[�h

        /* �L���X�g���Z�q�̃I�[�o�[���[�h */
        operator S_Matrix3x3<T>() const;                                                                            // S_Matrix3x3�^�ւ̃L���X�g
        operator std::string() const;                                                                               // string�^�ւ̃L���X�g
    };

    /* �ʖ� */
    using Matrix4x4 = S_Matrix4x4<>;                                                                                // Matrix4x4�^
};