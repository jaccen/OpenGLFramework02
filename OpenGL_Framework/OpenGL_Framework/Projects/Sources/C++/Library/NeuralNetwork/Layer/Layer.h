/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include <vector>


//-------------------------------------------------------------
//!
//! @brief ニューラルネットワーク
//! @brief ニューラルネットワーク関連の名前空間
//!
//-------------------------------------------------------------
namespace NeuralNetwork
{
    /* 型変換 */
    using ActiveFunction = float(*)(float);                                     ///< @brief ActiveFunction型を宣言


    //-------------------------------------------------------------
    //!
    //! @brief アクティブファンクション
    //! @brief 活性化関数をまとめたユーティリティクラス
    //!
    //-------------------------------------------------------------
    class C_ActiveFunction
    {
    public:
        static float s_Step(float x);                                           // 段階関数
        static float s_Linear(float x);                                         // 線形関数
        static float s_Sigmoid(float x);                                        // シグモイド関数
        static float s_HyperbolicTangent(float x);                              // 双曲線正接関数
    };


    //-------------------------------------------------------------
    //!
    //! @brief ノード
    //! @brief ノードを表すクラス
    //!
    //-------------------------------------------------------------
    struct S_Node
    {
        float outputValue_ = 0.0f;                                              ///< @brief 出力値
        float targetOutputValue_ = 0.0f;                                        ///< @brief 目標の出力値
        float error_ = 0.0f;                                                    ///< @brief エラー( 誤差 )
        std::vector<float> weights_;                                            ///< @brief 重み
        std::vector<float> weightAdjustments_;                                  ///< @brief 重みの調整値
    };


    //-------------------------------------------------------------
    //!
    //! @brief レイヤー
    //! @brief 層を表すクラス
    //!
    //-------------------------------------------------------------
    struct S_Layer
    {
        uint16_t childNodeCount_ = 0;                                           ///< @brief 子ノードの数
        uint16_t parentNodeCount_ = 0;                                          ///< @brief 親ノードの数
        float learningRate_ = 0.5f;                                             ///< @brief 学習率
        float momentumFactor_ = 0.5f;                                           ///< @brief モーメンタム因数
        bool useMomentumFlag_ = false;                                          ///< @brief モーメンタムの使用フラグ
        std::vector<S_Node> nodes_;                                             ///< @brief ノード
        std::vector<float> biasValues_;                                         ///< @brief バイアス値
        std::vector<float> biasWeights_;                                        ///< @brief バイアスの重み
        S_Layer* pParentLayer_ = nullptr;                                       ///< @brief 親のレイヤー
        S_Layer* pChildLayer_ = nullptr;                                        ///< @brief 子のレイヤー
        ActiveFunction pActiveFuction_ = C_ActiveFunction::s_Sigmoid;           ///< @brief 活性化関数

        S_Layer();                                                              // コンストラクタ
        ~S_Layer();                                                             // デストラクタ
        void Initialize(uint16_t nodeCount,                                     // 初期化処理
                        uint16_t parentNodeCount,
                        uint16_t childNodeCount,
                        S_Layer* pParentLayer,
                        S_Layer* pChildLayer);
        void Finalize();                                                        // 終了処理
        void RandomizeWeight();                                                 // ウェイトをランダム化
        void AdjustWeight();                                                    // ウェイトの調節
        void CalculateError();                                                  // エラーの計算
        void CalculateOutValue();                                               // 出力値を計算
    };
}