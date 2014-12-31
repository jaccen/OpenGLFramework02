/* ヘッダファイル */
#include "TestCamera.h"
#include "../../../../Input/Keyboard/KeyboardManager.h"
#include "../../../../Input/Mouse/MouseManager.h"
#include "../../../../Math/Vector/Vector4.h"
#include "../../../../Math/Quaternion/Quaternion.h"
#include "../../../../Math/Define/MathDefine.h"
#include <algorithm>


//-------------------------------------------------------------
//!
//! @brief カメラ
//! @brief カメラ関連の名前空間
//!
//-------------------------------------------------------------
namespace Camera
{
    /* 別名 */
    using Vector4 = Math::S_Vector4<float>;                 // Vector4型


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_TestCamera::C_TestCamera()
    {
        // 以前のマウスの座標を初期化
        previousMousePositionX_ = Input::C_MouseManager::s_GetInstance()->GetCursorPositionX();
        previousMousePositionY_ = Input::C_MouseManager::s_GetInstance()->GetCursorPositionY();
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_TestCamera::~C_TestCamera()
    {
    }


    /*************************************************************//**
     *
     *  @brief  テストカメラの更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TestCamera::Update()
    {
        // 視点か注視点が変更された場合、距離を再計算しフラグを下げる
        if (pointChangeFlag_ == true)
        {
            distance_ = eyePoint_ - targetPoint_;
            pointChangeFlag_ = false;
        }

        // カメラの向きを求める
        direction_ = targetPoint_ - eyePoint_;
        direction_.Normalize();
        direction_.Invert();

        // 各入力による更新処理
        if (keyboardFlag_ == true) InputKeyboardUpdate();
        if (mouseFlag_ == true) InputMouseUpdate();

        // カメラの更新処理
        C_PerspectiveCamera::Update();
    }


    /*************************************************************//**
     *
     *  @brief  視点を設定する
     *  @param  視点
     *  @return なし
     *
     ****************************************************************/
    void C_TestCamera::SetEyePoint(const Vector3& rEyePoint)
    {
        eyePoint_ = rEyePoint;

        // フラグが立っていない場合は立てる
        if (pointChangeFlag_ == false) pointChangeFlag_ = true;
    }


    /*************************************************************//**
     *
     *  @brief  注視点を設定する
     *  @param  注視点
     *  @return なし
     *
     ****************************************************************/
    void C_TestCamera::SetTargetPoint(const Vector3& rTargetPoint)
    {
        targetPoint_ = rTargetPoint;

        // フラグが立っていない場合は立てる
        if (pointChangeFlag_ == false) pointChangeFlag_ = true;
    }


    /*************************************************************//**
     *
     *  @brief  キー入力フラグを設定する
     *  @param  キー入力フラグ
     *  @return なし
     *
     ****************************************************************/
    void C_TestCamera::SetKeyboradFlag(bool keyboardFlag)
    {
        keyboardFlag_ = keyboardFlag;
    }


    /*************************************************************//**
     *
     *  @brief  マウス入力フラグを設定する
     *  @param  マウス入力フラグ
     *  @return なし
     *
     ****************************************************************/
    void C_TestCamera::SetMouseFlag(bool mouseFlag)
    {
        mouseFlag_ = mouseFlag;
    }


    /*************************************************************//**
     *
     *  @brief  移動の大きさを設定する
     *  @param  移動の大きさ
     *  @return なし
     *
     ****************************************************************/
    void C_TestCamera::SetMoveScale(float moveScale)
    {
        moveScale_ = moveScale;
    }


    /*************************************************************//**
     *
     *  @brief  キー入力による更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TestCamera::InputKeyboardUpdate()
    {
        // 上キーを入力した場合はカメラを前へ移動
        if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_UP) > 0)
        {
            eyePoint_ -= direction_ * moveScale_;
            targetPoint_ -= direction_ * moveScale_;
        }

        // 下キーを入力した場合はカメラを後ろへ移動
        if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_DOWN) > 0)
        {
            eyePoint_ += direction_ * moveScale_;
            targetPoint_ += direction_ * moveScale_;
        }

        // 左キーを入力した場合はカメラを左へ移動
        if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_LEFT) > 0)
        {
            // カメラの左向きを求める
            Vector3 leftDirection = Vector3::s_CrossProduct(direction_, upVector_);

            eyePoint_ += leftDirection * moveScale_;
            targetPoint_ += leftDirection * moveScale_;
        }

        // 右キーを入力した場合はカメラを右へ移動
        if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_RIGHT) > 0)
        {
            // カメラの右向きを求める
            Vector3 rightDirection = Vector3::s_CrossProduct(direction_, upVector_ * -1.0f);

            eyePoint_ += rightDirection * moveScale_;
            targetPoint_ += rightDirection * moveScale_;
        }
    }


    /*************************************************************//**
     *
     *  @brief  マウス入力による更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TestCamera::InputMouseUpdate()
    {
        // マウスのドラッグ時に利用する補正値
        const float RIGHT_DRAG_CORRECTION_VALUE = 0.01f;
        const float MIDDLE_DRAG_CORRECTION_VALUE_ = 0.02f;

        // マウスの座標を取得
        int mousePositionX = Input::C_MouseManager::s_GetInstance()->GetCursorPositionX();
        int mousePositionY = Input::C_MouseManager::s_GetInstance()->GetCursorPositionY();

        // マウスの移動量
        int mouseMovementX = mousePositionX - previousMousePositionX_;
        int mouseMovementY = mousePositionY - previousMousePositionY_;

        // マウスホイールをクリックしながらドラッグした場合はドラッグした方向に応じてカメラを移動
        if (Input::C_MouseManager::s_GetInstance()->GetButtonPressingCount(Input::BUTTON_MIDDLE) > 0)
        {
            // カメラの左向きを求める
            Vector3 leftDirection = Vector3::s_CrossProduct(direction_, upVector_);

            // カメラの下向きを求める
            Vector3 downDirection = Vector3::s_CrossProduct(direction_, leftDirection);

            // 移動量を求める
            Vector3 movement = (leftDirection * MIDDLE_DRAG_CORRECTION_VALUE_ * static_cast<float>(mouseMovementX))
                + (downDirection * MIDDLE_DRAG_CORRECTION_VALUE_ * static_cast<float>(-mouseMovementY));

            // 視点と注視点に移動量を追加
            eyePoint_ += movement * moveScale_;
            targetPoint_ += movement * moveScale_;
        }

        // 右クリックをしながらドラッグした場合はドラッグした方向に応じてカメラを回転
        if (Input::C_MouseManager::s_GetInstance()->GetButtonPressingCount(Input::BUTTON_RIGHT) > 0)
        {
            // マウスの移動量から回転角度を求める
            mouseRightDragAngleX_ -= mouseMovementX * RIGHT_DRAG_CORRECTION_VALUE;
            mouseRightDragAngleY_ += mouseMovementY * RIGHT_DRAG_CORRECTION_VALUE;

            // ジンバルロックにならないよう垂直回転に限界を設ける
            mouseRightDragAngleY_ = std::max(mouseRightDragAngleY_, static_cast<float>(Math::s_PI_DIVISION2 - RIGHT_DRAG_CORRECTION_VALUE) * -1.0f);
            mouseRightDragAngleY_ = std::min(mouseRightDragAngleY_, static_cast<float>(Math::s_PI_DIVISION2 - RIGHT_DRAG_CORRECTION_VALUE));

            // 回転行列を作成
            Matrix4 rotateMatrix = Matrix4::s_CreateRotationYawPitchRoll(mouseRightDragAngleY_,
                mouseRightDragAngleX_,
                0.0f);

            // 距離をVector4に変換
            Vector4 distanceV4(distance_, 0.0f);

            // 距離に回転行列をかけ、視点に追加
            distanceV4 = rotateMatrix * distanceV4;
            eyePoint_ = targetPoint_ + distanceV4.xyz_;
        }

        // マウスホイールを上にスクロールした場合はカメラを前へ移動
        if (Input::C_MouseManager::s_GetInstance()->GetWheelScrollingCount(Input::WHEEL_SCROLL_UP) > 0)
        {
            eyePoint_ -= direction_ * moveScale_;
            targetPoint_ -= direction_ * moveScale_;
        }

        // マウスホイールを下にスクロールした場合はカメラを後ろへ移動
        if (Input::C_MouseManager::s_GetInstance()->GetWheelScrollingCount(Input::WHEEL_SCROLL_DOWN) > 0)
        {
            eyePoint_ += direction_ * moveScale_;
            targetPoint_ += direction_ * moveScale_;
        }

        // 1フレーム前のマウスの座標を保持
        previousMousePositionX_ = mousePositionX;
        previousMousePositionY_ = mousePositionY;
    }
}