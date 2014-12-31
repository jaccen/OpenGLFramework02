/* ヘッダファイル */
#include "CameraManager.h"
#include "../Camera/Camera.h"
#include <deque>


//-------------------------------------------------------------
//!
//! @brief カメラ
//! @brief カメラ関連の名前空間
//!
//-------------------------------------------------------------
namespace Camera
{
    /** カメラの情報 */
    struct S_CameraData
    {
        CameraPtr pCamera_;                                                                 ///< @brief カメラ
        bool updateFlag_;                                                                   ///< @brief 更新フラグ

        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  カメラ
         *  @param  更新フラグ
         *
         ****************************************************************/
        S_CameraData(const CameraPtr& prCamera, bool updateFlag) :

            // カメラ
            pCamera_(prCamera),

            // 更新フラグ
            updateFlag_(updateFlag)

        {
        }
    };


    //-------------------------------------------------------------
    //!
    //! @brief カメラマネージャーインプリメント
    //! @brief カメラマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_CameraManager::C_CameraManagerImpl
    {
    public:
        C_CameraManagerImpl();                                                              // コンストラクタ
        ~C_CameraManagerImpl();                                                             // デストラクタ
        void Update();                                                                      // 更新処理
        void Entry(const CameraPtr& prCamera,                                               // 登録処理
                   const std::string& rId,
                   bool updateFlag = true);
        void Remove(const std::string& rId);                                                // 除去処理
        void AllRemove();                                                                   // 全てのカメラを除去
        boost::optional<const CameraPtr&> GetCamera(const std::string& rId) const;          // カメラを取得
    private:
        std::deque<std::pair<std::string, S_CameraData>> cameraDatas_;                      ///< @brief カメラの情報
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_CameraManager::C_CameraManagerImpl::C_CameraManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_CameraManager::C_CameraManagerImpl::~C_CameraManagerImpl()
    {
        if (cameraDatas_.empty() == false) AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  カメラの更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_CameraManager::C_CameraManagerImpl::Update()
    {
        for (auto& rCameraData : cameraDatas_)
        {
            if (rCameraData.second.updateFlag_ == true) rCameraData.second.pCamera_->Update();
        }
    }


    /*************************************************************//**
     *
     *  @brief  カメラの登録処理を行う
     *  @param  カメラ
     *  @param  ID
     *  @param  更新フラグ
     *  @return なし
     *
     ****************************************************************/
    void C_CameraManager::C_CameraManagerImpl::Entry(const CameraPtr& prCamera,
                                                     const std::string& rId,
                                                     bool updateFlag)
    {
        // 既に登録されている場合
        auto iterator = std::find_if(cameraDatas_.begin(),
                                     cameraDatas_.end(),
                                     [&](const std::pair<std::string, S_CameraData>& rpPatricleSystem){ return rpPatricleSystem.first == rId; });


        if (iterator != cameraDatas_.end())
        {
            std::cout << "[ C_CameraManagerImpl::Entry ] : カメラが既に登録されています。" << std::endl;
            std::cout << "                            ID : " << rId << std::endl;

            return;
        }

        cameraDatas_.emplace_back(std::piecewise_construct,
                                  std::forward_as_tuple(rId),
                                  std::forward_as_tuple(prCamera, updateFlag));
    }


    /*************************************************************//**
     *
     *  @brief  カメラの除去処理を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_CameraManager::C_CameraManagerImpl::Remove(const std::string& rId)
    {
        // カメラが登録されていない場合
        auto iterator = std::find_if(cameraDatas_.begin(),
                                     cameraDatas_.end(),
                                     [&](const std::pair<std::string, S_CameraData>& rCameraData){ return rCameraData.first == rId; });


        if (iterator == cameraDatas_.end())
        {
            std::cout << "[ C_CameraManagerImpl::Remove ] : カメラを登録していません。" << std::endl;
            std::cout << "                             ID : " << rId << std::endl;

            return;
        }

        cameraDatas_.erase(iterator);
    }


    /*************************************************************//**
     *
     *  @brief  全てのカメラの除去処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_CameraManager::C_CameraManagerImpl::AllRemove()
    {
        cameraDatas_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  カメラを取得する
     *  @param  ID
     *  @return 取得できた場合      ：カメラ
     *  @return 取得できなかった場合：none
     *
     ****************************************************************/
    boost::optional<const CameraPtr&> C_CameraManager::C_CameraManagerImpl::GetCamera(const std::string& rId) const
    {
        auto iterator = std::find_if(cameraDatas_.begin(),
                                     cameraDatas_.end(),
                                     [&](const std::pair<std::string, S_CameraData>& rpPatricleSystem){ return rpPatricleSystem.first == rId; });

        if (iterator == cameraDatas_.end()) return boost::none;

        return (*iterator).second.pCamera_;
    }
}