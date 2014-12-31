/* �w�b�_�t�@�C�� */
#include "RandomGeneratorImpl.h"
#include "../Math/Define/MathDefine.h"


//-------------------------------------------------------------
//!
//! @brief �����_��
//! @brief �����֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Random
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_RandomGenerator::C_RandomGenerator() :

        // �������
        upImpl_(std::make_unique<C_RandomGeneratorImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_RandomGenerator::~C_RandomGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �����̗������擾����
     *  @param  �ŏ��l
     *  @param  �ő�l
     *  @return ����( �ŏ��l�ȏ�A�ő�l�ȉ� )
     *
     ****************************************************************/
    int32_t C_RandomGenerator::Random(int32_t min, int32_t max)
    {
        // ���U���z��p���ė����𐶐�
        std::uniform_int_distribution<int32_t> distribution(min, max);
        return distribution(upImpl_->GetEngine());
    }


    /*************************************************************//**
     *
     *  @brief  �����̗������擾����
     *  @param  �ŏ��l
     *  @param  �ő�l
     *  @return ����( �ŏ��l�ȏ�A�ő�l�ȉ� )
     *
     ****************************************************************/
    float C_RandomGenerator::Random(float min, float max)
    {
        // ���U���z��p���ė����𐶐�
        std::uniform_real_distribution<float> distribution(min, std::nextafter(max, std::numeric_limits<float>::max()));
        return distribution(upImpl_->GetEngine());
    }


    /*************************************************************//**
     *
     *  @brief  �����ȗ������擾����
     *  @param  �Ȃ�
     *  @return ����
     *
     ****************************************************************/
    uint32_t C_RandomGenerator::PerfectRandom()
    {
        return upImpl_->GetDevice()();
    }


    /*************************************************************//**
     *
     *  @brief�@�~���������擾����
     *  @param  ���a
     *  @return 2D�x�N�g��
     *
     ****************************************************************/
    Vector2 C_RandomGenerator::CircumferenceRandom(float radius)
    {
        // �p�x�����߂�
        float angle = Random(0.0f, static_cast<float>(Math::s_PI2));

        return Vector2(std::cosf(angle) * radius, std::sinf(angle) * radius);
    }


    /*************************************************************//**
     *
     *  @brief  �~���������擾����
     *  @param  �ő唼�a
     *  @return 2D�x�N�g��
     *
     ****************************************************************/
    Vector2 C_RandomGenerator::CircleRandom(float maxRadius)
    {
        // ���a�Ɗp�x�����߂�
        float radius = std::sqrtf(Random()) * maxRadius;
        float angle = Random(0.0f, static_cast<float>(Math::s_PI2));

        return Vector2(std::cosf(angle) * radius, std::sinf(angle) * radius);
    }


    /*************************************************************//**
     *
     *  @brief  ���ʗ������擾����
     *  @param  ���a
     *  @return 3D�x�N�g��
     *
     ****************************************************************/
    Vector3 C_RandomGenerator::SphericalSurfaceRandom(float radius)
    {
        // �p�x2�����߂�
        float theta = Random(0.0f, static_cast<float>(Math::s_PI2));
        float phi = Random(0.0f, static_cast<float>(Math::s_PI2));

        // �R�T�C�������߁A���ꂩ��T�C�������߂�( �����_�����ψ�ɂ��邽�� )
        float cosine = std::cosf(theta);
        float sine = std::sqrtf(1 - (cosine * cosine));

        return Vector3(sine * std::cosf(phi) * radius, sine * std::sinf(phi) * radius, cosine * radius);
    }


    /*************************************************************//**
     *
     *  @brief  �����������擾����
     *  @param  �ő唼�a
     *  @return 3D�x�N�g��
     *
     ****************************************************************/
    Vector3 C_RandomGenerator::SphereRandom(float maxRadius)
    {
        // ���a�����߂�
        float radius = std::powf(Random(), 1.0f / 3.0f) * maxRadius;

        // �p�x2�����߂�
        float theta = Random(0.0f, static_cast<float>(Math::s_PI2));
        float phi = Random(0.0f, static_cast<float>(Math::s_PI2));

        // �R�T�C�������߁A���ꂩ��T�C�������߂�( �����_�����ψ�ɂ��邽�� )
        float cosine = std::cosf(theta);
        float sine = std::sqrtf(1 - (cosine * cosine));

        return Vector3(sine * std::cosf(phi) * radius, sine * std::sinf(phi) * radius, cosine * radius);
    }


    /*************************************************************//**
     *
     *  @brief  �O�p�������擾����
     *  @param  �ŏ��l
     *  @param  �ő�l
     *  @return ����
     *
     ****************************************************************/
    float C_RandomGenerator::TriangleRandom(float min, float max)
    {
        return (1.0f - std::sqrtf(1.0f - Random())) * (max - min) + min;
    }


    /*************************************************************//**
     *
     *  @brief  �~�`�W�����z�ŗ������擾����
     *  @param  �ő唼�a
     *  @param  �w��( 0.5�����F�~���ɏW�� �E 0.5�F�ψ� �E 0.5���߁F���S�ɏW�� )
     *  @return 2D�x�N�g��
     *
     ****************************************************************/
    Vector2 C_RandomGenerator::CircleContagiousDistribution(float maxRadius, float exponent)
    {
        // ���a�Ɗp�x�����߂�
        float radius = std::powf(Random(), exponent) * maxRadius;
        float angle = Random(0.0f, static_cast<float>(Math::s_PI2));

        return Vector2(std::cosf(angle) * radius, std::sinf(angle) * radius);
    }


    /*************************************************************//**
     *
     *  @brief  ���K���z�ŗ������擾����
     *  @param  ����
     *  @param  �W���΍�
     *  @return ����
     *
     ****************************************************************/
    float C_RandomGenerator::NormalDistributionRandom(float average, float standardDeviation)
    {
        // ���K���z�ŗ����𐶐�
        std::normal_distribution<float> distribution(average, standardDeviation);
        return distribution(upImpl_->GetEngine());
    }


    /*************************************************************//**
     *
     *  @brief  ����̊m����true���擾����
     *  @param  �m��( 0 �` 1 )
     *  @return �w�肵���m���Ftrue
     *  @return ����ȊO�Ffalse
     *
     ****************************************************************/
    bool C_RandomGenerator::RandomTrue(float probability)
    {
        // �x�E�k�[�C���z��p���ē���m����true��Ԃ�
        std::bernoulli_distribution distribution(probability);
        return distribution(upImpl_->GetEngine());
    }
}