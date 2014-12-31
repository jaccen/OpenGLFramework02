/* ヘッダファイル */
#include "MessageDispatcher.h"
#include "../Telegram/Telegram.h"
#include "../../GameObject.h"
#include "../../Manager/GameObjectManager.h"
#include <set>


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
        //! @brief メッセージマネージャーインプリメント
        //! @brief メッセージマネージャーのプライベート情報の実装
        //!
        //-------------------------------------------------------------
        class C_MessageDispatcher::C_MessageDispatcherImpl
        {
        public:
            C_MessageDispatcherImpl();                      // コンストラクタ
            ~C_MessageDispatcherImpl();                     // デストラクタ
            void Update();                                  // 更新処理
            void Send(const std::string& rSenderId,         // 送信処理
                      const std::string& rReceiverId,
                      const std::string& rMessage,
                      int32_t delayFrame);
        private:
            std::set<S_Telegram> telegrams;                 ///< @brief テレグラム
            int32_t frameCount_ = 0;                        ///< @brief フレーム数のカウンタ
        };


        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_MessageDispatcher::C_MessageDispatcherImpl::C_MessageDispatcherImpl()
        {
        }


        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_MessageDispatcher::C_MessageDispatcherImpl::~C_MessageDispatcherImpl()
        {
        }


        /*************************************************************//**
         *
         *  @brief  メッセージの更新処理を行う
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void C_MessageDispatcher::C_MessageDispatcherImpl::Update()
        {
            // フレーム数を1増加
            ++frameCount_;

            // 送信フレーム数の最も小さいテレグラムが
            // 送信条件を完了していた場合、メッセージを送信
            while ((telegrams.empty() == false)
                && (telegrams.begin()->sendFrame_ <= frameCount_))
            {
                // テレグラムを取得
                const S_Telegram& rTelegram = (*telegrams.begin());

                // 受信者を取得
                auto pReceiver = C_GameObjectManager::s_GetInstance()->GetGameObjectWithId(rTelegram.receiverId_);
                assert(pReceiver);

                // 受信者からメッセージ処理
                if (pReceiver.get()->MessageProcess(rTelegram) == false)
                {
                    std::cout << "[ C_MessageDispatcherImpl::Update ] メッセージ処理に失敗しました。" << std::endl;
                }

                // テレグラムを除去
                telegrams.erase(telegrams.begin());
            }
        }


        /*************************************************************//**
         *
         *  @brief  メッセージの送信処理を行う
         *  @param  送信者のID
         *  @param  受信者のID
         *  @prama  メッセージ
         *  @param  遅延フレーム数
         *  @return なし
         *
         ****************************************************************/
        void C_MessageDispatcher::C_MessageDispatcherImpl::Send(const std::string& rSenderId,
                                                                const std::string& rReceiverId,
                                                                const std::string& rMessage,
                                                                int32_t delayFrame)
        {
            // テレグラムを作成
            S_Telegram telegram(rSenderId, Type::s_NONE, rReceiverId, rMessage, delayFrame);

            // 送信者が登録されている場合、その送信者の種類をテレグラムに設定
            if (auto pSender = C_GameObjectManager::s_GetInstance()->GetGameObjectWithId(rSenderId))
            {
                telegram.senderType_ = (*pSender)->GetType();
            }

            // 受信者を取得
            auto pReceiver = C_GameObjectManager::s_GetInstance()->GetGameObjectWithId(rReceiverId);
            assert(pReceiver);

            if (delayFrame <= 0)
            {
                // メッセージを送信
                if (pReceiver.get()->MessageProcess(telegram) == false)
                {
                    std::cout << "[ C_MessageDispatcherImpl::Update ]メッセージ処理に失敗しました。" << std::endl;
                }
            }
            else
            {
                // 送信フレームを設定し、テレグラムを追加
                telegram.sendFrame_ += frameCount_;
                telegrams.emplace(telegram);
            }
        }
    }
}