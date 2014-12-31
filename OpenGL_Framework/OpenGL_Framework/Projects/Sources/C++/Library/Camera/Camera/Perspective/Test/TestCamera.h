/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../PerspectiveCamera.h"


//-------------------------------------------------------------
//!
//! @brief カメラ
//! @brief カメラ関連の名前空間
//!
//-------------------------------------------------------------
namespace Camera
{
    //-------------------------------------------------------------
    //!
    //! @brief テストカメラ
    //! @brief テスト用のカメラとなるクラス
    //!
    //-------------------------------------------------------------
    class C_TestCamera : public C_PerspectiveCamera
    {
    public:
        C_TestCamera();                                                     // コンストラクタ
        ~C_TestCamera() override;                                           // デストラクタ
        void Update() override;                                             // 更新処理
        void SetEyePoint(const Vector3& rEyePoint) override;                // 視点を設定
        void SetTargetPoint(const Vector3& rTargetPoint) override;          // 注視点を設定
        void SetKeyboradFlag(bool keyboardFlag);                            // キー入力フラグを設定
        void SetMouseFlag(bool mouseFlag);                                  // マウス入力フラグを設定
        void SetMoveScale(float moveScale);                                 // 移動の大きさを設定
    private:
        int32_t previousMousePositionX_ = 0;                                ///< @brief 1フレーム前ののマウスのX座標
        int32_t previousMousePositionY_ = 0;                                ///< @brief 1フレーム前のマウスのY座標
        float mouseRightDragAngleX_ = 0.0f;                                 ///< @brief 右クリックのドラッグ時のX方向の角度
        float mouseRightDragAngleY_ = 0.0f;                                 ///< @brief 右クリックのドラッグ時のY方向の角度
        float moveScale_ = 1.0f;                                            ///< @brief 移動の大きさ
        bool keyboardFlag_ = true;                                          ///< @brief キー入力を判断するフラグ
        bool mouseFlag_ = true;                                             ///< @brief マウス入力を判断するフラグ
        bool pointChangeFlag_ = false;                                      ///< @brief 視点か注視点を変更したか判断するフラグ
        Vector3 direction_;                                                 ///< @brief カメラの向き
        Vector3 distance_;                                                  ///< @brief 距離

        void InputKeyboardUpdate();                                         // キー入力による更新処理
        void InputMouseUpdate();                                            // マウス入力による更新処理
    };
}