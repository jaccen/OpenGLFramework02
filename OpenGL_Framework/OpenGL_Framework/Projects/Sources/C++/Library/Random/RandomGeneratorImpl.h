/* ヘッダファイル */
#include "RandomGenerator.h"
#include <random>


//-------------------------------------------------------------
//!
//! @brief ランダム
//! @brief 乱数関連の名前空間
//!
//-------------------------------------------------------------
namespace Random
{
    //-------------------------------------------------------------
    //!
    //! @brief ランダムマネージャーインプリメント
    //! @brief ランダムマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_RandomGenerator::C_RandomGeneratorImpl
    {
    public:
        C_RandomGeneratorImpl();                        // コンストラクタ
        ~C_RandomGeneratorImpl();                       // デストラクタ
        std::random_device& GetDevice();                // 乱数デバイスを取得
        std::mt19937& GetEngine();                      // 乱数エンジンを取得
    private:
        std::random_device device_;                     ///< @brief 乱数デバイス
        std::mt19937 engine_;                           ///< @brief 乱数エンジン
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_RandomGenerator::C_RandomGeneratorImpl::C_RandomGeneratorImpl()
    {
        // ランダムシードの初期化
        engine_.seed(device_());
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_RandomGenerator::C_RandomGeneratorImpl::~C_RandomGeneratorImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  乱数デバイスを取得する
     *  @param  なし
     *  @return 乱数デバイス
     *
     ****************************************************************/
    std::random_device& C_RandomGenerator::C_RandomGeneratorImpl::GetDevice()
    {
        return device_;
    }


    /*************************************************************//**
     *
     *  @brief  乱数エンジンを取得する
     *  @param  なし
     *  @return 乱数エンジン
     *
     ****************************************************************/
    std::mt19937& C_RandomGenerator::C_RandomGeneratorImpl::GetEngine()
    {
        return engine_;
    }
}