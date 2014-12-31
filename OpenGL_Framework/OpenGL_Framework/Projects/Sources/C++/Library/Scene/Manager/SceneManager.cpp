/* ヘッダファイル */
#include "SceneManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief シーン
//! @brief シーン関連の名前空間
//!
//-------------------------------------------------------------
namespace Scene
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  最初のシーン
     *
     ****************************************************************/
    C_SceneManager::C_SceneManager(C_BaseScene* pFirstScene) :

        // 実装情報
        upImpl_(std::make_unique<C_SceneManagerImpl>(pFirstScene, this))

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SceneManager::~C_SceneManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  シーンマネージャーの初期化処理を行う
     *  @param  なし
     *  @return 正常終了：SUCCESSFUL
     *  @return 異常終了：ERROR_TERMINATION
     *
     ****************************************************************/
    ecSceneReturn C_SceneManager::Initialize()
    {
        if (upImpl_->Initialize() == ecSceneReturn::ERROR_TERMINATION) return ecSceneReturn::ERROR_TERMINATION;

        return ecSceneReturn::SUCCESSFUL;
    }


    /*************************************************************//**
     *
     *  @brief  シーンマネージャーの更新処理を行う
     *  @param  なし
     *  @return 正常終了：CONTINUATIOIN
     *  @return 正常終了：SUCCESSFUL
     *  @return 異常終了：ERROR_TERTINATION
     *
     ****************************************************************/
    ecSceneReturn C_SceneManager::Update()
    {
        ecSceneReturn returnValue = upImpl_->Update();

        if (returnValue != ecSceneReturn::CONTINUATIOIN)
        {
            if (returnValue == ecSceneReturn::ERROR_TERMINATION)
            {
                return ecSceneReturn::ERROR_TERMINATION;
            }
            else
            {
                return ecSceneReturn::SUCCESSFUL;
            }
        }

        return ecSceneReturn::CONTINUATIOIN;
    }


    /*************************************************************//**
     *
     *  @brief  シーンマネージャーの描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SceneManager::Draw()
    {
        upImpl_->Draw();
    }


    /*************************************************************//**
     *
     *  @brief  シーンマネージャーの終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SceneManager::Finalize()
    {
        upImpl_->Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  次のシーンをプッシュする
     *  @param  次のシーン
     *  @param  以前のシーンに設定する更新フラグ
     *  @param  以前のシーンに設定する描画フラグ
     *  @return なし
     *
     ****************************************************************/
    void C_SceneManager::PushScene(C_BaseScene* pNextScene,
                                   bool previousUpdateFlag,
                                   bool presiousDrawFlag)
    {
        upImpl_->PushScene(pNextScene, previousUpdateFlag, presiousDrawFlag);
    }


    /*************************************************************//**
     *
     *  @brief  次のシーンをポップする
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SceneManager::PopScene()
    {
        upImpl_->PopScene();
    }


    /*************************************************************//**
     *
     *  @brief  現在のシーンとの入れ替えをする
     *  @param  次のシーン
     *  @return なし
     *
     ****************************************************************/
    void C_SceneManager::ReplaceScene(C_BaseScene* pNextScene)
    {
        upImpl_->ReplaceScene(pNextScene);
    }
}