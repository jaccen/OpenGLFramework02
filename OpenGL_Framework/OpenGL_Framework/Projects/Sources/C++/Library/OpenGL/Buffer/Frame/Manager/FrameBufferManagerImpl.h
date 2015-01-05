/* ヘッダファイル */
#include "FrameBufferMamager.h"
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
    //! @brief フレームバッファインプリメント
    //! @brief フレームバッファのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_FrameBufferManager::C_FrameBufferManagerImpl
    {
    public:
        C_FrameBufferManagerImpl();                                                                         // コンストラクタ
        ~C_FrameBufferManagerImpl();                                                                        // デストラクタ
        void Entry(const FrameBufferPtr& prUniformBuffer, const std::string& rId);                          // 登録処理
        void Remove(const std::string& rId);                                                                // 除去処理
        void AllRemove();                                                                                   // 全てのフレームバッファを除去
        boost::optional<const FrameBufferPtr&> GetFrameBuffer(const std::string& rId) const;                // フレームバッファを取得
    private:
        std::unordered_map<std::string, FrameBufferPtr> pFrameBuffers_;                                     ///< @brief フレームバッファ
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_FrameBufferManager::C_FrameBufferManagerImpl::C_FrameBufferManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_FrameBufferManager::C_FrameBufferManagerImpl::~C_FrameBufferManagerImpl()
    {
        if (pFrameBuffers_.empty() == false) AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  フレームバッファの登録を行う
     *  @param  フレームバッファ
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_FrameBufferManager::C_FrameBufferManagerImpl::Entry(const FrameBufferPtr& prFrameBuffer, const std::string& rId)
    {
        if (pFrameBuffers_.find(rId) != pFrameBuffers_.end())
        {
            std::cout << "[ C_FrameBufferManagerImpl::Entry ] : フレームバッファが既に登録されています。" << std::endl;
            std::cout << "                                 ID : " << rId << std::endl;

            return;
        }

        pFrameBuffers_.emplace(rId, prFrameBuffer);
    }


    /*************************************************************//**
     *
     *  @brief  フレームバッファの除去を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_FrameBufferManager::C_FrameBufferManagerImpl::Remove(const std::string& rId)
    {
        // フレームバッファが登録されていない場合
        if (pFrameBuffers_.find(rId) == pFrameBuffers_.end())
        {
            std::cout << "[ C_FrameBufferManagerImpl::Remove ] : フレームバッファを登録していません。" << std::endl;
            std::cout << "                                  ID : " << rId << std::endl;

            return;
        }

        pFrameBuffers_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  全てのフレームバッファの除去を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_FrameBufferManager::C_FrameBufferManagerImpl::AllRemove()
    {
        pFrameBuffers_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  フレームバッファを取得する
     *  @param  ID
     *  @return 登録されていた場合    ：フレームバッファ
     *  @return 登録されてなかった場合：none
     *
     ****************************************************************/
    boost::optional<const FrameBufferPtr&> C_FrameBufferManager::C_FrameBufferManagerImpl::GetFrameBuffer(const std::string& rId) const
    {
        auto iterator = pFrameBuffers_.find(rId);
        if (iterator == pFrameBuffers_.end()) return boost::none;

        return (*iterator).second;
    }
}