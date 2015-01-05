/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Singleton/Singleton.h"
#include "../Material/Material.h"


//-------------------------------------------------------------
//!
//! @brief マテリアル
//! @brief マテリアル関連の名前空間
//!
//-------------------------------------------------------------
namespace Material
{
    //-------------------------------------------------------------
    //!
    //! @brief マテリアルマネージャー
    //! @brief マテリアルを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_MaterialManager : public Singleton::C_Singleton<C_MaterialManager>
    {
        friend C_Singleton<C_MaterialManager>;
    public:
        void Entry(const MaterialPtr& prMaterial, const std::string& rId);                  // 登録処理
        void Remove(const std::string& rId);                                                // 除去処理
        void AllRemove();                                                                   // 全てのマテリアルを除去
        boost::optional<const MaterialPtr&> GetMaterial(const std::string& rId) const;      // マテリアルを取得
    private:
        /* 前方宣言 */
        class C_MaterialManagerImpl;

        std::unique_ptr<C_MaterialManagerImpl> upImpl_;                                     ///< @brief 実装情報

        C_MaterialManager();                                                                // コンストラクタ
        ~C_MaterialManager() override;                                                      // デストラクタ
    };
}