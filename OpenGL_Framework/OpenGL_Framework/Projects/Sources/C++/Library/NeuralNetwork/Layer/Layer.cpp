/* �w�b�_�t�@�C�� */
#include "Layer.h"
#include "../../../Library/Random/RandomGenerator.h"


//-------------------------------------------------------------
//!
//! @brief �j���[�����l�b�g���[�N
//! @brief �j���[�����l�b�g���[�N�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace NeuralNetwork
{

#pragma region C_ActiveFunction�N���X


    /*************************************************************//**
     *
     *  @brief  �i�K�֐�����l�����߂�
     *  @param  �l
     *  @return 0�܂���1
     *
     ****************************************************************/
    float C_ActiveFunction::s_Step(float x)
    {
        return (x <= 0.0f) ? 0.0f : 1.0f;
    }


    /*************************************************************//**
     *
     *  @brief  ���`�֐�����l�����߂�
     *  @param  �l
     *  @return �������Ɠ����l
     *
     ****************************************************************/
    float C_ActiveFunction::s_Linear(float x)
    {
        return x;
    }


    /*************************************************************//**
     *
     *  @brief  �V�O���C�h�֐�����l�����߂�
     *  @param  �l
     *  @return 0����1�܂ł̒l
     *
     ****************************************************************/
    float C_ActiveFunction::s_Sigmoid(float x)
    {
        return 1.0f / (1.0f + std::exp(-x));
    }


    /*************************************************************//**
     *
     *  @brief  �o�Ȑ����ڊ֐�����l�����߂�
     *  @param  �l
     *  @return -1����1�܂ł̒l
     *
     ****************************************************************/
    float C_ActiveFunction::s_HyperbolicTangent(float x)
    {
        float ePowerX = std::exp(x);
        float ePowerMinusX = std::exp(-x);

        return (ePowerX - ePowerMinusX) / (ePowerX + ePowerMinusX);
    }



#pragma endregion


#pragma region C_ActiveFunction�N���X


    /*************************************************************//**
     *
     *  @brief  �V�O���C�h���֐�����X�������߂�
     *  @param  �l
     *  @return �X��
     *
     ****************************************************************/
    float C_DerivativeFunction::s_Sigmoid(float x)
    {
        return x * (1.0f - x);
    }


#pragma endregion


#pragma region S_Layer�\����


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    S_Layer::S_Layer()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    S_Layer::~S_Layer()
    {
        if (nodes_.empty() == false) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �m�[�h��
     *  @param  �e�̃m�[�h��
     *  @param  �q�̃m�[�h��
     *  @param  �e�̃��C���[
     *  @param  �q�̃��C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void S_Layer::Initialize(uint16_t nodeCount,
                             uint16_t parentNodeCount,
                             uint16_t childNodeCount,
                             S_Layer* pParentLayer,
                             S_Layer* pChildLayer)
    {
        // �e�Ǝq�̃m�[�h����ݒ�
        parentNodeCount_ = parentNodeCount;
        childNodeCount_ = childNodeCount;

        // �m�[�h�̐���
        nodes_.resize(nodeCount);

        // �e�̃��C���[��ݒ�
        if (pParentLayer) pParentLayer_ = pParentLayer;

        // �q�̃��C���[��ݒ�
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
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
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
     *  @brief  �E�F�C�g�������_��������
     *  @param  �ŏ��l
     *  @param  �ő�l
     *  @return �Ȃ�
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
     *  @brief  �E�F�C�g�𒲐߂��s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void S_Layer::AdjustWeight()
    {
        if (pChildLayer_)
        {
            // ������d��
            float addWeight = 0.0f;

            for (auto& rNode : nodes_)
            {
                for (size_t i = 0; i < childNodeCount_; ++i)
                {
                    // ������d�݂��v�Z
                    addWeight = learningRate_ * pChildLayer_->nodes_[i].error_ * rNode.outputValue_;

                    if (useMomentumFlag_ == true)
                    {
                        // ���[�����^�����g�p����ꍇ�͉�����d�݂Ƀ��[�����^�����q�ƒ��ߒl���������l�𑫂��A
                        // ���ߒl�ɉ�����E�F�C�g��ݒ�
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
                // �o�C�A�X�̏d�݂𒲐�
                biasWeights_[i] += learningRate_ * pChildLayer_->nodes_[i].error_ * biasValues_[i];
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  �G���[�̌v�Z���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void S_Layer::CalculateError()
    {
        /* ���̓��C���[�� */
        if (pParentLayer_ == nullptr)
        {
            for (auto& rNode : nodes_)
            {
                rNode.error_ = 0.0f;
            }
        }
        /* �o�̓��C���[�� */
        else if (pChildLayer_ == nullptr)
        {
            for (auto& rNode : nodes_)
            {
                rNode.error_ = (rNode.targetOutputValue_ - rNode.outputValue_) * pDerivativeFunction_(rNode.outputValue_);
            }
        }
        /* �B�ꃌ�C���[�� */
        else
        {
            // �G���[�̍��v
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
     *  @brief �o�͒l�̌v�Z���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void S_Layer::CalculateOutValue()
    {
        if (pParentLayer_)
        {
            // �o�͒l
            float outValue = 0.0f;

            for (size_t i = 0, nodeCount = nodes_.size(); i < nodeCount; ++i)
            {
                // �o�͒l�����߂�
                for (size_t j = 0; j < parentNodeCount_; ++j)
                {
                    outValue += pParentLayer_->nodes_[j].outputValue_ * pParentLayer_->nodes_[j].weights_[i];
                }

                // �o�͒l�ɐe�̃o�C�A�X�l�����Z
                outValue += pParentLayer_->biasValues_[i] * pParentLayer_->biasWeights_[i];

                // ���`�������֐��ŏo�͒l������
                nodes_[i].outputValue_ = pActiveFuction_(outValue);
            }
        }
    }


#pragma endregion


}