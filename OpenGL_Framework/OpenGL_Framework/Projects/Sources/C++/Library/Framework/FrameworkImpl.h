/* �w�b�_�t�@�C�� */
#include "Framework.h"
#include "../Window/Window/BaseWindow.h"


//-------------------------------------------------------------
//!
//! @brief �t���[�����[�N
//! @brief �t���[�����[�N�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Framework
{
    //-------------------------------------------------------------
    //!
    //! @brief �t���[�����[�N�C���v�������g
    //! @brief �t���[�����[�N�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_Framework::C_FrameworkImpl
    {
    public:
        explicit C_FrameworkImpl(C_Framework* pGame);                       // �R���X�g���N�^
        ~C_FrameworkImpl();                                                 // �f�X�g���N�^

        C_Framework* GetGame() const;                                       // �Q�[�����擾
    private:
        C_Framework* pGame_ = nullptr;                                      ///< @brief �Q�[��
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_Framework::C_FrameworkImpl::C_FrameworkImpl(C_Framework* pGame) :

        // �Q�[��
        pGame_(pGame)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_Framework::C_FrameworkImpl::~C_FrameworkImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �Q�[�����擾
     *  @param  �Ȃ�
     *  @return �Q�[��
     *
     ****************************************************************/
    C_Framework* C_Framework::C_FrameworkImpl::GetGame() const
    {
        return pGame_;
    }
}