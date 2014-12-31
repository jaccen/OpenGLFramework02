/* �w�b�_�t�@�C�� */
#include "Fuzzy.h"
#include "../Define/MathDefine.h"


//-------------------------------------------------------------
///
/// @brief �}�X
/// @brief ���w�֘A�̖��O���
///
//-------------------------------------------------------------
namespace Math
{
    //-------------------------------------------------------------
    //!
    //! @brief �t�@�W�[
    //! @brief �t�@�W�[�_���֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace Fuzzy
    {

 #pragma region C_Membership�N���X


        /*************************************************************//**
         *
         *  @brief  �X�Ό^�Ń����o�V�b�v�x�����߂�
         *  @param  �l
         *  @param  �J�n�l
         *  @param  �I���l
         *  @param  �w�b�W�֐�
         *  @return �����o�V�b�v�x( 0����1�܂ł̒l )
         *
         ****************************************************************/
        template<typename T>
        float C_Membership<T>::s_Grade(T value, T start, T end, HedgeFunction pHedge)
        {
            if (value <= start)
            {
                return 0.0f;
            }
            else if (value >= end)
            {
                return 1.0f;
            }

            float x = static_cast<float>(value);
            float x0 = static_cast<float>(start);
            float x1 = static_cast<float>(end);
            float reciprocalDifference = 1 / (x1 - x0);

            float result = (x * reciprocalDifference) - (x0 * reciprocalDifference);

            // �w�b�W�֐�
            if (pHedge) result = pHedge(result);

            return ;
        }


        /*************************************************************//**
         *
         *  @brief  �t�X�Ό^�Ń����o�V�b�v�x�����߂�
         *  @param  �l
         *  @param  �J�n�l
         *  @param  �I���l
         *  @param  �w�b�W�֐�
         *  @return �����o�V�b�v�x( 0����1�܂ł̒l )
         *
         ****************************************************************/
        template<typename T>
        float C_Membership<T>::s_ReverseGrade(T value, T start, T end, HedgeFunction pHedge)
        {
            if (value <= start)
            {
                return 1.0f;
            }
            else if (value >= end)
            {
                return 0.0f;
            }

            float x = static_cast<float>(value);
            float x0 = static_cast<float>(start);
            float x1 = static_cast<float>(end);
            float reciprocalDifference = 1 / (x1 - x0);

            float result = (-x * reciprocalDifference) + (x1 * reciprocalDifference);

            // �w�b�W�֐�
            if (pHedge) result = pHedge(result);

            return (-x * reciprocalDifference) + (x1 * reciprocalDifference);
        }


        /*************************************************************//**
         *
         *  @brief  �O�p�`�^�Ń����o�V�b�v�x�����߂�
         *  @param  �l
         *  @param  �J�n�l
         *  @param  ���_
         *  @param  �I���l
         *  @param  �w�b�W�֐�
         *  @return �����o�V�b�v�x( 0����1�܂ł̒l )
         *
         ****************************************************************/
        template<typename T>
        float C_Membership<T>::s_Triangle(T value,
                                          T start,
                                          T top,
                                          T end,
                                          HedgeFunction pHedge)
        {
            float result = 0.0f;
            
            if (value == top)
            {
                result = 1.0f;
            }
            else if (value > start && value < top)
            {
                float x = static_cast<float>(value);
                float x0 = static_cast<float>(start);
                float x1 = static_cast<float>(top);
                float reciprocalDifference = 1 / (x1 - x0);

                result = (x * reciprocalDifference) - (x0 * reciprocalDifference);
            }
            else if (value > top && value < end)
            {
                float x = static_cast<float>(value);
                float x1 = static_cast<float>(top);
                float x2 = static_cast<float>(end);
                float reciprocalDifference = 1 / (x2 - x1);

                result = (-x * reciprocalDifference) + (x2 * reciprocalDifference);
            }

            // �w�b�W�֐�
            if (pHedge) result = pHedge(result);

            return result;
        }


        /*************************************************************//**
         *
         *  @brief  ��`�^�Ń����o�V�b�v�x�����߂�
         *  @param  �l
         *  @param  �����̊J�n�l
         *  @param  �㕔�̊J�n�l
         *  @param  �㕔�̏I���l
         *  @param  �����̏I���l
         *  @param  �w�b�W�֐�
         *  @return �����o�V�b�v�x( 0����1�܂ł̒l )
         *
         ****************************************************************/
        template<typename T>
        float C_Membership<T>::s_Trapezoid(T value,
                                           T bottomStart,
                                           T topStart,
                                           T topEnd,
                                           T bottomEnd,
                                           HedgeFunction pHedge)
        {
            float result = 0.0f;

            if (value >= topStart && value <= topEnd)
            {
                result = 1.0f;
            }
            else if (value > bottomStart && value < topStart)
            {
                float x = static_cast<float>(value);
                float x0 = static_cast<float>(bottomStart);
                float x1 = static_cast<float>(topStart);
                float reciprocalDifference = 1 / (x1 - x0);

                result = (x * reciprocalDifference) - (x0 * reciprocalDifference);
            }
            else if (value > topEnd && value < bottomEnd)
            {
                float x = static_cast<float>(value);
                float x2 = static_cast<float>(topEnd);
                float x3 = static_cast<float>(bottomEnd);
                float reciprocalDifference = 1 / (x3 - x2);

                result = (-x * reciprocalDifference) + (x3 * reciprocalDifference);
            }

            // �w�b�W�֐�
            if (pHedge) result = pHedge(result);

            return result;
        }


#pragma endregion


#pragma region C_Heage�N���X


        /*************************************************************//**
         *
         *  @brief  2����s��
         *  @param  �l
         *  @return 2�悵���l
         *
         ****************************************************************/
        float C_Heage::s_Very(float value)
        {
            return Square(value);
        }


        /*************************************************************//**
         *
         *  @brief  �����������߂�
         *  @param  �l
         *  @return �l�̕�����
         *
         ****************************************************************/
        float C_Heage::s_SomeWhat(float value)
        {
            return SquareRoot(value);
        }


#pragma endregion


#pragma region C_LogicalOperation�N���X


        /*************************************************************//**
         *
         *  @brief  �_���ς��s��
         *  @param  ��ڂ̒l
         *  @param  ��ڂ̒l
         *  @return �_���ς����l
         *
         ****************************************************************/
        float C_LogicalOperation::s_And(float lhs, float rhs)
        {
            return Minimize(lhs, rhs);
        }


        /*************************************************************//**
         *
         *  @brief  �_���a���s��
         *  @param  ��ڂ̒l
         *  @param  ��ڂ̒l
         *  @return �_���a�����l
         *
         ****************************************************************/
        float C_LogicalOperation::s_Or(float lhs, float rhs)
        {
            return Maximize(lhs, rhs);
        }


        /*************************************************************//**
         *
         *  @brief  �m���I�_���a���s��
         *  @param  ��ڂ̒l
         *  @param  ��ڂ̒l
         *  @return �m���I�_���a�����l
         *
         ****************************************************************/
        float C_LogicalOperation::s_ProbabilisticOr(float lhs, float rhs)
        {
            return (lhs + rhs) - (lhs * rhs);
        }


        /*************************************************************//**
         *
         *  @brief  �_���ے���s��
         *  @param  �l
         *  @return �_���ے肵���l
         *
         ****************************************************************/
        float C_LogicalOperation::s_Not(float value)
        {
            return 1.0f - value;
        }


#pragma endregion


#pragma region C_Defuzzify


        /*************************************************************//**
         *
         *  @brief  �����@���s��
         *  @param  �l
         *  @param  �d��
         *  @param  �v�f��
         *  @return �����@�����l
         *
         ****************************************************************/
        float C_Defuzzify::s_Height(float values[], float weights[], uint32_t elementCount)
        {
            float numerator = 0.0f, denominator = 0.0f;

            for (size_t i = 0; i < elementCount; ++i)
            {
                numerator += values[i] * weights[i];
                denominator += values[i];
            }

            return numerator / denominator;
        }


#pragma endregion


    }
}