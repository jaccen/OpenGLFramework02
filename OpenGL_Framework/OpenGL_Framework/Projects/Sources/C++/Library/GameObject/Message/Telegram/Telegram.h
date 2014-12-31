/* ��d�C���N���[�h�h�~ */
#pragma once


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
        //! @brief �e���O����
        //! @brief ���b�Z�[�W�̏���\���\����
        //!
        //-------------------------------------------------------------
        struct S_Telegram
        {
            std::string senderId_;                          ///< @brief ���M�҂�ID
            int32_t senderType_ = 0;                        ///< @brief ���M�҂̎��
            std::string receiverId_;                        ///< @brief ��M�҂�ID
            std::string message_;                           ///< @brief ���b�Z�[�W
            int32_t sendFrame_ = 0;                         ///< @brief ���M�t���[��

            S_Telegram() = default;                         // �f�t�H���g�R���X�g���N�^

            /*************************************************************//**
             *
             *  @brief  �R���X�g���N�^
             *  @param  ���M�҂�ID
             *  @param  ���M�҂̎��
             *  @param  ��M�҂�ID
             *  @param  ���b�Z�[�W
             *  @param  ���M�t���[��
             *
             ****************************************************************/
            S_Telegram(const std::string& rSenderId,
                int32_t senderType,
                const std::string& rReceiverId,
                const std::string& rMessage,
                int32_t sendFrame) :

                // ���M�҂�ID
                senderId_(rSenderId),

                // ���M�҂̎��
                senderType_(senderType),

                // ��M�҂�ID
                receiverId_(rReceiverId),

                // ���b�Z�[�W
                message_(rMessage),

                // ���M�t���[��
                sendFrame_(sendFrame)

            {
            }


#pragma region S_Telegram�^�Ƃ̃t�����h���Z�q�̃I�[�o�[���[�h


            /*************************************************************//**
             *
             *  @brief  2�̃e���O���������������f����
             *  @param  �e���O����
             *  @param  ������̃e���O����
             *  @return �����ꍇ : true
             *  @return �Ⴄ�ꍇ : false
             *
             ****************************************************************/
            friend bool operator==(const S_Telegram& rTelegram, const S_Telegram& rAnotherTelegram)
            {
                return ((rTelegram.senderId_ == rAnotherTelegram.senderId_)
                     && (rTelegram.senderType_ == rAnotherTelegram.senderType_)
                     && (rTelegram.receiverId_ == rAnotherTelegram.receiverId_)
                     && (rTelegram.message_ == rAnotherTelegram.message_)
                     && (rTelegram.sendFrame_ == rAnotherTelegram.sendFrame_));
            }


            /*************************************************************//**
             *
             *  @brief  2�̃e���O�������r����
             *  @param  �e���O����
             *  @param  ������̃e���O����
             *  @return ��ڂ̃e���O�����̕������M�t���[�������������ꍇ : true
             *  @return          2�̃e���O�����̑��M�t���[�����������ꍇ : false
             *  @return ��ڂ̃e���O�����̕������M�t���[�������傫���ꍇ : false
             *
             ****************************************************************/
            friend bool operator<(const S_Telegram& rTelegram, const S_Telegram& rAnotherTelegram)
            {
                if (rTelegram == rAnotherTelegram) return false;

                return  (rTelegram.sendFrame_ < rAnotherTelegram.sendFrame_);
            }

#pragma endregion 

        };
    }
}