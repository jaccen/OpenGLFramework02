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
    //! @brief �V���b�g���W�b�N
    //! @brief �ˌ��̃��W�b�N�̃C���^�[�t�F�[�X
    //!
    //-------------------------------------------------------------
    class C_ShotLogic
    {
    public:
        C_ShotLogic(int32_t shotInterval);                  // �R���X�g���N�^
        virtual ~C_ShotLogic();                             // �f�X�g���N�^
        bool Process();                                     // ����
        void SetShotInterval(int32_t shotInterval);         // �ˌ��̊Ԋu��ݒ�
    protected:
        int32_t shotInterval_ = 1;                          ///< @brief �ˌ��̊Ԋu
    private:
        virtual bool DoProcess() = 0;                       // ����J�̏���
    };
}