/* �w�b�_�t�@�C�� */
#include "FigureDrawerImpl.h"


//-------------------------------------------------------------
//!
//! @brief �t�B�M���A
//! @brief �}�`�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Figure
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_FigureDrawer::C_FigureDrawer() :

        // �������
        upImpl_(std::make_unique<C_FigureDrawerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_FigureDrawer::~C_FigureDrawer()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_FigureDrawer::Initialize()
    {
        if (upImpl_->Initialize() == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FigureDrawer::Finalize()
    {
        upImpl_->Finalize();
    }


        /*************************************************************//**
     *
     *  @brief  �_�̕`����s��
     *  @param  ���W
     *  @param  �F
     *  @param  �r���[�v���W�F�N�V�����s��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FigureDrawer::DrawPoint(const Vector3& rPosition,
                                   const Vector4& rColor,
                                   const Matrix4x4& rViewProjectionMatrix)
    {
        upImpl_->DrawPoint(rPosition, rColor, rViewProjectionMatrix);
    }


    /*************************************************************//**
     *
     *  @brief  ���̕`����s��
     *  @param  �J�n���W
     *  @param  �I�����W
     *  @param  �F
     *  @param  �r���[�v���W�F�N�V�����s��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FigureDrawer::DrawLine(const Vector3& rStartPosition,
                                  const Vector3& rEndPosition,
                                  const Vector4& rColor,
                                  const Matrix4x4& rViewProjectionMatrix)
    {
        upImpl_->DrawLine(rStartPosition, rEndPosition, rColor, rViewProjectionMatrix);
    }


    /*************************************************************//**
     *
     *  @brief  �_�̃T�C�Y��ݒ肷��
     *  @param  �_�̃T�C�Y
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FigureDrawer::SetPointSize(float pointSize)
    {
        upImpl_->SetPointSize(pointSize);
    }
}