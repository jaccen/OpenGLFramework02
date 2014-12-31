/* �w�b�_�t�@�C�� */
#include "Easing.h"
#include "../Define/MathDefine.h"


//-------------------------------------------------------------
///
/// @brief �}�X
/// @brief ���w�֘A�̖��O���
///
//-------------------------------------------------------------
namespace Math
{

#pragma region �ÓI�����o�ϐ��̏�����


    /* �f�t�H���g�̈��� */
    template<typename T>
    const T C_Easing<T>::s_DEFAULT_STRESS = static_cast<T>(1.70158);


#pragma endregion


    /*************************************************************//**
     *
     *  @brief  ���`( �ꎟ )��Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_Linear(T start, T end, T coefficient)
    {
        return (end - start) * coefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���̓񎟕�Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInQuadratic(T start,
                                     T end,
                                     T coefficient)
    {
        T calculateCoefficient = Square(coefficient);
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�A�E�g�̓񎟕�Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutQuadratic(T start,
                                      T end,
                                      T coefficient)
    {
        T calculateCoefficient = coefficient * (coefficient - static_cast<T>(2));
        return -(end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���E�A�E�g�̓񎟕�Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutQuadratic(T start,
                                        T end,
                                        T coefficient)
    {
        // ��ԌW����2�{
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // �v�Z��̕�ԌW��
        T calculateCoefficient = static_cast<T>(0);

        // ��ԌW����2�{��1����( ��ԌW����0.5���� )�̏ꍇ
        if (twiceCoefficient < static_cast<T>(1))
        {
            // ��ԌW�����v�Z���A�⊮����
            calculateCoefficient = Square(twiceCoefficient);
            return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
        }

        // ��ԌW����2�{��1���炷( ��ԌW����0 �` 1�ɍ��킹�� )
        --twiceCoefficient;

        // ��ԌW�����v�Z���A�⊮����
        calculateCoefficient = (twiceCoefficient * (twiceCoefficient - static_cast<T>(2))) - static_cast<T>(1);
        return -(end - start) / static_cast<T>(2) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���̎O����Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInCubic(T start,
                                 T end,
                                 T coefficient)
    {
        T calculateCoefficient = Cubic(coefficient);
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�A�E�g�̎O����Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutCubic(T start,
                                  T end,
                                  T coefficient)
    {
        // �W����1���炷
        --coefficient;

        // ��ԌW�����v�Z���A��Ԃ���
        T calculateCoefficient = Cubic(coefficient) + static_cast<T>(1);
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���E�A�E�g�̎O����Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutCubic(T start,
                                    T end,
                                    T coefficient)
    {
        // ��ԌW����2�{
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // �v�Z��̕�ԌW��
        T calculateCoefficient = static_cast<T>(0);

        // ��ԌW����2�{��1����( ��ԌW����0.5���� )�̏ꍇ
        if (twiceCoefficient < static_cast<T>(1))
        {
            // ��ԌW�����v�Z���A�⊮����
            calculateCoefficient = Cubic(twiceCoefficient);
            return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
        }

        // ��ԌW����2�{��2���炷( ��ԌW����-1 �` 0�ɍ��킹�� )
        twiceCoefficient -= static_cast<T>(2);

        // ��ԌW�����v�Z���A�⊮����
        calculateCoefficient = Cubic(twiceCoefficient) + static_cast<T>(2);
        return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���̎l����Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInQuartic(T start,
                                   T end,
                                   T coefficient)
    {
        T calculateCoefficient = std::pow(coefficient, static_cast<T>(4));
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�A�E�g�̎l����Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutQuartic(T start,
                                    T end,
                                    T coefficient)
    {
        // �W����1���炷
        --coefficient;

        // ��ԌW�����v�Z���A�⊮����
        T calculateCoefficient = std::pow(coefficient, static_cast<T>(4)) - static_cast<T>(1);
        return -(end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���E�A�E�g�̎l����Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutQuartic(T start,
                                      T end,
                                      T coefficient)
    {
        // ��ԌW����2�{
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // �v�Z��̕�ԌW��
        T calculateCoefficient = static_cast<T>(0);

        // ��ԌW����2�{��1����( ��ԌW����0.5���� )�̏ꍇ
        if (twiceCoefficient < static_cast<T>(1))
        {
            // ��ԌW�����v�Z���A�⊮����
            calculateCoefficient = std::pow(twiceCoefficient, static_cast<T>(4));
            return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
        }

        // ��ԌW����2�{��2���炷( ��ԌW����-1 �` 0�ɍ��킹�� )
        twiceCoefficient -= static_cast<T>(2);

        // ��ԌW�����v�Z���A�⊮����
        calculateCoefficient = std::pow(twiceCoefficient, static_cast<T>(4)) - static_cast<T>(2);
        return -(end - start) / static_cast<T>(2) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���̌܎���Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInQuintic(T start,
                                   T end,
                                   T coefficient)
    {
        T calculateCoefficient = std::pow(coefficient, static_cast<T>(5));
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�A�E�g�̌܎���Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutQuintic(T start,
                                    T end,
                                    T coefficient)
    {
        // �W����1���炷
        --coefficient;

        // ��ԌW�����v�Z���A�⊮����
        T calculateCoefficient = std::pow(coefficient, static_cast<T>(5)) + static_cast<T>(1);
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���E�A�E�g�̌܎���Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutQuintic(T start,
                                      T end,
                                      T coefficient)
    {
        // ��ԌW����2�{
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // �v�Z��̕�ԌW��
        T calculateCoefficient = static_cast<T>(0);

        // ��ԌW����2�{��1����( ��ԌW����0.5���� )�̏ꍇ
        if (twiceCoefficient < static_cast<T>(1))
        {
            // ��ԌW�����v�Z���A�⊮����
            calculateCoefficient = std::pow(twiceCoefficient, static_cast<T>(5));
            return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
        }

        // ��ԌW����2�{��2���炷( ��ԌW����-1 �` 0�ɍ��킹�� )
        twiceCoefficient -= static_cast<T>(2);

        // ��ԌW�����v�Z���A�⊮����
        calculateCoefficient = std::pow(twiceCoefficient, static_cast<T>(5)) + static_cast<T>(2);
        return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���̃T�C����Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInSine(T start,
                                T end,
                                T coefficient)
    {
        T calculateCoefficient = std::cos(static_cast<T>(s_PI_DIVISION2)* coefficient);
        return -(end - start) * calculateCoefficient + end;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�A�E�g�̃T�C����Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutSine(T start,
                                 T end,
                                 T coefficient)
    {
        T calculateCoefficient = std::sin(static_cast<T>(s_PI_DIVISION2)* coefficient);
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���E�A�E�g�̃T�C����Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutSine(T start,
                                   T end,
                                   T coefficient)
    {
        T calculateCoefficient = std::cos(static_cast<T>(s_PI)* coefficient) - static_cast<T>(1);
        return -(end - start) / static_cast<T>(2) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���̎w����Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInExponential(T start,
                                       T end,
                                       T coefficient)
    {
        T calculateCoefficient = std::pow(static_cast<T>(2), static_cast<T>(10) * (coefficient - static_cast<T>(1)));
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�A�E�g�̎w����Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutExponential(T start,
                                        T end,
                                        T coefficient)
    {
        T calculateCoefficient = -(std::pow(static_cast<T>(2), static_cast<T>(-10) * coefficient)) + static_cast<T>(1);
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���E�A�E�g�̎w����Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutExponential(T start,
                                          T end,
                                          T coefficient)
    {
        // ��ԌW����2�{
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // �v�Z��̕�ԌW��
        T calculateCoefficient = static_cast<T>(0);

        // ��ԌW����2�{��1����( ��ԌW����0.5���� )�̏ꍇ
        if (twiceCoefficient < static_cast<T>(1))
        {
            // ��ԌW�����v�Z���A�⊮����
            calculateCoefficient = std::pow(static_cast<T>(2), static_cast<T>(10) * (twiceCoefficient - static_cast<T>(1)));
            return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
        }

        // ��ԌW����2�{��1���炷( ��ԌW����0 �` 1�ɍ��킹�� )
        --twiceCoefficient;

        // ��ԌW�����v�Z���A�⊮����
        calculateCoefficient = -(std::pow(static_cast<T>(2), static_cast<T>(-10) * twiceCoefficient)) + static_cast<T>(2);
        return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���̉~�ʕ�Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInCircular(T start,
                                    T end,
                                    T coefficient)
    {
        T calculateCoefficient = std::sqrt(static_cast<T>(1) - Square(coefficient)) - static_cast<T>(1);
        return -(end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�A�E�g�̉~�ʕ�Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutCircular(T start,
                                     T end,
                                     T coefficient)
    {
        // �␳�W����1���炷
        --coefficient;

        // ��ԌW�����v�Z���A�⊮����
        T calculateCoefficient = std::sqrt(static_cast<T>(1) - Square(coefficient));
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���E�A�E�g�̉~�ʕ�Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutCircular(T start,
                                       T end,
                                       T coefficient)
    {
        // ��ԌW����2�{
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // �v�Z��̕�ԌW��
        T calculateCoefficient = static_cast<T>(0);

        // ��ԌW����2�{��1����( ��ԌW����0.5���� )�̏ꍇ
        if (twiceCoefficient < static_cast<T>(1))
        {
            // ��ԌW�����v�Z���A�⊮����
            calculateCoefficient = std::sqrt(static_cast<T>(1) - Square(twiceCoefficient)) - static_cast<T>(1);
            return -(end - start) / static_cast<T>(2) * calculateCoefficient + start;
        }

        // ��ԌW����2�{��2���炷( ��ԌW����-1 �` 0�ɍ��킹�� )
        twiceCoefficient -= static_cast<T>(2);

        // ��ԌW�����v�Z���A�⊮����
        calculateCoefficient = std::sqrt(static_cast<T>(1) - Square(twiceCoefficient)) + static_cast<T>(1);
        return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���̃o�b�N��Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @param  ����
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInBack(T start,
                                T end,
                                T coefficient,
                                T stress)
    {
        T calculateCoefficient = Square(coefficient) * ((stress + static_cast<T>(1)) * coefficient - stress);
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�A�E�g�̃o�b�N��Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @param  ����
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutBack(T start,
                                 T end,
                                 T coefficient,
                                 T stress)
    {
        // ��ԌW����1���炷
        --coefficient;

        // ��ԌW�����v�Z���A�⊮����
        T calculateCoefficient = (Square(coefficient) * ((stress + static_cast<T>(1)) * coefficient + stress)) + static_cast<T>(1);
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���E�A�E�g�̃o�b�N��Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @param  ����
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutBack(T start,
                                   T end,
                                   T coefficient,
                                   T stress)
    {
        // ��ԌW����2�{
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // �v�Z��̕�ԌW��
        T calculateCoefficient = static_cast<T>(0);

        // ���͂��኱���߂�
        stress *= static_cast<T>(1.525);

        // ��ԌW����2�{��1����( ��ԌW����0.5���� )�̏ꍇ
        if (twiceCoefficient < static_cast<T>(1))
        {
            // ��ԌW�����v�Z���A�⊮����
            calculateCoefficient = Square(twiceCoefficient) * ((stress + static_cast<T>(1)) * twiceCoefficient - stress);
            return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
        }

        // ��ԌW����2�{��2���炷( ��ԌW����-1 �` 0�ɍ��킹�� )
        twiceCoefficient -= static_cast<T>(2);

        // ��ԌW�����v�Z���A�⊮����
        calculateCoefficient = (Square(twiceCoefficient) * ((stress + static_cast<T>(1)) * twiceCoefficient + stress)) + static_cast<T>(2);
        return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���̃o�E���X��Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInBounce(T start,
                                  T end,
                                  T coefficient)
    {
        // ����
        T difference = end - start;

        // �C�[�Y�A�E�g�̃o�E���h��Ԃ�p���ĕ�Ԃ���
        return difference - s_EaseOutBounce(static_cast<T>(0), difference, static_cast<T>(1) - coefficient) + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�A�E�g�̃o�E���X��Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutBounce(T start,
                                   T end,
                                   T coefficient)
    {
        // 2��2.75��ƕ���( �o�E���h�炵�����o�����߂ɗp����̒萔 )
        const T POWER2_2DOT75 = static_cast<T>(7.5625);
        const T DENOMINATOR = static_cast<T>(2.75);

        // ����
        T difference = end - start;

        // �v�Z��̕�ԌW��
        T calculateCoefficient = static_cast<T>(0);

        /* ��ԌW������36%���� */
        if (coefficient < static_cast<T>(1) / DENOMINATOR)
        {
            // ��ԌW�����v�Z���A�⊮����
            calculateCoefficient = POWER2_2DOT75 * Square(coefficient);
            return difference * calculateCoefficient + start;
        }
        /* ��ԌW������72%���� */
        else if (coefficient < static_cast<T>(2) / DENOMINATOR)
        {
            // �o�E���h�ɉ����ĕ�ԌW�������炷
            coefficient -= static_cast<T>(1.5) / DENOMINATOR;

            // ��ԌW�����v�Z���A�⊮����
            calculateCoefficient = (POWER2_2DOT75 * Square(coefficient)) + static_cast<T>(0.75);
            return difference * calculateCoefficient + start;
        }
        /* ��ԌW������90%���� */
        else if (coefficient < static_cast<T>(2.5) / DENOMINATOR)
        {
            // �o�E���h�ɉ����ĕ�ԌW�������炷
            coefficient -= static_cast<T>(2.25) / DENOMINATOR;

            // ��ԌW�����v�Z���A�⊮����
            calculateCoefficient = (POWER2_2DOT75 * Square(coefficient)) + static_cast<T>(0.9375);
            return difference * calculateCoefficient + start;
        }

        // �o�E���h�ɉ����ĕ�ԌW�������炷
        coefficient -= static_cast<T>(2.625) / DENOMINATOR;

        // ��ԌW�����v�Z���A�⊮����
        calculateCoefficient = (POWER2_2DOT75 * Square(coefficient)) + static_cast<T>(0.984375);
        return difference * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���E�A�E�g�̃o�E���X��Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutBounce(T start,
                                     T end,
                                     T coefficient)
    {
        // ��ԌW����2�{
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // ����
        T difference = end - start;

        // ��ԌW����2�{��1����( ��ԌW����0.5���� )�̏ꍇ�A�C�[�Y�C����p���ĕ�Ԃ���
        if (twiceCoefficient < static_cast<T>(1)) return s_EaseInBounce(static_cast<T>(0), difference, twiceCoefficient) * static_cast<T>(0.5) + start;

        // �C�[�Y�A�E�g��p���ĕ⊮����
        return (s_EaseOutBounce(static_cast<T>(0), difference, twiceCoefficient - static_cast<T>(1)) + difference) * static_cast<T>(0.5) + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���̃C���X�e�B�b�N��Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInElastic(T start,
                                   T end,
                                   T coefficient)
    {
        // ��ԌW����0�̏ꍇ�͊J�n�l��Ԃ�
        if (coefficient == static_cast<T>(0)) return start;

        // ��ԌW����1�̏ꍇ�͏I���l��Ԃ�
        if (coefficient == static_cast<T>(1)) return end;

        // ��ԌW����1���炷
        --coefficient;

        // ��ԌW�����v�Z���A�⊮����
        T calculateCoefficient = (end - start) * std::pow(static_cast<T>(2), static_cast<T>(10) * (coefficient));
        return -(calculateCoefficient * std::sin((coefficient - static_cast<T>(0.075)) * static_cast<T>(s_PI2) / static_cast<T>(0.3))) + start;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�A�E�g�̃C���X�e�B�b�N��Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutElastic(T start,
                                    T end,
                                    T coefficient)
    {
        // ��ԌW����0�̏ꍇ�͊J�n�l��Ԃ�
        if (coefficient == static_cast<T>(0)) return start;

        // ��ԌW����1�̏ꍇ�͏I���l��Ԃ�
        if (coefficient == static_cast<T>(1)) return end;

        // ��ԌW�����v�Z���A�⊮����
        T calculateCoefficient = (end - start) * std::pow(static_cast<T>(2), static_cast<T>(-10) * (coefficient));
        return (calculateCoefficient * std::sin((coefficient - static_cast<T>(0.075)) * static_cast<T>(s_PI2) / static_cast<T>(0.3))) + end;
    }


    /*************************************************************//**
     *
     *  @brief  �C�[�Y�C���E�A�E�g�̃C���X�e�B�b�N��Ԃ��s��
     *  @param  �J�n�l
     *  @param  �I���l
     *  @param  ��ԌW��( 0 �` 1 )
     *  @return �J�n���̒l�ƏI�����̒l��⊮�����l
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutElastic(T start,
                                      T end,
                                      T coefficient)
    {
        // �v�Z��̕�ԌW��
        T calculateCoefficient = static_cast<T>(0);

        // ��ԌW����0�̏ꍇ�͊J�n�l��Ԃ�
        if (coefficient == static_cast<T>(0)) return start;

        // ��ԌW����1�̏ꍇ�͏I���l��Ԃ�
        if (coefficient == static_cast<T>(1)) return end;

        // ��ԌW����2�{
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // ��ԌW����2�{��1����( ��ԌW����0.5���� )�̏ꍇ
        if (twiceCoefficient < static_cast<T>(1))
        {
            // ��ԌW����2�{��1���炷( ��ԌW����-1 �` 0�ɍ��킹�� )
            --twiceCoefficient;

            // ��ԌW�����v�Z���A�⊮����
            calculateCoefficient = (end - start) * std::pow(static_cast<T>(2), static_cast<T>(10) * twiceCoefficient);
            return static_cast<T>(-0.5) * (calculateCoefficient * std::sin((twiceCoefficient - static_cast<T>(0.1125)) * static_cast<T>(s_PI2) / static_cast<T>(0.45))) + start;
        }

        // ��ԌW����2�{��1���炷( ��ԌW����0 �` 1�ɍ��킹�� )
        --twiceCoefficient;

        // ��ԌW�����v�Z���A�⊮����
        calculateCoefficient = (end - start) * std::pow(static_cast<T>(2), static_cast<T>(-10) * (twiceCoefficient));
        return calculateCoefficient * std::sin((twiceCoefficient - static_cast<T>(0.1125)) * static_cast<T>(s_PI2) / static_cast<T>(0.45)) * static_cast<T>(0.5) + end;
    }

    /* �����I�C���X�^���X�� */
    template class C_Easing<float>;
    template class C_Easing<double>;

}