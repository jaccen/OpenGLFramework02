/* ヘッダファイル */
#include "Layer.h"
#include "../../../Library/Random/RandomGenerator.h"


//-------------------------------------------------------------
//!
//! @brief ニューラルネットワーク
//! @brief ニューラルネットワーク関連の名前空間
//!
//-------------------------------------------------------------
namespace NeuralNetwork
{

#pragma region C_ActiveFunctionクラス


    /*************************************************************//**
     *
     *  @brief  段階関数から値を求める
     *  @param  値
     *  @return 0または1
     *
     ****************************************************************/
    float C_ActiveFunction::s_Step(float x)
    {
        return (x <= 0.0f) ? 0.0f : 1.0f;
    }


    /*************************************************************//**
     *
     *  @brief  線形関数から値を求める
     *  @param  値
     *  @return 引き数と同じ値
     *
     ****************************************************************/
    float C_ActiveFunction::s_Linear(float x)
    {
        return x;
    }


    /*************************************************************//**
     *
     *  @brief  シグモイド関数から値を求める
     *  @param  値
     *  @return 0から1までの値
     *
     ****************************************************************/
    float C_ActiveFunction::s_Sigmoid(float x)
    {
        return 1.0f / (1.0f + std::exp(-x));
    }


    /*************************************************************//**
     *
     *  @brief  双曲線正接関数から値を求める
     *  @param  値
     *  @return -1から1までの値
     *
     ****************************************************************/
    float C_ActiveFunction::s_HyperbolicTangent(float x)
    {
        float ePowerX = std::exp(x);
        float ePowerMinusX = std::exp(-x);

        return (ePowerX - ePowerMinusX) / (ePowerX + ePowerMinusX);
    }



#pragma endregion


#pragma region C_ActiveFunctionクラス


    /*************************************************************//**
     *
     *  @brief  シグモイド導関数から傾きを求める
     *  @param  値
     *  @return 傾き
     *
     ****************************************************************/
    float C_DerivativeFunction::s_Sigmoid(float x)
    {
        return x * (1.0f - x);
    }


#pragma endregion


#pragma region S_Layer構造体


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    S_Layer::S_Layer()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    S_Layer::~S_Layer()
    {
        if (nodes_.empty() == false) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  ノード数
     *  @param  親のノード数
     *  @param  子のノード数
     *  @param  親のレイヤー
     *  @param  子のレイヤー
     *  @return なし
     *
     ****************************************************************/
    void S_Layer::Initialize(uint16_t nodeCount,
                             uint16_t parentNodeCount,
                             uint16_t childNodeCount,
                             S_Layer* pParentLayer,
                             S_Layer* pChildLayer)
    {
        // 親と子のノード数を設定
        parentNodeCount_ = parentNodeCount;
        childNodeCount_ = childNodeCount;

        // ノードの生成
        nodes_.resize(nodeCount);

        // 親のレイヤーを設定
        if (pParentLayer) pParentLayer_ = pParentLayer;

        // 子のレイヤーを設定
        if (pChildLayer)
        {
            pChildLayer_ = pChildLayer;

            for (auto& rNode : nodes_)
            {
                rNode.weights_.resize(childNodeCount);
                rNode.weightAdjustments_.resize(childNodeCount);
            }

            biasValues_.resize(childNodeCount);
            for (auto& rBiasValue : biasValues_) rBiasValue = -1.0f;

            biasWeights_.resize(childNodeCount);
        }
        else
        {
            for (auto& rNode : nodes_)
            {
                rNode.weights_.clear();
                rNode.weightAdjustments_.clear();
            }

            biasValues_.clear();
            biasWeights_.clear();
        }
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void S_Layer::Finalize()
    {
        nodes_.clear();
        biasValues_.clear();
        biasWeights_.clear();

        pParentLayer_ = nullptr;
        pChildLayer_ = nullptr;
    }


    /*************************************************************//**
     *
     *  @brief  ウェイトをランダム化する
     *  @param  最小値
     *  @param  最大値
     *  @return なし
     *
     ****************************************************************/
    void S_Layer::RandomizeWeight()
    {
        for (auto& rNode : nodes_)
        {
            for (size_t i = 0; i < childNodeCount_; ++i)
            {
                rNode.weights_[i] = Random::C_RandomGenerator::s_GetInstance()->Random(-1.0f, 1.0f);
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  ウェイトを調節を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void S_Layer::AdjustWeight()
    {
        if (pChildLayer_)
        {
            // 加える重み
            float addWeight = 0.0f;

            for (auto& rNode : nodes_)
            {
                for (size_t i = 0; i < childNodeCount_; ++i)
                {
                    // 加える重みを計算
                    addWeight = learningRate_ * pChildLayer_->nodes_[i].error_ * rNode.outputValue_;

                    if (useMomentumFlag_ == true)
                    {
                        // モーメンタムを使用する場合は加える重みにモーメンタム因子と調節値をかけた値を足し、
                        // 調節値に加えるウェイトを設定
                        rNode.weights_[i] += addWeight + momentumFactor_ * rNode.weightAdjustments_[i];
                        rNode.weightAdjustments_[i] = addWeight;
                    }
                    else
                    {
                        rNode.weights_[i] += addWeight;
                    }
                }
            }

            for (size_t i = 0; i < childNodeCount_; ++i)
            {
                // バイアスの重みを調整
                biasWeights_[i] += learningRate_ * pChildLayer_->nodes_[i].error_ * biasValues_[i];
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  エラーの計算を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void S_Layer::CalculateError()
    {
        /* 入力レイヤー時 */
        if (pParentLayer_ == nullptr)
        {
            for (auto& rNode : nodes_)
            {
                rNode.error_ = 0.0f;
            }
        }
        /* 出力レイヤー時 */
        else if (pChildLayer_ == nullptr)
        {
            for (auto& rNode : nodes_)
            {
                rNode.error_ = (rNode.targetOutputValue_ - rNode.outputValue_) * pDerivativeFunction_(rNode.outputValue_);
            }
        }
        /* 隠れレイヤー時 */
        else
        {
            // エラーの合計
            float errorSum = 0.0f;

            for (auto& rNode : nodes_)
            {
                errorSum = 0.0f;

                for (size_t i = 0; i < childNodeCount_; ++i)
                {
                    errorSum += pChildLayer_->nodes_[i].error_ * rNode.weights_[i];
                }

                rNode.error_ = errorSum * pDerivativeFunction_(rNode.outputValue_);
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief 出力値の計算を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void S_Layer::CalculateOutValue()
    {
        if (pParentLayer_)
        {
            // 出力値
            float outValue = 0.0f;

            for (size_t i = 0, nodeCount = nodes_.size(); i < nodeCount; ++i)
            {
                // 出力値を求める
                for (size_t j = 0; j < parentNodeCount_; ++j)
                {
                    outValue += pParentLayer_->nodes_[j].outputValue_ * pParentLayer_->nodes_[j].weights_[i];
                }

                // 出力値に親のバイアス値を加算
                outValue += pParentLayer_->biasValues_[i] * pParentLayer_->biasWeights_[i];

                // 線形活性化関数で出力値を決定
                nodes_[i].outputValue_ = pActiveFuction_(outValue);
            }
        }
    }


#pragma endregion


}