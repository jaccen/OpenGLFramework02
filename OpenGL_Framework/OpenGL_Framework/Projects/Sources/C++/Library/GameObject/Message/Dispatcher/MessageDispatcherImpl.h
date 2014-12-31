/* �w�b�_�t�@�C�� */
#include "MessageDispatcher.h"
#include "../Telegram/Telegram.h"
#include "../../GameObject.h"
#include "../../Manager/GameObjectManager.h"
#include <set>


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
        //-------------------------------------------------------------
        //!
        //! @brief ���b�Z�[�W�}�l�[�W���[�C���v�������g
        //! @brief ���b�Z�[�W�}�l�[�W���[�̃v���C�x�[�g���̎���
        //!
        //-------------------------------------------------------------
        class C_MessageDispatcher::C_MessageDispatcherImpl
        {
        public:
            C_MessageDispatcherImpl();                      // �R���X�g���N�^
            ~C_MessageDispatcherImpl();                     // �f�X�g���N�^
            void Update();                                  // �X�V����
            void Send(const std::string& rSenderId,         // ���M����
                      const std::string& rReceiverId,
                      const std::string& rMessage,
                      int32_t delayFrame);
        private:
            std::set<S_Telegram> telegrams;                 ///< @brief �e���O����
            int32_t frameCount_ = 0;                        ///< @brief �t���[�����̃J�E���^
        };


        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_MessageDispatcher::C_MessageDispatcherImpl::C_MessageDispatcherImpl()
        {
        }


        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_MessageDispatcher::C_MessageDispatcherImpl::~C_MessageDispatcherImpl()
        {
        }


        /*************************************************************//**
         *
         *  @brief  ���b�Z�[�W�̍X�V�������s��
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_MessageDispatcher::C_MessageDispatcherImpl::Update()
        {
            // �t���[������1����
            ++frameCount_;

            // ���M�t���[�����̍ł��������e���O������
            // ���M�������������Ă����ꍇ�A���b�Z�[�W�𑗐M
            while ((telegrams.empty() == false)
                && (telegrams.begin()->sendFrame_ <= frameCount_))
            {
                // �e���O�������擾
                const S_Telegram& rTelegram = (*telegrams.begin());

                // ��M�҂��擾
                auto pReceiver = C_GameObjectManager::s_GetInstance()->GetGameObjectWithId(rTelegram.receiverId_);
                assert(pReceiver);

                // ��M�҂��烁�b�Z�[�W����
                if (pReceiver.get()->MessageProcess(rTelegram) == false)
                {
                    std::cout << "[ C_MessageDispatcherImpl::Update ] ���b�Z�[�W�����Ɏ��s���܂����B" << std::endl;
                }

                // �e���O����������
                telegrams.erase(telegrams.begin());
            }
        }


        /*************************************************************//**
         *
         *  @brief  ���b�Z�[�W�̑��M�������s��
         *  @param  ���M�҂�ID
         *  @param  ��M�҂�ID
         *  @prama  ���b�Z�[�W
         *  @param  �x���t���[����
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_MessageDispatcher::C_MessageDispatcherImpl::Send(const std::string& rSenderId,
                                                                const std::string& rReceiverId,
                                                                const std::string& rMessage,
                                                                int32_t delayFrame)
        {
            // �e���O�������쐬
            S_Telegram telegram(rSenderId, Type::s_NONE, rReceiverId, rMessage, delayFrame);

            // ���M�҂��o�^����Ă���ꍇ�A���̑��M�҂̎�ނ��e���O�����ɐݒ�
            if (auto pSender = C_GameObjectManager::s_GetInstance()->GetGameObjectWithId(rSenderId))
            {
                telegram.senderType_ = (*pSender)->GetType();
            }

            // ��M�҂��擾
            auto pReceiver = C_GameObjectManager::s_GetInstance()->GetGameObjectWithId(rReceiverId);
            assert(pReceiver);

            if (delayFrame <= 0)
            {
                // ���b�Z�[�W�𑗐M
                if (pReceiver.get()->MessageProcess(telegram) == false)
                {
                    std::cout << "[ C_MessageDispatcherImpl::Update ]���b�Z�[�W�����Ɏ��s���܂����B" << std::endl;
                }
            }
            else
            {
                // ���M�t���[����ݒ肵�A�e���O������ǉ�
                telegram.sendFrame_ += frameCount_;
                telegrams.emplace(telegram);
            }
        }
    }
}