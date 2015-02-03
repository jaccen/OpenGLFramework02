/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
//!
//! @brief �L�[�t���[��
//! @brief �L�[�t���[���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace KeyFrame
{
    /** ��Ԃ̎�� */
    enum class ecInterpolationType
    {
        CONSTANT,                                       ///< @brief ���
        LINEAR,                                         ///< @brief ���`���
        HERMITE,                                        ///< @brief �G���~�[�g���
    };


    //-------------------------------------------------------------
    //!
    //! @brief �L�[
    //! @brief �L�[��\���\����
    //!
    //-------------------------------------------------------------
    template<typename T>
    struct S_Key
    {
        ecInterpolationType interpolationType_;         ///< @brief ���
        int32_t frame_;                                 ///< @brief �t���[����
        T value_;                                       ///< @brief �l
        T tangent_;                                     ///< @brief �ڐ�
    };
}