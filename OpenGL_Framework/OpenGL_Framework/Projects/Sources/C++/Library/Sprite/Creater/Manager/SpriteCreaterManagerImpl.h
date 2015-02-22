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
    /* 前方宣言 */
    struct S_ManagementData;


    /* 別名 */
    using SpriteCreaterPtr = std::shared_ptr<C_SpriteCreater>;                                                      // SpriteCreaterPtr型
    using ManagementPair = std::pair<std::string, S_ManagementData>;                                                // ManagementPair型


    /** 管理情報 */
    struct S_ManagementData
    {
        float priority_ = 0.0f;                                                                                     ///< @brief プライオリティ
        SpriteCreaterPtr pSpriteCreater_;                                                                           ///< @brief スプライトクリエイター
    };

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
        void Draw();                                                                                                // 描画処理
        void Sort();                                                                                                // ソート処理
        bool Create(const std::string& rId,                                                                         // スプライトクリエイターを作成
                    const Camera::CameraPtr& prCamera,
                    const Texture::TextureDataPtr pTextureData,
                    uint32_t maxParticleCount,
                    float priority);
        void Destroy(const std::string& rId);                                                                       // スプライトクリエイターを破棄
        void AllDestroy();                                                                                          // スプライトクリエイターを全て破棄
        boost::optional<SpriteCreaterWeakPtr> GetSpriteCreater(const std::string& rId);                             // スプライトクリエイターを取得
    private:
        std::deque<ManagementPair> managementDatas_;                                                                ///< @brief 管理情報
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
        if (managementDatas_.empty() == false) AllDestroy();
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
        for (auto& rManagementData : managementDatas_) rManagementData.second.pSpriteCreater_->Draw();
    }


    /*************************************************************//**
     *
     *  @brief  ソート処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::Sort()
    {

        std::sort(managementDatas_.begin(),
                  managementDatas_.end(),
                  [](const ManagementPair& rManagementData, const ManagementPair& rAnotherManagementData){ return rManagementData.second.priority_ > rAnotherManagementData.second.priority_; });
    }

    /*************************************************************//**
     *
     *  @brief  スプライトクリエイターの作成する
     *  @param  ID
     *  @param  カメラ
     *  @parama テクスチャ情報
     *  @param  スプライトの最大数
     *  @param  優先度
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SpriteCreaterManager::C_SpriteCreaterManagerImpl::Create(const std::string& rId,
                                                                    const Camera::CameraPtr& prCamera,
                                                                    const Texture::TextureDataPtr pTextureData,
                                                                    uint32_t maxSpriteCount,
                                                                    float priority)
    {
        // 既に作成している場合
        auto iterator = std::find_if(managementDatas_.begin(),
                                     managementDatas_.end(),
                                     [&](const ManagementPair& rpPatricleSystem){ return rpPatricleSystem.first == rId; });


        if (iterator != managementDatas_.end())
        {
            std::cout << "[ C_SpriteCreaterManagerImpl::Create ] : 既に同じをスプライトクリエイターを作成しています。" << std::endl;
            std::cout << "                                    ID : " << rId << std::endl;

            return true;
        }

        // スプライトクリエイターを生成し、初期化
        auto pSpriteCreater = std::make_shared<C_SpriteCreater>();

        if (pSpriteCreater->Initialize(prCamera, pTextureData, maxSpriteCount) == false)
        {
            PrintLog("[ C_SpriteCreaterManagerImpl::Initialize ] : スプライトクリエイターの初期化処理に失敗しました。");

            return false;
        }

        // 管理情報を設定し、保持
        S_ManagementData managementData;
        managementData.pSpriteCreater_ = pSpriteCreater;
        managementData.priority_ = priority;

        managementDatas_.emplace_back(rId, managementData);

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
        auto iterator = std::find_if(managementDatas_.begin(),
                                     managementDatas_.end(),
                                     [&](const ManagementPair& rManagementData){ return rManagementData.first == rId; });


        if (iterator == managementDatas_.end())
        {
            std::cout << "[ C_SpriteCreaterManagerImpl::Destroy ] : スプライトクリエイターが作成されていません。" << std::endl;

            return;
        }

        (*iterator).second.pSpriteCreater_->Finalize();
        managementDatas_.erase(iterator);
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
        for (auto& rManagementData : managementDatas_) rManagementData.second.pSpriteCreater_->Finalize();
        managementDatas_.clear();
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
        auto iterator = std::find_if(managementDatas_.begin(),
                                     managementDatas_.end(),
                                     [&](const ManagementPair rpPatricleSystem){ return rpPatricleSystem.first == rId; });
        
        if (iterator == managementDatas_.end()) return boost::none;
        return (*iterator).second.pSpriteCreater_;
    }
}