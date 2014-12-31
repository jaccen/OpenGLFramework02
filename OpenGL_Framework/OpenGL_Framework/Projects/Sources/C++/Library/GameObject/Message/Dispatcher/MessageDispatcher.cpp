/* ヘッダファイル */
#include "MessageDispatcherImpl.h"


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
        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_MessageDispatcher::C_MessageDispatcher() :

            // 実装情報
            upImpl_(std::make_unique<C_MessageDispatcherImpl>())

        {
        }


        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_MessageDispatcher::~C_MessageDispatcher()
        {
        }


        /*************************************************************//**
         *
         *  @brief  メッセージの更新処理を行う
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void C_MessageDispatcher::Update()
        {
            upImpl_->Update();
        }


        /*************************************************************//**
         *
         *  @brief  メッセージの送信処理を行う
         *  @param  送信者のID
         *  @param  
         *  @return なし
         *
         ****************************************************************/
        void C_MessageDispatcher::Send(const std::string& rSenderId,
                                       const std::string& rReceiverId,
                                       const std::string& rMessage,
                                       int32_t delayFrame)
        {
            upImpl_->Send(rSenderId, rReceiverId, rMessage, delayFrame);
        }
    }
}