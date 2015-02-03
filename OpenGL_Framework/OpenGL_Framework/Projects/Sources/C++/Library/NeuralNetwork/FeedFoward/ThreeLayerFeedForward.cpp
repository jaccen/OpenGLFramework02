/* �w�b�_�t�@�C�� */
#include "ThreeLayerFeedForward.h"
#include "../../../Library/Math/Define/MathDefine.h"


//-------------------------------------------------------------
//!
//! @brief �j���[�����l�b�g���[�N
//! @brief �j���[�����l�b�g���[�N�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace NeuralNetwork
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    ThreeLayerFeedForward::ThreeLayerFeedForward()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    ThreeLayerFeedForward::~ThreeLayerFeedForward()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  ���̓��C���[�̃m�[�h��
     *  @param  �B�����C���[�̃m�[�h��
     *  @param  �o�̓��C���[�̃m�[�h��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void ThreeLayerFeedForward::Initialize(uint16_t inputLayerNodeCount,
                                           uint16_t hiddenLayerNodeCount,
                                           uint16_t outputLayerNodeCount)
    {
        // ���̓��C���[�̏���������
        inputLayer_.Initialize(inputLayerNodeCount,
                               0,
                               hiddenLayerNodeCount,
                               nullptr,
                               &hiddenLayer_);

        inputLayer_.RandomizeWeight();

        // �B�����C���[�̏���������
        hiddenLayer_.Initialize(hiddenLayerNodeCount,
                                inputLayerNodeCount,
                                outputLayerNodeCount,
                                &inputLayer_,
                                &outputLayer_);

        hiddenLayer_.RandomizeWeight();

        // �o�̓��C���[�̏���������
        outputLayer_.Initialize(outputLayerNodeCount,
                                hiddenLayerNodeCount,
                                0,
                                &hiddenLayer_,
                                nullptr);
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
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
     *  @brief  �t�B�[�h�t�H���[�h�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void ThreeLayerFeedForward::FeedForward()
    {
        hiddenLayer_.CalculateOutValue();
        outputLayer_.CalculateOutValue();
    }


    /*************************************************************//**
     *
     *  @brief  �o�b�N�v���p�Q�[�g�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void ThreeLayerFeedForward::BackPropagate()
    {
        // �G���[���v�Z
        outputLayer_.CalculateError();
	    hiddenLayer_.CalculateError();

        // �d�݂̒���
	    hiddenLayer_.AdjustWeight();
	    inputLayer_.AdjustWeight();
    }


    /*************************************************************//**
     *
     *  @brief  �G���[�̌v�Z���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
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
     *  @brief  ���[�����^����L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
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
     *  @brief  �o�͒l���擾����
     *  @param  �m�[�h�̃C���f�b�N�X
     *  @return �Ȃ�
     *
     ****************************************************************/
    float ThreeLayerFeedForward::GetOutputValue(uint16_t nodeIndex) const
    {
        assert(nodeIndex < outputLayer_.nodes_.size());

        return outputLayer_.nodes_[nodeIndex].outputValue_;
    }


    /*************************************************************//**
     *
     *  @brief  �ő�o�͒l�̃C���f�b�N�X���擾
     *  @param  �Ȃ�
     *  @return �ő�o�͒l�̃C���f�b�N�X
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
     *  @brief  ���͒l��ݒ肷��
     *  @param  �m�[�h�̃C���f�b�N�X
     *  @param  ���͒l
     *  @return �Ȃ�
     *
     ****************************************************************/
    void ThreeLayerFeedForward::SetInputValue(uint16_t nodeIndex, float inputValue)
    {
        assert(nodeIndex < inputLayer_.nodes_.size());

        inputLayer_.nodes_[nodeIndex].outputValue_ = inputValue;
    }


    /*************************************************************//**
     *
     *  @brief  ���͒l��ݒ肷��
     *  @param  �m�[�h�̃C���f�b�N�X
     *  @param  ���͒l
     *  @return �Ȃ�
     *
     ****************************************************************/
    void ThreeLayerFeedForward::SetTargetOutputValue(uint16_t nodeIndex, float targetOutputValue)
    {
        assert(nodeIndex < inputLayer_.nodes_.size());

        inputLayer_.nodes_[nodeIndex].outputValue_ = targetOutputValue;
    }


    /*************************************************************//**
     *
     *  @brief  �w�K����ݒ肷��
     *  @param  �w�K��
     *  @return �Ȃ�
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
     *  @brief  ���[�����^��������ݒ肷��
     *  @param  ���[�����^������
     *  @return �Ȃ�
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
     *  @brief  �������֐���ݒ肷��
     *  @param  �������֐�
     *  @param  ���C���[�̎��
     *  @return �Ȃ�
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
     *  @brief  ���֐���ݒ肷��
     *  @param  ���֐�
     *  @param  ���C���[�̎��
     *  @return �Ȃ�
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