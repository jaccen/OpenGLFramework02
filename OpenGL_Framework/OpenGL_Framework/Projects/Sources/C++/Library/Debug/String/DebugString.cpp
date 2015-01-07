/* �w�b�_�t�@�C�� */
#include "DebugStringImpl.h"


//-------------------------------------------------------------
//!
//! @brief �f�o�b�O
//! @brief �f�o�b�O�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Debug
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_DebugString::C_DebugString() :

        // �������
        upImpl_(std::make_unique<C_DebugStringImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_DebugString::~C_DebugString()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �t�H���g�̃t�@�C���p�X
     *  @param  �t�H���g�̃T�C�Y
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_DebugString::Initialize(const std::string& rFontFilePath,
                                   int32_t fontSize)
    {
        if (upImpl_->Initialize(rFontFilePath, fontSize) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �f�o�b�N�t�H���g�̕`�揈�����s��
     *  @param  ������
     *  @param  ���W
     *  @param  �X�P�[��
     *  @param  ��
     *  @param  ��
     *  @param  ��
     *  @param  ��������
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_DebugString::Draw(const std::string& rString,
                             const Vector3& rPosition,
                             float scale,
                             uint8_t red,
                             uint8_t green,
                             uint8_t blue,
                             ecTypographicAlignment alignment)
    {
        upImpl_->Draw(rString, rPosition, scale, red, green, blue, alignment);
    }


    /*************************************************************//**
     *
     *  @brief  �f�o�b�N�t�H���g�̏I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_DebugString::Finalize()
    {
        upImpl_->Finalize();
    }
}