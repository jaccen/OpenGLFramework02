/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Layer/Layer.h"


//-------------------------------------------------------------
//!
//! @brief �j���[�����l�b�g���[�N
//! @brief �j���[�����l�b�g���[�N�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace NeuralNetwork
{
    //-------------------------------------------------------------
    //!
    //! @brief �X���[���C���[�t�B�[�h�t�H���[�h
    //! @brief 3�w�t�H�[�h�t�H���[�h�^�̃l�b�g���[�N��\���N���X
    //!
    //-------------------------------------------------------------
    class ThreeLayerFeedForward
    {
    public:
        /* ���C���[�̎�� */
        enum eLayerType
        {
            INPUT,                                                                              ///< @brief ���̓��C���[
            HIDDEN,                                                                             ///< @brief �B�����C���[
            OUTPUT,                                                                             ///< @brief �o�̓��C���[
            ALL,                                                                                ///< @brief �S�Ẵ��C���[
        };

        ThreeLayerFeedForward();                                                                // �R���X�g���N�^
        ~ThreeLayerFeedForward();                                                               // �f�X�g���N�^
        void Initialize(uint16_t inputLayerNodeCount,                                           // ����������
                        uint16_t hiddenLayerNodeCount,
                        uint16_t outputLayerNodeCount);
        void Finalize();                                                                        // �I������
        void FeedForward();                                                                     // �t�B�[�h�t�H���[�h����
        void BackPropagate();                                                                   // �o�b�N�v���p�Q�[�g����
        float CalculateError();                                                                 // �G���[���v�Z
        void EnableMomentum(bool validFlag = false);                                            // ���[�����^����L����
        float GetOutputValue(uint16_t nodeIndex) const;                                         // �o�͒l���擾
        uint16_t GetMaxOutputValueIndex() const;                                                // �ő�o�͒l�̃C���f�b�N�X���擾
        void SetInputValue(uint16_t nodeIndex, float inputValue);                               // ���͒l��ݒ�
        void SetTargetOutputValue(uint16_t nodeIndex, float targetOutputValue);                 // �ڕW�Ƃ���o�͒l��ݒ�
        void SetLearningRate(float learningRate);                                               // �w�K����ݒ�
        void SetMomentumFactor(float momentumFactor);                                           // ���[�����^��������ݒ�
        void SetActiveFanction(ActiveFunction pActiveFunction, eLayerType layerType = ALL);     // �������֐���ݒ�
    private:
        S_Layer inputLayer_;                                                                    ///< @brief ���̓��C���[
        S_Layer hiddenLayer_;                                                                   ///< @brief �B�ꃌ�C���[
        S_Layer outputLayer_;                                                                   ///< @brief �o�̓��C���[
    };
}