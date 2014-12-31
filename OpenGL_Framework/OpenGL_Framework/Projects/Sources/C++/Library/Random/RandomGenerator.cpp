/* ヘッダファイル */
#include "RandomGeneratorImpl.h"
#include "../Math/Define/MathDefine.h"


//-------------------------------------------------------------
//!
//! @brief ランダム
//! @brief 乱数関連の名前空間
//!
//-------------------------------------------------------------
namespace Random
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_RandomGenerator::C_RandomGenerator() :

        // 実装情報
        upImpl_(std::make_unique<C_RandomGeneratorImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_RandomGenerator::~C_RandomGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  整数の乱数を取得する
     *  @param  最小値
     *  @param  最大値
     *  @return 乱数( 最小値以上、最大値以下 )
     *
     ****************************************************************/
    int32_t C_RandomGenerator::Random(int32_t min, int32_t max)
    {
        // 離散分布を用いて乱数を生成
        std::uniform_int_distribution<int32_t> distribution(min, max);
        return distribution(upImpl_->GetEngine());
    }


    /*************************************************************//**
     *
     *  @brief  実数の乱数を取得する
     *  @param  最小値
     *  @param  最大値
     *  @return 乱数( 最小値以上、最大値以下 )
     *
     ****************************************************************/
    float C_RandomGenerator::Random(float min, float max)
    {
        // 離散分布を用いて乱数を生成
        std::uniform_real_distribution<float> distribution(min, std::nextafter(max, std::numeric_limits<float>::max()));
        return distribution(upImpl_->GetEngine());
    }


    /*************************************************************//**
     *
     *  @brief  完璧な乱数を取得する
     *  @param  なし
     *  @return 乱数
     *
     ****************************************************************/
    uint32_t C_RandomGenerator::PerfectRandom()
    {
        return upImpl_->GetDevice()();
    }


    /*************************************************************//**
     *
     *  @brief　円周乱数を取得する
     *  @param  半径
     *  @return 2Dベクトル
     *
     ****************************************************************/
    Vector2 C_RandomGenerator::CircumferenceRandom(float radius)
    {
        // 角度を求める
        float angle = Random(0.0f, static_cast<float>(Math::s_PI2));

        return Vector2(std::cosf(angle) * radius, std::sinf(angle) * radius);
    }


    /*************************************************************//**
     *
     *  @brief  円内乱数を取得する
     *  @param  最大半径
     *  @return 2Dベクトル
     *
     ****************************************************************/
    Vector2 C_RandomGenerator::CircleRandom(float maxRadius)
    {
        // 半径と角度を求める
        float radius = std::sqrtf(Random()) * maxRadius;
        float angle = Random(0.0f, static_cast<float>(Math::s_PI2));

        return Vector2(std::cosf(angle) * radius, std::sinf(angle) * radius);
    }


    /*************************************************************//**
     *
     *  @brief  球面乱数を取得する
     *  @param  半径
     *  @return 3Dベクトル
     *
     ****************************************************************/
    Vector3 C_RandomGenerator::SphericalSurfaceRandom(float radius)
    {
        // 角度2つを求める
        float theta = Random(0.0f, static_cast<float>(Math::s_PI2));
        float phi = Random(0.0f, static_cast<float>(Math::s_PI2));

        // コサインを求め、それからサインを求める( ランダムを均一にするため )
        float cosine = std::cosf(theta);
        float sine = std::sqrtf(1 - (cosine * cosine));

        return Vector3(sine * std::cosf(phi) * radius, sine * std::sinf(phi) * radius, cosine * radius);
    }


    /*************************************************************//**
     *
     *  @brief  球内乱数を取得する
     *  @param  最大半径
     *  @return 3Dベクトル
     *
     ****************************************************************/
    Vector3 C_RandomGenerator::SphereRandom(float maxRadius)
    {
        // 半径を求める
        float radius = std::powf(Random(), 1.0f / 3.0f) * maxRadius;

        // 角度2つを求める
        float theta = Random(0.0f, static_cast<float>(Math::s_PI2));
        float phi = Random(0.0f, static_cast<float>(Math::s_PI2));

        // コサインを求め、それからサインを求める( ランダムを均一にするため )
        float cosine = std::cosf(theta);
        float sine = std::sqrtf(1 - (cosine * cosine));

        return Vector3(sine * std::cosf(phi) * radius, sine * std::sinf(phi) * radius, cosine * radius);
    }


    /*************************************************************//**
     *
     *  @brief  三角乱数を取得する
     *  @param  最小値
     *  @param  最大値
     *  @return 乱数
     *
     ****************************************************************/
    float C_RandomGenerator::TriangleRandom(float min, float max)
    {
        return (1.0f - std::sqrtf(1.0f - Random())) * (max - min) + min;
    }


    /*************************************************************//**
     *
     *  @brief  円形集中分布で乱数を取得する
     *  @param  最大半径
     *  @param  指数( 0.5未満：円周に集中 ・ 0.5：均一 ・ 0.5超過：中心に集中 )
     *  @return 2Dベクトル
     *
     ****************************************************************/
    Vector2 C_RandomGenerator::CircleContagiousDistribution(float maxRadius, float exponent)
    {
        // 半径と角度を求める
        float radius = std::powf(Random(), exponent) * maxRadius;
        float angle = Random(0.0f, static_cast<float>(Math::s_PI2));

        return Vector2(std::cosf(angle) * radius, std::sinf(angle) * radius);
    }


    /*************************************************************//**
     *
     *  @brief  正規分布で乱数を取得する
     *  @param  平均
     *  @param  標準偏差
     *  @return 乱数
     *
     ****************************************************************/
    float C_RandomGenerator::NormalDistributionRandom(float average, float standardDeviation)
    {
        // 正規分布で乱数を生成
        std::normal_distribution<float> distribution(average, standardDeviation);
        return distribution(upImpl_->GetEngine());
    }


    /*************************************************************//**
     *
     *  @brief  特定の確率でtrueを取得する
     *  @param  確率( 0 ～ 1 )
     *  @return 指定した確率：true
     *  @return それ以外：false
     *
     ****************************************************************/
    bool C_RandomGenerator::RandomTrue(float probability)
    {
        // ベウヌーイ分布を用いて特定確率でtrueを返す
        std::bernoulli_distribution distribution(probability);
        return distribution(upImpl_->GetEngine());
    }
}