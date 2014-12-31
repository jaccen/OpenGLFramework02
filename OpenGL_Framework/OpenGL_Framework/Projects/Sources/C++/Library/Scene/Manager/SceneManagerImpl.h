/* ヘッダファイル */
#include "SceneManager.h"
#include "../BaseScene.h"
#include "../../Debug/Helper/DebugHelper.h"
#include <deque>


//-------------------------------------------------------------
//!
//! @brief シーン
//! @brief シーン関連の名前空間
//!
//-------------------------------------------------------------
namespace Scene
{
    /** シーン変更のコマンド */
    enum class ecSceneChangeCommand
    {
        PUSH,                                                                       ///< @brief プッシュ
        POP,                                                                        ///< @brief ポップ
        REPLACE,                                                                    ///< @brief リプレイス
    };


    //-------------------------------------------------------------
    //!
    //! @brief ネクストシーンデータ
    //! @brief 次のシーンに切り替えるデータを表す構造体
    //!
    //-------------------------------------------------------------
    struct S_NextSceneData
    {
        bool previousUpdateFlag_ = false;                                           ///< @brief 前のシーンに設定する更新フラグ
        bool previousDrawFlag_ = false;                                             ///< @brief 前のシーンに設定する描画フラグ
        C_BaseScene* pNextScene_;                                                   ///< @brief 次のシーン

        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  次のシーン
         *  @param  前のシーンに設定する更新フラグ
         *  @param  前のシーンに設定する描画フラグ
         *
         ****************************************************************/
        S_NextSceneData(C_BaseScene* pNextScene,
                        bool previousUpdateFlag = true,
                        bool previousDrawFlag = true) :

            // 前のシーンに設定する各フラグ
            previousUpdateFlag_(previousUpdateFlag),
            previousDrawFlag_(previousDrawFlag),

            // 次のシーン
            pNextScene_(pNextScene)

        {
        }
    };


    //-------------------------------------------------------------
    //!
    //! @brief シーンマネージャーインプリメント
    //! @brief シーンマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_SceneManager::C_SceneManagerImpl
    {
    public:
        C_SceneManagerImpl(C_BaseScene* pFirstScene,                                // コンストラクタ
                           IC_SceneChanger* pSceneChanger);
        ~C_SceneManagerImpl();                                                      // デストラクタ
        ecSceneReturn Initialize();                                                 // 初期化処理
        ecSceneReturn Update();                                                     // 更新処理
        void Draw();                                                                // 描画処理
        void Finalize();                                                            // 終了処理
        void PushScene(C_BaseScene* pNextScene,                                     // 次のシーンをプッシュ
                       bool previousUpdateFlag,
                       bool presiousDrawFlag);
        void PopScene();                                                            // 現在のシーンをポップ
        void ReplaceScene(C_BaseScene* pNextScene);                                 // 現在のシーンと入れ替える
    private:
        IC_SceneChanger* pSceneChanger_ = nullptr;                                  ///< @brief シーンチェンジャー
        std::deque<std::unique_ptr<C_BaseScene>> upScenes_;                         ///< @brief シーン
        std::deque<S_NextSceneData> nextSceneDatas_;                                ///< @brief 次のシーンに切り替えるための情報
        std::deque<ecSceneChangeCommand> sceneExchangeCommands_;                    ///< @brief シーン変更のコマンド

        ecSceneReturn SceneChange();                                                // シーンの変更処理
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  最初のシーン
     *  @param  シーンチェンジャー
     *
     ****************************************************************/
    C_SceneManager::C_SceneManagerImpl::C_SceneManagerImpl(C_BaseScene* pFirstScene,
                                                           IC_SceneChanger* pSceneChanger) :

        // シーンチェンジャー
        pSceneChanger_(pSceneChanger)

    {
        // 最初のシーンを設定
        upScenes_.emplace_back(pFirstScene);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SceneManager::C_SceneManagerImpl::~C_SceneManagerImpl()
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
    ecSceneReturn C_SceneManager::C_SceneManagerImpl::Initialize()
    {
        assert(upScenes_.size() > 0);
        assert(upScenes_[0]);

        // 最初のシーンにシーンチェンジャーを設定
        upScenes_[0]->SetSceneChanger(pSceneChanger_);

        // 最初のシーンの初期化処理
        if (upScenes_[0]->Initialize() == ecSceneReturn::ERROR_TERMINATION)
        {
            PrintLog("[ C_SceneManagerImpl::Initialize ] : 最初のシーンの初期化処理に失敗しました。\n");

            return ecSceneReturn::ERROR_TERMINATION;
        }

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
    ecSceneReturn C_SceneManager::C_SceneManagerImpl::Update()
    {
        assert(upScenes_.size() > 0);
        assert(upScenes_[0]);

        // 各処理の戻り値
        ecSceneReturn returnValue = ecSceneReturn::CONTINUATIOIN;

        // シーンの変更処理
        returnValue = SceneChange();

        if (returnValue == ecSceneReturn::ERROR_TERMINATION)
        {
            PrintLog("[ C_SceneManagerImpl::Update ] : シーンの変更処理に失敗しました。\n");

            return ecSceneReturn::ERROR_TERMINATION;
        }

        for (auto& scene : upScenes_)
        {
            // 更新フラグが立っていた場合は更新
            if (scene->IsUpdateFlag() == true)
            {
                // シーンの更新処理
                returnValue = scene->Update();

                if (returnValue != ecSceneReturn::CONTINUATIOIN)
                {
                    if (returnValue == ecSceneReturn::ERROR_TERMINATION)
                    {
                        PrintLog("[ C_SceneManagerImpl::Update ] : シーンの更新処理に失敗しました。\n");

                        return ecSceneReturn::ERROR_TERMINATION;
                    }
                    else
                    {
                        return ecSceneReturn::SUCCESSFUL;
                    }
                }
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
    void C_SceneManager::C_SceneManagerImpl::Draw()
    {
        for (auto& scene : upScenes_)
        {
            // 描画フラグが立っていた場合は描画
            if (scene->IsDrawFlag() == true) scene->Draw();
        }
    }


    /*************************************************************//**
     *
     *  @brief  シーンマネージャーの終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SceneManager::C_SceneManagerImpl::Finalize()
    {
        for (auto& scene : upScenes_) scene->Finalize();
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
    void C_SceneManager::C_SceneManagerImpl::PushScene(C_BaseScene* pNextScene,
                                                       bool previousUpdateFlag,
                                                       bool presiousDrawFlag)
    {
        // 次のシーンへ切り替えるための情報を設定
        nextSceneDatas_.emplace_back(pNextScene,
                                     previousUpdateFlag,
                                     presiousDrawFlag);

        // シーン変更のコマンドにプッシュを追加
        sceneExchangeCommands_.emplace_back(ecSceneChangeCommand::PUSH);
    }


    /*************************************************************//**
     *
     *  @brief  次のシーンをポップする
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SceneManager::C_SceneManagerImpl::PopScene()
    {
        // シーン変更のコマンドにポップを追加
        sceneExchangeCommands_.emplace_back(ecSceneChangeCommand::POP);
    }


    /*************************************************************//**
     *
     *  @brief  現在のシーンとの入れ替えをする
     *  @param  次のシーン
     *  @return なし
     *
     ****************************************************************/
    void C_SceneManager::C_SceneManagerImpl::ReplaceScene(C_BaseScene* pNextScene)
    {
        // 次のシーンへ切り替えるための情報を設定
        nextSceneDatas_.emplace_back(pNextScene);

        // シーン変更のコマンドにポップを追加
        sceneExchangeCommands_.emplace_back(ecSceneChangeCommand::REPLACE);
    }


    /*************************************************************//**
     *
     *  @brief  シーンの変更を行う
     *  @param  なし
     *  @return 正常終了：SUCCESSFUL
     *  @return 異常終了：ERROR_TERTINATION
     *
     ****************************************************************/
    ecSceneReturn C_SceneManager::C_SceneManagerImpl::SceneChange()
    {
        // 次のシーンに切り替えるための情報のインデックス
        uint32_t nextSceneDataIndex = 0;

        // シーンの数から1引いた値
        int32_t nowSceneIndex = upScenes_.size() - 1;

        for (auto sceneExchangeCommand : sceneExchangeCommands_)
        {
            assert(nowSceneIndex >= 0);

            /* リプレイス */
            if (sceneExchangeCommand == ecSceneChangeCommand::REPLACE)
            {
                assert(nextSceneDataIndex < nextSceneDatas_.size());

                // 現在のシーンの終了処理を行い、そのシーンを削除
                upScenes_[nowSceneIndex]->Finalize();
                upScenes_.pop_back();

                // 次のシーンを取得
                std::unique_ptr<C_BaseScene> upNextScene(nextSceneDatas_[nextSceneDataIndex].pNextScene_);

                // 次のシーンにシーンチェンジャーを設定し、初期化
                upNextScene->SetSceneChanger(pSceneChanger_);

                if (upNextScene->Initialize() == ecSceneReturn::ERROR_TERMINATION)
                {
                    PrintLog("[ C_SceneManager::SceneChange ] : リプレイス時の次のシーンの初期化処理に失敗しました。\n");

                    return ecSceneReturn::ERROR_TERMINATION;
                }

                // 次のシーンを追加
                upScenes_.emplace_back(std::move(upNextScene));

                // 次のシーンに切り替えるための情報のインデックスを1増加
                ++nextSceneDataIndex;
            }
            /* プッシュ */
            else if (sceneExchangeCommand == ecSceneChangeCommand::PUSH)
            {
                assert(nextSceneDataIndex < nextSceneDatas_.size());

                // 現在のシーンに更新フラグと描画フラグを設定
                upScenes_[nowSceneIndex]->SetUpdateFlag(nextSceneDatas_[nextSceneDataIndex].previousUpdateFlag_);
                upScenes_[nowSceneIndex]->SetDrawFlag(nextSceneDatas_[nextSceneDataIndex].previousDrawFlag_);

                // 次のシーンを取得
                std::unique_ptr<C_BaseScene> upNextScene(nextSceneDatas_[nextSceneDataIndex].pNextScene_);

                // 次のシーンにシーンチェンジャーと親のシーンを設定し、初期化
                upNextScene->SetSceneChanger(pSceneChanger_);
                upNextScene->SetParentScene(upScenes_[nowSceneIndex].get());

                if (upNextScene->Initialize() == ecSceneReturn::ERROR_TERMINATION)
                {
                    PrintLog("[ C_SceneManager::SceneChange ] : プッシュ時の次のシーンの初期化処理に失敗しました。\n");

                    return ecSceneReturn::ERROR_TERMINATION;
                }

                // 次のシーンを追加
                upScenes_.emplace_back(std::move(upNextScene));

                // 次のシーンに切り替えるための情報のインデックスを1増加
                ++nextSceneDataIndex;

                // シーンの数から1引いた値を1増加
                ++nowSceneIndex;
            }
            /* ポップ */
            else
            {
                // シーンが2つ以上なければ処理しない
                if (nowSceneIndex > 0)
                {
                    // 現在のシーンの終了処理
                    upScenes_[nowSceneIndex]->Finalize();

                    // シーンの数から1引いた値を1減らす
                    --nowSceneIndex;

                    // 現在のシーンの1つ前のシーンの更新フラグと描画フラグを立てる
                    upScenes_[nowSceneIndex]->SetUpdateFlag(true);
                    upScenes_[nowSceneIndex]->SetDrawFlag(true);

                    // 現在のシーンを削除
                    upScenes_.pop_back();
                }
            }
        }

        // シーン切り替えのコマンドが存在している場合はすべて削除
        if (sceneExchangeCommands_.empty() == false) sceneExchangeCommands_.clear();

        // 次のシーンへ切り替えるための情報が存在している場合はすべて削除
        if (nextSceneDatas_.empty() == false) nextSceneDatas_.clear();

        return ecSceneReturn::SUCCESSFUL;
    }
}