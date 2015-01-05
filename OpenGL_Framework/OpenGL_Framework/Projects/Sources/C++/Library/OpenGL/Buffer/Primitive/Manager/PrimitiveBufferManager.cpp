/* ヘッダファイル */
#include "PrimitiveBufferManagerImpl.h"


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
    C_PrimitiveBufferManager::C_PrimitiveBufferManager() :

        // 実装情報
        upImpl_(std::make_unique<C_PrimitiveBufferManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PrimitiveBufferManager::~C_PrimitiveBufferManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  プリミティブバッファの登録を行う
     *  @param  プリミティブバッファ
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_PrimitiveBufferManager::Entry(const PrimitiveBufferPtr& prPrimitiveBuffer, const std::string& rId)
    {
        upImpl_->Entry(prPrimitiveBuffer, rId);
    }


    /*************************************************************//**
     *
     *  @brief  プリミティブバッファの除去を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_PrimitiveBufferManager::Remove(const std::string& rId)
    {
        upImpl_->Remove(rId);
    }


    /*************************************************************//**
     *
     *  @brief  全てのプリミティブバッファの除去を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PrimitiveBufferManager::AllRemove()
    {
        upImpl_->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  プリミティブバッファを取得する
     *  @param  ID
     *  @return 取得できた場合      ：プリミティブバッファ
     *  @return 取得できなかった場合：none
     *
     ****************************************************************/
    boost::optional<const PrimitiveBufferPtr&> C_PrimitiveBufferManager::GetPrimitiveBuffer(const std::string& rId) const
    {
        return upImpl_->GetPrimitiveBuffer(rId);
    }
}