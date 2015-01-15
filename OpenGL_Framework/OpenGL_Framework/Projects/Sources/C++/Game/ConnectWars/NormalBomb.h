/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "BaseBomb.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"


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
    //! @brief �m�[�}���{��
    //! @brief �ʏ�̃{��
    //!
    //-------------------------------------------------------------
    class C_NormalBomb : public C_BaseBomb
    {
    public:
        C_NormalBomb(const std::string& rId, int32_t type);         // �R���X�g���N�^
        ~C_NormalBomb() override;                                   // �f�X�g���N�^    
    private:
        int32_t stayFrame_ = 60;                                    ///< @brief �{���̎c��t���[����
        Timer::C_FrameCounter frameCounter_;                        ///< @brief �t���[���J�E���^�[

        void DoUpdate() override;                                   // ����J�̍X�V����
    };
}