/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief �x�[�X�p���[
    //! @brief �p���[�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BasePower
    {
    public:
        C_BasePower(int32_t power);                             // �R���X�g���N�^
        virtual ~C_BasePower();                                 // �f�X�g���N�^
        virtual void Add(int32_t power);                        // �l�𑫂�
        virtual void Subtract(int32_t power);                   // �l������
        virtual int32_t GetValue() const;                       // �l���擾
        virtual void SetValue(int32_t power);                   // �l��ݒ�
    protected:
        int32_t value_ = 0;                                     ///< @brief �l
    };
}