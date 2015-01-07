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
    //! @brief �x�[�X�q�b�g�|�C���g
    //! @brief �q�b�g�|�C���g�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BaseHitPoint
    {
    public:
        C_BaseHitPoint(int32_t maxValue);                       // �R���X�g���N�^
        virtual ~C_BaseHitPoint();                              // �f�X�g���N�^
        virtual void Reset();                                   // ������Ԃփ��Z�b�g
        virtual void Add(int32_t value);                        // �l�𑫂�
        virtual void Subtract(int32_t value);                   // �l������
        virtual bool CheckRemainValue() const;                  // �l���c���Ă��邩�m�F
        virtual int32_t GetValue() const;                       // �l���擾
        virtual int32_t GetMaxValue() const;                    // �ő�l���擾
        virtual void SetValue(int32_t value);                   // �l��ݒ�
        virtual void SetMaxValue(int32_t maxValue);             // �ő�l��ݒ�
    protected:
        int32_t value_ = 0;                                     ///< @brief �l
        int32_t maxValue_ = 0;                                  ///< @brief �ő�l
    };
}