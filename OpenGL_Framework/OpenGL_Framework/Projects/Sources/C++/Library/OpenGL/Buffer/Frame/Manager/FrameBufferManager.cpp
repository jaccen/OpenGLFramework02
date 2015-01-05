/* ヘッダファイル */
#include "FrameBufferManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL関連の名前空間
//!
//-------------------------------------------------------------
namespace OpenGL
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_FrameBufferManager::C_FrameBufferManager() :

        // 実装情報
        upImpl_(std::make_unique<C_FrameBufferManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_FrameBufferManager::~C_FrameBufferManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  フレームバッファの登録を行う
     *  @param  フレームバッファ
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_FrameBufferManager::Entry(const FrameBufferPtr& prFrameBuffer, const std::string& rId)
    {
        upImpl_->Entry(prFrameBuffer, rId);
    }


    /*************************************************************//**
     *
     *  @brief  フレームバッファの除去を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_FrameBufferManager::Remove(const std::string& rId)
    {
        upImpl_->Remove(rId);
    }


    /*************************************************************//**
     *
     *  @brief  全てのフレームバッファの除去を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_FrameBufferManager::AllRemove()
    {
        upImpl_->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  フレームバッファを取得する
     *  @param  ID
     *  @return 取得できた場合      ：フレームバッファ
     *  @return 取得できなかった場合：none
     *
     ****************************************************************/
    boost::optional<const FrameBufferPtr&> C_FrameBufferManager::GetFrameBuffer(const std::string& rId) const
    {
        return upImpl_->GetFrameBuffer(rId);
    }
}