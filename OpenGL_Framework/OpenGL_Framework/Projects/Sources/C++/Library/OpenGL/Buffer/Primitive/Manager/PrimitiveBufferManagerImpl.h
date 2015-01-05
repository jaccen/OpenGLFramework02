/* ヘッダファイル */
#include "PrimitiveBufferManager.h"
#include <unordered_map>


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
    //! @brief プリミティブバッファインプリメント
    //! @brief プリミティブバッファのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_PrimitiveBufferManager::C_PrimitiveBufferManagerImpl
    {
    public:
        C_PrimitiveBufferManagerImpl();                                                                         // コンストラクタ
        ~C_PrimitiveBufferManagerImpl();                                                                        // デストラクタ
        void Entry(const PrimitiveBufferPtr& prPrimitiveBuffer, const std::string& rId);                        // 登録処理
        void Remove(const std::string& rId);                                                                    // 除去処理
        void AllRemove();                                                                                       // 全てのプリミティブバッファを除去
        boost::optional<const PrimitiveBufferPtr&> GetPrimitiveBuffer(const std::string& rId) const;            // プリミティブバッファを取得
    private:
        std::unordered_map<std::string, PrimitiveBufferPtr> pPrimitiveBuffers_;                                 ///< @brief プリミティブバッファ
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PrimitiveBufferManager::C_PrimitiveBufferManagerImpl::C_PrimitiveBufferManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PrimitiveBufferManager::C_PrimitiveBufferManagerImpl::~C_PrimitiveBufferManagerImpl()
    {
        if (pPrimitiveBuffers_.empty() == false) AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  プリミティブバッファの登録を行う
     *  @param  プリミティブバッファ
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_PrimitiveBufferManager::C_PrimitiveBufferManagerImpl::Entry(const PrimitiveBufferPtr& prPrimitiveBuffer, const std::string& rId)
    {
        // プリミティブバッファが既に登録されている場合
        if (pPrimitiveBuffers_.find(rId) != pPrimitiveBuffers_.end())
        {
            std::cout << "[ C_PrimitiveBufferManagerImpl::Entry ] : プリミティブバッファが既に登録されています。" << std::endl;
            std::cout << "                                     ID : " << rId << std::endl;

            return;
        }

        pPrimitiveBuffers_.emplace(rId, prPrimitiveBuffer);
    }


    /*************************************************************//**
     *
     *  @brief  プリミティブバッファの除去を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_PrimitiveBufferManager::C_PrimitiveBufferManagerImpl::Remove(const std::string& rId)
    {
        // プリミティブバッファが登録されていない場合
        if (pPrimitiveBuffers_.find(rId) == pPrimitiveBuffers_.end())
        {
            std::cout << "[ C_PrimitiveBufferManagerImpl::Remove ] : プリミティブバッファを登録していません。" << std::endl;
            std::cout << "                                      ID : " << rId << std::endl;

            return;
        }

        pPrimitiveBuffers_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  全てのプリミティブバッファの除去を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PrimitiveBufferManager::C_PrimitiveBufferManagerImpl::AllRemove()
    {
        pPrimitiveBuffers_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  プリミティブバッファを取得する
     *  @param  ID
     *  @return 登録されていた場合    ：プリミティブバッファ
     *  @return 登録されてなかった場合：none
     *
     ****************************************************************/
    boost::optional<const PrimitiveBufferPtr&> C_PrimitiveBufferManager::C_PrimitiveBufferManagerImpl::GetPrimitiveBuffer(const std::string& rId) const
    {
        auto iterator = pPrimitiveBuffers_.find(rId);
        if (iterator == pPrimitiveBuffers_.end()) return boost::none;

        return (*iterator).second;
    }
}