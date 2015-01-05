/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../../../Singleton/Singleton.h"
#include "../PrimitiveBuffer.h"


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL関連の名前空間
//!
//-------------------------------------------------------------
namespace OpenGL
{
    //-------------------------------------------------------------
    //!
    //! @brief プリミティブバッファマネージャー
    //! @brief プリミティブバッファを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_PrimitiveBufferManager : public Singleton::C_Singleton<C_PrimitiveBufferManager>
    {
        friend C_Singleton<C_PrimitiveBufferManager>;
    public:
        void Entry(const PrimitiveBufferPtr& prPrimitiveBuffer, const std::string& rId);                    // 登録処理
        void Remove(const std::string& rId);                                                                // 除去処理
        void AllRemove();                                                                                   // 全てのプリミティブバッファを除去
        boost::optional<const PrimitiveBufferPtr&> GetPrimitiveBuffer(const std::string& rId) const;        // プリミティブバッファを取得
    private:
        /* 前方宣言 */
        class C_PrimitiveBufferManagerImpl;

        std::unique_ptr<C_PrimitiveBufferManagerImpl> upImpl_;                                              ///< @brief 実装情報

        C_PrimitiveBufferManager();                                                                         // コンストラクタ
        ~C_PrimitiveBufferManager() override;                                                               // デストラクタ
    };
}