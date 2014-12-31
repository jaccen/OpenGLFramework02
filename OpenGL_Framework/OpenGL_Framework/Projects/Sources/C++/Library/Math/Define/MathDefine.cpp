/* �w�b�_�t�@�C�� */
#include "MathDefine.h"


//-------------------------------------------------------------
///
/// @brief �}�X
/// @brief ���w�֘A�̖��O���
///
//-------------------------------------------------------------
namespace Math
{

    /*************************************************************//**
     *
     *  @brief  �x�����烉�W�A���l�ւ̕ϊ����s��
     *  @param  �p�x( �x�� )
     *  @return �p�x( ���W�A���l )
     *
     ****************************************************************/
    template<typename T>
    T ConvertDegreeToRadian(T degrees)
    {
        return degrees * static_cast<T>(s_ONE_RADIAN);
    }


    /*************************************************************//**
     *
     *  @brief  ���W�A���l����x���ւ̕ϊ����s��
     *  @param  �p�x( ���W�A���l )
     *  @return �p�x( �x�� )
     *
     ****************************************************************/
    template<typename T>
    T ConvertRadianToDegree(T radians)
    {
        return radians * static_cast<T>(s_STRAIGHT_DIVISION_PI);
    }


    /*************************************************************//**
     *
     *  @brief  �����������߂�
     *  @param  �l
     *  @return ������
     *
     ****************************************************************/
    template <typename T>
    T SquareRoot(T value)
    {
        assert(value >= static_cast<T>(0));

        T lastResult = value;
        T result = value / static_cast<T>(2);

        while (result != lastResult)
        {
            lastResult = result;
            result = (result + value / result) / static_cast<T>(2);
        }

        return result;
    }


    /*************************************************************//**
     *
     *  @brief  �]�ڂ����߂�
     *  @param  �p�x( ���W�A���l )
     *  @return �]��
     *
     ****************************************************************/
    template<typename T>
    T Cotangent(T radian)
    {
        return static_cast<T>(std::cos(static_cast<double>(radian)) / std::sin(static_cast<double>(radian)));
    }


    /*************************************************************//**
     *
     *  @brief  2�����ł̓��ς����߂�
     *  @param  ��ڂ�X���W
     *  @param  ��ڂ�Y���W
     *  @param  ��ڂ�X���W
     *  @param  ��ڂ�Y���W
     *  @return ����
     *
     ****************************************************************/
    template<typename T>
    T DotProduct2D(T x1, T y1, T x2, T y2)
    {
        return (x1 * x2) + (y1 * y2);
    }


    /*************************************************************//**
     *
     *  @brief  3�����ł̓��ς����߂�
     *  @param  ��ڂ�X���W
     *  @param  ��ڂ�Y���W
     *  @param  ��ڂ�Z���W
     *  @param  ��ڂ�X���W
     *  @param  ��ڂ�Y���W
     *  @param  ��ڂ�Z���W
     *  @return ����
     *
     ****************************************************************/
    template<typename T>
    T DotProduct3D(T x1, T y1, T z1, T x2, T y2, T z2)
    {
        return (x1 * x2) + (y1 * y2) + (z1 * z2);
    }


    /*************************************************************//**
     *
     *  @brief  2�����ł̊O�ς����߂�
     *  @param  ��ڂ�X���W
     *  @param  ��ڂ�Y���W
     *  @param  ��ڂ�X���W
     *  @param  ��ڂ�Y���W
     *  @return �O��
     *
     ****************************************************************/
    template<typename T>
    T CrossProduct2D(T x1, T y1, T x2, T y2)
    {
        return (x1 * y2) - (x2 * y1);
    }


    /*************************************************************//**
     *
     *  @brief  �ŏ��l�����s��
     *  @param  ��ڂ̒l
     *  @param  ��ڂ̒l
     *  @return �ŏ��l
     *
     ****************************************************************/
    template<typename T>
    T Minimize(T lhs, T rhs)
    {
        return (lhs < rhs) ? lhs : rhs;
    }


    /*************************************************************//**
     *
     *  @brief  �ő�l�����s��
     *  @param  ��ڂ̒l
     *  @param  ��ڂ̒l
     *  @return �ő�l
     *
     ****************************************************************/
    template<typename T>
    T Maximize(T lhs, T rhs)
    {
        return (lhs > rhs) ? lhs : rhs;
    }


    /*************************************************************//**
     *
     *  @brief  �l�̃N�����v���s��
     *  @param  �l
     *  @param  �ŏ��l
     *  @param  �ő�l
     *  @return �N�����v�����l
     *
     ****************************************************************/
    template<typename T>
    T Clamp(T value, T min, T max)
    {
        return value < min ? min : (value > max ? max : value);
    }


    /*************************************************************//**
     *
     *  @brief  �p�x��0�x����2�΂܂łɒ��߂���
     *  @param  �p�x( ���W�A���l )
     *  @return ���߂����p�x
     *
     ****************************************************************/
    template<typename T>
    T AdjustAngleFrom0ToPI2(T angle)
    {
        if (angle < static_cast<T>(0))
        {
            while (angle < 0) angle += static_cast<T>(s_PI2);
        }
        else
        {
            while (angle > s_PI2) angle -= static_cast<T>(s_PI2);
        }

        return angle;
    }


    /*************************************************************//**
     *
     *  @brief  �����s��
     *  @param  �l
     *  @return ��悵���l
     *
     ****************************************************************/
    template <typename T>
    T Square(T value)
    {
        return value * value;
    }


    /*************************************************************//**
     *
     *  @brief  �O����s��
     *  @param  �l
     *  @return �O�悵���l
     *
     ****************************************************************/
    template <typename T>
    T Cubic(T value)
    {
        return value * value * value;
    }


    /*************************************************************//**
     *
     *  @brief  2�̌��q�Ԃ̈ʒu�G�l���M�[�����߂�
     *  @param  �˗͋��x
     *  @param  ���͋��x
     *  @param  ����
     *  @param  �˗͌����W��
     *  @param  ���͌����W��
     *  @return �ʒu�G�l���M�[
     *
     ****************************************************************/
    template<typename T>
    T LennardJonesPotential(T repulsionStrength,
        T attractionStrength,
        T distance,
        T repulsionAttenuationCoefficient,
        T attractionAttenuationCoefficient)
    {
        return (repulsionStrength / std::pow(distance, repulsionAttenuationCoefficient))
            - (attractionStrength / std::pow(distance, attractionAttenuationCoefficient));
    }


    /*************************************************************//**
     *
     *  @brief  �V�O���C�h�֐�����l�����߂�
     *  @param  �l
     *  @param  �Q�C��
     *  @return 0����1�܂ł̒l
     *
     ****************************************************************/
    template<typename T>
    T Sigmoid(T x, T gain)
    {
        assert(gain);

        return static_cast<T>(1.0) / (static_cast<T>(1.0) + std::exp(-x * gain));
    }


    /*************************************************************//**
     *
     *  @brief  �ꎟ���K�E�V�A���֐�����l�����߂�
     *  @param  �l
     *  @param  �W���΍�( �� )
     *  @return 0����1�܂ł̒l
     *
     ****************************************************************/
    template<typename T>
    T OneDimensionalGaussian(T x, T standardDeviation)
    {
        const T ROOT_PI2 = static_cast<T>(2.506628274631);

        T leftSide = static_cast<T>(1.0) / (ROOT_PI2 * standardDeviation);
        T rightSide = std::exp(-Square(x) / (static_cast<T>(2.0) * Square(standardDeviation)));
        T result = leftSide * rightSide;

        return result;
    }


    /*************************************************************//**
     *
     *  @brief  �񎟌��K�E�V�A���֐�����l�����߂�
     *  @param  �l1
     *  @param  �l2
     *  @param  ���U( ��^2 )
     *  @return 0����1�܂ł̒l
     *
     ****************************************************************/
    template<typename T>
    T TwoDimensionsGaussian(T x, T y, T dispersion)
    {
        T leftSide = static_cast<T>(1.0) / (static_cast<T>(s_PI2) * dispersion);
        T rightSide = std::exp(-(Square(x) + Square(y)) / (static_cast<T>(2.0) * Square(dispersion)));
        T result = leftSide * rightSide;

        return result;
    }


#pragma region �����I�C���X�^���X��


    /* �x�����烉�W�A���l�֕ϊ� */
    template float ConvertDegreeToRadian(float);
    template double ConvertDegreeToRadian(double);


    /* ���W�A���l����x���֕ϊ� */
    template float ConvertRadianToDegree(float);
    template double ConvertRadianToDegree(double);


    /* ������ */
    template int32_t SquareRoot(int32_t);
    template float SquareRoot(float);
    template double SquareRoot(double);


    /* �]�� */
    template float Cotangent(float);
    template double Cotangent(double);


    /* 2D�̓��� */
    template float DotProduct2D(float, float, float, float);
    template double DotProduct2D(double, double, double, double);


    /* 3D�̓��� */
    template float DotProduct3D(float, float, float, float, float, float);
    template double DotProduct3D(double, double, double, double, double, double);


    /* 2D�̊O�� */
    template float CrossProduct2D(float, float, float, float);
    template double CrossProduct2D(double, double, double, double);


    /* �ŏ��l�𔻕� */
    template uint32_t Minimize(uint32_t, uint32_t);
    template int32_t Minimize(int32_t, int32_t);
    template float Minimize(float, float);
    template double Minimize(double, double);


    /* �ő�l�𔻕� */
    template uint32_t Maximize(uint32_t, uint32_t);
    template int32_t Maximize(int32_t, int32_t);
    template float Maximize(float, float);
    template double Maximize(double, double);


    /* �N�����v */
    template int32_t Clamp(int32_t, int32_t, int32_t);
    template float Clamp(float, float, float);
    template double Clamp(double, double, double);


    /* �p�x��0����2�΂܂łɒ��� */
    template float AdjustAngleFrom0ToPI2(float);
    template double AdjustAngleFrom0ToPI2(double);


    /* ��� */
    template int32_t Square(int32_t);
    template float Square(float);
    template double Square(double);


    /* �O�� */
    template int32_t Cubic(int32_t);
    template float Cubic(float);
    template double Cubic(double);


    /* ���i�[�h�E�W���[���Y�E�|�e���V���� */
    template float LennardJonesPotential(float, float, float, float, float);
    template double LennardJonesPotential(double, double, double, double, double);


    /* �V�O���C�h */
    template float Sigmoid(float, float);
    template double Sigmoid(double, double);


    /* 1�����K�E�V�A�� */
    template float OneDimensionalGaussian(float, float);
    template double OneDimensionalGaussian(double, double);


    /* 2�����K�E�V�A�� */
    template float TwoDimensionsGaussian(float, float, float);
    template double TwoDimensionsGaussian(double, double, double);


#pragma endregion

}