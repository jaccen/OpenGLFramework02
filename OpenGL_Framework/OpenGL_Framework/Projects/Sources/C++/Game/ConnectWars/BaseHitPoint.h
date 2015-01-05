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
        C_BaseHitPoint(int32_t maxHitPoint);                        // �R���X�g���N�^
        virtual ~C_BaseHitPoint();                                  // �f�X�g���N�^
        virtual void Reset();                                       // ������Ԃփ��Z�b�g
        virtual void Add(int32_t hitPoint);                         // �q�b�g�|�C���g��������
        virtual bool CheckRemainHitPoint() const;                   // �q�b�g�|�C���g���c���Ă��邩�m�F
        virtual int32_t GetHitPoint() const;                        // �q�b�g�|�C���g���擾
        virtual int32_t GetMaxHitPoint() const;                     // �ő�q�b�g�|�C���g���擾
        virtual void SetHitPoint(int32_t hitPoint);                 // �q�b�g�|�C���g��ݒ�
        virtual void SetMaxHitPoint(int32_t maxHitPoint);           // �ő�q�b�g�|�C���g��ݒ�
    protected:
        int32_t hitPoint_ = 0;                                      ///< @brief �q�b�g�|�C���g
        int32_t maxHitPoint_ = 0;                                   ///< @brief �ő�q�b�g�|�C���g
    };
}