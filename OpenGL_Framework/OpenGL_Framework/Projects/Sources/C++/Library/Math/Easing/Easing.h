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
    //-------------------------------------------------------------
    //!
    //! @brief �C�[�W���O
    //! @brief �C�[�W���O�̊֐����܂Ƃ߂����[�e�B���e�B�N���X
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    class C_Easing
    {
    public:
        /* �萔 */
        static const T s_DEFAULT_STRESS;                ///< @brief �f�t�H���g�̈���

        /* ���`( �ꎟ )��� */
        static T s_Linear(T start,
                          T end,
                          T coefficient);

        /* �C�[�Y�C���̓񎟕�� */
        static T s_EaseInQuadratic(T start,
                                   T end,
                                   T coefficient);

        /* �C�[�Y�A�E�g�̓񎟕�� */
        static T s_EaseOutQuadratic(T start,
                                    T end,
                                    T coefficient);

        /* �C�[�Y�C���E�A�E�g�̓񎟕�� */
        static T s_EaseInOutQuadratic(T start,
                                      T end,
                                      T coefficient);

        /* �C�[�Y�C���̎O����� */
        static T s_EaseInCubic(T start,
                               T end,
                               T coefficient);

        /* �C�[�Y�A�E�g�̎O����� */
        static T s_EaseOutCubic(T start,
                                T end,
                                T coefficient);

        /* �C�[�Y�C���E�A�E�g�̎O����� */
        static T s_EaseInOutCubic(T start,
                                  T end,
                                  T coefficient);

        /* �C�[�Y�C���̎l����� */
        static T s_EaseInQuartic(T start,
                                 T end,
                                 T coefficient);

        /* �C�[�Y�A�E�g�̎l����� */
        static T s_EaseOutQuartic(T start,
                                  T end,
                                  T coefficient);

        /* �C�[�Y�C���E�A�E�g�̎l����� */
        static T s_EaseInOutQuartic(T start,
                                    T end,
                                    T coefficient);

        /* �C�[�Y�C���̌܎���� */
        static T s_EaseInQuintic(T start,
                                 T end,
                                 T coefficient);

        /* �C�[�Y�A�E�g�̌܎���� */
        static T s_EaseOutQuintic(T start,
                                  T end,
                                  T coefficient);

        /* �C�[�Y�C���E�A�E�g�̌܎���� */
        static T s_EaseInOutQuintic(T start,
                                    T end,
                                    T coefficient);

        /* �C�[�Y�C���̃T�C����� */
        static T s_EaseInSine(T start,
                              T end,
                              T coefficient);

        /* �C�[�Y�A�E�g�̃T�C����� */
        static T s_EaseOutSine(T start,
                               T end,
                               T coefficient);

        /* �C�[�Y�C���E�A�E�g�̃T�C����� */
        static T s_EaseInOutSine(T start,
                                 T end,
                                 T coefficient);

        /* �C�[�Y�C���̎w����� */
        static T s_EaseInExponential(T start,
                                     T end,
                                     T coefficient);

        /* �C�[�Y�A�E�g�̎w����� */
        static T s_EaseOutExponential(T start,
                                      T end,
                                      T coefficient);

        /* �C�[�Y�C���E�A�E�g�̎w����� */
        static T s_EaseInOutExponential(T start,
                                        T end,
                                        T coefficient);

        /* �C�[�Y�C���̉~�ʕ�� */
        static T s_EaseInCircular(T start,
                                  T end,
                                  T coefficient);

        /* �C�[�Y�A�E�g�̉~�ʕ�� */
        static T s_EaseOutCircular(T start,
                                   T end,
                                   T coefficient);

        /* �C�[�Y�C���E�A�E�g�̉~�ʕ�� */
        static T s_EaseInOutCircular(T start,
                                     T end,
                                     T coefficient);

        /* �C�[�Y�C���̃o�b�N��� */
        static T s_EaseInBack(T start,
                              T end,
                              T coefficient,
                              T stress = s_DEFAULT_STRESS);

        /* �C�[�Y�A�E�g�̃o�b�N��� */
        static T s_EaseOutBack(T start,
                               T end,
                               T coefficient,
                               T stress = s_DEFAULT_STRESS);

        /* �C�[�Y�C���E�A�E�g�̃o�b�N��� */
        static T s_EaseInOutBack(T start,
                                 T end,
                                 T coefficient,
                                 T stress = s_DEFAULT_STRESS);

        /* �C�[�Y�C���̃o�E���X��� */
        static T s_EaseInBounce(T start,
                                T end,
                                T coefficient);

        /* �C�[�Y�A�E�g�̃o�E���X��� */
        static T s_EaseOutBounce(T start,
                                 T end,
                                 T coefficient);

        /* �C�[�Y�C���E�A�E�g�̃o�E���X��� */
        static T s_EaseInOutBounce(T start,
                                   T end,
                                   T coefficient);

        /* �C�[�Y�C���̃C���X�e�B�b�N��� */
        static T s_EaseInElastic(T start,
                                 T end,
                                 T coefficient);

        /* �C�[�Y�A�E�g�̃C���X�e�B�b�N��� */
        static T s_EaseOutElastic(T start,
                                  T end,
                                  T coefficient);

        /* �C�[�Y�C���E�A�E�g�̃C���X�e�B�b�N��� */
        static T s_EaseInOutElastic(T start,
                                    T end,
                                    T coefficient);
    };
}