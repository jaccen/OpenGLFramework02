/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../../Singleton/Singleton.h"
#include "../JsonObject.h"


//-------------------------------------------------------------
///
/// @brief JSON
/// @brief JSON関連のクラスや関数などに付ける名前空間
///
//-------------------------------------------------------------
namespace JSON
{
    //-------------------------------------------------------------
    //!
    //! @brief JSONオブジェクトマネージャー
    //! @brief JSONオブジェクトを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_JsonObjectManager : public Singleton::C_Singleton<C_JsonObjectManager>
    {
        friend C_Singleton<C_JsonObjectManager>;
    public:
        void Entry(const JsonObjectPtr& prLight, const std::string& rId);                       // 登録処理
        void Remove(const std::string& rId);                                                    // 除去処理
        void AllRemove();                                                                       // 全てのJSONオブジェクトを除去
        boost::optional<const JsonObjectPtr&> GetJsonObject(const std::string& rId) const;      // JSONオブジェクトを取得
    private:
        /* 前方宣言 */
        class C_JsonObjectManagerImpl;

        std::unique_ptr<C_JsonObjectManagerImpl> upImpl_;                                       ///< @brief 実装情報

        C_JsonObjectManager();                                                                  // コンストラクタ
        ~C_JsonObjectManager() override;                                                        // デストラクタ
    };
}