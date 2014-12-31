/* 二重インクルード防止 */
#pragma once


//-------------------------------------------------------------
//!
//! @brief ゲームオブジェクト
//! @brief ゲームオブジェクト関連の名前空間
//!
//-------------------------------------------------------------
namespace GameObject
{
    //-------------------------------------------------------------
    //!
    //! @brief メッセージ
    //! @brief メッセージ関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace Message
    {
        //-------------------------------------------------------------
        //!
        //! @brief テレグラム
        //! @brief メッセージの情報を表す構造体
        //!
        //-------------------------------------------------------------
        struct S_Telegram
        {
            std::string senderId_;                          ///< @brief 送信者のID
            int32_t senderType_ = 0;                        ///< @brief 送信者の種類
            std::string receiverId_;                        ///< @brief 受信者のID
            std::string message_;                           ///< @brief メッセージ
            int32_t sendFrame_ = 0;                         ///< @brief 送信フレーム

            S_Telegram() = default;                         // デフォルトコンストラクタ

            /*************************************************************//**
             *
             *  @brief  コンストラクタ
             *  @param  送信者のID
             *  @param  送信者の種類
             *  @param  受信者のID
             *  @param  メッセージ
             *  @param  送信フレーム
             *
             ****************************************************************/
            S_Telegram(const std::string& rSenderId,
                int32_t senderType,
                const std::string& rReceiverId,
                const std::string& rMessage,
                int32_t sendFrame) :

                // 送信者のID
                senderId_(rSenderId),

                // 送信者の種類
                senderType_(senderType),

                // 受信者のID
                receiverId_(rReceiverId),

                // メッセージ
                message_(rMessage),

                // 送信フレーム
                sendFrame_(sendFrame)

            {
            }


#pragma region S_Telegram型とのフレンド演算子のオーバーロード


            /*************************************************************//**
             *
             *  @brief  2つのテレグラムが同じか判断する
             *  @param  テレグラム
             *  @param  もう一つのテレグラム
             *  @return 同じ場合 : true
             *  @return 違う場合 : false
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
             *  @brief  2つのテレグラムを比較する
             *  @param  テレグラム
             *  @param  もう一つのテレグラム
             *  @return 一つ目のテレグラムの方が送信フレーム数が小さい場合 : true
             *  @return          2つのテレグラムの送信フレーム数が同じ場合 : false
             *  @return 一つ目のテレグラムの方が送信フレーム数が大きい場合 : false
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