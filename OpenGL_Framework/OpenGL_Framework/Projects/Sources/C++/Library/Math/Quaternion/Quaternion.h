/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Vector/Vector3.h"


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
    struct S_Matrix3x3;

    template<typename T>
    struct S_Matrix4x4;

    //-------------------------------------------------------------
    //!
    //! @brief �N�H�[�^�j�I��
    //! @brief �N�H�[�^�j�I����\���\����
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    struct S_Quaternion
    {
        /* �萔 */
        static const S_Quaternion s_IDENTITY;                                                               ///< @brief �P�ʃN�H�[�^�j�I��

        /* �����o�ϐ� */
        union
        {
            T a_[4];                                                                                        ///< brief 4�̗v�f�����z��

            struct
            {
                T t_;                                                                                       ///< @brief T����
                T x_;                                                                                       ///< @brief X����
                T y_;                                                                                       ///< @brief Y����
                T z_;                                                                                       ///< @brief Z����
            };

            struct
            {
                T t_;                                                                                       ///< @brief T����
                S_Vector3<T> xyz_;                                                                          ///< @brief X�EY�EZ����
            };
        };

        /* �����o�֐� */
        S_Quaternion();                                                                                     // �R���X�g���N�^
        explicit S_Quaternion(T value);                                                                     // �R���X�g���N�^
        S_Quaternion(T t, T x, T y, T z);                                                                   // �R���X�g���N�^
        S_Quaternion(T t, const S_Vector3<T>& rXYZ);                                                        // �R���X�g���N�^
        S_Quaternion(const S_Quaternion& rOther) = default;                                                 // �R�s�[�R���X�g���N�^
        ~S_Quaternion();                                                                                    // �f�X�g���N�^
        void Fill(T value);                                                                                 // �e���������̒l�ɕύX
        void Identity();                                                                                    // �P�ʃN�H�[�^�j�I����
        void Normalize();                                                                                   // ���K��
        void Invert();                                                                                      // �t�N�H�[�^�j�I����
        T GetLength() const;                                                                                // �������擾
        T GetLengthSquare() const;                                                                          // ������2����擾
        S_Quaternion GetNormalize() const;                                                                  // ���K�������N�H�[�^�j�I�����擾
        S_Quaternion GetInvert() const;                                                                     // �t�N�H�[�^�j�I�����擾
        T GetAngleFromXAxis() const;                                                                        // X������̊p�x���擾
        T GetAngleFromYAxis() const;                                                                        // Y������̊p�x���擾
        T GetAngleFromZAxis() const;                                                                        // Z������̊p�x���擾
        std::tuple<S_Vector3<T>, T> GetAxisAndAngle() const;                                                // ���Ɗp�x���擾
        std::string GetConvertToString() const;                                                             // �N�H�[�^�j�I���𕶎���ɕϊ����Ď擾

        /* �ÓI�����o�֐� */
        static T s_DotProduct(const S_Quaternion<T>& rLhs, const S_Quaternion<T>& rRhs);                    // ����
        static S_Quaternion s_CreateRotationAxis(const S_Vector3<T>& rAxis,                                 // �C�ӎ�����N�H�[�^�j�I�����쐬
                                                 T angle);
        static S_Quaternion s_CreateRotationPitchYawRoll(T pitch,                                           // 3���̉�]�𔽉f�����N�H�[�^�j�I�����쐬
                                                         T yaw,
                                                         T roll);
        static S_Quaternion s_CreateRotationPitchYawRoll(const S_Vector3<T>& rRotation);                    // 3���̉�]�𔽉f�����N�H�[�^�j�I�����쐬
        static S_Quaternion s_CreateLookRotation(const S_Vector3<T>& rDirection,                            // �C�ӂ̌����֌������߂̃N�H�[�^�j�I�����쐬
                                                 const S_Vector3<T>& rUpVector);
        static S_Quaternion s_CreateFromToRotation(const S_Vector3<T>& rFromDirection,                      // ������������։�]������N�H�[�^�j�I�����쐬 
                                                   const S_Vector3<T>& rToDirection);
        static S_Quaternion s_ConvertMatrix3x3ToQuaternion(const S_Matrix3x3<T>& rMatrix);                  // 3 * 3�̍s�񂩂�N�H�[�^�j�I���֕ϊ����Ď擾
        static S_Quaternion s_ConvertMatrix4x4ToQuaternion(const S_Matrix4x4<T>& rMatrix);                  // 4 * 4�̍s�񂩂�N�H�[�^�j�I���֕ϊ����Ď擾
        static S_Quaternion s_Lerp(const S_Quaternion& rStart,                                              // ���`���
                                   const S_Quaternion& rEnd,
                                   T coefficient);
        static S_Quaternion s_Slerp(const S_Quaternion& rStart,                                             // ���ʐ��`���
                                    const S_Quaternion& rEnd,
                                    T coefficient);

        /* S_Quaternion�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
        const S_Quaternion operator+(const S_Quaternion& rAnother) const;                                   // +���Z�q�̃I�[�o�[���[�h
        const S_Quaternion& operator+=(const S_Quaternion& rAnother);                                       // +=���Z�q�̃I�[�o�[���[�h
        const S_Quaternion operator-(const S_Quaternion& rAnother) const;                                   // -���Z�q�̃I�[�o�[���[�h
        const S_Quaternion& operator-=(const S_Quaternion& rAnother);                                       // -=���Z�q�̃I�[�o�[���[�h
        const S_Quaternion operator*(const S_Quaternion& rAnother) const;                                   // *���Z�q�̃I�[�o�[���[�h
        const S_Quaternion& operator*=(const S_Quaternion& rAnother);                                       // *=���Z�q�̃I�[�o�[���[�h
        bool operator==(const S_Quaternion& rAnother) const;                                                // ==���Z�q�̃I�[�o�[���[�h
        bool operator!=(const S_Quaternion& rAnother) const;                                                // !=���Z�q�̃I�[�o�[���[�h

        /* T�^�Ƃ̉��Z�q�̃I�[�o�[���[�h */
        const S_Quaternion operator*(T value) const;                                                        // *���Z�q�̃I�[�o�[���[�h
        const S_Quaternion& operator*=(T value);                                                            // *=���Z�q�̃I�[�o�[���[�h

        /* �L���X�g���Z�q�̃I�[�o�[���[�h */
        operator S_Vector3<T>() const;                                                                      // S_Vector3�^�ւ̃L���X�g
        operator std::string() const;                                                                       // string�^�ւ̃L���X�g

        #pragma region T�^�Ƃ̃t�����h���Z�q�̃I�[�o�[���[�h


        /*************************************************************//**
         *
         *  @brief  T�^�̒l�ƃN�H�[�^�j�I������Z����
         *  @param  T�^�̒l
         *  @param  �N�H�[�^�j�I��
         *  @return ��Z�����N�H�[�^�j�I��
         *
         ****************************************************************/
        friend const S_Quaternion operator*(T value,
                                            const S_Quaternion& rQuaternion)
        {
            return S_Quaternion(rQuaternion.t_ * value,
                                rQuaternion.x_ * value,
                                rQuaternion.y_ * value,
                                rQuaternion.z_ * value);
        }


        #pragma endregion
    };

    /* �ʖ� */
    using Quaternion = S_Quaternion<>;                                                                      // Quaternion�^
}
