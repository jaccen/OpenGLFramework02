/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../../Singleton/Assert/AssertSingleton.h"


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
        namespace
        {
            /* ��� */
            namespace Type
            {
                const int32_t s_NONE = -1;                                  ///< @brief �Ȃ�
            }
        }


        //-------------------------------------------------------------
        //!
        //! @brief ���b�Z�[�W�}�l�[�W���[
        //! @brief ���b�Z�[�W���Ǘ�����N���X
        //! @brief �� �Q�[���I�u�W�F�N�g�}�l�[�W���[�ƕ��p���邱��
        //!
        //-------------------------------------------------------------
        class C_MessageDispatcher : public Singleton::C_AssertSingleton<C_MessageDispatcher>
        {
        public:
            C_MessageDispatcher();                                      // �R���X�g���N�^
            ~C_MessageDispatcher() override;                            // �f�X�g���N�^
            void Update();                                              // �X�V����
            void Send(const std::string& rSenderId,                     // ���M����
                      const std::string& rReceiverId,
                      const std::string& rMessage,
                      int32_t delayFrame = 0);
        private:
            /* �O���錾 */
            class C_MessageDispatcherImpl;

            std::unique_ptr<C_MessageDispatcherImpl> upImpl_;           ///< @brief �������
        };
    }
}