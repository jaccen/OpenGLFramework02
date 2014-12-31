/* ヘッダファイル */
#include "CommonHelper.h"
#include <fstream>


//-------------------------------------------------------------
//!
//! @brief コモン
//! @brief 共通関連の名前空間
//!
//-------------------------------------------------------------
namespace Common
{
    /*************************************************************//**
     *
     *  @brief  メッセージボックスを表示
     *  @param  タイトル名
     *  @param  テキスト
     *  @param  ウィンドウハンドル
     *  @return はいを押した場合：true
     *  @return いいえを押した場合：false
     *
     ****************************************************************/
    bool C_CommonHelper::s_ShowMessageBox(const std::string& rTitleName,
                                          const std::string& rText)
    {

/* Windows時 */
#ifdef _WIN32

        if (MessageBoxA(nullptr, rText.c_str(), rTitleName.c_str(), MB_YESNO | MB_ICONQUESTION) == IDNO)
        {
            return false;
        }

#endif

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  Shift-JISの文字列からUTF-8文字列への変換を行う
     *  @param  Shift-JIS文字列
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    std::string C_CommonHelper::s_ConvertShiftJisToUtf8(const std::string& rShiftJisString)
    {
        assert(rShiftJisString.empty() == false);

/* Windows時 */
#ifdef _WIN32

        // Shift-JISからUnicodeへの変換に必要なバッファ数を確保
        int32_t unicodeStringBuffer = ::MultiByteToWideChar(CP_ACP, 0, rShiftJisString.c_str(), -1, nullptr, 0);

        if (unicodeStringBuffer == 0) return "";

        // Unicode文字列
        std::wstring unicodeString;

        // Unicode変換に必要なバッファ分だけ許容量を確保
        unicodeString.resize(unicodeStringBuffer);

        // Shift-JISからUnicodeへの変換
        if (::MultiByteToWideChar(CP_ACP, 0, rShiftJisString.c_str(), -1, &unicodeString[0], unicodeStringBuffer) == 0) return "";

        // UnicodeからUTF-8への変換に必要なバッファ数を確保
        const int32_t utf8Buffer = ::WideCharToMultiByte(CP_UTF8, 0, unicodeString.c_str(), -1, nullptr, 0, nullptr, nullptr);

        if (utf8Buffer == 0) return "";

        // UTF-8文字列
        std::string utf8String;

        // UTF-8変換に必要なバッファ分だけ許容量を確保
        utf8String.resize(utf8Buffer);

        // UnicodeからUTF-8への変換
        if (::WideCharToMultiByte(CP_UTF8, 0, unicodeString.c_str(), -1, &utf8String[0], utf8Buffer, nullptr, nullptr) == 0) return "";

#endif

        return utf8String;
    }


    /*************************************************************//**
     *
     *  @brief  文字列の前後にある指定した文字を取り除く
     *  @param  文字列
     *  @param  削除対象の文字
     *  @return なし
     *
     ****************************************************************/
    std::string C_CommonHelper::s_TrimString(const std::string& rString,
                                             const char* pTrimCharacterList)
    {
        std::string trimString = rString;

        // 削除対象の文字に含まれない文字が最初に見つかる位置を検索
        size_t location = trimString.find_first_not_of(pTrimCharacterList);

        // 最初から特殊文字のない位置まで削除
        trimString.erase(0, location);

        // 削除対象の文字に含まれない文字が最後に見つかる位置を検索
        location = trimString.find_last_not_of(pTrimCharacterList);

        // 特殊文字のない位置から1つ先の位置を削除
        trimString.erase(location + 1);

        return trimString;
    }


    /*************************************************************//**
     *
     *  @brief  ファイルのサイズを取得する
     *  @param  入力ファイル
     *  @return ファイルのサイズ
     *
     ****************************************************************/
    uint32_t C_CommonHelper::s_GetFileSize(std::ifstream* pInFile)
    {
        pInFile->seekg(0, std::ifstream::end);
        std::streamoff endPosition = pInFile->tellg();

        pInFile->clear();
        pInFile->seekg(0, std::ifstream::beg);
        std::streamoff beginPosition = pInFile->tellg();

        return static_cast<uint32_t>(endPosition - beginPosition);
    }
}