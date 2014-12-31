/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include <vector>


//-------------------------------------------------------------
//!
//! @brief �j���[�����l�b�g���[�N
//! @brief �j���[�����l�b�g���[�N�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace NeuralNetwork
{
    /* �^�ϊ� */
    using ActiveFunction = float(*)(float);                                     ///< @brief ActiveFunction�^��錾


    //-------------------------------------------------------------
    //!
    //! @brief �A�N�e�B�u�t�@���N�V����
    //! @brief �������֐����܂Ƃ߂����[�e�B���e�B�N���X
    //!
    //-------------------------------------------------------------
    class C_ActiveFunction
    {
    public:
        static float s_Step(float x);                                           // �i�K�֐�
        static float s_Linear(float x);                                         // ���`�֐�
        static float s_Sigmoid(float x);                                        // �V�O���C�h�֐�
        static float s_HyperbolicTangent(float x);                              // �o�Ȑ����ڊ֐�
    };


    //-------------------------------------------------------------
    //!
    //! @brief �m�[�h
    //! @brief �m�[�h��\���N���X
    //!
    //-------------------------------------------------------------
    struct S_Node
    {
        float outputValue_ = 0.0f;                                              ///< @brief �o�͒l
        float targetOutputValue_ = 0.0f;                                        ///< @brief �ڕW�̏o�͒l
        float error_ = 0.0f;                                                    ///< @brief �G���[( �덷 )
        std::vector<float> weights_;                                            ///< @brief �d��
        std::vector<float> weightAdjustments_;                                  ///< @brief �d�݂̒����l
    };


    //-------------------------------------------------------------
    //!
    //! @brief ���C���[
    //! @brief �w��\���N���X
    //!
    //-------------------------------------------------------------
    struct S_Layer
    {
        uint16_t childNodeCount_ = 0;                                           ///< @brief �q�m�[�h�̐�
        uint16_t parentNodeCount_ = 0;                                          ///< @brief �e�m�[�h�̐�
        float learningRate_ = 0.5f;                                             ///< @brief �w�K��
        float momentumFactor_ = 0.5f;                                           ///< @brief ���[�����^������
        bool useMomentumFlag_ = false;                                          ///< @brief ���[�����^���̎g�p�t���O
        std::vector<S_Node> nodes_;                                             ///< @brief �m�[�h
        std::vector<float> biasValues_;                                         ///< @brief �o�C�A�X�l
        std::vector<float> biasWeights_;                                        ///< @brief �o�C�A�X�̏d��
        S_Layer* pParentLayer_ = nullptr;                                       ///< @brief �e�̃��C���[
        S_Layer* pChildLayer_ = nullptr;                                        ///< @brief �q�̃��C���[
        ActiveFunction pActiveFuction_ = C_ActiveFunction::s_Sigmoid;           ///< @brief �������֐�

        S_Layer();                                                              // �R���X�g���N�^
        ~S_Layer();                                                             // �f�X�g���N�^
        void Initialize(uint16_t nodeCount,                                     // ����������
                        uint16_t parentNodeCount,
                        uint16_t childNodeCount,
                        S_Layer* pParentLayer,
                        S_Layer* pChildLayer);
        void Finalize();                                                        // �I������
        void RandomizeWeight();                                                 // �E�F�C�g�������_����
        void AdjustWeight();                                                    // �E�F�C�g�̒���
        void CalculateError();                                                  // �G���[�̌v�Z
        void CalculateOutValue();                                               // �o�͒l���v�Z
    };
}