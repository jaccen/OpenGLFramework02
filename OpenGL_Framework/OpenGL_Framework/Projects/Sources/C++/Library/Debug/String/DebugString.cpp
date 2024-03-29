/* ヘッダファイル */
#include "DebugStringImpl.h"


//-------------------------------------------------------------
//!
//! @brief デバッグ
//! @brief デバッグ関連の名前空間
//!
//-------------------------------------------------------------
namespace Debug
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_DebugString::C_DebugString() :

        // 実装情報
        upImpl_(std::make_unique<C_DebugStringImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_DebugString::~C_DebugString()
    {
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  フォントのファイルパス
     *  @param  フォントのサイズ
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_DebugString::Initialize(const std::string& rFontFilePath,
                                   int32_t fontSize)
    {
        if (upImpl_->Initialize(rFontFilePath, fontSize) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  デバックフォントの描画処理を行う
     *  @param  文字列
     *  @param  座標
     *  @param  スケール
     *  @param  赤
     *  @param  緑
     *  @param  青
     *  @param  文字揃え
     *  @return なし
     *
     ****************************************************************/
    void C_DebugString::Draw(const std::string& rString,
                             const Vector3& rPosition,
                             float scale,
                             uint8_t red,
                             uint8_t green,
                             uint8_t blue,
                             ecTypographicAlignment alignment)
    {
        upImpl_->Draw(rString, rPosition, scale, red, green, blue, alignment);
    }


    /*************************************************************//**
     *
     *  @brief  デバックフォントの終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_DebugString::Finalize()
    {
        upImpl_->Finalize();
    }
}