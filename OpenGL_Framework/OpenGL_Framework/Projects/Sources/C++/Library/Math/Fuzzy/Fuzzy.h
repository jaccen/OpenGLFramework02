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
    //! @brief �t�@�W�[
    //! @brief �t�@�W�[���_�֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace Fuzzy
    {
        /* �^�ϊ� */
        using HedgeFunction = float(*)(float);                                                              // HedgeFunction�^��錾

        //-------------------------------------------------------------
        //!
        //! @brief �����o�V�b�v
        //! @brief �����o�V�b�v�֐����܂Ƃ߂����[�e�B���e�B�N���X
        //!
        //-------------------------------------------------------------
        template<typename T = float>
        class C_Membership
        {
        public:
            static float s_Grade(T value, T start, T end, HedgeFunction pHedge = nullptr);                  // �X�Ό^
            static float s_ReverseGrade(T value, T start, T end,  HedgeFunction pHedge = nullptr);          // �t�X�Ό^
            static float s_Triangle(T value,                                                                // �O�p�`�^
                                    T start,
                                    T top,
                                    T end,
                                    HedgeFunction pHedge = nullptr);
            static float s_Trapezoid(T value,                                                               // ��`�^
                                     T bottomStart,
                                     T topStart,
                                     T topEnd,
                                     T bottomEnd,
                                     HedgeFunction pHedge = nullptr);
        }; 


        //-------------------------------------------------------------
        //!
        //! @brief �w�b�W
        //! @brief �w�b�W�֐����܂Ƃ߂����[�e�B���e�B�N���X
        //!
        //-------------------------------------------------------------
        class C_Heage
        {
        public:
            static float s_Very(float value);                                                               // 2��
            static float s_SomeWhat(float value);                                                           // ������
        };


        //-------------------------------------------------------------
        //!
        //! @brief ���W�J���I�y���[�V����
        //! @brief �_�����Z�֐����܂Ƃ߂����[�e�B���e�B�N���X
        //!
        //-------------------------------------------------------------
        class C_LogicalOperation
        {
        public:
            static float s_And(float lhs, float rhs);                                                       // �_����
            static float s_Or(float lhs, float rhs);                                                        // �_���a
            static float s_ProbabilisticOr(float lhs, float rhs);                                           // �m���I�_���a
            static float s_Not(float value);                                                                // �_���ے�
        };


        //-------------------------------------------------------------
        //!
        //! @brief �f�t�@�W�t�B
        //! @brief ��t�@�W�[�����s���֐����܂Ƃ߂����[�e�B���e�B�N���X
        //!
        //-------------------------------------------------------------
        class C_Defuzzify
        {
        public:
            static float s_Height(float values[], float weights[], uint32_t elementCount);                  // �����@
        };
    }
}