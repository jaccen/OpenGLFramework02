/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../../Singleton/Assert/AssertSingleton.h"


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
        namespace
        {
            /* 種類 */
            namespace Type
            {
                const int32_t s_NONE = -1;                                  ///< @brief なし
            }
        }


        //-------------------------------------------------------------
        //!
        //! @brief メッセージマネージャー
        //! @brief メッセージを管理するクラス
        //! @brief ※ ゲームオブジェクトマネージャーと併用すること
        //!
        //-------------------------------------------------------------
        class C_MessageDispatcher : public Singleton::C_AssertSingleton<C_MessageDispatcher>
        {
        public:
            C_MessageDispatcher();                                      // コンストラクタ
            ~C_MessageDispatcher() override;                            // デストラクタ
            void Update();                                              // 更新処理
            void Send(const std::string& rSenderId,                     // 送信処理
                      const std::string& rReceiverId,
                      const std::string& rMessage,
                      int32_t delayFrame = 0);
        private:
            /* 前方宣言 */
            class C_MessageDispatcherImpl;

            std::unique_ptr<C_MessageDispatcherImpl> upImpl_;           ///< @brief 実装情報
        };
    }
}