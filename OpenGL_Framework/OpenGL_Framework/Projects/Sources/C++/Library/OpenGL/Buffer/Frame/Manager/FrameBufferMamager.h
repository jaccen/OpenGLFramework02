/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../../../Singleton/Singleton.h"
#include "../FrameBuffer.h"


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
    //! @brief フレームバッファマネージャー
    //! @brief フレームバッファを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_FrameBufferManager : public Singleton::C_Singleton<C_FrameBufferManager>
    {
        friend C_Singleton<C_FrameBufferManager>;
    public:
        void Entry(const FrameBufferPtr& prFrameBuffer, const std::string& rId);                        // 登録処理
        void Remove(const std::string& rId);                                                            // 除去処理
        void AllRemove();                                                                               // 全てのフレームバッファを除去
        boost::optional<const FrameBufferPtr&> GetFrameBuffer(const std::string& rId) const;            // フレームバッファを取得
    private:
        /* 前方宣言 */
        class C_FrameBufferManagerImpl;

        std::unique_ptr<C_FrameBufferManagerImpl> upImpl_;                                              ///< @brief 実装情報

        C_FrameBufferManager();                                                                         // コンストラクタ
        ~C_FrameBufferManager() override;                                                               // デストラクタ
    };
}