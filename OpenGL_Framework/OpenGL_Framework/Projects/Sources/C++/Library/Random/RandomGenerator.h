/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Singleton/Singleton.h"
#include "../Math/Vector/Vector2.h"
#include "../Math/Vector/Vector3.h"


//-------------------------------------------------------------
//!
//! @brief ランダム
//! @brief 乱数関連の名前空間
//!
//-------------------------------------------------------------
namespace Random
{
    /* 別名 */
    using Vector2 = Math::S_Vector2<float>;                                             // Vector2型
    using Vector3 = Math::S_Vector3<float>;                                             // Vector3型


    //-------------------------------------------------------------
    //!
    //! @brief ランダムジェネレーター
    //! @brief 乱数を生成するクラス
    //!
    //-------------------------------------------------------------
    class C_RandomGenerator : public Singleton::C_Singleton<C_RandomGenerator>
    {
        friend C_Singleton<C_RandomGenerator>;                                          // シングルトンクラスをフレンド化
    public:
        int32_t Random(int32_t min, int32_t max);                                       // 整数の乱数を取得
        float Random(float min = 0.0f, float max = 1.0f);                               // 実数の乱数を取得
        uint32_t PerfectRandom();                                                       // 完璧な乱数を取得
        Vector2 CircumferenceRandom(float radius);                                      // 円周乱数を取得
        Vector2 CircleRandom(float maxRadius);                                          // 円内乱数を取得
        Vector3 SphericalSurfaceRandom(float radius);                                   // 球面乱数を取得
        Vector3 SphereRandom(float maxRadius);                                          // 球内乱数を取得
        float TriangleRandom(float min, float max);                                     // 三角乱数を取得
        Vector2 CircleContagiousDistribution(float maxRadius, float exponent);          // 円形集中分布で乱数を取得
        float NormalDistributionRandom(float average, float standardDeviation);         // 正規分布で乱数を取得
        bool RandomTrue(float probability);                                             // 特定の確率でtrueを取得
    private:
        /* 前方宣言 */
        class C_RandomGeneratorImpl;

        std::unique_ptr<C_RandomGeneratorImpl> upImpl_;                                 ///< @brief 実装情報

        C_RandomGenerator();                                                            // コンストラクタ
        ~C_RandomGenerator() override;                                                  // デストラクタ
    };
}