/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Singleton/Singleton.h"
#include "../Light/Light.h"


//-------------------------------------------------------------
//!
//! @brief ライト
//! @brief ライト関連の名前空間
//!
//-------------------------------------------------------------
namespace Light
{
    //-------------------------------------------------------------
    //!
    //! @brief ライトマネージャー
    //! @brief ライトを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_LightManager : public Singleton::C_Singleton<C_LightManager>
    {
        friend C_Singleton<C_LightManager>;
    public:
        void Entry(const LightPtr& prLight, const std::string& rId);                    // 登録処理
        void Remove(const std::string& rId);                                            // 除去処理
        void AllRemove();                                                               // 全てのライトを除去
        boost::optional<const LightPtr&> GetLight(const std::string& rId) const;        // ライトを取得
    private:
        /* 前方宣言 */
        class C_LightManagerImpl;

        std::unique_ptr<C_LightManagerImpl> upImpl_;                                    ///< @brief 実装情報

        C_LightManager();                                                               // コンストラクタ
        ~C_LightManager() override;                                                     // デストラクタ
    };
}