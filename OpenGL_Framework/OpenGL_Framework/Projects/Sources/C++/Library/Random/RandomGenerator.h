/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Singleton/Singleton.h"
#include "../Math/Vector/Vector2.h"
#include "../Math/Vector/Vector3.h"


//-------------------------------------------------------------
//!
//! @brief �����_��
//! @brief �����֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Random
{
    /* �ʖ� */
    using Vector2 = Math::S_Vector2<float>;                                             // Vector2�^
    using Vector3 = Math::S_Vector3<float>;                                             // Vector3�^


    //-------------------------------------------------------------
    //!
    //! @brief �����_���W�F�l���[�^�[
    //! @brief �����𐶐�����N���X
    //!
    //-------------------------------------------------------------
    class C_RandomGenerator : public Singleton::C_Singleton<C_RandomGenerator>
    {
        friend C_Singleton<C_RandomGenerator>;                                          // �V���O���g���N���X���t�����h��
    public:
        int32_t Random(int32_t min, int32_t max);                                       // �����̗������擾
        float Random(float min = 0.0f, float max = 1.0f);                               // �����̗������擾
        uint32_t PerfectRandom();                                                       // �����ȗ������擾
        Vector2 CircumferenceRandom(float radius);                                      // �~���������擾
        Vector2 CircleRandom(float maxRadius);                                          // �~���������擾
        Vector3 SphericalSurfaceRandom(float radius);                                   // ���ʗ������擾
        Vector3 SphereRandom(float maxRadius);                                          // �����������擾
        float TriangleRandom(float min, float max);                                     // �O�p�������擾
        Vector2 CircleContagiousDistribution(float maxRadius, float exponent);          // �~�`�W�����z�ŗ������擾
        float NormalDistributionRandom(float average, float standardDeviation);         // ���K���z�ŗ������擾
        bool RandomTrue(float probability);                                             // ����̊m����true���擾
    private:
        /* �O���錾 */
        class C_RandomGeneratorImpl;

        std::unique_ptr<C_RandomGeneratorImpl> upImpl_;                                 ///< @brief �������

        C_RandomGenerator();                                                            // �R���X�g���N�^
        ~C_RandomGenerator() override;                                                  // �f�X�g���N�^
    };
}