/* ヘッダファイル */
#include "SpriteCreaterManager.h"
#include "../../../Debug/Helper/DebugHelper.h"
#include <deque>


//-------------------------------------------------------------
//!
//! @brief スプライト
//! @brief スプライト関連の名前空間
//!
//-------------------------------------------------------------
namespace Sprite
{
    /* 別名 */
    using SpriteCreaterPtr = std::shared_ptr<C_SpriteCreater>;                                                      // SpriteCreaterPtr型


    //-------------------------------------------------------------
    //!
    //! @brief スプライトクリエイターマネージャーインプリメント
    //! @brief スプライトクリエイターのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_SpriteCreaterManager::C_SpriteCreaterManagerImpl
    {
    public:
        C_SpriteCreaterManagerImpl();                                                                               // コンストラクタ
        ~C_SpriteCreaterManagerImpl();                                                                              // デストラクタ
        void Update();                                                                                              // 更新処理
        void Draw();                                                                                                // 描画処理
        bool Create(const std::string& rId,                                                                         // スプライトクリエイターを作成
                    const Camera::CameraPtr& prCamera,
                    const Texture::TextureDataPtr pTextureData,
                    uint32_t maxParticleCount);
        void Destroy(const std::string& rId);                                                                       // スプライトクリエイターを破棄
        void AllDestroy();                                                                                          // スプライトクリエイターを全て破棄
        boost::optional<SpriteCreaterWeakPtr> GetSpriteCreater(const std::string& rId);                             // スプライトクリエイターを取得
    private:
        std::deque<std::pair<std::string, SpriteCreaterPtr>> pSpriteCreaters_;                                      ///< @brief スプライトクリエイター
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::C_SpriteCreaterManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::~C_SpriteCreaterManagerImpl()
    {
        if (pSpriteCreaters_.empty() == false) AllDestroy();
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::Draw()
    {
        for (auto &rPatricleSystem : pSpriteCreaters_) rPatricleSystem.second->Draw();
    }


    /*************************************************************//**
     *
     *  @brief  スプライトクリエイターの作成する
     *  @param  ID
     *  @param  カメラ
     *  @parama テクスチャ情報
     *  @param  スプライトの最大数
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::Create(const std::string& rId,
                                                                    const Camera::CameraPtr& prCamera,
                                                                    const Texture::TextureDataPtr pTextureData,
                                                                    uint32_t maxParticleCount)
    {
        // 既に作成している場合
        auto iterator = std::find_if(pSpriteCreaters_.begin(),
                                     pSpriteCreaters_.end(),
                                     [&](const std::pair<std::string, SpriteCreaterPtr>& rpPatricleSystem){ return rpPatricleSystem.first == rId; });


        if (iterator != pSpriteCreaters_.end())
        {
            std::cout << "[ C_SpriteCreaterManagerImpl::Create ] : 既に同じをスプライトクリエイターを作成しています。" << std::endl;
            std::cout << "                                    ID : " << rId << std::endl;

            return true;
        }

        // スプライトクリエイターを生成し、初期化
        auto pParticleSystem = std::make_shared<C_SpriteCreater>();

        if (pParticleSystem->Initialize(prCamera, pTextureData, maxParticleCount) == false)
        {
            PrintLog("[ C_SpriteCreaterManagerImpl::Initialize ] : スプライトクリエイターの初期化処理に失敗しました。");

            return false;
        }

        // スプライトクリエイターを保持する
        pSpriteCreaters_.emplace_back(rId, pParticleSystem);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  スプライトクリエイターを破棄する
     *  @parama ID
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::Destroy(const std::string& rId)
    {
        // スプライトクリエイターが作成されていない場合
        auto iterator = std::find_if(pSpriteCreaters_.begin(),
                                     pSpriteCreaters_.end(),
                                     [&](const std::pair<std::string, SpriteCreaterPtr>& rpPatricleSystem){ return rpPatricleSystem.first == rId; });


        if (iterator == pSpriteCreaters_.end())
        {
            std::cout << "[ C_SpriteCreaterManagerImpl::Destroy ] : スプライトクリエイターが作成されていません。" << std::endl;

            return;
        }

        (*iterator).second->Finalize();
        pSpriteCreaters_.erase(iterator);
    }


    /*************************************************************//**
     *
     *  @brief  スプライトクリエイターを全て破棄する
     *  @parama なし
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::AllDestroy()
    {
        for (auto& rParticleSystem : pSpriteCreaters_) rParticleSystem.second->Finalize();
        pSpriteCreaters_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  スプライトクリエイターを取得する
     *  @parama ID
     *  @return 作成されている場合  ：スプライトクリエイター
     *  @return 作成されていない場合：none
     *
     ****************************************************************/
    boost::optional<SpriteCreaterWeakPtr> C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::GetSpriteCreater(const std::string& rId)
    {
        auto iterator = std::find_if(pSpriteCreaters_.begin(),
                                     pSpriteCreaters_.end(),
                                     [&](const std::pair<std::string, SpriteCreaterPtr>& rpPatricleSystem){ return rpPatricleSystem.first == rId; });
        
        if (iterator == pSpriteCreaters_.end()) return boost::none;
        return (*iterator).second;
    }
}