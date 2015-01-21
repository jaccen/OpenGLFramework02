/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "Manager/SceneManager.h"


//-------------------------------------------------------------
//!
//! @brief シーン
//! @brief シーン関連の名前空間
//!
//-------------------------------------------------------------
namespace Scene
{
    //-------------------------------------------------------------
    //!
    //! @brief ベースシーン
    //! @brief シーンの基底クラス
    //!
    //-------------------------------------------------------------
    class C_BaseScene
    {
    public:
        C_BaseScene();                                                      // コンストラクタ
        virtual ~C_BaseScene();                                             // デストラクタ
        virtual ecSceneReturn Initialize();                                 // 初期化処理
        virtual ecSceneReturn Update() = 0;                                 // 更新処理
        virtual void Draw() = 0;                                            // 描画処理
        virtual void Finalize();                                            // 終了処理
        bool IsUpdateFlag() const;                                          // 更新フラグを取得
        bool IsDrawFlag() const;                                            // 描画フラグを取得
        void SetUpdateFlag(bool updateFlag);                                // 更新フラグを設定
        void SetDrawFlag(bool drawFlag);                                    // 描画フラグを設定
        void SetSceneChanger(IC_SceneChanger* pSceneChanger);               // シーンチェンジャーを設定
        void SetParentScene(C_BaseScene* pParentScene);                     // 親のシーンを設定
    protected:
        IC_SceneChanger* GetSceneChanger() const;                           // シーンチェンジャーを取得

        template<typename T>
        T* GetParentScene() const;                                          // 親のシーンを取得
    private:
        bool updateFlag_ = true;                                            ///< @brief 更新フラグ
        bool drawFlag_ = true;                                              ///< @brief 描画フラグ
        IC_SceneChanger* pSceneChanger_ = nullptr;                          ///< @brief シーンチェンジャー
        C_BaseScene* pParentScene_ = nullptr;                               ///< @brief 親のシーン
    };


#pragma region メンバ関数


    /*************************************************************//**
     *
     *  @brief  親のシーンを取得する
     *  @param  なし
     *  @return 親のシーン
     *
     ****************************************************************/
    template<typename T>
    T* C_BaseScene::GetParentScene() const
    {
        return static_cast<T*>(pParentScene_);
    }


#pragma endregion

}