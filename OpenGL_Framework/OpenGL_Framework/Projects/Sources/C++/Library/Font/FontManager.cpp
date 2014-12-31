/* ヘッダファイル */
#include "FontManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief フォント
//! @brief フォント関連の名前空間
//!
//-------------------------------------------------------------
namespace Font
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_FontManager::C_FontManager() :

        // 実装情報
        upImpl_(std::make_unique<C_FontManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_FontManager::~C_FontManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  フォントの初期化処理を行う
     *  @param  なし
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_FontManager::Initialize()
    {
        const int32_t FONT_INITIALIZE_ERROR_VALUE = -1;

        if (::TTF_Init() == FONT_INITIALIZE_ERROR_VALUE)
        {
            PrintLog("[ C_FontManager::Initialize ] : フォントの初期化処理に失敗しました。\n");
            PrintLog("                   エラー内容 : %s\n", TTF_GetError());

            return false;
        }

        // 終了処理のフラグを下げる
        upImpl_->SetFinalizeFlag(false);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  フォントの終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_FontManager::Finalize()
    {
        upImpl_->Finalize();
        upImpl_->SetFinalizeFlag(true);
    }


    /*************************************************************//**
     *
     *  @brief  フォントのロードを行う
     *  @param  ファイルパス
     *  @param  サイズ
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_FontManager::Load(const std::string& rFilePath, int32_t size)
    {
        if (upImpl_->Load(rFilePath, size) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  フォントの解放を行う
     *  @param  ファイルパス
     *  @param  サイズ
     *  @return なし
     *
     ****************************************************************/
    void C_FontManager::Release(const std::string& rFilePath, int32_t size)
    {
        upImpl_->Release(rFilePath, size);
    }


    /*************************************************************//**
     *
     *  @brief  フォントを全て解放する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_FontManager::AllRelease()
    {
        upImpl_->AllRelease();
    }


    /*************************************************************//**
     *
     *  @brief  フォントを取得する
     *  @param  ファイルパス
     *  @param  サイズ
     *  @return フォント
     *
     ****************************************************************/
    boost::optional<const FontPtr&> C_FontManager::GetFont(const std::string& rFilePath, int32_t size) const
    {
        return upImpl_->GetFont(rFilePath, size);
    }
}