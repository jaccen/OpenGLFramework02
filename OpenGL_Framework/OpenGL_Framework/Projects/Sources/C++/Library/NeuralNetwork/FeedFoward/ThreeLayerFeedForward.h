/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Layer/Layer.h"


//-------------------------------------------------------------
//!
//! @brief ニューラルネットワーク
//! @brief ニューラルネットワーク関連の名前空間
//!
//-------------------------------------------------------------
namespace NeuralNetwork
{
    //-------------------------------------------------------------
    //!
    //! @brief スリーレイヤーフィードフォワード
    //! @brief 3層フォードフォワード型のネットワークを表すクラス
    //!
    //-------------------------------------------------------------
    class ThreeLayerFeedForward
    {
    public:
        /* レイヤーの種類 */
        enum eLayerType
        {
            INPUT,                                                                              ///< @brief 入力レイヤー
            HIDDEN,                                                                             ///< @brief 隠しレイヤー
            OUTPUT,                                                                             ///< @brief 出力レイヤー
            ALL,                                                                                ///< @brief 全てのレイヤー
        };

        ThreeLayerFeedForward();                                                                // コンストラクタ
        ~ThreeLayerFeedForward();                                                               // デストラクタ
        void Initialize(uint16_t inputLayerNodeCount,                                           // 初期化処理
                        uint16_t hiddenLayerNodeCount,
                        uint16_t outputLayerNodeCount);
        void Finalize();                                                                        // 終了処理
        void FeedForward();                                                                     // フィードフォワード処理
        void BackPropagate();                                                                   // バックプロパゲート処理
        float CalculateError();                                                                 // エラーを計算
        void EnableMomentum(bool validFlag = false);                                            // モーメンタムを有効化
        float GetOutputValue(uint16_t nodeIndex) const;                                         // 出力値を取得
        uint16_t GetMaxOutputValueIndex() const;                                                // 最大出力値のインデックスを取得
        void SetInputValue(uint16_t nodeIndex, float inputValue);                               // 入力値を設定
        void SetTargetOutputValue(uint16_t nodeIndex, float targetOutputValue);                 // 目標とする出力値を設定
        void SetLearningRate(float learningRate);                                               // 学習率を設定
        void SetMomentumFactor(float momentumFactor);                                           // モーメンタム因数を設定
        void SetActiveFanction(ActiveFunction pActiveFunction, eLayerType layerType = ALL);     // 活性化関数を設定
    private:
        S_Layer inputLayer_;                                                                    ///< @brief 入力レイヤー
        S_Layer hiddenLayer_;                                                                   ///< @brief 隠れレイヤー
        S_Layer outputLayer_;                                                                   ///< @brief 出力レイヤー
    };
}