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
        virtual void Add(int32_t power);                        // �p���[��������
        virtual int32_t GetPower() const;                       // �p���[���擾
        virtual void SetPower(int32_t power);                   // �p���[��ݒ�
    protected:
        int32_t power_ = 0;                                     ///< @brief �p���[
    };
}