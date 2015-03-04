/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectWarsDefine.h"
#include "../../Library/GameObject/GameObject.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"
#include "../../Library/Camera/Camera/Camera.h"
#include "../../Library/Shader/GLSL/Uniform/Manager/UniformBufferManager.h"
#include "../../Library/KeyFrame/KeyAnimation.h"
#include "../../Library/JSON/Object/JsonObject.h"
#include "../../Library/Camera/Camera/Perspective/PerspectiveCamera.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /** カメラデータの種類 */
    enum class ecCameraDataType
    {
        BACKGROUND_EYE_POINT,
        BACKGROUND_TARGET_POINT,
        BACKGROUND_UP_VECTOR,
    };


    //-------------------------------------------------------------
    //!
    //! @brief カメラコントローラー
    //! @brief カメラを制御するためのクラス
    //!
    //-------------------------------------------------------------
    class C_CameraController : public GameObject::C_GameObject
    {
    public:
        C_CameraController(const std::string& rId, int32_t type);               // コンストラクタ
        virtual ~C_CameraController() override;                                 // デストラクタ
        bool Update() override;                                                 // 更新処理
        void Draw() override;                                                   // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override;                // メッセージ処理
        void SetCameraData(const JSON::JsonObjectPtr& prCameraData);            // カメラデータを設定
        void SetNowFrame(int32_t frame);                                        // 現在のフレーム数を設定
        void SetIndex(int32_t index, ecCameraDataType cameraDataType);          // インデックスの設定
    protected:
        Camera::CameraPtr pMainCamera_;                                         ///< @brief メインカメラ
        std::shared_ptr<Camera::C_PerspectiveCamera> pBackgroundCamera_;        ///< @brief 背景カメラ
        S_CameraData mainCameraData_;                                           ///< @brief メインカメラデータ
        S_CameraData backgroundCameraData_;                                     ///< @brief 背景カメラデータ
        Shader::GLSL::UniformBufferPtr pMainCameraBuffer_;                      ///< @brief メインカメラバッファ
        Shader::GLSL::UniformBufferPtr pBackgroundCameraBuffer_;                ///< @brief 背景カメラバッファ
        KeyFrame::C_KeyAnimation<Vector3> backgroundCameraWorkers_[3];          ///< @brief 背景カメラワーカー
    };
}
