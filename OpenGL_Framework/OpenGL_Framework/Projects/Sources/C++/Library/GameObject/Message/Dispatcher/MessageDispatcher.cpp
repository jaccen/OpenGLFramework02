/* �w�b�_�t�@�C�� */
#include "MessageDispatcherImpl.h"


//-------------------------------------------------------------
//!
//! @brief �Q�[���I�u�W�F�N�g
//! @brief �Q�[���I�u�W�F�N�g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace GameObject
{
    //-------------------------------------------------------------
    //!
    //! @brief ���b�Z�[�W
    //! @brief ���b�Z�[�W�֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace Message
    {
        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_MessageDispatcher::C_MessageDispatcher() :

            // �������
            upImpl_(std::make_unique<C_MessageDispatcherImpl>())

        {
        }


        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_MessageDispatcher::~C_MessageDispatcher()
        {
        }


        /*************************************************************//**
         *
         *  @brief  ���b�Z�[�W�̍X�V�������s��
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_MessageDispatcher::Update()
        {
            upImpl_->Update();
        }


        /*************************************************************//**
         *
         *  @brief  ���b�Z�[�W�̑��M�������s��
         *  @param  ���M�҂�ID
         *  @param  ��M�҂�ID
         *  @param  ���b�Z�[�W
         *  @param  �x���t���[��
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_MessageDispatcher::Send(const std::string& rSenderId,
                                       const std::string& rReceiverId,
                                       const std::string& rMessage,
                                       int32_t delayFrame)
        {
            upImpl_->Send(rSenderId, rReceiverId, rMessage, delayFrame);
        }

        
        /*************************************************************//**
         *
         *  @brief  �A�N�e�B�u��Ԃ�L��������
         *  @param  �L�������f����t���O
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_MessageDispatcher::EnableActive(bool validFlag)
        {
            upImpl_->EnableActive(validFlag);
        }
    }
}