/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
///
/// @brief �}�X
/// @brief ���w�֘A�̖��O���
///
//-------------------------------------------------------------
namespace Math
{
    namespace
    {
        const double s_PI_DIVISION4 = 0.785398163397447;                ///< @brief �� / 4
        const double s_PI_DIVISION3 = 1.047197551196596;                ///< @brief �� / 3
        const double s_PI_DIVISION2 = 1.570796326794895;                ///< @brief �� / 2
        const double s_PI = 3.14159265358979;                           ///< @brief ��
        const double s_PI2 = 6.2831853071795;                           ///< @brief 2��
        const double s_ONE_DIVISION_PI = 0.31830988618379;              ///< @brief 1 / ��
        const double s_STRAIGHT_DIVISION_PI = 57.295779513082379;       ///< @brief 180 / ��
        const double s_ONE_RADIAN = 0.017453292519943;                  ///< @brief 1���W�A��( �� / 180 )
        const double s_ROOT2 = 1.414213562373095;                       ///< @brief ��2
        const double s_ROOT3 = 1.732050807568877;                       ///< @brief ��3
        const double s_EPSILON = 0.00001;                               ///< @brief �덷�l�������ɏ��̒l
    }

    /* �x�����烉�W�A���l�֕ϊ� */
    template<typename T>
    T ConvertDegreeToRadian(T degrees);

    // ���W�A���l����x���֕ϊ�
    template<typename T>
    T ConvertRadianToDegree(T radians);

    /* ������ */
    template <typename T>
    T SquareRoot(T value);

    /* �]�� */
    template<typename T>
    T Cotangent(T radian);

    /* 2D�̓��� */
    template<typename T>
    T DotProduct2D(T x1, T y1, T x2, T y2);

    /* 3D�̓��� */
    template<typename T>
    T DotProduct3D(T x1, T y1, T z1, T x2, T y2, T z2);

    /* 2D�̊O�� */
    template<typename T>
    T CrossProduct2D(T x1, T y1, T x2, T y2);

    /* �ŏ��l�� */
    template<typename T>
    T Minimize(T lhs, T rhs);

    /* �ő�l�� */
    template<typename T>
    T Maximize(T lhs, T rhs);

    /* �N�����v */
    template<typename T>
    T Clamp(T value, T min, T max);

    /* �p�x��0����2�΂܂łɒ��� */
    template<typename T>
    T AdjustAngleFrom0ToPI2(T angle);

    /* ��� */
    template<typename T>
    T Square(T value);

    /* �O�� */
    template<typename T>
    T Cubic(T value);

    /* ���i�[�h�E�W���[���Y�E�|�e���V���� */
    template<typename T>
    T LennardJonesPotential(T repulsionStrength,
                            T attractionStrength,
                            T distance,
                            T repulsionAttenuationCoefficient,
                            T attractionAttenuationCoefficient);

    /* �V�O���C�h */
    template<typename T>
    T Sigmoid(T x, T gain = static_cast<T>(1.0));

    /* 1�����K�E�V�A�� */
    template<typename T>
    T OneDimensionalGaussian(T x, T standardDeviation = static_cast<T>(1.0));

    /* 2�����K�E�V�A�� */
    template<typename T>
    T TwoDimensionsGaussian(T x, T y, T dispersion = static_cast<T>(1.0));
}