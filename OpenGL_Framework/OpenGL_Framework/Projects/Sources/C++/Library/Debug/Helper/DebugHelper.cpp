/* ヘッダファイル */
#include "DebugHelper.h"


//-------------------------------------------------------------
//!
//! @brief デバッグ
//! @brief デバッグ関連の名前空間
//!
//-------------------------------------------------------------
namespace Debug
{

/* Unicode時 */
#ifdef _UNICODE


    /*************************************************************//**
     *
     *  @brief  停止処理を行う
     *  @param  ファイル名
     *  @param  行
     *  @param  メッセージ
     *  @return なし
     *
     ****************************************************************/
    void C_DebugHelper::s_Halt(const std::wstring& rFilename,
                               int32_t line, 
                               const std::wstring& rMessage,
                               const std::wstring& rTitle)
    {
        // ファイル名、行、メッセージを合わせる
        const int32_t BUFFER_NUMBER = 512;

        TCHAR mergeMessage[BUFFER_NUMBER];
        wsprintf(mergeMessage, TEXT("[ Line : %d ]\nFileName : %s\n Message : %s"), line, rFilename.c_str(), rMessage.c_str());

        // メッセージを表示
        MessageBox(nullptr, mergeMessage, rTitle.c_str(), MB_ICONHAND | MB_OK);

        // 強制終了
        const int32_t STATUS_CODE = -1;

        std::exit(STATUS_CODE);
    }


#else


    /*************************************************************//**
     *
     *  @brief  停止処理を行う
     *  @param  ファイル名
     *  @param  行
     *  @param  メッセージ
     *  @return なし
     *
     ****************************************************************/
    void C_DebugHelper::s_Halt(const std::string& rFilename,
                               int32_t line,
                               const std::string& rMessage,
                               const std::string& rTitle)
    {
        // ファイル名、行、メッセージを合わせる
        const int32_t BUFFER_NUMBER = 512;

        char mergeMessage[BUFFER_NUMBER];
        ::sprintf_s(mergeMessage, "[ Line : %d ]\nFileName : %s\n Message : %s", line, rFilename.c_str(), rMessage.c_str());

        // メッセージを表示
        MessageBox(nullptr, mergeMessage, rTitle.c_str(), MB_ICONHAND | MB_OK);

        // 強制終了
        const int32_t STATUS_CODE = -1;

        std::exit(STATUS_CODE);
    }


#endif

}