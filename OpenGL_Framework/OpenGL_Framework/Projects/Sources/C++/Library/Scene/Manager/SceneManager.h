/* 二重インクルード防止 */
#pragma once


//-------------------------------------------------------------
//!
//! @brief シーン
//! @brief シーン関連の名前空間
//!
//-------------------------------------------------------------
namespace Scene
{
    /* 前方宣言 */
    class C_BaseScene;


    /** シーンの戻り値 */
    enum class ecSceneReturn
    {
        CONTINUATIOIN,                                                      ///< @brief 続行
        SUCCESSFUL,                                                         ///< @brief 正常終了
        ERROR_TERMINATION,                                                  ///< @brief エラー終了
    };


    //-------------------------------------------------------------
    //!
    //! @brief シーンチェンジャー( インターフェース )
    //! @brief シーンを変更するための関数を持つインターフェース
    //!
    //-------------------------------------------------------------
    class IC_SceneChanger
    {
    public:
        IC_SceneChanger(){};                                                //!< @brief コンストラクタ
        virtual ~IC_SceneChanger(){};                                       //!< @brief デストラクタ
        virtual void PushScene(C_BaseScene* pNextScene,                     //!< @brief シーンをプッシュ
                               bool previousUpdateFlag = false,
                               bool presiousDrawFlag = true) = 0;
        virtual void PopScene() = 0;                                        //!< @brief シーンをポップ
        virtual void ReplaceScene(C_BaseScene* pNextScene) = 0;             //!< @brief シーンを入れ替え
    };


    //-------------------------------------------------------------
    //!
    //! @brief シーンマネージャー
    //! @brief シーンを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_SceneManager : public IC_SceneChanger
    {
    public:
        explicit C_SceneManager(C_BaseScene* pFirstScene);                  // コンストラクタ
        ~C_SceneManager() override;                                         // デストラクタ
        ecSceneReturn Initialize();                                         // 初期化処理
        ecSceneReturn Update();                                             // 更新処理
        void Draw();                                                        // 描画処理
        void Finalize();                                                    // 終了処理
        void PushScene(C_BaseScene* pNextScene,                             // 次のシーンをプッシュ
                       bool previousUpdateFlag,
                       bool presiousDrawFlag) override;
        void PopScene() override;                                           // 現在のシーンをポップ
        void ReplaceScene(C_BaseScene* pNextScene) override;                // 現在のシーンと入れ替える
    private:
        /* 前方宣言 */
        class C_SceneManagerImpl;

        std::unique_ptr<C_SceneManagerImpl> upImpl_;                        // 実装情報
    };
}
