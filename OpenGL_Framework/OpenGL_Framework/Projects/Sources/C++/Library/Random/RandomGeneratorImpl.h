/* �w�b�_�t�@�C�� */
#include "RandomGenerator.h"
#include <random>


//-------------------------------------------------------------
//!
//! @brief �����_��
//! @brief �����֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Random
{
    //-------------------------------------------------------------
    //!
    //! @brief �����_���}�l�[�W���[�C���v�������g
    //! @brief �����_���}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_RandomGenerator::C_RandomGeneratorImpl
    {
    public:
        C_RandomGeneratorImpl();                        // �R���X�g���N�^
        ~C_RandomGeneratorImpl();                       // �f�X�g���N�^
        std::random_device& GetDevice();                // �����f�o�C�X���擾
        std::mt19937& GetEngine();                      // �����G���W�����擾
    private:
        std::random_device device_;                     ///< @brief �����f�o�C�X
        std::mt19937 engine_;                           ///< @brief �����G���W��
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_RandomGenerator::C_RandomGeneratorImpl::C_RandomGeneratorImpl()
    {
        // �����_���V�[�h�̏�����
        engine_.seed(device_());
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_RandomGenerator::C_RandomGeneratorImpl::~C_RandomGeneratorImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �����f�o�C�X���擾����
     *  @param  �Ȃ�
     *  @return �����f�o�C�X
     *
     ****************************************************************/
    std::random_device& C_RandomGenerator::C_RandomGeneratorImpl::GetDevice()
    {
        return device_;
    }


    /*************************************************************//**
     *
     *  @brief  �����G���W�����擾����
     *  @param  �Ȃ�
     *  @return �����G���W��
     *
     ****************************************************************/
    std::mt19937& C_RandomGenerator::C_RandomGeneratorImpl::GetEngine()
    {
        return engine_;
    }
}