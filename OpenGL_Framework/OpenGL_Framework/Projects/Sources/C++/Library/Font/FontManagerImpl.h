/* ヘッダファイル */
#include "FontManager.h"
#include "../Debug/Helper/DebugHelper.h"
#include "../Common/CommonHelper.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief フォント
//! @brief フォント関連の名前空間
//!
//-------------------------------------------------------------
namespace Font
{
    //-------------------------------------------------------------
    //!
    //! @brief フォントマネージャーインプリメント
    //! @brief フォントマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_FontManager::C_FontManagerImpl
    {
    public:
        C_FontManagerImpl();                                                                        // コンストラクタ
        ~C_FontManagerImpl();                                                                       // デストラクタ
        void Finalize();                                                                            // 終了処理
        bool Load(const std::string& rFilePath, int32_t size);                                      // ロード処理
        void Release(const std::string& rFilePath, int32_t size);                                   // 解放処理
        void AllRelease();                                                                          // 全て解放
        boost::optional<const FontPtr&> GetFont(const std::string& rFilePath, int32_t size);        // フォントを取得
        void SetFinalizeFlag(bool finalizeFlag);                                                    // 終了処理を行ったか判断するフラグを設定
    private:
        std::unordered_map<std::string, FontPtr> pFonts_;                                           ///< @brief フォント
        bool finalizeFlag_ = false;                                                                 ///< @brief 終了処理を行ったか判断するフラグ
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_FontManager::C_FontManagerImpl::C_FontManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_FontManager::C_FontManagerImpl::~C_FontManagerImpl()
    {
        if (finalizeFlag_ == false) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  フォントの終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_FontManager::C_FontManagerImpl::Finalize()
    {
        // フォントを全て解放
        AllRelease();

        // フォントの終了処理
        ::TTF_Quit();
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
    bool C_FontManager::C_FontManagerImpl::Load(const std::string& rFilePath, int32_t size)
    {
        // ID
        const std::string ID = rFilePath + std::to_string(size);

        // 既にロードしている場合
        if (pFonts_.find(ID) != pFonts_.end())
        {
            std::cout << "[ C_FontManagerImpl::Load ] : 既に同じフォントをロードしています。" << std::endl;
            std::cout << "               ファイルパス : " << rFilePath << std::endl;

            return true;
        }

        // フォントをロード
        FontPtr pTempFont(::TTF_OpenFont(Common::C_CommonHelper::s_ConvertShiftJisToUtf8(rFilePath).c_str(), size),
                          [](Font* pFont){ ::TTF_CloseFont(pFont); });

        if (!pTempFont)
        {
            PrintLog("[ C_FontManagerImpl::TextureCreate ] : フォントのロードに失敗しました。\n");
            PrintLog("                        ファイルパス : %s\n", rFilePath.c_str());
            PrintLog("                          エラー内容 : %s\n", TTF_GetError());

            return false;
        }

        // ロードしたフォントを保持する
        pFonts_.emplace(ID, pTempFont);

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
    void C_FontManager::C_FontManagerImpl::Release(const std::string& rFilePath, int32_t size)
    {
        // ID
        const std::string ID = rFilePath + std::to_string(size);

        // フォントがロードされていない場合
        if (pFonts_.find(ID) == pFonts_.end())
        {
            std::cout << "[ C_FontManager::Release ] : フォントがロードされていません。" << std::endl;

            return;
        }

        // 要素を削除
        pFonts_.erase(ID);
    }


    /*************************************************************//**
     *
     *  @brief  フォントを全て解放する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_FontManager::C_FontManagerImpl::AllRelease()
    {
        pFonts_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  フォントを取得する
     *  @param  ファイルパス
     *  @param  サイズ
     *  @return フォント
     *
     ****************************************************************/
    boost::optional<const FontPtr&> C_FontManager::C_FontManagerImpl::GetFont(const std::string& rFilePath, int32_t size)
    {
        const std::string ID = rFilePath + std::to_string(size);

        auto iterator = pFonts_.find(ID);
        if (iterator == pFonts_.end()) return boost::none;

        return (*iterator).second;
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行ったか判断するフラグを設定
     *  @param  終了処理を行ったか判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_FontManager::C_FontManagerImpl::SetFinalizeFlag(bool finalizeFlag)
    {
        finalizeFlag_ = finalizeFlag;
    }
}