/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Singleton/Singleton.h"



//-------------------------------------------------------------
//!
//! @brief カメラ
//! @brief カメラ関連の名前空間
//!
//-------------------------------------------------------------
namespace Camera
{
    /* 前方宣言 */
    class IC_Camera;


    /* 別名 */
    using CameraPtr = std::shared_ptr<IC_Camera>;                                           // CameraPtr型


    //-------------------------------------------------------------
    //!
    //! @brief カメラマネージャー
    //! @brief カメラを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_CameraManager : public Singleton::C_Singleton<C_CameraManager>
    {
        friend C_Singleton<C_CameraManager>;                                                // シングルトンクラスをフレンド化
    public:
        C_CameraManager();                                                                  // コンストラクタ
        ~C_CameraManager() override;                                                        // デストラクタ
        void Update();                                                                      // 更新処理
        void Entry(const CameraPtr& prCamera,                                               // 登録処理
                   const std::string& rId,
                   bool updateFlag = true);
        void Remove(const std::string& rId);                                                // 除去処理
        void AllRemove();                                                                   // 全てのカメラを除去
        boost::optional<const CameraPtr&> GetCamera(const std::string& rId) const;          // カメラを取得
    private:
        /* 前方宣言 */
        class C_CameraManagerImpl;

        std::unique_ptr<C_CameraManagerImpl> upImpl_;                                       ///< @brief 実装情報
    };
}
