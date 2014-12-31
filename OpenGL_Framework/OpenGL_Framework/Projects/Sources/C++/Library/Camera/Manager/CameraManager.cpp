/* ヘッダファイル */
#include "CameraManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief カメラ
//! @brief カメラ関連の名前空間
//!
//-------------------------------------------------------------
namespace Camera
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_CameraManager::C_CameraManager() :

        // 実装情報
        upImpl_(std::make_unique<C_CameraManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_CameraManager::~C_CameraManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  カメラの更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_CameraManager::Update()
    {
        upImpl_->Update();
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
    void C_CameraManager::Entry(const CameraPtr& prCamera,
                                const std::string& rId,
                                bool updateFlag)
    {
        upImpl_->Entry(prCamera, rId, updateFlag);
    }


    /*************************************************************//**
     *
     *  @brief  カメラの除去処理を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_CameraManager::Remove(const std::string& rId)
    {
        upImpl_->Remove(rId);
    }


    /*************************************************************//**
     *
     *  @brief  全てのカメラの除去処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_CameraManager::AllRemove()
    {
        upImpl_->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  カメラを取得する
     *  @param  ID
     *  @return 取得できた場合      ：カメラ
     *  @return 取得できなかった場合：none
     *
     ****************************************************************/
    boost::optional<const CameraPtr&> C_CameraManager::GetCamera(const std::string& rId) const
    {
        return upImpl_->GetCamera(rId);
    }
}