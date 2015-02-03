/* ヘッダファイル */
#include "ThreeLayerFeedForward.h"
#include "../../../Library/Math/Define/MathDefine.h"


//-------------------------------------------------------------
//!
//! @brief ニューラルネットワーク
//! @brief ニューラルネットワーク関連の名前空間
//!
//-------------------------------------------------------------
namespace NeuralNetwork
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    ThreeLayerFeedForward::ThreeLayerFeedForward()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    ThreeLayerFeedForward::~ThreeLayerFeedForward()
    {
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  入力レイヤーのノード数
     *  @param  隠しレイヤーのノード数
     *  @param  出力レイヤーのノード数
     *  @return なし
     *
     ****************************************************************/
    void ThreeLayerFeedForward::Initialize(uint16_t inputLayerNodeCount,
                                           uint16_t hiddenLayerNodeCount,
                                           uint16_t outputLayerNodeCount)
    {
        // 入力レイヤーの初期化処理
        inputLayer_.Initialize(inputLayerNodeCount,
                               0,
                               hiddenLayerNodeCount,
                               nullptr,
                               &hiddenLayer_);

        inputLayer_.RandomizeWeight();

        // 隠しレイヤーの初期化処理
        hiddenLayer_.Initialize(hiddenLayerNodeCount,
                                inputLayerNodeCount,
                                outputLayerNodeCount,
                                &inputLayer_,
                                &outputLayer_);

        hiddenLayer_.RandomizeWeight();

        // 出力レイヤーの初期化処理
        outputLayer_.Initialize(outputLayerNodeCount,
                                hiddenLayerNodeCount,
                                0,
                                &hiddenLayer_,
                                nullptr);
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void ThreeLayerFeedForward::Finalize()
    {
        inputLayer_.Finalize();
        hiddenLayer_.Finalize();
        outputLayer_.Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  フィードフォワード処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void ThreeLayerFeedForward::FeedForward()
    {
        hiddenLayer_.CalculateOutValue();
        outputLayer_.CalculateOutValue();
    }


    /*************************************************************//**
     *
     *  @brief  バックプロパゲート処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void ThreeLayerFeedForward::BackPropagate()
    {
        // エラーを計算
        outputLayer_.CalculateError();
	    hiddenLayer_.CalculateError();

        // 重みの調整
	    hiddenLayer_.AdjustWeight();
	    inputLayer_.AdjustWeight();
    }


    /*************************************************************//**
     *
     *  @brief  エラーの計算を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    float ThreeLayerFeedForward::CalculateError()
    {
        float error = 0.0f;

        for (auto& rOutputLayerNode : outputLayer_.nodes_)
        {
            error += Math::Square(rOutputLayerNode.outputValue_ - rOutputLayerNode.targetOutputValue_);
        }

        error /= outputLayer_.nodes_.size();

        return error;
    }


    /*************************************************************//**
     *
     *  @brief  モーメンタムを有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void ThreeLayerFeedForward::EnableMomentum(bool validFlag)
    {
        inputLayer_.useMomentumFlag_ = validFlag;
        hiddenLayer_.useMomentumFlag_ = validFlag;
        outputLayer_.useMomentumFlag_ = validFlag;
    }


    /*************************************************************//**
     *
     *  @brief  出力値を取得する
     *  @param  ノードのインデックス
     *  @return なし
     *
     ****************************************************************/
    float ThreeLayerFeedForward::GetOutputValue(uint16_t nodeIndex) const
    {
        assert(nodeIndex < outputLayer_.nodes_.size());

        return outputLayer_.nodes_[nodeIndex].outputValue_;
    }


    /*************************************************************//**
     *
     *  @brief  最大出力値のインデックスを取得
     *  @param  なし
     *  @return 最大出力値のインデックス
     *
     ****************************************************************/
    uint16_t ThreeLayerFeedForward::GetMaxOutputValueIndex() const
    {
        assert(outputLayer_.nodes_.empty() == false);

        float maxOutputValue = outputLayer_.nodes_[0].outputValue_;
        uint16_t maxOutputValueIndex = 0;

        for (size_t i = 1, nodeCount = outputLayer_.nodes_.size(); i < nodeCount; ++i)
        {
            if (maxOutputValue < outputLayer_.nodes_[i].outputValue_)
            {
                maxOutputValue = outputLayer_.nodes_[i].outputValue_;
                maxOutputValueIndex = i;
            }
        }

        return maxOutputValueIndex;
    }


    /*************************************************************//**
     *
     *  @brief  入力値を設定する
     *  @param  ノードのインデックス
     *  @param  入力値
     *  @return なし
     *
     ****************************************************************/
    void ThreeLayerFeedForward::SetInputValue(uint16_t nodeIndex, float inputValue)
    {
        assert(nodeIndex < inputLayer_.nodes_.size());

        inputLayer_.nodes_[nodeIndex].outputValue_ = inputValue;
    }


    /*************************************************************//**
     *
     *  @brief  入力値を設定する
     *  @param  ノードのインデックス
     *  @param  入力値
     *  @return なし
     *
     ****************************************************************/
    void ThreeLayerFeedForward::SetTargetOutputValue(uint16_t nodeIndex, float targetOutputValue)
    {
        assert(nodeIndex < inputLayer_.nodes_.size());

        inputLayer_.nodes_[nodeIndex].outputValue_ = targetOutputValue;
    }


    /*************************************************************//**
     *
     *  @brief  学習率を設定する
     *  @param  学習率
     *  @return なし
     *
     ****************************************************************/
    void ThreeLayerFeedForward::SetLearningRate(float learningRate)
    {
        inputLayer_.learningRate_ = learningRate;
        hiddenLayer_.learningRate_ = learningRate;
        outputLayer_.learningRate_ = learningRate;
    }


    /*************************************************************//**
     *
     *  @brief  モーメンタム因数を設定する
     *  @param  モーメンタム因数
     *  @return なし
     *
     ****************************************************************/
    void ThreeLayerFeedForward::SetMomentumFactor(float momentumFactor)
    {
        inputLayer_.momentumFactor_ = momentumFactor;
        hiddenLayer_.momentumFactor_ = momentumFactor;
        outputLayer_.momentumFactor_ = momentumFactor;
    }


    /*************************************************************//**
     *
     *  @brief  活性化関数を設定する
     *  @param  活性化関数
     *  @param  レイヤーの種類
     *  @return なし
     *
     ****************************************************************/
    void ThreeLayerFeedForward::SetActiveFanction(ActiveFunction pActiveFunction, eLayerType layerType)
    {
        switch (layerType)
        {
        case INPUT:

            inputLayer_.pActiveFuction_ = pActiveFunction;

            break;
        case HIDDEN:

            hiddenLayer_.pActiveFuction_ = pActiveFunction;

            break;
        case OUTPUT:

            outputLayer_.pActiveFuction_ = pActiveFunction;
            
            break;
        default:

            inputLayer_.pActiveFuction_ = pActiveFunction;
            hiddenLayer_.pActiveFuction_ = pActiveFunction;
            outputLayer_.pActiveFuction_ = pActiveFunction;

            break;
        }
    }


    /*************************************************************//**
     *
     *  @brief  導関数を設定する
     *  @param  導関数
     *  @param  レイヤーの種類
     *  @return なし
     *
     ****************************************************************/
    void ThreeLayerFeedForward::SetDerivativeFunction(DerivativeFunction pDerivativeFunction, eLayerType layerType)
    {
        switch (layerType)
        {
        case INPUT:

            inputLayer_.pDerivativeFunction_ = pDerivativeFunction;

            break;
        case HIDDEN:

            hiddenLayer_.pDerivativeFunction_ = pDerivativeFunction;

            break;
        case OUTPUT:

            outputLayer_.pDerivativeFunction_ = pDerivativeFunction;
            
            break;
        default:

            inputLayer_.pDerivativeFunction_ = pDerivativeFunction;
            hiddenLayer_.pDerivativeFunction_ = pDerivativeFunction;
            outputLayer_.pActiveFuction_ = pDerivativeFunction;

            break;
        }
    }
}