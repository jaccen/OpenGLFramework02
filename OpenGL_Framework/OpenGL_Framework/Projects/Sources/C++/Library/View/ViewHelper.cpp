/* �w�b�_�t�@�C�� */
#include "ViewHelper.h"
#include "../Figure/FigureDrawer.h"


//-------------------------------------------------------------
//!
//! @brief �r���[
//! @brief �r���[�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace View
{
    /*************************************************************//**
     *
     *  @brief  �O���b�h�̕`����s��
     *  @param  ���̔����̒���
     *  @param  ���̊Ԋu
     *  @param  ���̐�
     *  @param  ���̐F
     *  @param  �r���[�v���W�F�N�V�����s��
     *
     ****************************************************************/
    void C_ViewHelper::s_DrawGrid(float lineHelfLength,
                                  float lineInterval,
                                  uint32_t lineCount, 
                                  const Vector4& rLineColor,
                                  const Matrix4x4& rViewProjectionMatrix)
    {
        // �}�`�̕`��҂��擾
        auto pFigureDrawer = Figure::C_FigureDrawer::s_GetInstance();

        // ���̒[
        float lineSide = -lineInterval * static_cast<float>(lineCount / 2);

        Figure::Vector3 startPosition;
        Figure::Vector3 endPosition;

        for (size_t i = 0; i < lineCount; ++i)
        {
            // ����`��
            startPosition = Figure::Vector3(lineSide, 0.0f, lineHelfLength);
            endPosition = Figure::Vector3(lineSide, 0.0f, -lineHelfLength);
            pFigureDrawer->DrawLine(startPosition, endPosition, rLineColor, rViewProjectionMatrix);

            startPosition = Figure::Vector3(lineHelfLength, 0.0f, lineSide);
            endPosition = Figure::Vector3(-lineHelfLength, 0.0f, lineSide);
            pFigureDrawer->DrawLine(startPosition, endPosition, rLineColor, rViewProjectionMatrix);

            // ���̒[���Ԋu�����炷
            lineSide += lineInterval;
        }
    }

    /*************************************************************//**
     *
     *  @brief  ���̕`����s��
     *  @param  ���̒���
     *  @param  �r���[�v���W�F�N�V�����s��
     *
     ****************************************************************/
    void C_ViewHelper::s_DrawAxis(float lineLength,
                                  const Matrix4x4& rViewProjectionMatrix)
    {
        // �e���̐F
        Figure::Vector4 colorAxisX(1.0f, 0.0f, 0.0f, 1.0f);
        Figure::Vector4 colorAxisY(0.0f, 1.0f, 0.0f, 1.0f);
        Figure::Vector4 colorAxisZ(0.0f, 0.0f, 1.0f, 1.0f);

        // �}�`�̕`��҂��擾
        auto pFigureDrawer = Figure::C_FigureDrawer::s_GetInstance();

        // ���_
        Figure::Vector3 origin;

        // ����`��
        pFigureDrawer->DrawLine(origin, Figure::Vector3(lineLength, 0.0f, 0.0f), colorAxisX, rViewProjectionMatrix);
        pFigureDrawer->DrawLine(origin, Figure::Vector3(0.0f, lineLength, 0.0f), colorAxisY, rViewProjectionMatrix);
        pFigureDrawer->DrawLine(origin, Figure::Vector3(0.0f, 0.0f, lineLength), colorAxisZ, rViewProjectionMatrix);
    }
}