/* 二重インクルード防止 */
#pragma once


//-------------------------------------------------------------
//!
//! @brief ゲームオブジェクト
//! @brief ゲームに存在するオブジェクト関連の名前空間
//!
//-------------------------------------------------------------
namespace GameObject
{
    /* 前方宣言 */
    namespace Message
    {
        struct S_Telegram;
    }


    //-------------------------------------------------------------
    //!
    //! @brief ゲームオブジェクト
    //! @brief ゲームオブジェクトの基底クラス
    //!
    //-------------------------------------------------------------
    class C_GameObject
    {
    public:
        C_GameObject() = default;                                                       // コンストラクタ
        C_GameObject(const std::string& rId,                                            // コンストラクタ
                     int32_t type);
        virtual ~C_GameObject();                                                        // デストラクタ
        virtual bool Update() = 0;                                                      // 更新処理
        virtual void Draw() = 0;                                                        // 描画処理
        virtual bool MessageProcess(const Message::S_Telegram& rTelegram) = 0;          // メッセージ処理
        void AddStringToId(const std::string& rString);                                 // IDに文字列を加える
        const std::string& GetId() const;                                               // IDを取得
        int32_t GetType() const;                                                        // 種類を取得
        bool IsExistanceFlag() const;                                                   // 存在を確認するフラグを取得
        void SetId(const std::string& rId);                                             // IDを設定
        void SetType(int32_t type);                                                     // 種類を設定
        void SetExistanceFlag(bool existanceFlag);                                      // 存在を確認するフラグを設定
    protected:
        std::string id_;                                                                ///< @brief ID
        int32_t type_ = -1;                                                             ///< @brief 種類
        bool existenceFlag_ = true;                                                     ///< @brief 存在のフラグ
    };
}